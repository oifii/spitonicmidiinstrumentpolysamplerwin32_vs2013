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

#include "PolySynth.h"

//spi, begin
#include "SuperBufferPlayer.h"
extern SuperBufferPlayer* global_psuperplayer;
//spi, begin

void BasicPolyphonicAllocator::addVoice(Synth synth)
{
    PolyVoice v;
    v.synth = synth;
    v.currentNote = 0;

    inactiveVoiceQueue.push_back(voiceData.size());
    voiceData.push_back(v);
}

void BasicPolyphonicAllocator::noteOn(int note, int velocity)
{
    int voiceNumber = getNextVoice(note);

    if (voiceNumber < 0)
        return; // no voice available

    cout << ">> " << "Starting note " << note << " on voice " << voiceNumber << "\n";

    PolyVoice& voice = voiceData[voiceNumber];

	//spi, begin
	global_psuperplayer[voiceNumber].setBuffer(note);
	//spi, end
    voice.synth.setParameter("polyNote", note);
    voice.synth.setParameter("polyGate", 1.0);
    voice.synth.setParameter("polyVelocity", velocity);
    voice.synth.setParameter("polyVoiceNumber", voiceNumber);

    voice.currentNote = note;

    activeVoiceQueue.remove(voiceNumber);
    activeVoiceQueue.push_back(voiceNumber);
    inactiveVoiceQueue.remove(voiceNumber);
}

void BasicPolyphonicAllocator::noteOff(int note)
{
    // clear the oldest active voice with this note number
    for (int voiceNumber : activeVoiceQueue)
    {
        PolyVoice& voice = voiceData[voiceNumber];
        if (voice.currentNote == note)
        {
            cout << ">> " << "Stopping note " << note << " on voice " << voiceNumber << "\n";

            voice.synth.setParameter("polyGate", 0.0);

            activeVoiceQueue.remove(voiceNumber);
            inactiveVoiceQueue.remove(voiceNumber);
            inactiveVoiceQueue.push_back(voiceNumber);

            break;
        }
    }
}

int BasicPolyphonicAllocator::getNextVoice(int note)
{
    // Find a voice not playing any note
    if (inactiveVoiceQueue.size())
    {
        return inactiveVoiceQueue.front();
    }

    return -1;
}

int OldestNoteStealingPolyphonicAllocator::getNextVoice(int note)
{
    int voice = BasicPolyphonicAllocator::getNextVoice(note);
    if (voice >= 0)
        return voice;

    if (activeVoiceQueue.size())
    {
        return activeVoiceQueue.front();
    }

    return -1;
}

int LowestNoteStealingPolyphonicAllocator::getNextVoice(int note)
{
    int voice = BasicPolyphonicAllocator::getNextVoice(note);
    if (voice >= 0)
        return voice;

    // Find the playing voice with the lowest note that's lower than the requested note
    int lowestNote = note;
    int lowestVoice = -1;
    for (int voiceNumber : activeVoiceQueue)
    {
        PolyVoice& voice = voiceData[voiceNumber];
        if (voice.currentNote < lowestNote)
        {
            lowestNote = voice.currentNote;
            lowestVoice = voiceNumber;
        }
    }

    return lowestVoice;
}