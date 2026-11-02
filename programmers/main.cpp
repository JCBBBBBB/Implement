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

		T* newData = new[other.m_capacity];

		try
		{
			for (int i = 0; i < other.m_size; i++)
			{
				newData[i] = other.m_data[i];
			}
		}
		catch
		{
			delete[] newData;
			newData = nullptr;
		}

		// 지금 newData에 다 복사된거니까
		m_data = newData;
		m_capacity = other.m_capacity;
		m_size = other.m_size;

		return *this;
	}

	// Vector<int> vec = std::move(a);
	Vector(Vector&& other)
	{
		// 현재 내 Vector에 other거 다 복사
		m_data = other.m_data;
		m_capacity = other.m_capacity;
		m_size = other.m_size;

		other.m_data = nullptr; // 이게 주소만 끊는거지, 아예 delete는 안하네, delte하면 현재 m_data도 끊기니까겠지
		other.m_capacity = 0;
		other.m_size = 0;
	}

	// 이동 대입 연산자
	Vector& operator=(Vector&& other) // Vector& 이유는? 객체를 복사하지 않고 참조로 반환
	{
		if (this == &other)
		{
			return *this;
		}

		delete[] m_data;
		m_data = nullptr;

		m_data = other.m_data;
		m_capacity = other.m_capacity;
		m_size = other.m_size;

		other.m_data = nullptr;
		other.m_capacity = 0;
		other.m_size = 0;

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