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
#include <signal.h>
#include "yg1006.h"
#include <stdlib.h>
#include "groveloudness.h"
#include "sensors.h"


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
	//Data array
	int sensorData[6];
	int rSensorData[6];

	drawMainMenu();
	buzz(0, 5000);

	// main loop
		for (;;) {
			//Check mode change
			pos = poll(pos, rSensorData); //poll d pad and blit cursor

			//Check clock to see if ready to scan sensors
			duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
			if (duration > clockRate)
			  {
			    scan_sensors(sensorData, rSensorData);
			    clockRate += SAMPLE_RATE;
			  }
		}

	delete lcd;
	delete flame;
//! [Interesting]
        return 0;
}
