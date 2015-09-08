/*
 * button.h
 *
 *  Created on: Aug 19, 2015
 *      Author: Tyler Spadgenske
 *      GPL License v2
 */

#ifndef BUTTON_H_
#define BUTTON_H_

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
int poll(int pos)
{
	bool mode = false;
	sleep(0.9);
	if (mode == false)
	{
	//Check for down button press
	if (down_pin->read() == 0)
	{
		mode = true;
		pos += 1;
		if (pos == 4)
		{
			pos = 3;
		}
	}
	//check for back button press
	if (back_pin->read() == 0)
	{
		std::cout << "Back" << std::endl;
		mode = true;
	}
	//check for select button press
	if (select_pin->read() == 0)
	{
		std::cout << "select" << std::endl;
		mode = true;
	}
	//check for up button press
	if (up_pin->read() == 0)
	{
		mode = true;
		pos -= 1;
		if (pos == -1)
		{
			pos = 1;
		}
	}
	}

	//Wait for bounce
	if (mode != false)
	{
		//Blit cursor at current pos
		if (pos == 1){
			lcd->setCursor(10, 0);
			lcd->write("  ");
			lcd->setCursor(9, 0);
			lcd->write(" <");
		}
		if (pos == 2){
			lcd->setCursor(11, 0);
			lcd->write("  ");
			lcd->setCursor(9, 0);
			lcd->write("  ");
			lcd->setCursor(10, 0);
			lcd->write(" <");
		}
		if (pos == 3){
			lcd->setCursor(10, 0);
			lcd->write("  ");
			lcd->setCursor(11, 0);
			lcd->write(" <");
		}
		//Wait a little then reset
		mode = false;
	}
	return pos;
}

#endif /* BUTTON_H_ */
