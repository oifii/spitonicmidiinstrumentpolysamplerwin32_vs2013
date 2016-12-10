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
//
//  BandlimitedOscillatorTest.cpp
//  TonicDemo
//
//  Created by Nick Donaldson on 7/21/13.
//

#ifndef TonicDemo_BandlimitedOscillatorTest_cpp
#define TonicDemo_BandlimitedOscillatorTest_cpp

#include "Tonic.h"

using namespace Tonic;

class BandlimitedOscillatorTestSynth : public Synth
{

public:
  
  BandlimitedOscillatorTestSynth()
  {
    ControlParameter blend = addParameter("blend").min(0).max(1);
  
    Generator freqSweep = SineWave().freq(0.25) * 1000 + 1080;
    Generator smoothBlend = blend.smoothed();
    
    Generator output = (SquareWave().freq(freqSweep) * (1.0 - smoothBlend)) + (SquareWaveBL().freq(freqSweep) * smoothBlend);
    setOutputGen(output * 0.25);
  }
  
};

TONIC_REGISTER_SYNTH(BandlimitedOscillatorTestSynth);

#endif