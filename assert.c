 #include "assert.h"
 #include "fxlib.h"
 void assert(char *text) //displays an error message, and waits for a restart
 {
	PopUpWin(5);
	locate(2, 2);
	Print(text);
	Bdisp_PutDisp_DD();
	while(1){}
 }
