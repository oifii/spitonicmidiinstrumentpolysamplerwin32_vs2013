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

#ifndef StepSequencerBufferPlayerExpSynth_h
#define StepSequencerBufferPlayerExpSynth_h

#include "Tonic.h"
#include <functional>

#include <sndfile.hh>

using namespace Tonic;

#define INT_TO_STRING( x ) dynamic_cast< std::ostringstream & >( \
	(std::ostringstream() << std::dec << x)).str()

class StepSequencerBufferPlayerExpSynth : public Synth{

public:
	StepSequencerBufferPlayerExpSynth(){

		//#if TONIC_HAS_CPP_11
#if 1
		const int NUM_STEPS = 8;

		// synth paramters are like instance variables -- they're values you can set later, by calling synth.setParameter()
		ControlGenerator bpm = addParameter("tempo", 80).min(50).max(300);

		// ControlMetro generates a "trigger" message at a given bpm. We multiply it by four because we
		// want four 16th notes for every beat
		ControlGenerator metro = ControlMetro().bpm(4 * bpm);

		// ControlStepper increments a value every time it's triggered, and then starts at the beginning again
		// Here, we're using it to move forward in the sequence
		ControlGenerator step = ControlStepper().end(NUM_STEPS).trigger(metro);

		// ControlSwitcher holds a list of ControlGenerators, and routes whichever one the inputIndex is pointing
		// to to its output.
		ControlSwitcher track1volumes = ControlSwitcher().inputIndex(step);

		//SampleTable buffer = loadAudioFile("D:\\oifii-org\\httpdocs\\ha-org\\had\\dj-oifii\\BASSDRUMS (House Minimal Trance D&B Techno) PACK 1\\BD (1).wav",2);
		SndfileHandle file1;
		file1 = SndfileHandle("D:\\oifii-org\\httpdocs\\ha-org\\had\\dj-oifii\\BASSDRUMS (House Minimal Trance D&B Techno) PACK 1\\BD (1).wav");
		//file1 = SndfileHandle("D:\\oifii-org\\httpdocs\\ha-org\\had\\dj-oifii\\BASSDRUMS (House Minimal Trance D&B Techno) PACK 1\\BD (9).wav");
		assert(file1.samplerate() == 44100);
		assert(file1.channels() == 2);
		SampleTable buffer1(file1.frames(), file1.channels());
		file1.read(buffer1.dataPointer(), file1.frames()*file1.channels());
		BufferPlayer bPlayer1;
		//bPlayer.setBuffer(buffer).loop(false).trigger(ControlMetro().bpm(120));
		//bPlayer.setBuffer(buffer).loop(false).trigger(ControlMetro().bpm(bpm));
		bPlayer1.setBuffer(buffer1).loop(false);

		ControlGenerator track1volume1 = addParameter("track1volume1", 1.0f).min(0.0f).max(1.0f);
		ControlGenerator track1volume2 = addParameter("track1volume2", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track1volume3 = addParameter("track1volume3", 1.0f).min(0.0f).max(1.0f);
		ControlGenerator track1volume4 = addParameter("track1volume4", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track1volume5 = addParameter("track1volume5", 1.0f).min(0.0f).max(1.0f);
		ControlGenerator track1volume6 = addParameter("track1volume6", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track1volume7 = addParameter("track1volume7", 1.0f).min(0.0f).max(1.0f);
		ControlGenerator track1volume8 = addParameter("track1volume8", 0.0f).min(0.0f).max(1.0f);
		track1volumes.addInput(track1volume1);
		track1volumes.addInput(track1volume2);
		track1volumes.addInput(track1volume3);
		track1volumes.addInput(track1volume4);
		track1volumes.addInput(track1volume5);
		track1volumes.addInput(track1volume6);
		track1volumes.addInput(track1volume7);
		track1volumes.addInput(track1volume8);

		// ControlSwitcher holds a list of ControlGenerators, and routes whichever one the inputIndex is pointing to to its output.
		ControlSwitcher track2volumes = ControlSwitcher().inputIndex(step);

		SndfileHandle file2;
		file2 = SndfileHandle("D:\\oifii-org\\httpdocs\\ha-org\\had\\dj-oifii\\Function.Loops.Spirit.Progressive.Trance.and.Psy.WAV\\DRUMS\\DRUM_01_HIHAT_138bpm(single-128ms).wav");
		assert(file2.samplerate() == 44100);
		assert(file2.channels() == 2);
		SampleTable buffer2(file2.frames(), file2.channels());
		file2.read(buffer2.dataPointer(), file2.frames()*file2.channels());
		BufferPlayer bPlayer2;
		//bPlayer2.setBuffer(buffer2).loop(false).trigger(ControlMetro().bpm(120 * 4));
		//bPlayer2.setBuffer(buffer2).loop(false).trigger(metro);
		bPlayer2.setBuffer(buffer2).loop(false);

		ControlGenerator track2volume1 = addParameter("track2volume1", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track2volume2 = addParameter("track2volume2", 1.0f).min(0.0f).max(1.0f);
		ControlGenerator track2volume3 = addParameter("track2volume3", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track2volume4 = addParameter("track2volume4", 1.0f).min(0.0f).max(1.0f);
		ControlGenerator track2volume5 = addParameter("track2volume5", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track2volume6 = addParameter("track2volume6", 1.0f).min(0.0f).max(1.0f);
		ControlGenerator track2volume7 = addParameter("track2volume7", 0.0f).min(0.0f).max(1.0f);
		ControlGenerator track2volume8 = addParameter("track2volume8", 1.0f).min(0.0f).max(1.0f);
		track2volumes.addInput(track2volume1);
		track2volumes.addInput(track2volume2);
		track2volumes.addInput(track2volume3);
		track2volumes.addInput(track2volume4);
		track2volumes.addInput(track2volume5);
		track2volumes.addInput(track2volume6);
		track2volumes.addInput(track2volume7);
		track2volumes.addInput(track2volume8);

		//Generator gen = bPlayer.trigger(metro) * bufferplayervolumes.smoothed();
		//Generator gen = bPlayer2.trigger(metro) * bufferplayervolumes.smoothed();
		Generator track1 = bPlayer1.trigger(metro) * track1volumes;
		Generator track2 = bPlayer2.trigger(metro) * track2volumes;

		/*
		StereoDelay delay = StereoDelay(3.0f, 3.0f)
			.delayTimeLeft(0.5 + SineWave().freq(0.2) * 0.01)
			.delayTimeRight(0.55 + SineWave().freq(0.23) * 0.01)
			//.feedback(0.3)
			.feedback(0.7)
			.dryLevel(0.8)
			//.wetLevel(0.2);
			.wetLevel(0.8);
			setOutputGen(track1+delay.input(track2));
			*/
		setOutputGen(track1 + track2);

		//setOutputGen(bPlayer + bPlayer2); //works
		//setLimitOutput(false);
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

#pragma message("C++11 Support not available - StepSequencerBufferPlayerExpSynth disabled")

#endif
	}
};

TONIC_REGISTER_SYNTH(StepSequencerBufferPlayerExpSynth)

#endif
