#include <iostream>
#include <DataPoint.h>

int main(void)
{
	JHCVLibrary::DataPoint x1({ 1,2,3,4,5 });
	JHCVLibrary::DataPoint x2({ 10,10,10,10,10 });

	auto j = x1 + x2;
	
	std::cout << JHCVLibrary::DataPoint::GetEuclideanDistance(x1, x2, 2, 4);
	

	return 0;
}