#include "../Include/DataPoint.h"
#include <cassert>

namespace JHCVLibrary
{
	int DataPoint::GetDimension() const
	{
		return m_nDimension;
	}

	void DataPoint::AccumulateAndSave(const DataPoint & in_dataPoint)
	{
		assert(this->IsReadyToUse() && in_dataPoint.IsReadyToUse());
		assert(m_nDimension == in_dataPoint.m_nDimension);

		for (int i = 0; i < m_nDimension; ++i)
		{
			m_pData[i] += in_dataPoint.m_pData[i];
		}
	}

	void DataPoint::ScalarMultiplyAndSave(const double in_scalar)
	{
		assert(IsReadyToUse() == true);

		for (int i = 0; i < m_nDimension; ++i)
		{
			m_pData[i] *= in_scalar;
		}
	}

	inline bool DataPoint::IsReadyToUse() const
	{
		if (m_pData != nullptr && m_nDimension > 0)
		{
			return true;
		}
		return false;
	}

	DataPoint::DataPoint(const int in_nDim)
	{
		assert(in_nDim > 0);

		m_pData = new double[in_nDim];
		if (m_pData)
		{
			for (int i = 0; i < in_nDim; ++i)
			{
				m_pData[i] = 0;
			}
			m_nDimension = in_nDim;
		}
		else
		{
			// if memory cannot be allocated, raise an assertion!
			assert(false);
			m_pData = nullptr;
			m_nDimension = -1;
		}
	}

	DataPoint::DataPoint(const DataPoint & in_dataPoint)
	{
		assert(in_dataPoint.IsReadyToUse());

		m_pData = new double[in_dataPoint.m_nDimension];
		if (m_pData)
		{
			for (int i = 0; i < in_dataPoint.m_nDimension; ++i)
			{
				m_pData[i] = in_dataPoint.m_pData[i];
			}
			m_nDimension = in_dataPoint.m_nDimension;
		}
		else
		{
			// if memory cannot be allocated, raise an assertion!
			assert(false);
			m_pData = nullptr;
			m_nDimension = -1;
		}
	}

	DataPoint::DataPoint(std::initializer_list<double> in_argList)
	{
		assert(in_argList.size() > 0);
		int nListSize = in_argList.size();

		this->m_pData = new double[nListSize];

		if (this->m_pData)	// if allocation has succeeded
		{
			int index = 0;
			for (auto iter = in_argList.begin(); iter != in_argList.end(); ++iter)
			{
				this->m_pData[index] = *iter;
				index++;
			}
			this->m_nDimension = nListSize;
		}
		else
		{
			assert(false);
			m_pData = nullptr;
			m_nDimension = -1;
		}
	}

	DataPoint DataPoint::operator*(const double in_scalar)
	{
		assert(this->IsReadyToUse());
		DataPoint retPoint(m_nDimension);

		for (int index = 0; index < m_nDimension; ++index)
		{
			retPoint.m_pData[index] = this->m_pData[index] * in_scalar;
		}

		return retPoint;
	}

	DataPoint DataPoint::operator+(const DataPoint & in_dataPoint) const
	{
		assert(this->IsReadyToUse() && in_dataPoint.IsReadyToUse());
		assert(this->m_nDimension == in_dataPoint.m_nDimension);

		DataPoint retPoint(m_nDimension);

		for (int index = 0; index < m_nDimension; ++index)
		{
			retPoint.m_pData[index] = this->m_pData[index] + in_dataPoint.m_pData[index];
		}

		return retPoint;
	}

	DataPoint DataPoint::operator-(const DataPoint & in_dataPoint) const
	{
		assert(this->IsReadyToUse() && in_dataPoint.IsReadyToUse());
		assert(this->m_nDimension == in_dataPoint.m_nDimension);

		DataPoint retPoint(m_nDimension);

		for (int index = 0; index < m_nDimension; ++index)
		{
			retPoint.m_pData[index] = this->m_pData[index] - in_dataPoint.m_pData[index];
		}

		return retPoint;
	}

	double & DataPoint::operator[](const int index)
	{
		assert(IsReadyToUse());
		assert(index >= 0 && index < m_nDimension);
		return m_pData[index];
	}

	const double & DataPoint::operator[](const int index) const
	{
		assert(IsReadyToUse());
		assert(index >= 0 && index < m_nDimension);

		return m_pData[index];
	}

	DataPoint& DataPoint::operator=(const DataPoint & in_dataPoint)
	{
		assert(this->IsReadyToUse() && in_dataPoint.IsReadyToUse());
		assert(m_nDimension == in_dataPoint.m_nDimension);

		for (int index = 0; index < in_dataPoint.m_nDimension; ++index)
		{
			this->m_pData[index] = in_dataPoint.m_pData[index];
		}
		return (*this);
	}

	JHCVLibrary::DataPoint::~DataPoint()
	{
		if (m_pData)
		{
			delete m_pData;
		}
		m_pData = nullptr;
		m_nDimension = -1;
	}
}
