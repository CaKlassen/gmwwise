#include "GMWAlert.h"

// Displays an error message
void GMW_EXCEPTION(string msg)
{	
	NSAlert *alert = [[NSAlert alloc] init];
	[alert addButtonWithTitle:@"OK"];
	[alert setMessageText:@"Exception"];
	[alert setInformativeText:[NSString stringWithFormat:@"%s", msg.c_str()]];
	[alert setAlertStyle:NSWarningAlertStyle];
	[alert runModal];
}
