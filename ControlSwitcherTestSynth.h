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
#ifndef TonicDemo_ControlInputTestSynth_cpp
#define TonicDemo_ControlInputTestSynth_cpp

#include "Tonic.h"
#include <functional>

using namespace Tonic;

class ControlSwitcherTestSynth : public Synth{

public:
  ControlSwitcherTestSynth(){
  
//#if TONIC_HAS_CPP_11
#if 1

    ControlMetro metro = ControlMetro().bpm(80 * 4);
	ControlGenerator modeSwitch = ControlMetro().bpm(4);
	//ControlGenerator modeSwitch = ControlMetro().bpm(4 * 4);
    
    const int numSteps = 20;
	//const int numSteps = 5;
	//const int numSteps = 100;

    ControlGenerator phraseStart = ControlRandom().min(0).max(5).trigger(modeSwitch);
    
    ControlGenerator phraseLen = ControlRandom().min(3).max(11).trigger(modeSwitch);
    
    ControlStepper step = ControlStepper()
      .start(phraseStart)
      .end(phraseStart + phraseLen - 1)
      .trigger(metro);
    
    ControlGenerator clickVol = addParameter("clickVol");
    ADSR clickEnv =  ADSR(0, 0.01, 0, 0).trigger(metro);
    Generator clickIntensity = (1 + clickVol).smoothed();
    Generator click = SineWave().freq(300 + 1000 * clickEnv ) * clickEnv * 0.03 ;
    
    ControlSwitcher fmAmount = ControlSwitcher().inputIndex(step);
    ControlSwitcher sustain = ControlSwitcher().inputIndex(step);
    ControlSwitcher decay = ControlSwitcher().inputIndex(step);
    ControlSwitcher spreadSeq = ControlSwitcher().inputIndex(step);
    
    for(int i = 0; i < numSteps; i++){
      fmAmount.addInput(randomFloat(0, 10));
      sustain.addInput(randomFloat(0, 0.7));
      decay.addInput(randomFloat(0.03, 0.1));
      spreadSeq.addInput(randomFloat(0, 0.5));
    }
    
	Generator freq = ControlValue(50).smoothed();
	//Generator freq = ControlValue(25).smoothed();
	//Generator freq = ControlValue(100).smoothed();
    Generator tremelo =  1 + ( SineWave().freq(15) *  ADSR(0, 0.5, 0,0).trigger(modeSwitch) );
    Generator bassEnv = ADSR(0.001, 0.1 ,0,0).decay(decay).legato(true).sustain(sustain * sustain).trigger(metro);
	//Generator bassEnv = ADSR(0.1, 0.1, 0, 0).decay(decay).legato(true).sustain(sustain * sustain).trigger(metro);
	ControlGenerator spread = ControlRandom().min(0).max(0.5).trigger(modeSwitch);// * spreadSeq;
    ControlGenerator wave = ControlRandom().min(0.4).max(0.9).trigger(modeSwitch);
    
    auto makeBass = [&](Generator bassFreq){
      return RectWave()
      .pwm(wave + 0.04 * bassEnv)
      .freq(
        bassFreq
        + bassFreq
          * SineWave()
            .freq(bassFreq * 1.99)
          * (
            fmAmount
            * 0.7
            + addParameter("addtlFM")
            ).smoothed()
      );
    };
    
    Generator bass =
    (
      makeBass(freq)
      >> MonoToStereoPanner().pan(-1 * spread)
    )
    +
    (
      makeBass(freq * 1.02)
      >> MonoToStereoPanner().pan(1 * spread)
    )
      
      //>> HPF12().cutoff(addParameter("hpf") * 1000)
      >> LPF12().cutoff(5500)
	  //>> LPF12().cutoff(11000)
	  >> StereoDelay(1.1, 1.2).wetLevel(0.1);
	  //>> StereoDelay(1.1, 1.2).wetLevel(0.8);
    Generator bassWithAmp = bass * bassEnv * tremelo;
	setOutputGen(bassWithAmp + click);
	//setOutputGen(bass  + click);
#else
      
#pragma message("C++11 Support not available - ControlSwitcherTestSynth disabled")
      
#endif
  }
};

TONIC_REGISTER_SYNTH(ControlSwitcherTestSynth)

#endif
