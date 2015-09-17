/*Functions for interacting with mysql database
copyright (c) 2015 Tyler Spadgenske*/

#ifndef DB_H_
#define DB_H_

#include <iostream>
#include <cstdio>
#include <my_global.h>
#include <mysql.h>
#include <string>
#undef max
#undef min
#include <sstream>

//Error handling
void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

//Creates sensor database
void createdb(MYSQL *con){
  if (con == NULL)
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

  if (mysql_real_connect(con, "localhost", "root", "",
          NULL, 0, NULL, 0) == NULL)
  {
      finish_with_error(con);
  }

  if (mysql_query(con, "CREATE DATABASE IF NOT EXISTS EDE"))
  {
      finish_with_error(con);
  }
}

//Function to add sensor tables
void addtables(MYSQL *tabcon){
  if (tabcon == NULL)
  {
      fprintf(stderr, "%s\n", mysql_error(tabcon));
      exit(1);
  }

  if (mysql_real_connect(tabcon, "localhost", "root", "",
          "EDE", 0, NULL, 0) == NULL)
  {
      finish_with_error(tabcon);
  }

  //air quality sensor table
  if (mysql_query(tabcon, "CREATE TABLE IF NOT EXISTS air(id int NOT NULL AUTO_INCREMENT, reading int, record timestamp default now(), primary key (id))"))
  {
      finish_with_error(tabcon);
  }
  //MQ2 gas sensor table
  if (mysql_query(tabcon, "CREATE TABLE IF NOT EXISTS gas(id int NOT NULL AUTO_INCREMENT, reading int, record timestamp default now(), primary key (id))"))
  {
      finish_with_error(tabcon);
  }
  //sound sensor table
  if (mysql_query(tabcon, "CREATE TABLE IF NOT EXISTS sound(id int NOT NULL AUTO_INCREMENT, reading int, record timestamp default now(), primary key (id))"))
  {
      finish_with_error(tabcon);
  }
  //flame sensor table
  if (mysql_query(tabcon, "CREATE TABLE IF NOT EXISTS flame(id int NOT NULL AUTO_INCREMENT, reading int, record timestamp default now(), primary key (id))"))
  {
      finish_with_error(tabcon);
  }
  //temperature sensor table
  if (mysql_query(tabcon, "CREATE TABLE IF NOT EXISTS temp(id int NOT NULL AUTO_INCREMENT, reading int, record timestamp default now(), primary key (id))"))
  {
      finish_with_error(tabcon);
  }
  //mailbox sensor table
  if (mysql_query(tabcon, "CREATE TABLE IF NOT EXISTS mail(id int NOT NULL AUTO_INCREMENT, reading int, record timestamp default now(), primary key (id))"))
  {
      finish_with_error(tabcon);
  }
  //frontdoor sensor table
  if (mysql_query(tabcon, "CREATE TABLE IF NOT EXISTS frontdoor(id int NOT NULL AUTO_INCREMENT, reading int, record timestamp default now(), primary key (id))"))
  {
      finish_with_error(tabcon);
  }
  //Garage door sensor table
  if (mysql_query(tabcon, "CREATE TABLE IF NOT EXISTS garagedoor(id int NOT NULL AUTO_INCREMENT, reading int, record timestamp default now(), primary key (id))"))
  {
      finish_with_error(tabcon);
  }
}

//Setup database and tables Function
void setupdb()
{
  //Create DATABASE EDE and add sensor tables if first run
  MYSQL *con = mysql_init(NULL);
  createdb(con);
  mysql_close(con);
  MYSQL *tabcon = mysql_init(NULL);
  addtables(tabcon);
  mysql_close(tabcon);
}

//Store sensor values in database
void storesensors(int air, int gas, int sound, int temp, int flame)
{
  MYSQL *con = mysql_init(NULL);

  //Make sure of valid connection
  if (con == NULL)
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

  if (mysql_real_connect(con, "localhost", "root", "",
          "EDE", 0, NULL, 0) == NULL)
  {
      finish_with_error(con);
  }

  //Store sensor readings
  //Air Quality
  std::ostringstream s;
  s << "INSERT INTO air (reading) values(" << air << ")";

  std::string text = s.str();
  const char * c = text.c_str();
  if (mysql_query(con, c)) {
      finish_with_error(con);
  }

  //Gas
  std::ostringstream t;
  t << "INSERT INTO gas (reading) values(" << gas << ")";

  text = t.str();
  c = text.c_str();
  if (mysql_query(con, c)) {
      finish_with_error(con);
  }

  //Sound
  std::ostringstream r;
  r << "INSERT INTO sound (reading) values(" << sound << ")";

  text = r.str();
  c = text.c_str();
  if (mysql_query(con, c)) {
      finish_with_error(con);
  }

  //Flame
  std::ostringstream e;
  e << "INSERT INTO flame (reading) values(" << flame << ")";

  text = e.str();
  c = text.c_str();
  if (mysql_query(con, c)) {
      finish_with_error(con);
  }

  //temp
  std::ostringstream i;
  i << "INSERT INTO temp (reading) values(" << temp << ")";

  text = i.str();
  c = text.c_str();
  if (mysql_query(con, c)) {
      finish_with_error(con);
  }

    mysql_close(con);
  }

#endif /* DB_H_ */
