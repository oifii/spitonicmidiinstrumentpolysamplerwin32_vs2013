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
//  CompressorTestSynth.cpp
//  TonicDemo
//
//  Created by Nick Donaldson on 3/25/13.

//


#include "Tonic.h"

using namespace Tonic;

class CompressorTestSynth : public Synth
{
  
public:
  CompressorTestSynth(){
    
    ControlParameter threshold = addParameter("threshold", -12.f).displayName("Threshold (dbFS)").min(-60.f).max(0.f);
    //ControlParameter ratio = addParameter("ratio", 2.0f).displayName("Ratio").min(1.0f).max(64.f).logarithmic(true); //original
	ControlParameter ratio = addParameter("ratio", 1.0f).displayName("Ratio").min(1.0f).max(64.f).logarithmic(true); //spi
	//ControlParameter attack = addParameter("attackTime", 0.001).displayName("Attack Time (s)").min(0.001).max(0.1).logarithmic(true); //original
	ControlParameter attack = addParameter("attackTime", 0.1).displayName("Attack Time (s)").min(0.001).max(0.1).logarithmic(true); //spi
	//ControlParameter release = addParameter("releaseTime", 0.05).displayName("Release Time (s)").min(0.01).max(0.08).logarithmic(true); //original
	ControlParameter release = addParameter("releaseTime", 0.01).displayName("Release Time (s)").min(0.01).max(0.08).logarithmic(true); //spi
    ControlParameter gain = addParameter("gain", 0.f).displayName( "Makeup Gain (dbFS)").min(0.f).max(36.0f);
	ControlParameter bypass = addParameter("bypass", false).parameterType(ControlParameterTypeToggle); //original
	//ControlParameter bypass = addParameter("bypass", true).parameterType(ControlParameterTypeToggle); //spi
    
    // Emulation of 808 snare with long, quiet noise decay
    //Generator hpNoise = (Noise() * dBToLin(-18.0)) >> HPF24().cutoff(2000.0) >> LPF12().cutoff(8000); //original
	Generator hpNoise = (Noise() * dBToLin(-2.0)) >> HPF24().cutoff(2000.0) >> LPF12().cutoff(8000); //spi
	//Generator tones = SineWave().freq(180) * dBToLin(-6.0) + SineWave().freq(332) * dBToLin(-18.0); //original
	Generator tones = SineWave().freq(180) * dBToLin(0.0) + SineWave().freq(332) * dBToLin(-2.0); //spi

    //ControlGenerator snareGate = ControlPulse(60.0*0.8/80.0).trigger( ControlMetro(80) ); //original
	ControlGenerator snareGate = ControlPulse(60.0*0.8 / 80.0).trigger(ControlMetro(140)); //spi
	//ADSR toneADSR = ADSR(0.0005, 0.03, 0.0, 0.01).trigger(snareGate); //original
	ADSR toneADSR = ADSR(0.001, 0.03, 0.0, 0.01).trigger(snareGate); //spi
	ADSR noiseADSR = ADSR(0.001, 0.25, 0.0, 0.25).trigger(snareGate); //original
  
    // Squaring gives something a bit closer to exponential
    // TODO: Exponential ADSR
    Generator noiseEnv = noiseADSR * noiseADSR;
    
    Compressor compressor = Compressor()
                            .attack(attack)
                            .release(0.06)
                            .threshold( ControlDbToLinear().input(threshold) )
                            .ratio( ratio )
                            .lookahead(0.001)
                            .makeupGain(ControlDbToLinear().input(gain))
                            .bypass(bypass);
        
    Generator outputGen = ( ( ( tones * toneADSR ) + ( hpNoise * noiseEnv ) ) >> compressor ) * 0.5;
    
    setOutputGen(outputGen);
  }
  
};

TONIC_REGISTER_SYNTH(CompressorTestSynth);