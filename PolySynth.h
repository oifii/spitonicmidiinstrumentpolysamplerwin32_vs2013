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
//  PolySynth.cpp
//  PolyMIDIDemo
//
//  Created by Michael Dewberry on 6/7/13.
//
//

#include "Tonic.h"

using namespace Tonic;

template<typename VoiceAllocator>
class PolySynthWithAllocator : public Synth
{
public:
    PolySynthWithAllocator() : Synth() 
    {
        setOutputGen(mixer); 
    }

    void addVoice(Synth synth)
    {
        allocator.addVoice(synth);
        mixer.addInput(synth);
    }

    typedef Synth (VoiceCreateFn)();
    void addVoices(VoiceCreateFn createFn, int count)
    {
        for (int i = 0; i < count; i++)
            addVoice(createFn());
    }

    void noteOn(int note, int velocity)
    {
        allocator.noteOn(note, velocity);
    }

    void noteOff(int note)
    {
        allocator.noteOff(note);
    }

protected:
    Mixer mixer;
    VoiceAllocator allocator;
};

class BasicPolyphonicAllocator
{
public:
    class PolyVoice
    {
    public:
        int currentNote;
        Synth synth;
    };

    void addVoice(Synth synth);
    void noteOn(int noteNumber, int velocity);
    void noteOff(int noteNumber);

protected:
    virtual int getNextVoice(int note);
    vector<PolyVoice> voiceData;
    list<int> inactiveVoiceQueue;
    list<int> activeVoiceQueue;
};

class OldestNoteStealingPolyphonicAllocator : public BasicPolyphonicAllocator
{
protected:
    virtual int getNextVoice(int note);
};

class LowestNoteStealingPolyphonicAllocator : public BasicPolyphonicAllocator
{
protected:
    virtual int getNextVoice(int note);
};

typedef PolySynthWithAllocator<LowestNoteStealingPolyphonicAllocator> PolySynth;

