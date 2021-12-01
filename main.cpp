#include <iostream>

#include "typesData.hpp"
#include "BooleanMatrix.hpp"

int main()
{
	BooleanMatrix res;
	BooleanMatrix a(1, 3);
	BooleanMatrix b(1, 3);


	a(0, 0) = "1";
	a(0, 1) = "1";
	a(0, 2) = "1";

	b(0, 0) = "1";
	b(0, 1) = "1";
	b(0, 2) = "-";


	res = a * b;
	std::cout << "product(" <<  res.rows() << "x" << res.cols() << "):" << std::endl;
	res.printMatrix();
	std::cout << std::endl;

	res = a + b;
	std::cout << "sum(" <<  res.rows() << "x" << res.cols() << "):" << std::endl;
	res.printMatrix();
	std::cout << std::endl;


	BooleanMatrix matrix(2, 3);

	matrix(0, 0) = "0";
	matrix(0, 1) = "1";
	matrix(0, 2) = "-";
	matrix(1, 0) = "1";
	matrix(1, 1) = "-";
	matrix(1, 2) = "0";

	std::cout << "negation:" << std::endl;
	matrix.negation().printMatrix();

	return (0);
}