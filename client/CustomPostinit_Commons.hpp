#ifndef __CustomPostinit_Commons_hpp__
#define __CustomPostinit_Commons_hpp__
#include "client.hpp"
#define CPI_DECLARE(A) extern void (A)(PostInitData&, InitData&, GameData&)
#define CPI_DEFINE(A) void (A)(PostInitData &pd, InitData &d, GameData &gd)
#endif // __CustomPostinit_Commons_hpp__
