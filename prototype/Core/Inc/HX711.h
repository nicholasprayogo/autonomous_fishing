/**
 *
 * HX711 library for Arduino
 * https://github.com/bogde/HX711
 *
 * Modified by: Hasib Arian <Hasib.arian@ryerson.ca>
 * For: MEC825 - CAPSTONE PROJECT
 *
 * MIT License
 * (c) 2018 Bogdan Necula
 *
**/
#include <stdio.h>
#include <stdbool.h>


		// Initialize library with data output pin, clock input pin and gain factor.
		// Channel selection is made by passing the appropriate gain:
		// - With a gain factor of 64 or 128, channel A is selected
		// - With a gain factor of 32, channel B is selected
		// The library default is "128" (Channel A).
	extern void begin(int bytegain);

		// Check if HX711 is ready
		// from the datasheet: When output data is not ready for retrieval, digital output pin DOUT is high. Serial clock
		// input PD_SCK should be low. When DOUT goes to low, it indicates data is ready for retrieval.
	extern bool is_ready();

		// Wait for the HX711 to become ready
	extern void wait_ready(unsigned long delay_ms);
//		bool wait_ready_retry(int retries = 3, unsigned long delay_ms = 0);
//		bool wait_ready_timeout(unsigned long timeout = 1000, unsigned long delay_ms = 0);

		// set the gain factor; takes effect only after a call to read()
		// channel A can be set for a 128 or 64 gain; channel B has a fixed 32 gain
		// depending on the parameter, the channel is also set to either A or B
//	extern void set_gain(int gain);

		// waits for the chip to be ready and returns a reading
	extern long read();

		// returns an average reading; times = how many times to read
	extern long read_average(int times);
	extern unsigned long readCount();

		// returns (read_average() - OFFSET), that is the current value without the tare weight; times = how many readings to do
	//extern double get_value(byte times = 1);

		// returns get_value() divided by SCALE, that is the raw value divided by a value obtained via calibration
		// times = how many readings to do
	//extern float get_units(byte times = 1);

		// set the OFFSET value for tare weight; times = how many times to read the tare value
	//extern void tare(byte times = 10);

		// set the SCALE value; this value is used to convert the raw data to "human readable" data (measure units)
	//extern void set_scale(float scale = 1.f);

		// get the current SCALE
	//extern float get_scale();

		// set OFFSET, the value that's subtracted from the actual reading (tare weight)
	//extern void set_offset(long offset = 0);

		// get the current OFFSET
	//extern long get_offset();

		// puts the chip into power down mode
	//extern void power_down();

		// wakes up the chip after power down mode
	//extern void power_up();

