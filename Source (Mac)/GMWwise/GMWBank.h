/*
Author : cédric liaudet
URL    : http://code.google.com/p/gmwwise/

=================================================================================
This library is free software; you can redistribute it and/or modify 
it under the terms of the GNU Lesser General Public License as published
by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version. 
This library is distributed in the hope that it will be useful, but without any warranty; 
without even the implied warranty of merchantability or fitness for a particular purpose. 
See the GNU Lesser General Public License for more details.
=================================================================================
*/
#ifndef _GMW_BANK_
#define _GMW_BANK_

#include "GMWConfig.h"

extern "C"
{
	/// @brief Close every banks.
	void GMWClearBanks(void);

	/// @brief Set the path to load bank.
	///
	/// @param banks_path The path.
	///
	/// @return 0 or an error code.
	double GMWSetBasePath(const char* banks_path);

	/// @brief Define the subdirectory for language.
	///
	/// @param lng_path Subdirectory.
	/// 
	/// @return 0 or an error code.
	double GMWSetLangSpecificDirName(const char* lng_path);

	/// @brief Load bank by name.
	/// 
	/// @param bank_name Name of the bank.
	/// 
	/// @return Id of the loaded bank or an error code.
	double GMWLoadBank(const char* bank_name);

	/// @brief Unload bank by id.
	///
	/// @param bank_id Bank to unload.
	/// 
	/// @return 0 or an error code.
	double GMWUnloadBank(double bank_id);
}

#endif // _GMW_BANK_
