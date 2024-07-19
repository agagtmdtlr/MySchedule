#pragma once

namespace cm
{
	template<typename T>
	class Vector
	{
	public:
		Vector(int n = 1)
			: data(new T[n]), capacity(n), length(0)
		{
			
		}

		void push_back(T item)
		{
			if (capacity >= length)
			{
				T* newData = new T[capacity * 2];
				for (int i = 0; i < capacity; i++)
				{
					newData[i] = data[i];
				}

				delete[] data;
				data = newData;
				capacity *= 2;
			}

			data[length] = item;

			length++;
		}

		T operator[](int i) { return data[i]; }

	private:
		T* data;
		int capacity;
		int length;
	};
}