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
#ifndef SimpleInstrumentSynth_h
#define SimpleInstrumentSynth_h

#include "Tonic.h"
#include <functional>

using namespace Tonic;

class SimpleInstrumentSynth : public Synth{

public:
	SimpleInstrumentSynth(){

		//#if TONIC_HAS_CPP_11
#if 1
		/*
		Generators and ControlGenerators both output a steady stream of data. 
		Generators output at the sample rate (in this case, 44100 hertz.
		ControlGenerators output at the control rate, which is much lower than the sample rate.
		*/

		// create a named parameter on the synth which we can set at runtime
		ControlGenerator midiNote = addParameter("midiNumber");

		// convert a midi note to a frequency (plugging that parameter into another object)
		ControlGenerator noteFreq = ControlMidiToFreq().input(midiNote);

		// Here's the actual noise-making object
		Generator tone = SawtoothWave().freq(noteFreq);
		//Generator tone = SineWave().freq(noteFreq); //original
		//Generator tone = LFNoise().setFreq(noteFreq);



		// Let's put a filter on the tone
		//tone = LPF12().input(tone).Q(10).cutoff((noteFreq * 2) + SineWave().freq(3) * 0.5 * noteFreq); //original
		//tone = LPF12().input(tone).Q(10).cutoff((noteFreq * 2) + SineWave().freq(10) * 0.5 * noteFreq);
		//tone = LPF12().input(tone).Q(10).cutoff((noteFreq * 2) + SineWave().freq(1) * 0.5 * noteFreq);

		// It's just a steady tone until we modulate the amplitude with an envelope
		ControlGenerator envelopeTrigger = addParameter("trigger");
		Generator toneWithEnvelope = tone * ADSR().attack(0.01).decay(1.5).sustain(0).release(0).trigger(envelopeTrigger).legato(true);

		// let's send the tone through some delay
		Generator toneWithDelay = StereoDelay(0.5, 0.75).input(toneWithEnvelope).wetLevel(0.1).feedback(0.2); //original
		//Generator toneWithDelay = StereoDelay(0.5, 0.75).input(toneWithEnvelope).wetLevel(0.8).feedback(0.2); //spi

		setOutputGen(toneWithDelay);

#else

#pragma message("C++11 Support not available - ControlSwitcherTestSynth disabled")

#endif
	}
};

TONIC_REGISTER_SYNTH(SimpleInstrumentSynth)

#endif
