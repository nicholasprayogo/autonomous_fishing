/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */
#include <stdbool.h>
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

#include "ssd1306.h"
#include "HX711.h"
#include <stdio.h>
#include <string.h>
#include "fonts.h"


/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  HAL_PWREx_EnableVddIO2();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, MOTOR_STEP_PIN_Pin|EXTERNAL_LED_BLUE_Pin|MOTOR_DIRECTION_PIN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Motor_Initialized_Pin|ONBOARD__RED__LED_Pin|ONBOARD__BLUE__LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, ONBOARD__GREEN__LED_Pin|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = EMERGENCY_SHUTDOWN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(EMERGENCY_SHUTDOWN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = MOTOR_STEP_PIN_Pin|EXTERNAL_LED_BLUE_Pin|MOTOR_DIRECTION_PIN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = Motor_Initialized_Pin|ONBOARD__RED__LED_Pin|ONBOARD__BLUE__LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LIMIT_SWITCH_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LIMIT_SWITCH_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PC10 */
  GPIO_InitStruct.Pin = ONBOARD__GREEN__LED_Pin|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PC11 */
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 2 */
//CALLBACK IMPLEMENTED FROM STM32L4XX_HAL_GPIO.C
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

//WE DON'T REALLY NEED TO WORRY ABOUT DEBOUNCING BECAUSE IF THE BUTTON IS SWITCHED THEN WE MUST TURN OFF THE SYSTEM ANYWAYS
	static bool isOn;

	//BELOW IS JUST CODE IN PLACE OF TOTAL SYSTEM SHUTDOWN.
	//EVERYTHING SHOULD STOP IN ITS PLACE IMMEDIATELY

	//NOTE: PIN 13 IS FOR ONBOARD EMERGENCY STOP BUTTON
	if (GPIO_Pin == GPIO_PIN_13){
		if(isOn == false){

				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, SET);
				isOn = true;
				while (1){
					for(int i; i < 5000000; i++){

						 	 	  SSD1306_GotoXY (0,0);
							      SSD1306_Puts ("EMERGENCY" , &Font_7x10, 1);
							      SSD1306_GotoXY (0, 15);
							      SSD1306_Puts ("BUTTON", &Font_7x10, 1);
							      SSD1306_GotoXY (0, 30);
							      SSD1306_Puts ("PRESSED", &Font_7x10, 1);
							      SSD1306_UpdateScreen(); //display
							      SSD1306_InvertDisplay(1);   // invert the display
							      HAL_Delay (3000);
							      SSD1306_InvertDisplay(0);   // invert the display
							      HAL_Delay (3000);
							      SSD1306_InvertDisplay(1);   // invert the display
							      HAL_Delay (5000);
							      SSD1306_Clear();

					}
				}
			}
	}

// ELSE IF IT WAS THE LIMIT SWITCH THEN:
	else{

			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, SET);
			//set the PB11 to high to signal initialization  of motor
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12, RESET);
			HAL_Delay(500);

				  for(int x = 0; x < 10; x++){ //take 20 steps forward
					  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
				      HAL_Delay(15); //perfect speed, change to 20 for slow speed!
				      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
				      HAL_Delay(15);

				  }
	}

}
/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
