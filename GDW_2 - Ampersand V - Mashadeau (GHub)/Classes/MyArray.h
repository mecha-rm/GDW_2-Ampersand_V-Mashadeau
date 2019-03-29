#pragma once

#include <iostream>

namespace OOP
{
	// Question 1: MyArray.h file
	template<typename T>
	class MyArray
	{
	public:

		// Question 3: takes the size of the array, and makes the array.
		MyArray(const unsigned int size) : arr(new T[size]), SIZE(size) {}

		// Question 2: size() function.
		const unsigned int Size() const { return SIZE; }

		T * operator[](const unsigned int index) // operator[] function.
		{
			try
			{
				if (index >= SIZE) // throws an error if this is the case.
					throw index;
				else
					return &arr[index];
			}
			catch (...)
			{
				std::cout << "'Out of bounds' exception thrown." << std::endl;
			}
		}


		// Begin() Function.
		T * Begin() const { return &arr[0]; }

		// End() Function.
		T * End() const { return &arr[SIZE - 1]; }

	private:
		T * arr = nullptr; // dynamic array that values are stored in.

		const unsigned int SIZE; // the size of the array.

	protected:
	};
}