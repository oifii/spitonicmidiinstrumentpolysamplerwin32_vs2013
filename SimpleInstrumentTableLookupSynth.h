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

#ifndef SimpleInstrumentTableLookupSynth_h
#define SimpleInstrumentTableLookupSynth_h

#include "Tonic.h"

using namespace Tonic;

class SimpleInstrumentTableLookupSynth : public Synth{

public:
	SimpleInstrumentTableLookupSynth(){

		//#if TONIC_HAS_CPP_11
#if 1
		/*
		Generators and ControlGenerators both output a steady stream of data.
		Generators output at the sample rate (in this case, 44100 hertz.
		ControlGenerators output at the control rate, which is much lower than the sample rate.
		*/

		//1) Build a table of arbitrary length. TableLookupOsc requires power-of-two+1 length tables, but they will be resized if necessary.
		// Try changing this to 2049 and compare the sound. Should be perceptually almost identical.
		const unsigned int tablesize = 2500;

		// You can register this in a collection if you want to use it in a few oscillators
		SampleTable lookupTable = SampleTable(tablesize, 1);

		TonicFloat norm = 1.0f / tablesize;
		TonicFloat * tableData = lookupTable.dataPointer();
		for (unsigned int i = 0; i<tablesize; i++){

			// sum a few sine waves
			TonicFloat phase = TWO_PI * i * norm;
			//*tableData++ = 0.75f * sinf(phase) + 0.5f * sinf(phase * 2) + 0.25f * sinf(phase * 5); //original
			//*tableData++ = 0.75f * sinf(phase) + 0.5f * sinf(phase * 2) + 0.25f * sinf(phase * 5) + 0.25f * sinf(phase * 7) + 0.25f * sinf(phase * 9); //spi
			//*tableData++ = 0.75f * sinf(phase) + 0.5f * sinf(phase * 2) + 0.25f * sinf(phase * 5) + 0.25f * sinf(phase * 7) + 0.25f * sinf(phase * 9) + 0.25f * sinf(phase * 11) + 0.25f * sinf(phase * 13) + 0.25f * sinf(phase * 15); //spi
			//*tableData++ = 0.75f * sinf(phase) + 0.5f * sinf(phase * 2) + 0.25f * cosf(phase * 5) + 0.25f * sinf(phase * 7) + 0.25f * cosf(phase * 9) + 0.25f * sinf(phase * 11) + 0.25f * cosf(phase * 13) + 0.25f * sinf(phase * 15); //spi
			//*tableData++ = 0.25f * sinf(phase) + 0.25f * sinf(phase * 2) + 0.25f * sinf(phase * 5) + 0.25f * sinf(phase * 7) + 0.25f * sinf(phase * 9) + 0.25f * sinf(phase * 11) + 0.25f * sinf(phase * 13) + 0.25f * sinf(phase * 15); //spi
			//*tableData++ = 0.25f * sinf(phase) + 0.125f * sinf(phase * 2) + 0.125f * sinf(phase * 5) + 0.125f * sinf(phase * 7) + 0.25f * sinf(phase * 9) + 0.25f * sinf(phase * 11) + 0.25f * sinf(phase * 13) + 0.25f * sinf(phase * 15); //spi
			*tableData++ = 0.25f * sinf(phase) + 0.125f * sinf(phase * 2) + 0.125f * sinf(phase * 4) + 0.125f * sinf(phase * 5) + 0.125f * sinf(phase * 9) + 0.125f * sinf(phase * 10) + 0.125f * sinf(phase * 13) + 0.125f * sinf(phase * 15); //spi
		}

		//2) define a midi note control generator
		// create a named parameter on the synth which we can set at runtime
		ControlGenerator midiNote = addParameter("midiNote");
		ControlGenerator midiNoteVelocity = addParameter("midiNoteVelocity");

		//3) define a note frequency control generator
		// convert a midi note to a frequency (plugging that parameter into another object)
		ControlGenerator noteFreq = ControlMidiToFreq().input(midiNote);

		//4) define a envelop trigger control generator
		ControlGenerator envelopeTrigger = addParameter("trigger");

		//5) define oscillator
		//TableLookupOsc osc = TableLookupOsc().setLookupTable(lookupTable).freq(noteFreq + 40 * SineWave().freq(5)); //spi
		//TableLookupOsc osc = TableLookupOsc().setLookupTable(lookupTable).freq(noteFreq + 40 * SineWave().freq(5) * (127 - midiNoteVelocity)/127.f); //spi
		TableLookupOsc osc = TableLookupOsc().setLookupTable(lookupTable).freq(noteFreq); //spi

		//tone = BPF24().input(tone).Q(0.1).cutoff((noteFreq)+SineWave().freq(127 - midiNoteVelocity) * 0.5 * noteFreq);

		// It's just a steady tone until we modulate the amplitude with an envelope
		//Generator oscWithEnvelope = osc * ADSR().attack(0.01).decay(1.5).sustain(0).release(0).trigger(envelopeTrigger).legato(true); //good
		//Generator oscWithEnvelope = osc * ADSR().attack(0.01).decay(0.1).sustain(0).release(0).trigger(envelopeTrigger).legato(false); //good
		//Generator oscWithEnvelope = osc * ADSR().attack(0.01).decay(1.5).sustain(0).release(0).trigger(envelopeTrigger).legato(false); //good
		//Generator oscWithEnvelope = osc * ADSR().attack(0.01).decay(0.1).sustain(0.0).release(0.0).trigger(envelopeTrigger); //good
		Generator oscWithEnvelope = osc * ADSR().attack(0.01).decay(5).sustain(0.0).release(0.0).trigger(envelopeTrigger); //good

		// let's send the tone through some delay
		//Generator oscWithDelay = StereoDelay(1.5, 1).input(oscWithEnvelope).wetLevel(0.8).feedback(0.7); //spi
		//Generator oscWithDelay = StereoDelay(1.5, 1).input(oscWithEnvelope).wetLevel(0.2).feedback(0.7); //spi
		Generator oscWithDelay = StereoDelay(1.5, 1).input(oscWithEnvelope).wetLevel(0.5).feedback(0.7); //spi

		setOutputGen(oscWithDelay);
		//setOutputGen(oscWithEnvelope);

#else

#pragma message("C++11 Support not available - SimpleInstrumentTableLookupSynth disabled")

#endif
	}
};

TONIC_REGISTER_SYNTH(SimpleInstrumentTableLookupSynth)

#endif
