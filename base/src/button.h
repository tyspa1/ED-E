/*
 * button.h
 *
 *  Created on: Aug 19, 2015
 *      Author: Tyler Spadgenske
 *      GPL License v2
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <string>
#include <sstream>
#include "oled.h"
#include "buzz.h"
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>

//Setup GPIO
mraa::Gpio* down_pin = new mraa::Gpio(4);
mraa::Gpio* back_pin = new mraa::Gpio(5);
mraa::Gpio* select_pin = new mraa::Gpio(6);
mraa::Gpio* up_pin = new mraa::Gpio(7);

//sets the buttons to inputs
void setup()
{
	down_pin->dir(mraa::DIR_IN);
	back_pin->dir(mraa::DIR_IN);
	select_pin->dir(mraa::DIR_IN);
	up_pin->dir(mraa::DIR_IN);
}

//Poll buttons
int poll(int pos, int sensorData[])
{
	bool update = false;

	sleep(0.9);

	if (update != true)
		{
		if (pos <= 3)
		{
			//Check for down button press
			if (down_pin->read() == 0)
			{
				update = true;
				pos = 5;
			}
			//check for back button press
			if (back_pin->read() == 0)
			{
				update = true;
				std::cout << "Back" << std::endl;
				pos = 4;
			}
			//check for select button press
			if (select_pin->read() == 0)
			{
				update = true;
				std::cout << "select" << std::endl;
				pos = 4;
			}
			//check for up button press
			if (up_pin->read() == 0)
			{
				update = true;
			pos = 6;
			}
		}
	}

	if (update != true)
	{
		//View data menu
		if (pos == 4)
		{
			//check for back button press
			if (back_pin->read() == 0)
			{
				update = true;
				std::cout << "Back" << std::endl;
				pos = 1;
				drawMainMenu();
			}
			//check for select button press
			if (select_pin->read() == 0)
			{
				update = true;
				std::cout << "select" << std::endl;
				pos = 1;
				drawMainMenu();
			}
		}
	}

	if (update != true)
		{
			//Settings menu
			if (pos == 5)
			{
				//check for back button press
				if (back_pin->read() == 0)
				{
					update = true;
					std::cout << "Back" << std::endl;
					pos = 1;
					sleep(1);
				}
				//check for select button press
				if (select_pin->read() == 0)
				{
					update = true;
					std::cout << "select" << std::endl;
					pos = 1;
					sleep(1);
				}
			}
		}

	//Wait for bounce
	if (update != false)
	{
		if (pos == 4){
			//Clear screen
			lcd->setCursor(0, 0);
			lcd->write("            ");
			lcd->setCursor(1, 0);
			lcd->write("            ");
			lcd->setCursor(2, 0);
			lcd->write("            ");
			lcd->setCursor(3, 0);
			lcd->write("            ");
			lcd->setCursor(4, 0);
			lcd->write("            ");
			lcd->setCursor(5, 0);
			lcd->write("            ");
			lcd->setCursor(6, 0);
			lcd->write("            ");
			lcd->setCursor(7, 0);
			lcd->write("            ");
			lcd->setCursor(8, 0);
			lcd->write("            ");
			lcd->setCursor(9, 0);
			lcd->write("            ");
			lcd->setCursor(10, 0);
			lcd->write("------------");
			lcd->setCursor(11, 0);
			lcd->write("    EXIT    ");

			//Write sensor data to screen
			//Air Quality
			std::stringstream y;
			y << "Air: " << sensorData[0];
			std::string air = y.str();
			lcd->setCursor(0, 0);
			lcd->write(air);

			//Gas
			std::stringstream e;
			e << "Gas: " << sensorData[2];
			std::string gas = e.str();
			lcd->setCursor(1, 0);
			lcd->write(gas);

			//Flame
			std::stringstream a;
			a << "Flame: " << sensorData[1];
			std::string flame = a.str();
			lcd->setCursor(2, 0);
			lcd->write(flame);

			//Sound
			std::stringstream r;
			r << "Sound: " << sensorData[3];
			std::string sound = r.str();
			lcd->setCursor(3, 0);
			lcd->write(sound);

			//Temp
			std::stringstream t;
			t << "Temp: " << sensorData[4];
			std::string temp = t.str();
			lcd->setCursor(4, 0);
			lcd->write(temp);

			}

		if (pos == 5){
			lcd->setCursor(9, 0);
			lcd->write("    IP:     ");
			lcd->setCursor(10, 0);

			//Get IP address
			struct ifaddrs * ifAddrStruct=NULL;
			struct ifaddrs * ifa=NULL;
			void * tmpAddrPtr=NULL;

			getifaddrs(&ifAddrStruct);

			char *addr;
			for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
				if (ifa ->ifa_addr->sa_family==AF_INET) { // check it is IP4
					// is a valid IP4 Address
				    tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
				    char addressBuffer[INET_ADDRSTRLEN];
				    inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);

				    if (strcmp(ifa->ifa_name, "wlan0") == 0) {
				    	addr = addressBuffer;
				    	std::cout << addr << std::endl;
				    	break;
				       }


				   	   }
				    }
			if (ifAddrStruct!=NULL)
				 freeifaddrs(ifAddrStruct);//remember to free ifAddrStruct

			lcd->write(addr);
			lcd->setCursor(11, 0);
			lcd->write("            ");
		}

		if (pos == 6)
		{
			std::cout << "Shutdown" << std::endl;
			buzz(0, 5000);
			system("shutdown");
			exit(0);
		}


		//Wait a little then reset
		update = false;
	}
	return pos;
}

#endif /* BUTTON_H_ */
