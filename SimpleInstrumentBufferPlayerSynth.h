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

#ifndef SimpleInstrumentBufferPlayerSynth_h
#define SimpleInstrumentBufferPlayerSynth_h

#include "Tonic.h"
#include <functional>

#include <sndfile.hh>

using namespace Tonic;

class SimpleInstrumentBufferPlayerSynth : public Synth{

public:
	SimpleInstrumentBufferPlayerSynth(){

		//#if TONIC_HAS_CPP_11
#if 1
		/*
		Generators and ControlGenerators both output a steady stream of data.
		Generators output at the sample rate (in this case, 44100 hertz.
		ControlGenerators output at the control rate, which is much lower than the sample rate.
		*/
		//1) load a sample file
		//SampleTable buffer = loadAudioFile("D:\\oifii-org\\httpdocs\\ha-org\\had\\dj-oifii\\worldaudio_wav\\00min15sec-and-less\\Geoffrey Oryema - TAO -  mara(introlater)_9sec.wav",2);
		SndfileHandle file1;
		//file1 = SndfileHandle("D:\\oifii-org\\httpdocs\\ha-org\\had\\dj-oifii\\worldaudio_wav\\00min15sec-and-less\\Geoffrey Oryema - TAO -  mara(introlater)_9sec.wav");
		file1 = SndfileHandle("D:\\oifii-org\\httpdocs\\ha-org\\had\\dj-oifii\\worldaudio_wav\\00min30sec-and-less\\GF - Subramanian - track 03(intro)_18sec.wav");
		assert(file1.samplerate() == 44100);
		assert(file1.channels() == 2);
		float file1duration_s = ((float)file1.frames()) / ((float)file1.samplerate());
		SampleTable buffer1(file1.frames(), file1.channels());
		file1.read(buffer1.dataPointer(), file1.frames()*file1.channels());
		BufferPlayer bPlayer1;
		bPlayer1.setBuffer(buffer1).loop(false);

		//2) define a midi note control generator
		// create a named parameter on the synth which we can set at runtime
		ControlGenerator midiNote = addParameter("midiNote");
		ControlGenerator midiNoteVelocity = addParameter("midiNoteVelocity");

		//3) define a note frequency control generator
		// convert a midi note to a frequency (plugging that parameter into another object)
		ControlGenerator noteFreq = ControlMidiToFreq().input(midiNote);

		/*
		// Here's the actual noise-making object
		Generator tone = SawtoothWave().freq(noteFreq);
		//Generator tone = SineWave().freq(noteFreq); //original
		//Generator tone = LFNoise().setFreq(noteFreq);
		*/
		//4) define a envelop trigger control generator
		ControlGenerator envelopeTrigger = addParameter("trigger");

		//5) define a tone generator
		Generator tone = bPlayer1.trigger(envelopeTrigger); //good
		//Generator tone = PinkNoise(); //file1duration_s = 1.5;
		//Generator tone = LFNoise().setFreq(noteFreq); //file1duration_s = 1.5;
		//Generator tone = SawtoothWave().freq(noteFreq); //good
		//Generator tone = SineWave().freq(noteFreq); file1duration_s = 1.5; //good

		// Let's put a filter on the tone
		//tone = LPF12().input(tone).Q(10).cutoff((noteFreq * 2) + SineWave().freq(3) * 0.5 * noteFreq); //original
		//tone = LPF12().input(tone).Q(10).cutoff((noteFreq * 2) + SineWave().freq(10) * 0.5 * noteFreq);
		//tone = LPF12().input(tone).Q(10).cutoff((noteFreq * 2) + SineWave().freq(1) * 0.5 * noteFreq);

		//6) let's put a bandpass filter on the tone
		//tone = BPF12().input(tone).Q(10).cutoff(noteFreq);
		//tone = BPF12().input(tone).Q(0.1).cutoff(noteFreq);
		//tone = BPF24().input(tone).Q(0.1).cutoff(noteFreq);
		//tone = BPF24().input(tone).Q(0.001).cutoff(noteFreq);
		//tone = BPF24().input(tone).Q(0.001).cutoff((noteFreq * 2) + SineWave().freq(10) * 0.5 * noteFreq);
		//tone = BPF24().input(tone).Q(10).cutoff((noteFreq * 2) + SineWave().freq(10) * 0.5 * noteFreq);
		//tone = BPF24().input(tone).Q(1).cutoff((noteFreq * 2) + SineWave().freq(10) * 0.5 * noteFreq); //good
		//tone = BPF24().input(tone).Q(1).cutoff((noteFreq) + SineWave().freq(10) * 0.5 * noteFreq); //good 
		//tone = BPF24().input(tone).Q(0.1).cutoff((noteFreq)+SineWave().freq(1) * 0.5 * noteFreq);  
		//tone = BPF24().input(tone).Q(0.1).cutoff((noteFreq)+SineWave().freq(127) * 0.5 * noteFreq);
		tone = BPF24().input(tone).Q(0.1).cutoff((noteFreq)+SineWave().freq(127-midiNoteVelocity) * 0.5 * noteFreq);

		// It's just a steady tone until we modulate the amplitude with an envelope
		//ControlGenerator envelopeTrigger = addParameter("trigger");
		//Generator toneWithEnvelope = tone * ADSR().attack(0.01).decay(1.5).sustain(0).release(0).trigger(envelopeTrigger).legato(true);
		Generator toneWithEnvelope = tone * ADSR().attack(0.01).decay(file1duration_s).sustain(0).release(0).trigger(envelopeTrigger).legato(true); //good
		//Generator toneWithEnvelope = tone * ADSR().attack(0.01).decay(file1duration_s*0.1).sustain(file1duration_s*0.9).release(0).trigger(envelopeTrigger).legato(true); //bad

		// let's send the tone through some delay
		//Generator toneWithDelay = StereoDelay(0.5, 0.75).input(toneWithEnvelope).wetLevel(0.1).feedback(0.2); //original
		//Generator toneWithDelay = StereoDelay(0.5, 0.75).input(toneWithEnvelope).wetLevel(0.8).feedback(0.7); //spi
		Generator toneWithDelay = StereoDelay(0.5, 0.75).input(toneWithEnvelope).wetLevel(0.8).feedback(0.2); //spi

		setOutputGen(toneWithDelay); //original
		//setOutputGen(toneWithEnvelope);

#else

#pragma message("C++11 Support not available - ControlSwitcherTestSynth disabled")

#endif
	}
};

TONIC_REGISTER_SYNTH(SimpleInstrumentBufferPlayerSynth)

#endif
