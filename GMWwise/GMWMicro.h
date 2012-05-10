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
#ifndef _GMW_MICRO_
#define _GMW_MICRO_

#include "GMWConfig.h"

extern "C"
{
	/// @brief Start recording.
	/// 
	/// @return 0.
	GMW_API double STDCALL GMWStartRecord(void);

	/// @brief Stop recording.
	/// 
	/// @return 0.
	GMW_API double STDCALL GMWStopRecord(void);
}

#endif // _GMW_MICRO_