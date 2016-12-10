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

//
//  FMDrone.h
//  TonicDemo
//
//  Created by Nick Donaldson on 2/15/13.

//

/*
Because of the fancy TONIC_REGISTER_SYNTH macro, and because this synth has the same interface
as Synth it's not necessary to create a header file. You can create an instance of this synth using
SynthFactory::createInstance(SYNTH_NAME), where SYNTH_NAME is the name supplied to TONIC_REGISTER_SYNTH.
*/

#ifndef TonicDemo_FMDrone_h
#define TonicDemo_FMDrone_h

#include "Tonic.h"

using namespace Tonic;

class FMDroneSynth : public Synth {


public:
	FMDroneSynth(){

		//ControlParameter volume = addParameter("volume", -12.f).displayName("Volume (dbFS)").min(-60.f).max(0.f); //original
		ControlParameter volume = addParameter("volume", -0.0f).displayName("Volume (dbFS)").min(-60.f).max(0.f); //spi
		//ControlParameter carrierPitch = addParameter("carrierPitch", 28.f).displayName("Carrier Pitch").min(20.f).max(32.f); //original
		ControlParameter carrierPitch = addParameter("carrierPitch", 20.f).displayName("Carrier Pitch").min(20.f).max(64.f); //spi
		//ControlParameter modIndex = addParameter("modIndex", 0.25f).displayName("FM Amount").min(0.f).max(1.0f); //original
		ControlParameter modIndex = addParameter("modIndex", 1.0f).displayName("FM Amount").min(0.f).max(1.0f); //spi
		//ControlParameter lfoAmt = addParameter("lfoAmt", 0.5f).displayName("LFO Amount").min(0.f).max(1.f); //original
		ControlParameter lfoAmt = addParameter("lfoAmt", 1.0f).displayName("LFO Amount").min(0.f).max(1.f); //spi

		Generator rCarrierFreq = ControlMidiToFreq().input(carrierPitch).smoothed();
		Generator rModFreq = rCarrierFreq * 4.0f;

		Generator outputGen = SineWave()
			.freq(rCarrierFreq
			+ (
			SineWave().freq(rModFreq) *
			rModFreq *
			(modIndex.smoothed() * (1.0f + SineWave().freq((LFNoise().setFreq(0.5f) + 1.f) * 2.f + 0.2f) * (lfoAmt * 0.5f).smoothed()))
			)
			) * ControlDbToLinear().input(volume).smoothed() * ((SineWave().freq(0.15f) + 1.f) * 0.75f + 0.25);

		setOutputGen(outputGen);

	}

};

TONIC_REGISTER_SYNTH(FMDroneSynth);

#endif