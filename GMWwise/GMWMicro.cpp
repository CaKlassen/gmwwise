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
#include "GMWMicro.h"
#include "wwise/SoundInput.h"

extern "C"
{
	SoundInput g_SoundInput;

	//----------------------------------------------------------------
	// Start recording. ----------------------------------------------
	double GMWStartRecord(void)
	{
		g_SoundInput.InputOn();

		return EC_NONE;
	}

	//----------------------------------------------------------------
	// Stop recording. -----------------------------------------------
	double GMWStopRecord(void)
	{
		g_SoundInput.InputOff();

		return EC_NONE;
	}
}
