/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ssd1306.h"
#include "HX711.h"
#include <stdio.h>
#include <string.h>
#include "fonts.h"
//#include "i2c.h"
//#include "bitmap.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

int motorAtBoundary = 0; //check if motor at boundary
int initialized =0;

//-----motor pins------
//const int dirPin = 7; ||GPIOA, GPIO_PIN12, SET/RESET|| -- OUTPUT
//const int stepPin = 8; ||GPIOA, GPIO_PIN5, SET/RESET|| -- OUTPUT

const int stepsPerRevolution = 200;

//-----routine pins------
//const uint8_t motorLimit = 2;  ||GPIO  ||
//const uint8_t emergencyButton= 3;  ||GPIO  ||

//-----reading pin-------
long reading=0;
long prevReading;
int pollCast = 0;


const uint8_t initLED = 13;//green or blue LED ||GPIO  ||
const uint8_t emergencyLED = 12;//red LED ||GPIO  ||
//uint8_t led_state = HIGH; check led state||GPIO  ||
int passTime = 0;

//-----fishy vars-------
int fishCaught = 0;
int fishRejected = 0;


/* USER CODE END Variables */
/* Definitions for OLED */
osThreadId_t OLEDHandle;
const osThreadAttr_t OLED_attributes = {
  .name = "OLED",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for MOTOR */
osThreadId_t MOTORHandle;
const osThreadAttr_t MOTOR_attributes = {
  .name = "MOTOR",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

void motorInit();
void castPole();
void reelPole();
void rejectFish();

/* USER CODE END FunctionPrototypes */

void OLEDupdater(void *argument);
void MOTORupdater(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of OLED */
  OLEDHandle = osThreadNew(OLEDupdater, NULL, &OLED_attributes);

  /* creation of MOTOR */
  MOTORHandle = osThreadNew(MOTORupdater, NULL, &MOTOR_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_OLEDupdater */
/**
  * @brief  Function implementing the OLED thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_OLEDupdater */
void OLEDupdater(void *argument)
{
  /* USER CODE BEGIN OLEDupdater */
  /* Infinite loop */
	SSD1306_Init();  // initialise
	for(;;)
	{

	      SSD1306_Clear();
	  if (motorAtBoundary == 1 && initialized == 1){

	      SSD1306_GotoXY (0,0);
	      SSD1306_Puts ("Fish Caught: 1" , &Font_7x10, 1);
	      SSD1306_GotoXY (0, 15);
	      SSD1306_Puts ("Fish Rejected: 2", &Font_7x10, 1);
	      SSD1306_GotoXY (0, 30);
	      SSD1306_Puts ("Action:Waiting For", &Font_7x10, 1);
	      SSD1306_GotoXY (0, 40);
	      SSD1306_Puts ("Fish", &Font_7x10, 1);
	      SSD1306_UpdateScreen(); //display
	      HAL_Delay (5000);
	      SSD1306_Clear();

	  }

	  if(motorAtBoundary == 0){
	      SSD1306_GotoXY (0,0);
	      SSD1306_Puts ("Motor Initializing " , &Font_7x10, 1);
	      SSD1306_GotoXY (0, 15);
	      SSD1306_Puts ("", &Font_7x10, 1);
	      SSD1306_GotoXY (0, 30);
	      SSD1306_Puts ("Please Wait", &Font_7x10, 1);
	      SSD1306_UpdateScreen(); //display
	      HAL_Delay (5000);
	      SSD1306_Clear();
	  }



	}
  /* USER CODE END OLEDupdater */
}

/* USER CODE BEGIN Header_MOTORupdater */
/**
* @brief Function implementing the MOTOR thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_MOTORupdater */
void MOTORupdater(void *argument)
{
  /* USER CODE BEGIN MOTORupdater */
  /* Infinite loop */
  for(;;)
  {

	  if (initialized == 0){ //reel
		  motorInit();
	  }


	  if (passTime == 0){
		  if (pollCast == 0){
			  castPole(); 		//cast
			  pollCast =1;
			  osDelay(5000);	//wait
		  }
		  if (pollCast == 1){		//reel when fish detected
			  reelPole();
			  pollCast = 0;
			  osDelay(10000);
		  }
		  passTime++;
	  }

	  if (passTime == 1){

		  rejectFish(); // cast, wait, reel, unreel
		  passTime++;
	  }

  }

  /* USER CODE END MOTORupdater */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

void motorInit(){

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, SET);// set motor dir clockwise LOW for cc // SET MOTOR DIR SO THAT IT ROTATES BACKWARDS
	for(int x = 0; x < stepsPerRevolution; x++){
		if((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6)) == 0){ //check if the motor has been initialized.
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
	        osDelay(15); //perfect speed, change to 20 for slow speed!
	        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
	        osDelay(15);
		}
		else{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, SET);
//			osDelay(250);
//			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, RESET);
//			osDelay(250);
//			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, SET);
//			osDelay(250);
//			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, RESET);
//			osDelay(500);
			initialized =1;
			motorAtBoundary = 1;
	        return;
	      }
	}

}

void castPole(){

	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12, RESET); //write dir

	  for(int x = 0; x < 50; x++){
		  if(motorAtBoundary == 1){  //check for initialization
	          HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
	          osDelay(15); //perfect speed, change to 20 for slow speed!
	          HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
	          osDelay(15);
		  }
	  }
	  //update OLED

}
void reelPole(){

	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12, SET);  // high towards back of A frame

	  for(int x = 0; x < 50; x++)
	  {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
        osDelay(15); //perfect speed, change to 20 for slow speed!
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
        osDelay(15);
	  }

	  fishCaught++;

	  //update OLED

}

//cast, reel, cast!
void rejectFish(){


	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12, RESET);  // CAST
	  for(int x = 0; x < 50; x++){
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
		  osDelay(15); //perfect speed, change to 20 for slow speed!
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
		  osDelay(15);
	  }

	  osDelay(10000);					//WAIT
	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12, SET); //REEL
	  for(int x = 0; x < 35; x++){
		  if(motorAtBoundary == 1){  //check for initialization
	          HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
	          osDelay(15); //perfect speed, change to 20 for slow speed!
	          HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
	          osDelay(15);
		  }
	  }

	  osDelay(100);

	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12, RESET);  // UNREEL
	  for(int x = 0; x < 35; x++)
	  {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
      osDelay(15); //perfect speed, change to 20 for slow speed!
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
      osDelay(15);
	  }

	  fishRejected++;


}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
