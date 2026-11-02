#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<typename T>
class Vector
{
public:
	Vector()
	{
		m_data = nullptr;
		m_capacity = 0;
		m_size = 0;
	}

	~Vector()
	{
		delete[] m_data;
		m_data = nullptr;
	}

	//Vector<int> c(a)
	Vector(const Vector& other)
	{
		m_data = new T[other.m_capacity];

		for (int i = 0; i < other.m_size; i++)
		{
			m_data[i] = other.m_data[i];
		}

		m_capacity = other.m_capacity;
		m_size = other.m_size;
	}

	//Vector<int> c = a -> c에 이미 데이터가 있다면 초기화하고 넣어야 함
	Vector& operator=(const Vector& other)
	{
		if (this == &other)
		{
			return *this;
		}

		if (m_data)
		{
			delete[] m_data;
			m_data = nullptr;
		}

		m_data = new T[other.m_capacity];

		for (int i = 0; i < other.m_size; i++)
		{
			m_data[i] = other.m_data[i];
		}

		m_capacity = other.m_capacity;
		m_size = other.m_size;

		return *this;
	}



private:
	T* m_data;
	int m_capacity;
	int m_size;
};



int main()
{

}