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

#ifndef SimpleInstrumentTableLookupSPEARSynth_h
#define SimpleInstrumentTableLookupSPEARSynth_h

#include "Tonic.h"

#include "speartextpartialsreader.h"

using namespace Tonic;

class SimpleInstrumentTableLookupSPEARSynth : public Synth{

public:
	SimpleInstrumentTableLookupSPEARSynth(){

		//#if TONIC_HAS_CPP_11
#if 1
		/*
		Generators and ControlGenerators both output a steady stream of data.
		Generators output at the sample rate (in this case, 44100 hertz.
		ControlGenerators output at the control rate, which is much lower than the sample rate.
		*/
		/*
		//0) loadin SPEAR partials text file
		SpearTextPartialsReader mySpearTextPartialsReader("a1_tum_ot_l29(partials).txt");
		//A1 is 55 Hz
		for (vector<float>::iterator it = mySpearTextPartialsReader.partialfrequencies.begin(), end = mySpearTextPartialsReader.partialfrequencies.end(); it != end; ++it)
		{
			(*it) = (*it) / 55.f;
			//std::cout << (*it) << "\n";  
		}
		*/
		/*
		SpearTextPartialsReader mySpearTextPartialsReader("PersianNey B3 Vel_2(partials).txt");
		//B3 is 246.9 Hz
		for (vector<float>::iterator it = mySpearTextPartialsReader.partialfrequencies.begin(), end = mySpearTextPartialsReader.partialfrequencies.end(); it != end; ++it)
		{
			(*it) = (*it) / 246.9;
			//std::cout << (*it) << "\n";  
		}
		*/
		/*
		SpearTextPartialsReader mySpearTextPartialsReader("VC-8_mV_sus-sh_mf_B3(partials).txt");
		//B3 is 246.9 Hz
		for (vector<float>::iterator it = mySpearTextPartialsReader.partialfrequencies.begin(), end = mySpearTextPartialsReader.partialfrequencies.end(); it != end; ++it)
		{
			(*it) = (*it) / 246.9;
			//std::cout << (*it) << "\n";  
		}
		*/
		/*
		SpearTextPartialsReader mySpearTextPartialsReader("HA_ES_flag_p_B3(partials).txt");
		//B3 is 246.9 Hz
		for (vector<float>::iterator it = mySpearTextPartialsReader.partialfrequencies.begin(), end = mySpearTextPartialsReader.partialfrequencies.end(); it != end; ++it)
		{
			(*it) = (*it) / 246.9;
			//std::cout << (*it) << "\n";  
		}
		*/
		/*
		SpearTextPartialsReader mySpearTextPartialsReader("LHkora B3 Vel_1(partials).txt");
		//B3 is 246.9 Hz
		for (vector<float>::iterator it = mySpearTextPartialsReader.partialfrequencies.begin(), end = mySpearTextPartialsReader.partialfrequencies.end(); it != end; ++it)
		{
			(*it) = (*it) / 246.9;
			//std::cout << (*it) << "\n";  
		}
		*/
		/*
		SpearTextPartialsReader mySpearTextPartialsReader("CRM-Tone03-B3(partials).txt");
		//B3 is 246.9 Hz
		for (vector<float>::iterator it = mySpearTextPartialsReader.partialfrequencies.begin(), end = mySpearTextPartialsReader.partialfrequencies.end(); it != end; ++it)
		{
			(*it) = (*it) / 246.9;
			//std::cout << (*it) << "\n";  
		}
		*/
		/*
		SpearTextPartialsReader mySpearTextPartialsReader("ARP2600_2osc_Saw_C4(partials).txt");
		//C4 is 261.6 Hz
		for (vector<float>::iterator it = mySpearTextPartialsReader.partialfrequencies.begin(), end = mySpearTextPartialsReader.partialfrequencies.end(); it != end; ++it)
		{
			(*it) = (*it) / 261.6;
			//std::cout << (*it) << "\n";  
		}
		*/
		/*
		SpearTextPartialsReader mySpearTextPartialsReader("ARP2600_50-50_Pulse_C4(partials).txt"); //good
		//C4 is 261.6 Hz
		for (vector<float>::iterator it = mySpearTextPartialsReader.partialfrequencies.begin(), end = mySpearTextPartialsReader.partialfrequencies.end(); it != end; ++it)
		{
			(*it) = (*it) / 261.6;
			//std::cout << (*it) << "\n";  
		}
		*/
		/*
		SpearTextPartialsReader mySpearTextPartialsReader("ATC 132_ms0_072_c4(partials).txt"); 
		//C4 is 261.6 Hz
		for (vector<float>::iterator it = mySpearTextPartialsReader.partialfrequencies.begin(), end = mySpearTextPartialsReader.partialfrequencies.end(); it != end; ++it)
		{
			(*it) = (*it) / 261.6;
			//std::cout << (*it) << "\n";  
		}
		*/
		/*
		SpearTextPartialsReader mySpearTextPartialsReader("Analog Strings 2_ms0_072_c4(partials).txt"); //good
		//C4 is 261.6 Hz
		for (vector<float>::iterator it = mySpearTextPartialsReader.partialfrequencies.begin(), end = mySpearTextPartialsReader.partialfrequencies.end(); it != end; ++it)
		{
			(*it) = (*it) / 261.6;
			//std::cout << (*it) << "\n";  
		}
		*/
		/*
		SpearTextPartialsReader mySpearTextPartialsReader("kick 1(partials).txt"); 
		//unknown fondammental
		for (vector<float>::iterator it = mySpearTextPartialsReader.partialfrequencies.begin(), end = mySpearTextPartialsReader.partialfrequencies.end(); it != end; ++it)
		{
			(*it) = (*it) / 100.0;
			//std::cout << (*it) << "\n";  
		}
		*/
		/*
		SpearTextPartialsReader mySpearTextPartialsReader("snare 1(partials).txt");
		//unknown fondammental
		for (vector<float>::iterator it = mySpearTextPartialsReader.partialfrequencies.begin(), end = mySpearTextPartialsReader.partialfrequencies.end(); it != end; ++it)
		{
			(*it) = (*it) / 100.0;
			//std::cout << (*it) << "\n";  
		}
		*/
		/*
		SpearTextPartialsReader mySpearTextPartialsReader("Boes-R(C2)-V(190)-dB(2294)-T(MF)-M(120)-P(1027-04-02)(partials).txt");
		//C2 is 65.41 Hz
		for (vector<float>::iterator it = mySpearTextPartialsReader.partialfrequencies.begin(), end = mySpearTextPartialsReader.partialfrequencies.end(); it != end; ++it)
		{
			(*it) = (*it) / 65.41;
			//std::cout << (*it) << "\n";  
		}
		*/
		/*
		SpearTextPartialsReader mySpearTextPartialsReader("Gong C 04(partials).txt"); 
		//C4 is 261.6 Hz
		for (vector<float>::iterator it = mySpearTextPartialsReader.partialfrequencies.begin(), end = mySpearTextPartialsReader.partialfrequencies.end(); it != end; ++it)
		{
			(*it) = (*it) / 261.6;
			//std::cout << (*it) << "\n";  
		}
		*/
		
		SpearTextPartialsReader mySpearTextPartialsReader("HPchanter C4 Vel_1(partials).txt"); //close to ni
		//C4 is 261.6 Hz
		for (vector<float>::iterator it = mySpearTextPartialsReader.partialfrequencies.begin(), end = mySpearTextPartialsReader.partialfrequencies.end(); it != end; ++it)
		{
			(*it) = (*it) / 261.6;
			//std::cout << (*it) << "\n";  
		}
		
		/*
		SpearTextPartialsReader mySpearTextPartialsReader("KB-6_sforz_fp_B1(partials).txt");
		//B1 is 61.74 Hz
		for (vector<float>::iterator it = mySpearTextPartialsReader.partialfrequencies.begin(), end = mySpearTextPartialsReader.partialfrequencies.end(); it != end; ++it)
		{
			(*it) = (*it) / 61.74;
			//std::cout << (*it) << "\n";  
		}
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
			TonicFloat sinesum = 0.0f;
			for (int i = 0; i<mySpearTextPartialsReader.partialfrequencies.size(); i++)
			{
				sinesum += mySpearTextPartialsReader.partialamplitudes[i] * sinf(phase * mySpearTextPartialsReader.partialfrequencies[i]);
				//sinesum += mySpearTextPartialsReader.partialamplitudes[i] * sinf(phase * floor(mySpearTextPartialsReader.partialfrequencies[i]));
				//std::cout << i << ", " << mySpearTextPartialsReader.partialfrequencies[i] << ", " << mySpearTextPartialsReader.partialamplitudes[i] << "\n";
			}
			*tableData++ = sinesum;
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

#pragma message("C++11 Support not available - SimpleInstrumentTableLookupSPEARSynth disabled")

#endif
	}
};

TONIC_REGISTER_SYNTH(SimpleInstrumentTableLookupSPEARSynth)

#endif
