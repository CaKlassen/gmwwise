#ifndef _GMW_ENGINE_
#define _GMW_ENGINE_

#include "GMWConfig.h"

extern "C"
{
	// Initialise Wwise.
    // Renvoie 0 sinon un code d'erreur.
	GMW_API double STDCALL GMWInit(void);

	// Ferme Wwise et libere tout les donnees
	// Renvoie toujours 0.
    GMW_API double STDCALL GMWShutdown(void);

	// Traitement des evenements.
	// A faire chaque frame.
	// Renvoie toujours 0.
    GMW_API double STDCALL GMWProcessAudio(void);

	// Definie l'etat d'un groupe d'etat.
	// stateGroup Identifiant du groupe d'etat.
	// state Identifiant du nouvel etat.
	// Renvoie 0 ou un code d'erreur.
	GMW_API double STDCALL GMWSetState(double stateGroup, double state);	

    // Enregistrement d'un plugin wwise.
    // type Type de plugin.
    // Renvoie 0 ou un code d'erreur.
    // 
    // List des types:
    // 0 Sine
    // 1 Tone Generator
    // 2 Silence
    // 3 Audio Input
    // 4 Delay
    // 5 Parametric EQ
    // 6 Matrix Reverb
    // 7 Compressor
    // 8 Expander
    // 9 Peak Limiter
    // 10 Roomverb.
    GMW_API double STDCALL GMWRegisterPlugin(double type);

    // Enregistrement d'un codec.
    // type Type de codec.
    // Renvoie 0 ou un code d'erreur.
    //
    // List des codecs:
    // 0 Vorbis
    GMW_API double STDCALL GMWRegisterCodec(double type);
}

#endif // _GMW_ENGINE_
