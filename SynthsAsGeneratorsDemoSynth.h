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
#ifndef __SynthsAsGenerators_cpp__
#define __SynthsAsGenerators_cpp__

#include "Tonic.h"

using namespace Tonic;

class SynthsAsGeneratorsDemoSynth : public Synth
{
  public:
  
    SynthsAsGeneratorsDemoSynth(){
      
      // Add two synths together and put them both through some delay
      Synth noiseSynth = SynthFactory::createInstance("FilteredNoiseSynth");
      Synth octaverSynth = SynthFactory::createInstance("ControlSnapToScaleTestSynth");
      
      // get all the control parameters and add them to this synth
      addParametersFromSynth(noiseSynth);
      addParametersFromSynth(octaverSynth);
      
      //StereoDelay delay = StereoDelay(0.5f,0.5f).delayTimeLeft(0.2).delayTimeRight(0.3).dryLevel(1.0f).wetLevel(0.3f).feedback(0.3f); //original
	  StereoDelay delay = StereoDelay(0.5f, 0.5f).delayTimeLeft(0.2).delayTimeRight(0.3).dryLevel(1.0f).wetLevel(0.8f).feedback(0.3f);

      setOutputGen(((noiseSynth * 0.5 + octaverSynth) >> delay) * 0.8 );
      
    }
  
  
};

TONIC_REGISTER_SYNTH(SynthsAsGeneratorsDemoSynth);

#endif