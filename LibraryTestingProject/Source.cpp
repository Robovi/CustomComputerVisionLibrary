#include <iostream>
#include <vector>
#include <opencv2\opencv.hpp>

#include <DataPointSet.h>
#include <GeneralAlgorithms.h>
int main(void)
{
	auto inputImage = cv::imread("cameraman.jpg");
	cv::Mat convertedImage;
	cv::cvtColor(inputImage, convertedImage, CV_BGR2GRAY);

	JHCVLibrary::DataPointSet kk(convertedImage, 0, 0);

	std::vector<double> bandwidth = { 8, 4 }; // hs = 8, hr = 4
	std::vector<int> bandwidthIndexes = { 1, 2 };
	std::vector<JHCVLibrary::DataPoint> resultPoints;
	JHCVLibrary::PerformMeanShiftOverWholePoints(kk.GetDataArray(), bandwidth, bandwidthIndexes, 15, 1, resultPoints);

	//cv::pyrMeanShiftFiltering()
	//resultPoints

	
	return 0;
}