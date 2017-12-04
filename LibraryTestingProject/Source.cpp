#include <iostream>
#include <DataPoint.h>
#include <vector>
#include <GeneralAlgorithms.h>

int main(void)
{
	
	JHCVLibrary::DataPoint x1({ 1, 1 });
	JHCVLibrary::DataPoint x2({ 1.1, 1 });
	JHCVLibrary::DataPoint x3({ 0.9, 1 });
	JHCVLibrary::DataPoint x4({ 1.1, 1.1 });

	JHCVLibrary::DataPoint x5({ 8, 8 });
	JHCVLibrary::DataPoint x6({ 8, 8.1 });
	JHCVLibrary::DataPoint x7({ 7.9, 8.1 });
	JHCVLibrary::DataPoint x8({ 7.9, 8 });

	std::vector<JHCVLibrary::DataPoint> wholePoints;
	std::vector<JHCVLibrary::DataPoint> resultPoints;

	wholePoints.push_back(x1);
	wholePoints.push_back(x2);
	wholePoints.push_back(x3);
	wholePoints.push_back(x4);
	wholePoints.push_back(x5);
	wholePoints.push_back(x6);
	wholePoints.push_back(x7);
	wholePoints.push_back(x8);

	JHCVLibrary::PerformMeanShiftOverWholePoints(wholePoints, { 1, 1 }, { 0 }, 0.5, resultPoints);
	
	for (int i = 0; i < wholePoints.size(); ++i)
	{
		std::cout << wholePoints[i] << std::endl;
		std::cout << resultPoints[i] << std::endl;
		std::cout << "\n\n";
	}


	auto j = x1 + x2;
	
	////std::cout << JHCVLibrary::DataPoint::GetEuclideanDistance(x1, x2, 2, 4);
	//std::cout << (x1-x2).GetMagnitudeSquare(2, 3) << std::endl;
	//

	
	return 0;
}