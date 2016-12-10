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

#ifndef StepSequencerBufferPlayerEffectExpSynth_h
#define StepSequencerBufferPlayerEffectExpSynth_h

#include "Tonic.h"
#include <functional>

#include <sndfile.hh>

using namespace Tonic;

#define INT_TO_STRING( x ) dynamic_cast< std::ostringstream & >( \
	(std::ostringstream() << std::dec << x)).str()

class StepSequencerBufferPlayerEffectExpSynth : public Synth{

public:
	StepSequencerBufferPlayerEffectExpSynth(){

		//#if TONIC_HAS_CPP_11
#if 1
		const int NUM_STEPS = 8;

		//SampleTable buffer = loadAudioFile("D:\\oifii-org\\httpdocs\\ha-org\\had\\dj-oifii\\worldaudio_wav\\00min15sec-and-less\\Geoffrey Oryema - TAO -  mara(introlater)_9sec.wav",2);
		SndfileHandle file1;
		file1 = SndfileHandle("D:\\oifii-org\\httpdocs\\ha-org\\had\\dj-oifii\\worldaudio_wav\\00min15sec-and-less\\Geoffrey Oryema - TAO -  mara(introlater)_9sec.wav");
		//file1 = SndfileHandle("D:\\oifii-org\\httpdocs\\ha-org\\had\\dj-oifii\\worldaudio_wav\\00min30sec-and-less\\GF - Subramanian - track 03(intro)_18sec.wav");
		assert(file1.samplerate() == 44100);
		assert(file1.channels() == 2);
		SampleTable buffer1(file1.frames(), file1.channels());
		file1.read(buffer1.dataPointer(), file1.frames()*file1.channels());
		BufferPlayer bPlayer1;
		bPlayer1.setBuffer(buffer1).loop(false);

		float file1duration_s = ((float)file1.frames()) / ((float)file1.samplerate());
		float file1duration_bpm = 60.f/file1duration_s;
		// synth paramters are like instance variables -- they're values you can set later, by calling synth.setParameter()
		ControlGenerator bpm = addParameter("tempo", file1duration_bpm).min(file1duration_bpm).max(10.f*file1duration_bpm);
		//ControlGenerator bpm = addParameter("tempo", 80).min(50).max(300);

		// Send a trigger message immediately, don't wait for the first beat to happen with the metrenome 
		ControlTrigger initialTrigger;
		initialTrigger.trigger();

		// ControlMetro generates a "trigger" message at a given bpm. 
		ControlGenerator metro = initialTrigger + ControlMetro().bpm(bpm);

		// ControlStepper increments a value every time it's triggered, and then starts at the beginning again
		// Here, we're using it to move forward in the sequence
		ControlGenerator step = ControlStepper().end(NUM_STEPS).trigger(metro);

		// ControlSwitcher holds a list of ControlGenerators, and routes whichever one the inputIndex is pointing to to its output.
		ControlSwitcher track1volumes = ControlSwitcher().inputIndex(step);
		ControlGenerator track1volume1 = addParameter("track1volume1", 1.0f).min(0.0f).max(1.0f);
		ControlGenerator track1volume2 = addParameter("track1volume2", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track1volume3 = addParameter("track1volume3", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track1volume4 = addParameter("track1volume4", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track1volume5 = addParameter("track1volume5", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track1volume6 = addParameter("track1volume6", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track1volume7 = addParameter("track1volume7", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track1volume8 = addParameter("track1volume8", 0.0f).min(0.0f).max(1.0f);
		track1volumes.addInput(track1volume1);
		track1volumes.addInput(track1volume2);
		track1volumes.addInput(track1volume3);
		track1volumes.addInput(track1volume4);
		track1volumes.addInput(track1volume5);
		track1volumes.addInput(track1volume6);
		track1volumes.addInput(track1volume7);
		track1volumes.addInput(track1volume8);
		Generator track1 = bPlayer1.trigger(metro) * track1volumes;

		// ControlSwitcher holds a list of ControlGenerators, and routes whichever one the inputIndex is pointing to to its output.
		ControlSwitcher track2volumes = ControlSwitcher().inputIndex(step);
		ControlGenerator track2volume1 = addParameter("track2volume1", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track2volume2 = addParameter("track2volume2", 1.0f).min(0.0f).max(1.0f);
		ControlGenerator track2volume3 = addParameter("track2volume3", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track2volume4 = addParameter("track2volume4", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track2volume5 = addParameter("track2volume5", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track2volume6 = addParameter("track2volume6", 1.0f).min(0.0f).max(1.0f);
		ControlGenerator track2volume7 = addParameter("track2volume7", 1.0f).min(0.0f).max(1.0f);
		ControlGenerator track2volume8 = addParameter("track2volume8", 1.0f).min(0.0f).max(1.0f);
		track2volumes.addInput(track2volume1);
		track2volumes.addInput(track2volume2);
		track2volumes.addInput(track2volume3);
		track2volumes.addInput(track2volume4);
		track2volumes.addInput(track2volume5);
		track2volumes.addInput(track2volume6);
		track2volumes.addInput(track2volume7);
		track2volumes.addInput(track2volume8);
		Generator track2 = bPlayer1.trigger(metro) * track2volumes;

		// ControlSwitcher holds a list of ControlGenerators, and routes whichever one the inputIndex is pointing to to its output.
		ControlSwitcher track3volumes = ControlSwitcher().inputIndex(step);
		ControlGenerator track3volume1 = addParameter("track3volume1", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track3volume2 = addParameter("track3volume2", 1.0f).min(0.0f).max(1.0f);
		ControlGenerator track3volume3 = addParameter("track3volume3", 1.0f).min(0.0f).max(1.0f);
		ControlGenerator track3volume4 = addParameter("track3volume4", 1.0f).min(0.0f).max(1.0f);
		ControlGenerator track3volume5 = addParameter("track3volume5", 1.0f).min(0.0f).max(1.0f);
		ControlGenerator track3volume6 = addParameter("track3volume6", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track3volume7 = addParameter("track3volume7", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track3volume8 = addParameter("track3volume8", 0.0f).min(0.0f).max(1.0f);
		track3volumes.addInput(track3volume1);
		track3volumes.addInput(track3volume2);
		track3volumes.addInput(track3volume3);
		track3volumes.addInput(track3volume4);
		track3volumes.addInput(track3volume5);
		track3volumes.addInput(track3volume6);
		track3volumes.addInput(track3volume7);
		track3volumes.addInput(track3volume8);
		Generator track3 = bPlayer1.trigger(metro) * track3volumes;

		// ControlSwitcher holds a list of ControlGenerators, and routes whichever one the inputIndex is pointing to to its output.
		ControlSwitcher track4volumes = ControlSwitcher().inputIndex(step);
		ControlGenerator track4volume1 = addParameter("track4volume1", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track4volume2 = addParameter("track4volume2", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track4volume3 = addParameter("track4volume3", 1.0f).min(0.0f).max(1.0f);
		ControlGenerator track4volume4 = addParameter("track4volume4", 1.0f).min(0.0f).max(1.0f);
		ControlGenerator track4volume5 = addParameter("track4volume5", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track4volume6 = addParameter("track4volume6", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track4volume7 = addParameter("track4volume7", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track4volume8 = addParameter("track4volume8", 0.0f).min(0.0f).max(1.0f);
		track4volumes.addInput(track4volume1);
		track4volumes.addInput(track4volume2);
		track4volumes.addInput(track4volume3);
		track4volumes.addInput(track4volume4);
		track4volumes.addInput(track4volume5);
		track4volumes.addInput(track4volume6);
		track4volumes.addInput(track4volume7);
		track4volumes.addInput(track4volume8);
		Generator track4 = bPlayer1.trigger(metro) * track4volumes;

		// ControlSwitcher holds a list of ControlGenerators, and routes whichever one the inputIndex is pointing to to its output.
		ControlSwitcher track5volumes = ControlSwitcher().inputIndex(step);
		ControlGenerator track5volume1 = addParameter("track5volume1", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track5volume2 = addParameter("track5volume2", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track5volume3 = addParameter("track5volume3", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track5volume4 = addParameter("track5volume4", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track5volume5 = addParameter("track5volume5", 1.0f).min(0.0f).max(1.0f);
		ControlGenerator track5volume6 = addParameter("track5volume6", 1.0f).min(0.0f).max(1.0f);
		ControlGenerator track5volume7 = addParameter("track5volume7", 1.0f).min(0.0f).max(1.0f);
		ControlGenerator track5volume8 = addParameter("track5volume8", 1.0f).min(0.0f).max(1.0f);
		track5volumes.addInput(track5volume1);
		track5volumes.addInput(track5volume2);
		track5volumes.addInput(track5volume3);
		track5volumes.addInput(track5volume4);
		track5volumes.addInput(track5volume5);
		track5volumes.addInput(track5volume6);
		track5volumes.addInput(track5volume7);
		track5volumes.addInput(track5volume8);
		Generator track5 = bPlayer1.trigger(metro) * track5volumes;

		///////////////
		//effect track1
		///////////////
		//no effect on track 1

		///////////////
		//effect track2
		///////////////
		StereoDelay effect2 = StereoDelay(3.0f, 3.0f)
		.delayTimeLeft(0.5 + SineWave().freq(0.2) * 0.01)
		.delayTimeRight(0.55 + SineWave().freq(0.23) * 0.01)
		//.feedback(0.3)
		.feedback(0.7)
		.dryLevel(0.2)
		//.dryLevel(0.8)
		//.wetLevel(0.2);
		.wetLevel(0.8);

		///////////////
		//effect track3
		///////////////
		HPF24 effect3 = HPF24()
			//.cutoff(5000 + SineWave().freq(1.0) * 5000)
			.cutoff(6000 + SineWave().freq(1.0) * 5000)
		.Q(0.1);

		///////////////
		//effect track4
		///////////////
		/*
		ControlParameter dry = addParameter("dry",-6.f).displayName("Dry Level (dbFS)").min(-60.f).max(0.f);
		ControlParameter wet = addParameter("wet",-20.f).displayName("Wet Level (dbFS)").min( -60.f).max(0.f);
		ControlParameter time = addParameter("decayTime", 1.0f).displayName("Decay Time (s)").min(0.1f).max(10.f);
		ControlParameter lowDecay = addParameter("lowDecay", 16000.0f).displayName("Decay Lowpass Cutoff (Hz)").min(4000.0f).max(20000.0f);
		ControlParameter hiDecay = addParameter("hiDecay",20.0f).displayName("Decay Highpass Cutoff (Hz)").min(20.f).max(250.f);
		ControlParameter preDelay = addParameter("preDelay", 0.001f).displayName("Pre-delay").min(0.001f).max(0.05f);
		ControlParameter inputLPF = addParameter("inputLPF",18000.f).displayName("Input LPF cutoff (Hz)").min(4000.0f).max(20000.0f);
		ControlParameter inputHPF = addParameter("inputHPF",20.f).displayName("Input HPF cutoff (Hz)").min(20.f).max(250.f);
		ControlParameter density = addParameter("density",0.5f).displayName("Density");
		ControlParameter shape = addParameter("shape",0.5f).displayName("Shape");
		ControlParameter size = addParameter("size",0.5f).displayName("Room Size");
		ControlParameter stereo = addParameter("stereo",0.5f).displayName("Stereo Width");
		*/
		Reverb effect4 = Reverb()
			.preDelayTime(0.001f)
			.inputLPFCutoff(18000.f)
			.inputHPFCutoff(20.f)
			.decayTime(1.f)
			.decayLPFCutoff(16000.0f)
			.decayHPFCutoff(20.0f)
			.stereoWidth(0.5f)
			.density(0.5f)
			.roomShape(0.5f)
			.roomSize(0.5f)
			.dryLevel(ControlDbToLinear().input(-6.f))
			.wetLevel(ControlDbToLinear().input(-20.f));

		///////////////
		//effect track5
		///////////////
		LPF24 effect5 = LPF24()
			.cutoff(5000 + SineWave().freq(1.0) * 5000)
			//.cutoff(6000 + SineWave().freq(1.0) * 5000)
			.Q(0.1);


		setOutputGen(track1 + effect2.input(track2) + effect3.input(track3) + effect4.input(track4) + effect5.input(track5));
		//setOutputGen(track1);

		//Generator tone = SawtoothWave().freq(50);
		//setOutputGen(tone); //works

		/*
		const int NUM_STEPS = 8;

		// synth paramters are like instance variables -- they're values you can set later, by
		// calling synth.setParameter()
		ControlGenerator bpm = addParameter("tempo", 100).min(50).max(300);
		ControlGenerator transpose = addParameter("transpose", 0).min(-6).max(6);

		// ControlMetro generates a "trigger" message at a given bpm. We multiply it by four because we
		// want four 16th notes for every beat
		ControlGenerator metro = ControlMetro().bpm(4 * bpm);

		// ControlStepper increments a value every time it's triggered, and then starts at the beginning again
		// Here, we're using it to move forward in the sequence
		ControlGenerator step = ControlStepper().end(NUM_STEPS).trigger(metro);

		// ControlSwitcher holds a list of ControlGenerators, and routes whichever one the inputIndex is pointing
		// to to its output.
		ControlSwitcher pitches = ControlSwitcher().inputIndex(step);
		ControlSwitcher cutoffs = ControlSwitcher().inputIndex(step);
		ControlSwitcher glides = ControlSwitcher().inputIndex(step);

		// stick a bunch of random values into the pitch and cutoff lists
		for (int i = 0; i < NUM_STEPS; i++){
		ControlGenerator pitchForThisStep = addParameter("step" + INT_TO_STRING(i) + "Pitch", randomFloat(10, 80)).min(10).max(80);
		pitches.addInput(pitchForThisStep);

		ControlGenerator cutoff = addParameter("step" + INT_TO_STRING(i) + "Cutoff", 500).min(30).max(1500);
		cutoffs.addInput(cutoff);

		ControlGenerator glide = addParameter("step" + INT_TO_STRING(i) + "Glide", 0).min(0).max(0.1);
		glides.addInput(glide);

		}

		// Define a scale according to steps in a 12-note octave. This is a pentatonic scale. Like using
		// just the black keys on a piano
		vector<float> scale;
		scale.push_back(0);
		scale.push_back(2);
		scale.push_back(3);
		scale.push_back(5);
		scale.push_back(7);
		scale.push_back(10);

		// ControlSnapToScale snaps a float value to the nearest scale value, no matter what octave its in
		ControlGenerator midiNote = transpose + ControlSnapToScale().setScale(scale).input(pitches);

		ControlGenerator frequencyInHertz = ControlMidiToFreq().input(midiNote);

		// now that we've done all that, we have a frequency signal that's changing 4x per beat
		//Generator tone = RectWave().freq(frequencyInHertz.smoothed().length(glides));
		//Generator tone = SineWave().freq(frequencyInHertz.smoothed().length(glides));
		Generator tone = SawtoothWave().freq(frequencyInHertz.smoothed().length(glides));

		// create an amplitude signal with an ADSR envelope, and scale it down a little so it's not scary loud
		Generator amplitude = ADSR(0.01, 0.1, 0, 0).trigger(metro) * 0.3;

		// create a filter, and feed the cutoff sequence in to it
		LPF24 filter = LPF24().cutoff(cutoffs).Q(0.1);
		filter.input(tone * amplitude);

		// rout the output of the filter to the synth's main output
		setOutputGen(filter);
		//setOutputGen(tone * amplitude);
		*/

#else

#pragma message("C++11 Support not available - StepSequencerBufferPlayerEffectExpSynth disabled")

#endif
	}
};

TONIC_REGISTER_SYNTH(StepSequencerBufferPlayerEffectExpSynth)

#endif
