#ifndef _GMW_BANK_
#define _GMW_BANK_

#include "GMWConfig.h"

extern "C"
{
	// Fermeture de toute les banques.
	void GMWClearBanks(void);

	// Definie le chemin ou se trouve les banques sonores.
	// banks_path Chemin du dossier ou ce trouve les banques sonores.
	// Renvoie 0 sinon un code d'erreur.
	GMW_API double STDCALL GMWSetBasePath(const char* banks_path);

	// Definie le sous repertoire de langue.
	// lng_path Chemin du sous repertoire de langue.
	// Renvoie 0 sinon un code d'erreur.
	GMW_API double STDCALL GMWSetLangSpecificDirName(const char* lng_path);

	// Chargement de la banque.
	// bank_id Nom de la banque.
	// Renvoie l'identifiant de la banque sinon un code d'erreur.
	GMW_API double STDCALL GMWLoadBank(const char* bank_name);

	// Dechargement de la banque.
	// bank_id Identifiant de la banque.
	// Renvoie 0 sinon un code d'erreur.
	GMW_API double STDCALL GMWUnloadBank(double bank_id);
}

#endif // _GMW_BANK_
