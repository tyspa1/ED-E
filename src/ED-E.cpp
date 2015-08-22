/*ED-E Home Automation
copyright 2015 (c) Tyler Spadgenske
GPL v2 License

ED-E Core unit software
 */

#include "ssd1327.h"
#include <ssd1308.h>
#include <sainsmartks.h>
#include <jhd1313m1.h>
#include <eboled.h>
#include "mraa.hpp"
#include <iostream>
#include <unistd.h>
#include "oled.h"
#include "button.h"
#include <cstdio>
#include <ctime>
#include "tp401.h"
#include <mq9.h>
#include <mq5.h>
#include <mq3.h>
#include <mq2.h>
#include <buzzer.h>
#include <lcm1602.h>

upm::TP401* airSensor = new upm::TP401(0); // Instantiate new grove air quality sensor on analog pin A0

//Check built in sensors and save data
void scan_sensors()
{
	std::cout << "Sampling built in sensors" << std::endl;
	int value = airSensor->getSample(); // Read raw value
	std::cout << "Air quality" << value << std::endl;
}

int main(int argc, char **argv)
{
	//Constants
	int SAMPLE_RATE = 20;
	//create clock
	std::clock_t start;
	start = std::clock();
	double duration;
	int clockRate = SAMPLE_RATE;
	//Item select position
	int pos = 1;
	drawMainMenu();

	// main loop
		for (;;) {
			//Check mode change
			pos = poll(pos); //poll d pad and blit cursor

			//Check clock to see if ready to scan sensors
			duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
			if (duration > clockRate)
			  {
			    scan_sensors();
			    clockRate += SAMPLE_RATE;
			  }
		}

	delete lcd;
//! [Interesting]
        return 0;
}
