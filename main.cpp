#include <iostream>

#include "typesData.hpp"
#include "BooleanMatrix.hpp"

int main()
{
	BooleanMatrix res;
	// BooleanMatrix a(1, 3);
	// BooleanMatrix b(1, 3);

	BooleanMatrix f1(4, 3);
	BooleanMatrix f2(2, 3);
	BooleanMatrix f3(1, 3);


	f1(0, 0) = "1";
	f1(0, 1) = "-";
	f1(0, 2) = "1";

	f1(1, 0) = "0";
	f1(1, 1) = "1";
	f1(1, 2) = "0";

	f1(2, 0) = "1";
	f1(2, 1) = "1";
	f1(2, 2) = "0";

	f1(3, 0) = "0";
	f1(3, 1) = "1";
	f1(3, 2) = "1";

	f2(0, 0) = "1";
	f2(0, 1) = "0";
	f2(0, 2) = "0";

	f2(1, 0) = "0";
	f2(1, 1) = "1";
	f2(1, 2) = "-";


	f3(0, 0) = "1";
	f3(0, 1) = "-";
	f3(0, 2) = "-";


	// res = f1 * f2.negation() * f3;
	res = f1;
	res *= f2;
	res *= f3;
	std::cout << "product f1 * f2 * f3 (" <<  res.rows() << "x" << res.cols() << "):" << std::endl;
	// res = res * f3;
	std::cout << "res" << std::endl;
	res.printMatrix();
	std::cout << std::endl;

	// res = a + b;
	// std::cout << "sum(" <<  res.rows() << "x" << res.cols() << "):" << std::endl;
	// res.printMatrix();
	// std::cout << std::endl;


	// BooleanMatrix matrix(2, 3);

	// matrix(0, 0) = "0";
	// matrix(0, 1) = "1";
	// matrix(0, 2) = "-";
	// matrix(1, 0) = "1";
	// matrix(1, 1) = "-";
	// matrix(1, 2) = "0";

	// std::cout << "negation:" << std::endl;
	// f3.negation().printMatrix();

	return (0);
}