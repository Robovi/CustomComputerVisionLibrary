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

namespace JHCVLibrary
{
	class JHCVLIBRARY_API DataPoint
	{
	private:
		double *m_pData;
		int m_nDimension;

	public:
		int GetDimension() const;
		void AccumulateAndSave(const DataPoint &in_dataPoint);
		void ScalarMultiplyAndSave(const double in_scalar);

	public:
		inline bool IsReadyToUse() const;

		DataPoint(const int in_Dim);
		DataPoint(const DataPoint &in_dataPoint);
		DataPoint(std::initializer_list<double> in_argList);

		DataPoint operator*(const double in_scalar);
		DataPoint operator+(const DataPoint& in_dataPoint) const;
		DataPoint operator-(const DataPoint& in_dataPoint) const;
		double& operator[](const int index);
		const double& operator[](const int index) const;
		DataPoint& operator=(const DataPoint& in_dataPoint);

		~DataPoint();
	};

	JHCVLIBRARY_API std::ostream& operator<<(std::ostream& os, const DataPoint& obj);
}