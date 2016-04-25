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
#ifndef _GMW_ENGINE_
#define _GMW_ENGINE_

#include "GMWConfig.h"

extern "C"
{
	/// @brief Initialization of Wwise.
	/// 
	/// @return 0 or an error code.
	/// 
	/// @remarks
	///		Have to called in first.
	double GMWInit(void);

	/// @brief Shutdown Wwise and free all resources.
	///
	/// @return 0.
	///
	/// @remarks
	///		Have to called in last.
	double GMWShutdown(void);

	/// @brief Update the sound engine.
	/// 	
	/// @return 0.
	///
	/// @remarks
	///		Have to be called once per frame.
	double GMWProcessAudio(void);

	/// @brief Set state of the specified group.
	/// 
	/// @param _dStateGroup ID of the group.
	/// @param _dState New value to set.
	/// 
	/// @return 0 or an error code.
	double GMWSetState(double _dStateGroup, double _dState);

    /// @brief Register a wwise plugin.
	///
	/// @param _dType Type of plugin.
	/// 
	/// @return 0 or an error code.
    ///
	/// @remarks
	///		Plugin list:
    ///			0 Sine
    ///			1 Tone Generator
    ///			2 Silence
    ///			3 Audio Input
    ///			4 Delay
    ///			5 Parametric EQ
    ///			6 Matrix Reverb
    ///			7 Compressor
    ///			8 Expander
    ///			9 Peak Limiter
    ///			10 Roomverb.
	///			11 Pitch Shifter
	///			12 Meter
	double GMWRegisterPlugin(double _dType);

    /// @brief Register a wwise codec.
	/// 
	/// @param _dType Type of codec.
	/// 
	/// @return 0 or an error code.
	/// 
	/// @remarks
	///		Codecs list:
    ///			0 Vorbis
	double GMWRegisterCodec(double _dType);
}

#endif // _GMW_ENGINE_
