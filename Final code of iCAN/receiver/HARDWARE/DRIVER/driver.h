#ifndef __DRIVER_H
#define __DRIVER_H	 
#include "sys.h"
void ENDIR_Init (void);
void ENDIR_Set (void);
#define en PFout(13)// PF13
#define dir PFout(14)// PF14
#endif
 /****************************
#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5	
 ****************************/
