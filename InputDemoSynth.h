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

#include "Tonic.h"

using namespace Tonic;

// Expects a RingBuffer called "input" to already exist and be capturing input
class InputDemoSynth : public Synth {
  
public:
  
  InputDemoSynth(){
    
    ControlParameter inputGain = addParameter("inputGain", 0.f).displayName("Input Gain (dbFS)").min(-12.f).max(12.f);
    ControlParameter ringFreq = addParameter("ringFreq", 10.f).displayName("Ring Mod Frequency").min(10.f).max(1000.f).logarithmic(true);
    
    // This will try to read from a globally-known ring buffer called "input"
    RingBufferReader inputReader = RingBufferReader().bufferName("input");
    
    Generator ringModInput = inputReader * (inputGain >> ControlDbToLinear()).smoothed() * SineWave().freq( ringFreq.smoothed(0.5) );
    
    BasicDelay delay = BasicDelay(1.2f).delayTime(0.5f).wetLevel(0.4f).dryLevel(1.0f).feedback(0.6f);
    
    setOutputGen((ringModInput >> delay) * 0.5f);
  }
  
};

TONIC_REGISTER_SYNTH(InputDemoSynth);