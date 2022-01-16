#include <iostream>

#include "typesData.hpp"
#include "BooleanMatrix.hpp"

int main()
{
	BooleanMatrix ret;

	// initialize
	// BooleanMatrix psi_0(2, 3);
	// BooleanMatrix psi_1(1, 3);
	// BooleanMatrix psi_2(1, 10);

	// psi_0(0, 0) = "0";
	// psi_0(0, 1) = "1";
	// psi_0(0, 2) = "-";

	// psi_0(1, 0) = "1";
	// psi_0(1, 1) = "-";
	// psi_0(1, 2) = "0";

	// psi_1(0, 0) = "-";
	// psi_1(0, 1) = "1";
	// psi_1(0, 2) = "0";

	BooleanMatrix psi_1(1, 6);
	BooleanMatrix psi_2(1, 6);
	BooleanMatrix psi_3(1, 6);
	BooleanMatrix psi_4(1, 6);
	BooleanMatrix psi_5(1, 6);
	BooleanMatrix psi_6(1, 6);

	for (size_t i = 0; i < psi_1.cols(); i++)
	{
		psi_1(0, i) = "-";
		psi_2(0, i) = "-";
		psi_3(0, i) = "-";
		psi_4(0, i) = "-";
		psi_5(0, i) = "-";
		psi_6(0, i) = "-";
	}
	

	psi_1(0, 0) = "1";
	psi_2(0, 1) = "1";
	psi_3(0, 2) = "1";
	psi_4(0, 3) = "1";
	psi_5(0, 4) = "1";
	psi_6(0, 5) = "1";

	// (psi_1 + (psi_2 * psi_3) + (psi_4 * psi_5 * psi_6)).orthogonalize().printMatrix();
	ret = (psi_1 + (psi_2 * psi_3) + (psi_4 * psi_5 * psi_6));
	ret.printMatrix();
	std::cout << "-------------------------" << std::endl;
	// TODO(Vladislvaert): ПРоверить корректность работы ортоганализации
	ret.orthogonalize().printMatrix();
	// (psi_1 * (psi_2 * psi_3)).printMatrix();



	return (0);
}