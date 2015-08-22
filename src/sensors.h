/*
 * sensors.h
 *
 *  Created on: Aug 22, 2015
 *      Author: Tyler Spadgenske
 */

#ifndef SENSORS_H_
#define SENSORS_H_

//Create all the sensor objects

// Instantiate new grove air quality sensor on analog pin A0
upm::TP401* airSensor = new upm::TP401(0);

// Instantiate a yg1006 flame sensor on digital pin D2
upm::YG1006* flame = new upm::YG1006(2);

//Setup the MQ2 Gas Sensor
uint16_t buffer [128];
upm::MQ2 *sensor = new upm::MQ2(1);
thresholdContext ctx;

// Instantiate a Grove Loudness sensor on analog pin A2
upm::GroveLoudness* loudness = new upm::GroveLoudness(2);

//Check built in sensors and save data
void scan_sensors()
{
	std::cout << "Sampling built in sensors" << std::endl;
	//Air Quality
	int airQualityReading = airSensor->getSample(); // Read raw value
	std::cout << "Air quality: " << airQualityReading << std::endl;

	//Flame
	bool flameReading = flame->flameDetected();
	std::cout << "Fire detected: " << flameReading << std::endl;

	//MQ2 Gas
	ctx.averageReading = 0;
	ctx.runningAverage = 0;
	ctx.averagedOver   = 2;
	int len = sensor->getSampledWindow (2, 128, buffer);
	if (len) {
		int thresh = sensor->findThreshold (&ctx, 30, buffer, len);
	    std::cout << "MQ2 Gas: " << thresh << std::endl;
	}

	//Sound
	int val = loudness->value();
	std::cout << "Loudness value (higher is louder): " << val << std::endl;
}




#endif /* SENSORS_H_ */
