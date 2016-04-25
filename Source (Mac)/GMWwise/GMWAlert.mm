//
//  GMWAlert.cpp
//  GMWwise
//
//  Created by ChristoferKlassen on 2016-04-25.
//  Copyright © 2016 Chris Klassen. All rights reserved.
//

#include "GMWAlert.h"

void GMW_EXCEPTION(string msg)
{	
	NSAlert *alert = [[NSAlert alloc] init];
	[alert addButtonWithTitle:@"OK"];
	[alert setMessageText:@"Exception"];
	[alert setInformativeText:[NSString stringWithFormat:@"%s", msg.c_str()]];
	[alert setAlertStyle:NSWarningAlertStyle];
	[alert runModal];
}