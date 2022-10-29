#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

#define MAIN_DEBUG

#ifdef MAIN_DEBUG
#define MN_DEBUG(x) Serial.print(x)
#define MN_DEBUGLN(x) Serial.println(x)
#define MN_DEBUG_F(x) Serial.print(F(x))
#define MN_DEBUGLN_F(x) Serial.println(F(x))
#else
#define MN_DEBUG(x)
#define MN_DEBUGLN(x)
#define MN_DEBUG_F(x)
#define MN_DEBUGLN_F(x)
#endif

#define CORE_0 0
#define CORE_1 1

#endif