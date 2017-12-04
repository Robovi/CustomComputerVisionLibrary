#include "..\Include\GeneralAlgorithms.h"
#include <cassert>
#include <cmath>

namespace JHCVLibrary
{
	/************************************/
	/************************************/
	/**** General Functions *************/
	/************************************/
	/************************************/

	static double _GaussianKernelProfile(const double x)
	{
		if (x >= 0)
		{
			return exp(-0.5*x);
		}
		else
		{
			return 0;
		}
	}

	static double _UniformKernelProfile(const double x)
	{
		if (x >= 0 && x <= 1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	// Given a vector, it calculates the weight using a gaussian kernel profile. (This function uses the product of the same kernel profiles
	// profile = exp{ -0.5 * x }
	//
	//	Example: 
	//	in_bandwidths = { 10, 20 }
	//  in_bandwidthIndexes = { 1, 4 }
	//  
	//  x0, x1 ==> bandwidth = 10
	//  x2, x3, x4 ==> bandwidth = 20
	static double _GaussianKernel(const DataPoint& in_vector, const std::vector<double> &in_bandwidths, const std::vector<int> &in_bandwidthIndexes)
	{
		const int nBandwidth = in_bandwidths.size();
		assert(nBandwidth >= 1);
		assert(nBandwidth == in_bandwidthIndexes.size());
		assert(in_vector.IsReadyToUse());

		int left = 0;
		double totalProduct = 1;

		for (int index = 0; index < nBandwidth; ++index)
		{
			auto currentBandwidth = in_bandwidths[index];
			auto theNumberInKernelProfile = in_vector.GetMagnitudeSquare(left, in_bandwidthIndexes[index]) / (currentBandwidth * currentBandwidth);
			
			totalProduct *= _GaussianKernelProfile(theNumberInKernelProfile);

			left = in_bandwidthIndexes[index] + 1;
		}

		return totalProduct;
	}

	// !! Function --> Perform a mean shift procedure to a given initial point based on given the whole set of all points.
	void PerformMeanShift(const DataPoint & in_initialPoint, const std::vector<DataPoint>& in_wholePoints,
		const std::vector<double>& in_bandwidths, const std::vector<int>& in_bandwidthsIndexes,
		const double in_epsilon, DataPoint & out_shiftedPoint)
	{
		// Default => Gaussian Function
		// Iterate Over all points in order to compare in_initialPoint with every point
		
		DataPoint currentPoint(in_initialPoint);					  // startPoint = in_initialPoint
		DataPoint weightedAveragePoint(in_initialPoint.GetDimension());	  

		// Initialization
		double totalWeight = 0;					// for Division
		weightedAveragePoint.MakeZero();		// summationPoint = Zero Vector
		//out_shiftedPoint.MakeZero();			// initialization of output point
				
		while (true)
		{
			for (int index = 0; index < in_wholePoints.size(); ++index)
			{
				const DataPoint& comparePoint = in_wholePoints[index];

				auto diffVector = comparePoint - currentPoint;
				auto weight = _GaussianKernel(diffVector, in_bandwidths, in_bandwidthsIndexes);

				weightedAveragePoint.AccumulateAndSave(comparePoint * weight);
				totalWeight += weight;
			}

			weightedAveragePoint.ScalarMultiplyAndSave(1 / totalWeight); // through this division, weightedAveragePoint becomes the real weighted average point!
			auto moveLength = DataPoint::GetEuclideanDistance(weightedAveragePoint, currentPoint, 0, currentPoint.GetDimension() - 1); // calculate the magnitude of this step

			if (moveLength < in_epsilon) // if the length of this step is lower than in_epsilon, convergence!
			{
				out_shiftedPoint = weightedAveragePoint;
				break;
			}

			// calculate epsilon
			currentPoint = weightedAveragePoint;		// shift the current point to the weighted average point

			totalWeight = 0;
			weightedAveragePoint.MakeZero();
		}
	}

	void PerformMeanShiftOverWholePoints(const std::vector<DataPoint>& in_wholePoints, const std::vector<double>& in_bandwidths, const std::vector<int>& in_bandwidthsIndexes, const double in_epsilon, std::vector<DataPoint>& out_shiftedPoints)
	{
		assert(in_wholePoints.size() >= 1 && out_shiftedPoints.size() == 0);
		assert(in_bandwidths.size() == in_bandwidthsIndexes.size());
		assert(in_epsilon > 0);
		
		int nWholePoints = in_wholePoints.size();
		DataPoint shiftedPoint(in_wholePoints[0].GetDimension());

		for (int index = 0; index < nWholePoints; ++index)
		{
			const DataPoint& currentPoint = in_wholePoints[index];
			
			PerformMeanShift(currentPoint, in_wholePoints, in_bandwidths, in_bandwidthsIndexes, in_epsilon, shiftedPoint);
			out_shiftedPoints.push_back(shiftedPoint);
		}
	}


	
	

}
