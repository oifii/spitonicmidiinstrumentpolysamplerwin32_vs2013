/*
 * Copyright (c) 2015-2016 Stephane Poirier
 *
 * stephane.poirier@oifii.org
 *
 * Stephane Poirier
 * 3532 rue Ste-Famille, #3
 * Montreal, QC, H2X 2L1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef TonicDemo_XYSpeed_cpp
#define TonicDemo_XYSpeed_cpp

#include "Tonic.h"

using namespace Tonic;

class XYSpeedSynth : public Synth{

  public:
  XYSpeedSynth(){
    Generator speed = ControlXYSpeed().x(addParameter("x")).y(addParameter("y")).smoothed();
    Generator outputGen = RectWave()
      .freq(100 + 20 * speed)
      .pwm( 0.05 + (SineWave().freq(0.1) + 1) * 0.2)
    * SineWave()
        .freq(1 + 20 * speed)
    >> LPF12().cutoff(100 + 6000 * speed)
    >> StereoDelay(0.1, 0.15).wetLevel(0.1);
    ;
    
    setOutputGen(outputGen);
  }

};


TONIC_REGISTER_SYNTH(XYSpeedSynth);

#endif
