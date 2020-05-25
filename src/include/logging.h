#ifndef _LOGGING_H_
#define _LOGGING_H_

#include <iostream>
#include <string.h>
#include <stdarg.h>
static char logBuff[200];
void logd(const char *fmt, ...);

#endif