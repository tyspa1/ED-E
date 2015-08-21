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

int main(int argc, char **argv)
{
	//Item select position
	int pos = 1;
	drawMainMenu();

	// main loop
		for (;;) {
			//Check mode change
			pos = poll(pos); //poll d pad and blit cursor
		}

	delete lcd;
//! [Interesting]
        return 0;
}
