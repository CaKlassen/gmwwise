#include "GMWBank.h"
#include "GMWStringUtil.h"

#if defined(_WIN32)
#include "wwise/AkFilePackageLowLevelIOBlocking.h"
#elif defined(__APPLE__) || defined(__unix__)
#include "AkFilePackageLowLevelIOBlocking.h"
#endif

#include <vector>

extern CAkFilePackageLowLevelIOBlocking g_lowLevelIO;

extern "C"
{
	static std::vector<AkBankID> banksLoaded;
    static wchar_t* wbanks_path = 0;
	static wchar_t* wlng_path = 0;
	
	// Unloads all banks
	void GMWClearBanks(void)
	{
		gmw::StringUtil::free(wbanks_path);
        wbanks_path = 0;

		gmw::StringUtil::free(wlng_path);
		wlng_path = 0;

		if(!banksLoaded.empty())
		{
			std::vector<AkBankID>::iterator it = banksLoaded.begin(), it_end = banksLoaded.end();

			// Clear all banks
			AK::SoundEngine::ClearBanks();

			banksLoaded.clear();
		}
	}

	// Sets the base path for bank loading
	double GMWSetBasePath(const char* banks_path)
	{
		wbanks_path = gmw::StringUtil::str2wstr(banks_path);
        if(!wbanks_path)
		{
			errorCode = AK_Fail;
			return -1;
		}
        else
		{
			AKRESULT result;

#if defined(_WIN32)
            result = g_lowLevelIO.SetBasePath(wbanks_path);
#elif defined(__APPLE__) || defined(__unix__)
			result = g_lowLevelIO.SetBasePath((const AkOSChar*)banks_path);
#endif
            if (result != AK_Success)
			{
				errorCode = result;
				return -1;
			}
		}
		
		return 0;
	}

	// Loads a bank
	double GMWLoadBank(const char* bank_name)
	{
        AkBankID bankID;
        wchar_t* wbank_name = gmw::StringUtil::str2wstr(bank_name);
		if (!wbank_name)
		{
			errorCode = AK_Fail;
			return -1;
		}

		// Attempt to load the bank
        AKRESULT result = AK::SoundEngine::LoadBank(wbank_name, AK_DEFAULT_POOL_ID, bankID);

        if(result != AK_Success)
		{
			errorCode = result;
			return -1;
		}
        
        gmw::StringUtil::free(wbank_name);

		banksLoaded.push_back(bankID);

		return static_cast<double>(bankID);
	}

	// Unloads a bank
	double GMWUnloadBank(double bank_id)
	{
		if(bank_id < 0)
		{
			errorCode = AK_InvalidID;
			return -1;
		}

		AKRESULT result = AK::SoundEngine::UnloadBank(static_cast<AkBankID>(bank_id), NULL, NULL);
		if(result != AK_Success)
		{
			errorCode = result;
			return -1;
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

		return 0;
	}
}
