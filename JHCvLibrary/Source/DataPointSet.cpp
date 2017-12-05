#include "..\Include\DataPointSet.h"
#include <assert.h>

namespace JHCVLibrary
{
	// [in_leftRange, in_rightRange] => range (color)
	DataPointSet::DataPointSet(const cv::Mat & in_cvConvertedMatrix, int in_leftRange, int in_rightRange)
	{
		assert(in_leftRange >= 0 && in_rightRange >= in_leftRange);
		// First of all, convert bgr format to Luv format

		const int nHeight = in_cvConvertedMatrix.rows;
		const int nWidth = in_cvConvertedMatrix.cols;
		const int nColorDimension = in_rightRange - in_leftRange + 1;

		m_dataPoints.clear();

		for (int yIndex = 0; yIndex < nHeight; ++yIndex)
		{
			for (int xIndex = 0; xIndex < nWidth; ++xIndex)
			{
				auto eachPixel = in_cvConvertedMatrix.at<cv::Vec<unsigned char, 1>>(yIndex, xIndex);
				// new data point's dimensionality is 2 + (left range - right range + 1), which is (spatial + color)
				DataPoint savedDataPoint(2 + (in_rightRange - in_leftRange + 1));

				// spatial information
				savedDataPoint[0] = (double)xIndex;
				savedDataPoint[1] = (double)yIndex;

				// color information
				for (int colorIndex = in_leftRange; colorIndex <= in_rightRange; ++colorIndex)
				{
					savedDataPoint[2 + colorIndex] = (double)eachPixel[colorIndex];
				}

				// register the current pixel into the array of dataPoint
				m_dataPoints.push_back(savedDataPoint);
			}
		}
	}

	const std::vector<DataPoint>& DataPointSet::GetDataArray() const
	{
		// TODO: insert return statement here
		return m_dataPoints;
	}

	int DataPointSet::GetNumberOfPoints() const
	{
		return m_dataPoints.size();
	}
}
