/*
  SevenSeg 1.2.1
  SevenSeg.h - Library for controlling a 7-segment LCD
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

#ifndef SevenSeg74HC595_h
#define SevenSeg74HC595_h

#include "SevenSeg.h"


class SevenSeg74HC595 : public SevenSeg
{

  public:
    SevenSeg74HC595(int,int,int);
    virtual void clearDisp();
    virtual void writeSeg(unsigned char);
    
  private:
    SevenSeg74HC595(int,int,int,int,int,int,int);
    SevenSeg74HC595(int,int,int,int,int,int,int,int);
    int _latch;
    int _clock;
    int _data; 
};

#endif
