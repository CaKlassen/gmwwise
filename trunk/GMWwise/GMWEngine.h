#ifndef _GMW_ENGINE_
#define _GMW_ENGINE_

#include "GMWConfig.h"

extern "C"
{
	// Initialise Wwise.
    // Renvoie 0 sinon un code d'erreur.
	GMW_API double GMWInit(void);

	// Ferme Wwise et libere tout les donnees
	// Renvoie toujours 0.
    GMW_API double GMWShutdown(void);

	// Traitement des evenements.
	// A faire chaque frame.
	// Renvoie toujours 0.
    GMW_API double GMWProcessAudio(void);

	// Definie l'etat d'un groupe d'etat.
	// stateGroup Identifaint du groupe d'etat.
	// state Identifiant du nouvel etat.
	// Renvoie 0 ou un code d'erreur.
	GMW_API double GMWSetState(double stateGroup, double state);	
}

#endif // _GMW_ENGINE_
