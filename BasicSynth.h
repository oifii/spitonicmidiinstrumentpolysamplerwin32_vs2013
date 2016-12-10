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
#ifndef BasicSynth_h
#define BasicSynth_h

#include "Tonic.h"
#include <functional>

using namespace Tonic;

class BasicSynth : public Synth{

public:
	BasicSynth(){

//#if TONIC_HAS_CPP_11
#if 1
		// create a new oscillator which we'll use for the actual audio signal
		SineWave tone = SineWave();

		// create a sine wave we'll use for some vibrato
		SineWave vibratoOsc = SineWave();
		vibratoOsc.freq(10);

		// you can use the regular arithmatic operators on Generators and their subclasses (SineWave extends Generator)
		float basePitch = 400;
		Generator frequency = basePitch + (vibratoOsc * basePitch * 0.01);

		// plug that frequency generator into the frequency slot of the main audio-producing sine wave
		tone.freq(frequency);

		// let's also create a tremelo effect
		SineWave tremeloSine = SineWave().freq(1);

		// set the synth's final output generator
		setOutputGen(tone * tremeloSine);

#else

#pragma message("C++11 Support not available - ControlSwitcherTestSynth disabled")

#endif
	}
};

TONIC_REGISTER_SYNTH(BasicSynth)

#endif
