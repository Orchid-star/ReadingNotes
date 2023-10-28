#pragma once
#pragma once

#ifdef DLL_PRO
#define DLL_CLASS _declspec(dllexport)
#else
#define DLL_CLASS _declspec(dllimport)
#endif