#ifndef _ctmath_hpp
#define _ctmath_hpp
#include <iostream>



class Math {
public:

	const float PI = 3.141592653589793f;
	const float EUF = 2.718281828459045f;



	void max(int x , int y , int z) {
		if (x > y && x > z)
			std::cout << x ;

		else if (y > x && y > z)
			std::cout << y << std::endl;

		else if (z > x && z > y)
			std::cout << x << std::endl;
	}
	
	void min(int x , int y , int z) {
		if (x < y && x < z)
			std::cout << x << std::endl;

		else if (y < x && y < z)
			std::cout << y << std::endl;

		else if (z < x && z < y)
			std::cout << x << std::endl;
	}

};


int addition(int x , int y) {
	return x + y;
}
	
int subtraction(int x, int y) {
	return x - y;
}

int multiplication(int x, int y) {
	return x * y;
}

int division(int x, int y) {
	if (y == 0) {
		throw std::runtime_error("Division by zero error.");
	}
	return x / y;
}




#endif _ctmath_hpp