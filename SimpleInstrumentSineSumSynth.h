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

#ifndef SimpleInstrumentSineSumSynth_h
#define SimpleInstrumentSineSumSynth_h

#include "Tonic.h"

using namespace Tonic;

//#define NUM_SINES 5
#define NUM_SINES 10


class SimpleInstrumentSineSumSynth : public Synth{

public:
	SimpleInstrumentSineSumSynth(){

		//#if TONIC_HAS_CPP_11
#if 1
		/*
		Generators and ControlGenerators both output a steady stream of data.
		Generators output at the sample rate (in this case, 44100 hertz.
		ControlGenerators output at the control rate, which is much lower than the sample rate.
		*/

		//1) define a midi note control generator
		// create a named parameter on the synth which we can set at runtime
		ControlGenerator midiNote = addParameter("midiNote");
		ControlGenerator midiNoteVelocity = addParameter("midiNoteVelocity");

		//2) define a note frequency control generator
		// convert a midi note to a frequency (plugging that parameter into another object)
		ControlGenerator noteFreq = ControlMidiToFreq().input(midiNote);

		//3) define a envelop trigger control generator
		ControlGenerator envelopeTrigger = addParameter("trigger");

		//4)
		ControlParameter pitch = addParameter("pitch", 0);
		Adder outputAdder;
		for (int s = 0; s<NUM_SINES; s++){

			//ControlGenerator pitchGen = ((pitch * 220 + 220) * powf(2, (s - (NUM_SINES / 2)) * 5.0f / 12.0f));
			//ControlGenerator pitchGen = ((noteFreq * 220 + 220) * powf(2, (s - (NUM_SINES / 2)) * 5.0f / 12.0f)); //intrigating
			ControlGenerator pitchGen = ((pitch * noteFreq + noteFreq) * powf(2, (s - (NUM_SINES / 2)) * 5.0f / 12.0f)); //better
			outputAdder.input(SineWave().freq(pitchGen.smoothed()));
			//outputAdder.input(TriangleWave().freq(pitchGen.smoothed()));
			//outputAdder.input(RectWave().freq(pitchGen.smoothed()));

		}
		//Generator osc = outputAdder * ((1.0f / NUM_SINES) * 0.5f); //original
		Generator osc = outputAdder * ((1.0f / NUM_SINES) * 1.0f); //spi


		// It's just a steady tone until we modulate the amplitude with an envelope
		//Generator oscWithEnvelope = osc * ADSR().attack(0.01).decay(1.5).sustain(0).release(0).trigger(envelopeTrigger).legato(true); //good
		//Generator oscWithEnvelope = osc * ADSR().attack(0.01).decay(0.1).sustain(0).release(0).trigger(envelopeTrigger).legato(false); //good
		Generator oscWithEnvelope = osc * ADSR().attack(0.01).decay(1.5).sustain(0).release(0).trigger(envelopeTrigger).legato(false); //good
		//Generator oscWithEnvelope = osc * ADSR().attack(0.01).decay(0.1).sustain(0.0).release(0.0).trigger(envelopeTrigger); //good
		//Generator oscWithEnvelope = osc * ADSR().attack(0.01).decay(5).sustain(0.0).release(0.0).trigger(envelopeTrigger); //good

		//Generator oscWithHPF = HPF12().cutoff(60).input(oscWithEnvelope); //to cut the DC but does not work

		// let's send the tone through some delay
		//Generator oscWithDelay = StereoDelay(1.5, 1).input(oscWithEnvelope).wetLevel(0.8).feedback(0.7); //spi
		//Generator oscWithDelay = StereoDelay(1.5, 1).input(oscWithEnvelope).wetLevel(0.2).feedback(0.7); //spi
		Generator oscWithDelay = StereoDelay(1.5, 1).input(oscWithEnvelope).wetLevel(0.5).feedback(0.7); //spi

		setOutputGen(oscWithDelay);
		//setOutputGen(oscWithEnvelope);
		//setOutputGen(oscWithHPF);

#else

#pragma message("C++11 Support not available - SimpleInstrumentSineSumSynth disabled")

#endif
	}
};

TONIC_REGISTER_SYNTH(SimpleInstrumentSineSumSynth)

#endif
