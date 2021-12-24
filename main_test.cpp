#include <iostream>

#include "typesData.hpp"
#include "BooleanMatrix.hpp"

#include <ctime>

int main()
{
	BooleanMatrix res;
	// BooleanMatrix a(1, 3);
	// BooleanMatrix b(1, 3);

	BooleanMatrix f1(6, 10);
	BooleanMatrix f2(1, 3);
	BooleanMatrix f3(1, 3);

	f1(0, 0) = "1";
	f1(0, 1) = "-";
	f1(0, 2) = "-";
	f1(0, 3) = "-";
	f1(0, 4) = "-";
	f1(0, 5) = "-";
	f1(0, 6) = "1";
	f1(0, 7) = "0";
	f1(0, 8) = "-";
	f1(0, 9) = "1";

	f1(1, 0) = "-";
	f1(1, 1) = "1";
	f1(1, 2) = "-";
	f1(1, 3) = "-";
	f1(1, 4) = "-";
	f1(1, 5) = "-";
	f1(1, 6) = "1";
	f1(1, 7) = "1";
	f1(1, 8) = "1";
	f1(1, 9) = "1";

	f1(2, 0) = "-";
	f1(2, 1) = "-";
	f1(2, 2) = "1";
	f1(2, 3) = "-";
	f1(2, 4) = "-";
	f1(2, 5) = "-";
	f1(2, 6) = "0";
	f1(2, 7) = "0";
	f1(2, 8) = "0";
	f1(2, 9) = "0";

	f1(3, 0) = "-";
	f1(3, 1) = "-";
	f1(3, 2) = "-";
	f1(3, 3) = "1";
	f1(3, 4) = "-";
	f1(3, 5) = "-";
	f1(3, 6) = "1";
	f1(3, 7) = "0";
	f1(3, 8) = "-";
	f1(3, 9) = "1";


	f1(4, 0) = "-";
	f1(4, 1) = "-";
	f1(4, 2) = "-";
	f1(4, 3) = "-";
	f1(4, 4) = "1";
	f1(4, 5) = "-";
	f1(4, 6) = "1";
	f1(4, 7) = "0";
	f1(4, 8) = "-";
	f1(4, 9) = "1";

	f1(5, 0) = "-";
	f1(5, 1) = "-";
	f1(5, 2) = "-";
	f1(5, 3) = "-";
	f1(5, 4) = "-";
	f1(5, 5) = "1";
	f1(5, 6) = "1";
	f1(5, 7) = "0";
	f1(5, 8) = "-";
	f1(5, 9) = "0";

	// f2(0, 0) = "-";
	// f2(0, 1) = "-";
	// f2(0, 2) = "0";

	// f2(1, 0) = "0";
	// f2(1, 1) = "1";
	// f2(1, 2) = "-";


	f3(0, 0) = "0";
	f3(0, 1) = "-";
	f3(0, 2) = "-";
	

	// res = f1 * f2.negation() * f3;
	res = f1.row(0);
	// res += f1.row(1);
	for (uint_t i = 1; i < 6; i++)
	{
		res += f1.row(i);
	}
	
	
	// res *= f2;
	// res *= f3;
	std::cout << "product f1 * f2 * f3 (" <<  res.rows() << "x" << res.cols() << "):" << std::endl;
	// res = res * f3;
	std::cout << "res" << std::endl;
	res.printMatrix();
	std::cout << std::endl;
	unsigned int start_time =  clock(); // начальное время
    
	res.orthogonalize().printMatrix();
	unsigned int end_time = clock(); // конечное время
    unsigned int search_time = end_time - start_time; // искомое время
	std::cout << std::endl;
	std::cout << "time = " << search_time/1000.0 << std::endl;	// res.negation().printMatrix();
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