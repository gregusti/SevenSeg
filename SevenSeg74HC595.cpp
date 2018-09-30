/*
  SevenSeg 1.2.1
  SevenSeg.cpp - Library for controlling a 7-segment LCD
  Copyright 2013, 2015, 2017 Sigvald Marholm <marholm@marebakken.com>

  This file is part of SevenSeg.

  SevenSeg is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  SevenSeg is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with SevenSeg.  If not, see <http://www.gnu.org/licenses/>.
 */
 
 #include "SevenSeg74HC595.h"
 
SevenSeg74HC595::SevenSeg74HC595(int latch, int data, int clock) : SevenSeg(-1, -1, -1, -1, -1, -1, -1, -1) {
    _latch = latch;
    _clock = clock;
    _data = data;
    
    pinMode(latch,OUTPUT);
    pinMode(clock,OUTPUT);
    pinMode(data,OUTPUT);
}

// Write segments from binary bits
void SevenSeg74HC595::writeSeg(unsigned char bits) {
  Serial.print("7SegHC "); Serial.println(bits);
  digitalWrite(_latch,LOW);
  shiftOut(_data, _clock, MSBFIRST, bits);
  digitalWrite(_latch,HIGH);
}

void SevenSeg74HC595::clearDisp() {
  SevenSeg::clearDisp();
  SevenSeg74HC595::writeSeg(0);
}

