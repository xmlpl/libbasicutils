/*******************************************************************\

              Copyright (C) 2004 Joseph Coffland

    This program is free software; you can redistribute it and/or
     modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
        of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
             GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
     along with this program; if not, write to the Free Software
      Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
                           02111-1307, USA.

            For information regarding this software email
                   jcofflan@users.sourceforge.net

\*******************************************************************/
#include "BasicRandomNumberGenerator.h"


BasicRandomNumberGenerator *BasicRandomNumberGenerator::singleton = NULL;

BasicRandomNumberGenerator *BasicRandomNumberGenerator::getInstance() {
  if (!singleton) singleton = new BasicRandomNumberGenerator();
  return singleton;
}

void BasicRandomNumberGenerator::setSeed(const unsigned int seed) {
  this->seed = seed;
  srand(seed);
}

bool BasicRandomNumberGenerator::getBool() {
  if (!bits) {
    bitBuf = rand();
    bits = sizeof(int) * 8;
  }

  bool value = bitBuf & 1;
  bits--;
  bitBuf = bitBuf >> 1;

  return value;
}

long BasicRandomNumberGenerator::getInteger(const long min, const long max) {
  return min + (int)(((max - min) + 1) * getRatio());
}

double BasicRandomNumberGenerator::getRatio() {
  return rand() / (RAND_MAX + 1.0);
}

