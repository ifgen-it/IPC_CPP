// DynamicLib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#define MY_DLL
#include "DynamicLib.h"


__declspec(dllexport) double Add(double x, double y)
{
	return x + y;
}

__declspec(dllexport) double Subtract(double x, double y)
{
	return x - y;
}

__declspec(dllexport) double Multiply(double x, double y)
{
	return x * y;
}

__declspec(dllexport) double Divide(double x, double y)
{
	return x / y;
}