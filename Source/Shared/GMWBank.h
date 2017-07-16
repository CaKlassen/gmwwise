#ifndef _GMW_BANK_
#define _GMW_BANK_

#include "GMWConfig.h"

extern "C"
{
	/// <summary>Closes every bank</summary>
	void GMWClearBanks(void);

	/// <summary>Sets the bank load path</summary>
	/// <param name="banks_path">the bank load path</param>
	/// <returns>0 on success, -1 on fail</returns>
	GMW_API double STDCALL GMWSetBasePath(const char* banks_path);
	
	///<summary>Loads a bank by string name</summary>
	///<param name="bank_name">the bank name</param>
	///<returns>the ID of the loaded bank, or -1 on fail</returns>
	GMW_API double STDCALL GMWLoadBank(const char* bank_name);

	///<summary>Unloads a bank by its ID</summary>
	///<param name="bank_id">the bank ID</param>
	///<returns>0 on success, -1 on fail</returns>
	GMW_API double STDCALL GMWUnloadBank(double bank_id);
}

#endif // _GMW_BANK_
