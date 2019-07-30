#include "matrix.h"
#include <iostream>
#include <thread>

int main()
{
	int m = 3;
	int k = 4;
	Matrix<int> q(m, k);
	Matrix<int> pointer = new Matrix<int>(m, k);

	return 0;
}