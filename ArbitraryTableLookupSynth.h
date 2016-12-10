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
//  ArbitraryTableLookupDemo.cpp
//  TonicDemo
//
//  Created by Nick Donaldson on 5/21/13.
//

#ifndef TonicDemo_ArbitraryTableLookupDemo_h
#define TonicDemo_ArbitraryTableLookupDemo_h

#include "Tonic.h"

using namespace Tonic;

class ArbitraryTableLookupSynth : public Synth
{
  
public:

  ArbitraryTableLookupSynth(){
    
    // Build a table of arbitrary length. TableLookupOsc requires power-of-two+1 length tables, but they will be resized if necessary.
    // Try changing this to 2049 and compare the sound. Should be perceptually almost identical.
    const unsigned int tablesize = 2500;
    
    // You can register this in a collection if you want to use it in a few oscillators
    SampleTable lookupTable = SampleTable(tablesize, 1);
    
    TonicFloat norm = 1.0f / tablesize;
    TonicFloat * tableData = lookupTable.dataPointer();
    for (unsigned int i=0; i<tablesize; i++){
      
      // sum a few sine waves
      TonicFloat phase = TWO_PI * i * norm;
      *tableData++ = 0.75f * sinf(phase) + 0.5f * sinf( phase * 2 ) + 0.25f * sinf(phase * 5);
      
    }
    
    TableLookupOsc osc = TableLookupOsc().setLookupTable(lookupTable).freq( 100 + 40 * SineWave().freq(0.1) );
    
    setOutputGen(osc * 0.25);
    
  }
  
};

TONIC_REGISTER_SYNTH(ArbitraryTableLookupSynth);

#endif

