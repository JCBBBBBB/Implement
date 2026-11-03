#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

template<typename T>
class Vector
{
public:
	Vector()
	{
		m_capacity = 1;
		m_size = 0;
		m_data = new T[m_capacity];
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

		T* newData = new T[other.m_capacity];

		try
		{
			for (int i = 0; i < other.m_size; i++)
			{
				newData[i] = other.m_data[i];
			}
		}
		catch(...)
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

	int size() const // const 붙인 이유? : 이 함수 안에서 값을 고치는 일이 없다
	{
		return m_size;
	}

	int capacity() const
	{
		return m_capacity;
	}

	bool empty() const
	{
		return m_size == 0; // m_size가 0이면 true 반환, 0이 아니면 false 반환
	}

	// 제일 뒤에 원소 넣는다. capacity
	void push_back(const T& data)
	{
		if (m_size >= m_capacity) // 원소의 개수가 용량 개수랑 같아지면
		{
			T* newData = new T[m_capacity * 2]; // 용량 2배
			// 이제 전거를 여기다 복사해야겠지
			for (int i = 0; i < m_size; i++)
			{
				newData[i] = m_data[i]; // 데이터 복사
			}

			m_data = newData; // m_data의 주소를 newData의 시작주소로
			m_capacity = m_capacity * 2; // m_capacity를 2배로

		}

		m_data[m_size++] = data;
	}
	
	// 제일 뒤에 있는거 지운다, capacity는 유지
	void pop_back()
	{
		// m_size가 0이었다면 비어있는거니까 그냥 return
		if (m_size == 0)
		{
			return;
		}


		m_size--; // size만 1 감소시키면 
	}

	T& operator[](int index)
	{
		return m_data[index];
	}

	T& at(int index)
	{
		try
		{
			if (index < 0 || index >= m_size)
			{
				throw(std::out_of_range("Index Error"));
			}

			return m_data[index];
		}
		catch (const std::out_of_range& error)
		{
			cout << error.what() << endl;
			throw;
		}
	}

	void clear()
	{
		m_size = 0;
	}

	void reserve(int n)
	{
		if (n <= m_capacity)
		{
			return;
		}

		T* newData = new T[n];
		for (int i = 0; i < m_size; i++)
		{
			newData[i] = m_data[i];
		}

		delete[] m_data;
		m_data = nullptr;

		m_data = newData;
		m_capacity = n;
	}

	void resize(int n)
	{
		if (n == m_size || n < 0) // 바꿀 크기가 현재 수용크기보다 같다면
		{
			return;
		}
		else if (n < m_size) // 바꿀 크기가 현재 수용크기보다 작다면
		{
			m_size = n;
		}
		else // 바꿀 크기가 현재 수용크기보다 크다면
		{
			if (n > m_capacity)
			{
				reserve(n);
			}

			for (int i = m_size; i < n; i++)
			{
				m_data[i] = T{};
			}

			m_size = n;

		}
	}
	
	/*operator[]	인덱스로 원소 접근.범위 검사 없음
		at()	인덱스로 원소 접근.범위를 벗어나면 예외 발생
		clear()	모든 원소 제거.할당한 공간은 유지
		reserve()	필요하면 저장 공간 확장.size는 유지
		resize()	원소 수 변경.늘리면 원소 생성, 줄이면 원소 소멸*/
	

private:
	T* m_data;
	int m_capacity;
	int m_size;
};



int main()
{
	Vector<int> vec;

	vec.push_back(2);
	vec.clear();

	cout << vec[0];

}