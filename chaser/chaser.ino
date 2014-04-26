/*
Chaser for Rainbowduino with MMA7660 Orientation/Motion Detection Sensor
Copyright (c) 2014 Danilo de Jesus da Silva Bellini
License is MIT. See COPYING.txt for more information.
*/
#include <Rainbowduino.h>
#include <Wire.h>
#define ACCVAL 2

typedef struct{
  int x;
  int y;
} Point;

/* MMA7660FC 3-Axis Orientation/Motion Detection Sensor (accelerometer) datasheet */
/* http://www.freescale.com.cn/files/sensors/doc/data_sheet/MMA7660FC.pdf */

void init_acc(){
  Wire.begin();
  Wire.beginTransmission(0x4c); // MMA7660, page 21
  Wire.write(0x07); Wire.write(0x00); // Stand by for config
  Wire.endTransmission();
  Wire.beginTransmission(0x4c);
  Wire.write(0x08); Wire.write(0x00); // Max sample rate (120 samples/second)
  Wire.endTransmission();
  Wire.beginTransmission(0x4c);
  Wire.write(0x07); Wire.write(0x01);
  Wire.endTransmission();
}

Point acc_data;

void read_acc(){
  Wire.requestFrom(0x4c, 3); // MMA7660, page 21
  acc_data.x = Wire.read();
  acc_data.y = Wire.read();
  Wire.read(); /* Neglects z */

  if(acc_data.x == -1) acc_data.x = 0; // Not available
  acc_data.x = acc_data.x < 32 ? acc_data.x : acc_data.x - 64;
  if(acc_data.y == -1) acc_data.y = 0; // Not available
  acc_data.y = acc_data.y < 32 ? acc_data.y : acc_data.y - 64;
}

void setup(){
  Rb.init();
  init_acc();
}

uint32_t red   = 0x00330000;
uint32_t green = 0x00003300;
uint32_t blue  = 0x00000033;
uint32_t black = 0x00000000;

Point p = {0, 0},
      q = {7, 6},
      delta_p = {1, 1},
      delta_q = {-1, 0};

void update_point(void *from, void *delta){
  Point *f = (Point *) from;
  Point *d = (Point *) delta;
  f->x = (f->x + d->x + 8) % 8;
  f->y = (f->y + d->y + 8) % 8;
}

void loop(){
  read_acc();

  Rb.setPixelXY(p.x, p.y, black);
  Rb.setPixelXY(q.x, q.y, black);

  delta_p.x ^= random(2);
  delta_p.y ^= random(2);
  delta_q.x = (acc_data.x >= ACCVAL) - (acc_data.x <= -ACCVAL);
  delta_q.y = (acc_data.y <= -ACCVAL) - (acc_data.y >= ACCVAL);

  update_point(&p, &delta_p);
  update_point(&q, &delta_q);

  if((p.x == q.x) && (p.y == q.y))
    Rb.setPixelXY(p.x, p.y, red);
  else{
    Rb.setPixelXY(p.x, p.y, blue);
    Rb.setPixelXY(q.x, q.y, green);
  }
  
  delay(100);
}
