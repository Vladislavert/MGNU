#include <iostream>

#include "typesData.hpp"
#include "BooleanMatrix.hpp"

int main()
{
	BooleanMatrix ret;

	// initialize
	BooleanMatrix psi_0(1, 10);
	BooleanMatrix psi_1(1, 10);
	BooleanMatrix psi_2(1, 10);
	BooleanMatrix psi_3(1, 10);
	BooleanMatrix psi_4(1, 10);
	BooleanMatrix psi_5(1, 10);
	BooleanMatrix psi_6(1, 10);
	BooleanMatrix psi_7(1, 10);
	BooleanMatrix psi_8(1, 10);
	BooleanMatrix psi_9(1, 10);
	BooleanMatrix psi_10(2, 10);
	BooleanMatrix psi_11(1, 10);
	BooleanMatrix psi_12(9, 10);

	for (size_t j = 0; j < psi_0.cols(); j++)
	{
		psi_0(0, j) = "1";
		psi_1(0, j) = "1";
		psi_2(0, j) = "1";
		psi_3(0, j) = "1";
		psi_4(0, j) = "1";
		psi_5(0, j) = "1";
		psi_6(0, j) = "1";
		psi_7(0, j) = "1";
		psi_8(0, j) = "1";
		psi_9(0, j) = "1";
		psi_10(0, j) = "1";
		psi_10(1, j) = "1";
		psi_11(0, j) = "1";
	}
	psi_1(0, 7) = "0";
	psi_2(0, 6) = "0";
	psi_3(0, 4) = "0";

	psi_4(0, 6) = "0";
	psi_4(0, 7) = "0";

	psi_5(0, 4) = "0";
	psi_5(0, 7) = "0";

	psi_6(0, 4) = "0";
	psi_6(0, 6) = "0";

	psi_7(0, 4) = "-";

	psi_8(0, 4) = "-";
	psi_8(0, 7) = "0";

	psi_9(0, 4) = "0";
	psi_9(0, 6) = "0";
	psi_9(0, 7) = "0";

	psi_10(0, 1) = "0";
	psi_10(0, 6) = "-";
	psi_10(0, 7) = "-";
	psi_10(0, 8) = "-";

	psi_10(1, 6) = "-";
	psi_10(1, 7) = "-";
	psi_10(1, 8) = "0";

	psi_11(1, 4) = "-";
	psi_11(1, 5) = "0";
	psi_11(1, 6) = "0";

	for (size_t i = 0; i < psi_12.rows(); i++)
		for (size_t j = 0; j < psi_12.cols(); j++)
			psi_12(i, j) = "-";
	psi_12(0, 0) = "0";
	psi_12(1, 2) = "0";
	psi_12(2, 3) = "0";
	psi_12(3, 9) = "0";
	psi_12(4, 1) = "0";
	psi_12(4, 4) = "0";
	psi_12(5, 4) = "0";
	psi_12(5, 8) = "0";
	psi_12(6, 1) = "0";
	psi_12(6, 5) = "0";
	psi_12(7, 5) = "0";
	psi_12(7, 8) = "0";
	psi_12(8, 5) = "0";
	psi_12(8, 6) = "0";
	psi_12(8, 7) = "0";

	// end initialize

	psi_12.negation().orthogonalize().printMatrix();


	// check lab_4

	for (size_t i = 0; i < psi_0.cols(); i++)
	{
		psi_0(0, i) = "1";
		psi_0(0, i) = "0";
	
		std::cout << "elements_" << i << ": ";
		(psi_0 * psi_4).printMatrix();
	}
	


	return (0);
}