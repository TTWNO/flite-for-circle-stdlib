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
#include "sound.h"
extern "C" {
#include "flite.h"
}

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <exception>
#include <memory>
#include <cassert>

#define SOUND_SAMPLES		(sizeof Sound / sizeof Sound[0] / SOUND_CHANNELS)

extern "C" {
void usenglish_init(cst_voice *v);
cst_lexicon *cmulex_init(void);

void cmu_grapheme_lang_init(cst_voice *v);
cst_lexicon *cmu_grapheme_lex_init(void);

void flite_set_lang_list(void)
{
   flite_add_lang("eng",usenglish_init,cmulex_init);
   flite_add_lang("usenglish",usenglish_init,cmulex_init);
}

}

CKernel::CKernel (void)
:	CStdlibAppStdio("06-tts"),
	mSound(&mInterrupt)
{
	mActLED.Blink (5);	// show we are alive
}


static void flite_voice_list_print(void)
{
    cst_voice *voice;
    const cst_val *v;

    printf("Voices available: ");
    for (v=flite_voice_list; v; v=val_cdr(v))
    {
        voice = val_voice(val_car(v));
        printf("%s ",voice->name);
    }
    printf("\n");

    return;
}

CStdlibApp::TShutdownMode CKernel::Run (void)
{
	mActLED.Blink (5);	// show we are alive
	mLogger.Write (GetKernelName (), LogNotice, "C++ Standard Library Demo");
	mActLED.Blink (5);	// show we are alive

	int tts_ret = flite_init();
	flite_set_lang_list();
	cst_voice* voice = flite_voice_load("cmu_us_slt.flitevox");
	// maigc property that sets the rate of flite voices
	flite_feat_set_float(voice->features, "duration_stretch", 0.4);
	flite_add_voice(voice);
	flite_voice_list_print();
	char msg[100] = {0};
	sprintf(msg, "TTS: %d, LL: %d\n", tts_ret, flite_lang_list_length);
	mLogger.Write (GetKernelName (), LogNotice, msg);

	cst_wave* wave = flite_text_to_wave("Welcome to the new world of TTS on bare-metal hardware!", voice);
	cst_wave_resample(wave, 44100);
	mSound.Playback(wave->samples, wave->num_samples, 1, 16);
	for (unsigned nCount = 0; mSound.PlaybackActive (); nCount++)
	{
		mScreen.Rotor (0, nCount);
	}

	mActLED.Blink (5);	// show we are alive
	mLogger.Write (GetKernelName (), LogNotice, "C++ Standard Library Test finished");
	mActLED.Blink (5);	// show we are alive

	return ShutdownHalt;
}
