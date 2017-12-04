// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the JHCVLIBRARY_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// JHCVLIBRARY_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef JHCVLIBRARY_EXPORTS
#define JHCVLIBRARY_API __declspec(dllexport)
#else
#define JHCVLIBRARY_API __declspec(dllimport)
#endif

#pragma once
#include <initializer_list>
#include <iostream>
#include <vector>
#include "DataPoint.h"

namespace JHCVLibrary
{
	JHCVLIBRARY_API void PerformMeanShift(const DataPoint& in_initialPoint,
										const std::vector<DataPoint> &in_wholePoints,
										const std::vector<double> &in_bandwidths,
										const std::vector<int> &in_bandwidthsIndexes,
										const double in_epsilon,
										DataPoint &out_shiftedPoint);
	
}