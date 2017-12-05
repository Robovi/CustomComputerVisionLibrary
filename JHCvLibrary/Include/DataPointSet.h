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
#include "DataPoint.h"
#include <vector>
#include <opencv2\opencv.hpp>

namespace JHCVLibrary
{
	class JHCVLIBRARY_API DataPointSet
	{
	private:
		std::vector<DataPoint> m_dataPoints;

	public:
		DataPointSet(const cv::Mat &in_cvBgrMat, int in_leftRange, int in_rightRange);
		const std::vector<DataPoint>& GetDataArray() const;
		
		int GetNumberOfPoints() const;
	};
}