/*
  horgand - a organ software

  jackoutput.h  -  some jack definitions
  Copyright (C) 2003-2004 Josep Andreu (Holborn)
  Author: Josep Andreu

  This program is free software; you can redistribute it and/or modify
  it under the terms of version 2 of the GNU General Public License
  as published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License (version 2) for more details.

  You should have received a copy of the GNU General Public License
(version2)
  along with this program; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA

*/


#ifndef JACK_OUTPUT_H
#define JACK_OUTPUT_H


#include "Holrgan.h"

int JACKstart(HOR *hor_);
void JACKfinish();

#endif
