//
// kernel.cpp
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#include "kernel.h"

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <exception>
#include <memory>
#include <cassert>
#include <flite>

CKernel::CKernel (void)
:	CStdlibAppStdio("06-tts"),
	mSound(&mInterrupt)
{
	mActLED.Blink (5);	// show we are alive
}

CStdlibApp::TShutdownMode CKernel::Run (void)
{
	mActLED.Blink (5);	// show we are alive
	mLogger.Write (GetKernelName (), LogNotice, "C++ Standard Library Demo");
	mActLED.Blink (5);	// show we are alive

	//mSound.Playback(Sound, SOUND_SAMPLES, SOUND_CHANNELS, SOUND_BITS);
	for (unsigned nCount = 0; mSound.PlaybackActive (); nCount++)
	{
		mScreen.Rotor (0, nCount);
	}

	mActLED.Blink (5);	// show we are alive
	mLogger.Write (GetKernelName (), LogNotice, "C++ Standard Library Test finished");
	mActLED.Blink (5);	// show we are alive

	return ShutdownHalt;
}
