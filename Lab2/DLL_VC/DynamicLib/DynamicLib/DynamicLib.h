#pragma once


extern "C" {
#ifdef MY_DLL
#define LINKDLL __declspec(dllexport)
#else
#define LINKDLL __declspec(dllimport)
#endif // MY_DLL



	LINKDLL double Add(double x, double y);

	LINKDLL double Subtract(double x, double y);

	LINKDLL double Multiply(double x, double y);

	LINKDLL double Divide(double x, double y);

}

