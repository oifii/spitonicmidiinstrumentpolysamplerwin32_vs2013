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

#ifndef FilterExpSynth_h
#define FilterExpSynth_h

#include "Tonic.h"
#include <functional>

#include <sndfile.hh>

using namespace Tonic;

#define INT_TO_STRING( x ) dynamic_cast< std::ostringstream & >( \
	(std::ostringstream() << std::dec << x)).str()

class FilterExpSynth : public Synth{

public:
	FilterExpSynth(){

		//#if TONIC_HAS_CPP_11
#if 1
		const int NUM_STEPS = 8;

		//SampleTable buffer = loadAudioFile("D:\\oifii-org\\httpdocs\\ha-org\\had\\dj-oifii\\worldaudio_wav\\00min15sec-and-less\\Geoffrey Oryema - TAO -  mara(introlater)_9sec.wav",2);
		SndfileHandle file1;
		//file1 = SndfileHandle("D:\\oifii-org\\httpdocs\\ha-org\\had\\dj-oifii\\worldaudio_wav\\00min15sec-and-less\\Geoffrey Oryema - TAO -  mara(introlater)_9sec.wav");
		file1 = SndfileHandle("D:\\oifii-org\\httpdocs\\ha-org\\had\\dj-oifii\\worldaudio_wav\\00min30sec-and-less\\GF - Subramanian - track 03(intro)_18sec.wav");
		assert(file1.samplerate() == 44100);
		assert(file1.channels() == 2);
		SampleTable buffer1(file1.frames(), file1.channels());
		file1.read(buffer1.dataPointer(), file1.frames()*file1.channels());
		BufferPlayer bPlayer1;
		bPlayer1.setBuffer(buffer1).loop(false);

		float file1duration_s = ((float)file1.frames()) / ((float)file1.samplerate());
		float file1duration_bpm = 60.f / file1duration_s;
		// synth paramters are like instance variables -- they're values you can set later, by calling synth.setParameter()
		ControlGenerator bpm = addParameter("tempo", file1duration_bpm).min(file1duration_bpm).max(10.f*file1duration_bpm);
		//ControlGenerator bpm = addParameter("tempo", 80).min(50).max(300);

		// Send a trigger message immediately, don't wait for the first beat to happen with the metrenome 
		ControlTrigger initialTrigger;
		initialTrigger.trigger();

		// ControlMetro generates a "trigger" message at a given bpm. 
		ControlGenerator metro = initialTrigger + ControlMetro().bpm(bpm);


		ControlGenerator track1volume1 = addParameter("track1volume1", 1.0f).min(0.0f).max(1.0f);
		Generator track1 = bPlayer1.trigger(metro) * track1volume1;


		StereoDelay stereodelay = StereoDelay(3.0f, 3.0f)
			.delayTimeLeft(0.5 + SineWave().freq(0.2) * 0.01)
			.delayTimeRight(0.55 + SineWave().freq(0.23) * 0.01)
			//.feedback(0.3)
			.feedback(0.7)
			.dryLevel(0.2)
			//.dryLevel(0.8)
			//.wetLevel(0.2);
			.wetLevel(0.8);

		StereoDelay stereodelay2 = StereoDelay(3.0f, 3.0f)
			.delayTimeLeft(0.5 + SineWave().freq(0.2) * 0.01)
			.delayTimeRight(0.55 + SineWave().freq(0.23) * 0.01)
			//.feedback(0.3)
			.feedback(0.5 + SineWave().freq(1) * 0.3)
			.dryLevel(0.2)
			//.dryLevel(0.8)
			//.wetLevel(0.2);
			.wetLevel(0.8);

		HPF24 hpfilter = HPF24()
			.cutoff(5000 + SineWave().freq(0.1) * 5000)
			//.cutoff(6000 + SineWave().freq(1.0) * 5000)
			.Q(0.1);

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
		Reverb reverb = Reverb()
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

		Reverb reverb2 = Reverb()
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
			.dryLevel(0.2) //.dryLevel(ControlDbToLinear().input(-20.f))
			.wetLevel(0.2);//.wetLevel(ControlDbToLinear().input(-6.f));

		LPF24 lpfilter = LPF24()
			.cutoff(5000 + SineWave().freq(1.0) * 5000)
			//.cutoff(6000 + SineWave().freq(1.0) * 5000)
			.Q(0.1);


		//setOutputGen(lpfilter.input(track1));
		//setOutputGen(hpfilter.input(track1) + reverb2.input(track1)*0.3 + stereodelay2.input(track1)*0.3);
		setOutputGen(hpfilter.input(track1) + reverb2.input(track1)*randomFloat(0.1, 0.5) + stereodelay2.input(track1)*randomFloat(0.1, 0.5));
		//setOutputGen(stereodelay.input(track1));
		//setOutputGen(stereodelay2.input(track1));
		//setOutputGen(reverb2.input(track1));
		//setOutputGen(track1);

		//Generator tone = SawtoothWave().freq(50);
		//setOutputGen(tone); //works



#else

#pragma message("C++11 Support not available - FilterExpSynth disabled")

#endif
	}
};

TONIC_REGISTER_SYNTH(FilterExpSynth)

#endif
