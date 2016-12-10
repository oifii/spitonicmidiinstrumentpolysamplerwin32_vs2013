
#ifndef SUPERBUFFERPLAYER_H
#define SUPERBUFFERPLAYER_H

#include "Tonic.h"

using namespace Tonic;


#define SUPERBUFFERPLAYER_NUMBEROFBUFFERS	128

class SuperBufferPlayer : public BufferPlayer{
protected:
	SampleTable _pbuffers[SUPERBUFFERPLAYER_NUMBEROFBUFFERS];
public:

	SuperBufferPlayer& setBuffers(SampleTable** pbuffers)
	{
		for (int i = 0; i < SUPERBUFFERPLAYER_NUMBEROFBUFFERS; i++)
		{
			_pbuffers[i] = *(pbuffers[i]);
		}
		gen()->setBuffer(_pbuffers[0]);
		return *this;
	};

	SuperBufferPlayer& setBuffer(ControlParameter midinotenumber)
	{
		gen()->setBuffer(_pbuffers[(int)(midinotenumber.getValue())]);
		return *this;
	};

	SuperBufferPlayer& setBuffer(int midinotenumber)
	{
		gen()->setBuffer(_pbuffers[midinotenumber]);
		return *this;
	};

};

#endif //SUPERBUFFERPLAYER_H