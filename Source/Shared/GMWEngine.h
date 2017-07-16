#ifndef _GMW_ENGINE_
#define _GMW_ENGINE_

#include "GMWConfig.h"

extern "C"
{
	///<summary>Initializes the Wwise engine</summary>
	///<returns>0 on success, -1 on fail</returns>
	GMW_API double STDCALL GMWInit(void);

	///<summary>Shuts down the Wwise engine</summary>
	///<returns>0 on success, -1 on fail</returns>
	GMW_API double STDCALL GMWShutdown(void);

	///<summary>Processes a frame of audio</summary>
	///<returns>0 on success, -1 on fail</returns>
    GMW_API double STDCALL GMWProcessAudio(void);

	///<summary>Sets the state of a specific state group</summary>
	///<param name="_dStateGroup">the state group</param>
	///<param name="_dState">the state</param>
	///<returns>0 on success, -1 on faile</returns>
	GMW_API double STDCALL GMWSetState(double _dStateGroup, double _dState);	
}

#endif // _GMW_ENGINE_
