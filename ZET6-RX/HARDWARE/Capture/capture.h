#ifndef __CAPTURE_H
#define __CAPTURE_H
#include "sys.h"

#define TRIG_OUT PBout(1)
#define ECHO_IN  PBin(0)

void CAPTURE_Init(void);
u32 GetEchoTimer(void);
float Hcsr04GetLength(void);

#endif
