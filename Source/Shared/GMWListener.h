#ifndef _GMW_LISTENER_
#define _GMW_LISTENER_

#include "GMWConfig.h"

extern "C"
{
	///<summary>Sets the position of the listener in 2D space</summary>
	///<param name="pos_x">the x position</param>
	///<param name="pos_y">the y position</param>
	///<param name="o_x">the x orientation</param>
	///<param name="o_y">the y orientation</param>
	///<returns>0 on success, -1 on fail</returns>
	GMW_API double STDCALL GMWSet2DListenerPosition(double pos_x, double pos_y, double o_x, double o_y);

	///<summary>Sets the position of the listener in 3D space</summary>
	///<param name="pos_x">the x position</param>
	///<param name="pos_y">the y position</param>
	///<param name="pos_z">the z position</param>
	///<param name="o_x">the x orientation</param>
	///<param name="o_y">the y orientation</param>
	///<param name="o_z">the z orientation</param>
	///<returns>0 on success, -1 on fail</returns>
	GMW_API double STDCALL GMWSet3DListenerPosition(double pos_x, double pos_y, double pos_z, double o_x, double o_y, double o_z);

	///<summary>Sets the active listeners for a game object using a bitmask. Example: 0101 -> set listeners 1 and 3 to active</summary>
	///<param name="gameObjectID">the ID of the game object</param>
	///<param name="listenerBitmask">the listener bitmask</param>
	///<returns>0 on success, -1 on fail</returns>
    GMW_API double STDCALL GMWSetActiveListeners(double gameObjectID, double listenerBitmask);
}

#endif // _GMW_LISTENER_
