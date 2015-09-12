/*
 * buzz.h
 *
 *  Created on: Sep 12, 2015
 *      Author: Kim
 */

#include "buzzer.h"

#ifndef BASE_SRC_BUZZ_H_
#define BASE_SRC_BUZZ_H_

//Sound the buzzer
int chord_ind[] = { DO, RE, MI, FA, SOL, LA, SI, DO, SI };

void buzz(int chord, int play_time)
{
	// create Buzzer instance
	upm::Buzzer* sound = new upm::Buzzer(3);
	std::cout << sound->playSound(chord_ind[chord], 1000000) << std::endl;
	usleep(play_time);
	delete sound;
}



#endif /* BASE_SRC_BUZZ_H_ */
