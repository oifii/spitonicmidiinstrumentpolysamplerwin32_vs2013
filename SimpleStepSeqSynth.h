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
#ifndef TonicDemo_SimpleStepSeqSynth_h
#define TonicDemo_SimpleStepSeqSynth_h


#include "Tonic.h"

using namespace Tonic;

class SimpleStepSeqSynth : public Synth {
  

public:
  SimpleStepSeqSynth(){
      
//#if TONIC_HAS_CPP_11
#if 1 
    const int NUM_STEPS = 8; //original
	//const int NUM_STEPS = 80;

    ControlGenerator metro = ControlMetro().bpm(4 * addParameter("tempo",100).min(50).max(300));
    
    ControlGenerator step = ControlStepper().end(NUM_STEPS).trigger(metro);
    ControlGenerator transpose = addParameter("transpose", 0).min(-6).max(6);
    ControlSwitcher pitches = ControlSwitcher().inputIndex(step);
    ControlSwitcher cutoffs = ControlSwitcher().inputIndex(step);
    
    for(int i = 0; i < NUM_STEPS; i++){
      float initialValue =  randomFloat(10, 80);
      pitches.addInput(addParameter("step" + to_string(i) + "Pitch", initialValue).min(10).max(80));
      cutoffs.addInput(addParameter("step" + to_string(i) + "Cutoff", 500).min(30).max(1500));
    }
  
    ControlGenerator midiNote = transpose + (pitches >> ControlSnapToScale().setScale({0,2,3,5,7,10}));
  
    Generator outputGen = SquareWave().freq( midiNote >> ControlMidiToFreq() ) * ADSR(0.01, 0.1, 0,0).trigger(metro) * 0.1;
	outputGen = (outputGen >> LPF24().cutoff(cutoffs).Q(0.1)); //original
	//outputGen = (outputGen >> LPF24().cutoff(cutoffs).Q(0.8)); 
    //outputGen = outputGen >> Reverb().wetLevel(0.1).dryLevel(1).decayTime(1);

    setOutputGen(outputGen);
    
#else
      
#pragma message("C++11 Support not available - SimpleStepSeqSynth disabled")
      
#endif
      
  }
    
};

TONIC_REGISTER_SYNTH(SimpleStepSeqSynth);


#endif
