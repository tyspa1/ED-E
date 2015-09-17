/*
Send Data to the cloud (Intel iot analytics)
copyright (c) 2015 Tyler Spadgenske
*/

#ifndef IOT_H_
#define IOT_H_

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <string>
#undef max
#undef min
#include <sstream>


void saveToCloud(int air, int gas, int sound, int temp, int flame)
{
  //Send gas sensor data
  std::ostringstream e;
  e << "iotkit-admin observation MQ2_Gas " << gas;
  std::string text = e.str();
  const char * c = text.c_str();
  system(c);

  //Send air quality sensor data
  std::ostringstream f;
  f << "iotkit-admin observation Air_Quality " << air;
  text = f.str();
  c = text.c_str();
  system(c);

  //Send sound sensor data
  std::ostringstream g;
  g << "iotkit-admin observation Sound " << sound;
  text = g.str();
  c = text.c_str();
  system(c);

  //Send flame sensor data
  std::ostringstream h;
  h << "iotkit-admin observation Flame " << flame;
  text = h.str();
  c = text.c_str();
  system(c);

  //Send temp sensor data
  std::ostringstream i;
  i << "iotkit-admin observation Temp " << temp;
  text = i.str();
  c = text.c_str();
  system(c);
}

#endif /* IOT_H_ */
