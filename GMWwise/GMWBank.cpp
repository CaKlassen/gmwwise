/*
Author : c�dric liaudet
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
#include "GMWBank.h"
#include "GMWStringUtil.h"
#include "wwise/AkFilePackageLowLevelIOBlocking.h"
#include <vector>

extern CAkFilePackageLowLevelIOBlocking g_lowLevelIO;

extern "C"
{
	static std::vector<AkBankID> banksLoaded;
    static wchar_t* wbanks_path = 0;
	static wchar_t* wlng_path = 0;
	
	//----------------------------------------------------------------
	// Close every banks. --------------------------------------------
	void GMWClearBanks(void)
	{
		gmw::StringUtil::free(wbanks_path);
        wbanks_path = 0;

		gmw::StringUtil::free(wlng_path);
		wlng_path = 0;

		if(!banksLoaded.empty())
		{
			std::stringstream sstr;
			sstr << "All banks must be unloaded : " << banksLoaded.size() << " are loaded.";
			GMW_EXCEPTION(sstr.str().c_str());

			std::vector<AkBankID>::iterator it = banksLoaded.begin(), it_end = banksLoaded.end();
			
			/*
			for(; it <= it_end; it++)
			{
				AK::SoundEngine::UnloadBank(*it, );
			}
			*/

			// Clear all banks
			AK::SoundEngine::ClearBanks();

			banksLoaded.clear();
		}
	}

	//----------------------------------------------------------------
	// Set the path to load bank. ------------------------------------
	double GMWSetBasePath(const char* banks_path)
	{
		wbanks_path = gmw::StringUtil::str2wstr(banks_path);
        if(!wbanks_path)
		{
            GMW_EXCEPTION("Unable to set base path.");

			return EC_IO;
		}
        else
            g_lowLevelIO.SetBasePath(wbanks_path);
		
		return EC_NONE;
	}

	//----------------------------------------------------------------
	// Load bank by name. --------------------------------------------
	double GMWLoadBank(const char* bank_name)
	{
        AkBankID bankID;
        wchar_t* wbank_name = gmw::StringUtil::str2wstr(bank_name);

        AKRESULT result = AK::SoundEngine::LoadBank(wbank_name, AK_DEFAULT_POOL_ID, bankID);
        if(result != AK_Success)
		{
            std::stringstream sstr;
            sstr << "Unable to load the bank : " << bank_name << "\nwwise : ";

            switch(result)
            {
            case AK_InsufficientMemory:
                sstr << "insufficient memory to store bank data.";
                break;
            case AK_BankReadError:
                sstr << "bank read error.";
                break;
            case AK_WrongBankVersion:
                sstr << "invalid bank version : make sure the version version of Wwise\n that you used to generate the SoundBanks matches that of the SDK you are currently using.";
                break;
            case AK_InvalidFile:
                sstr << "file specified could not be opened.";
                break;
            case AK_InvalidParameter:
                sstr << "invalid parameter, invalid memory alignment.";
                break;
            case AK_Fail:
                sstr << "load failed for unknow reason.";
                break;
            }

            GMW_EXCEPTION(sstr.str().c_str());

			return EC_BANK;
		}
        
        gmw::StringUtil::free(wbank_name);

		banksLoaded.push_back(bankID);

		return static_cast<double>(bankID);
	}

	//----------------------------------------------------------------
	// Unload bank by id. --------------------------------------------
	double GMWUnloadBank(double bank_id)
	{
		if(bank_id < 0)
		{
			GMW_EXCEPTION("Bad bank ID : ID must be higher or equal to 0");

			return EC_BAD_ARGS;
		}

		if(AK::SoundEngine::UnloadBank(static_cast<AkBankID>(bank_id), NULL, NULL) != AK_Success)
		{
			GMW_EXCEPTION("Unable to unload the bank.");

			return EC_BANK;
		}

		std::vector<AkBankID>::iterator it = banksLoaded.begin(), it_end = banksLoaded.end();
		for(; it <= it_end; it++)
		{
			if((*it) == bank_id)
			{
				banksLoaded.erase(it);
				break;
			}
		}

		return EC_NONE;
	}
}