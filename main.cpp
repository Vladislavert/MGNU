#include <iostream>

#include "typesData.hpp"
#include "BooleanMatrix.hpp"

//TODO (chuvarevanv@mail.ru): rename 
const uint_t kQuantityElements = 10;
const uint_t kJ = 6;
const uint_t kJInverse = 9;

BooleanMatrix		threePointMatrix()
{
	BooleanMatrix resMatrix(kJ, kQuantityElements);

	for	(uint_t i = 0; i < kJ; i++)
	{
		for (uint_t j = 0; j < kQuantityElements; j++)
		{
			resMatrix(i, j) = "1";
		}
	}

	resMatrix(0, 1) = "-";
	resMatrix(0, 6) = "-";
	resMatrix(0, 7) = "-";
	resMatrix(0, 8) = "-";

	resMatrix(1, 4) = "0";
	resMatrix(1, 6) = "-";
	resMatrix(1, 7) = "-";

	resMatrix(2, 4) = "0";
	resMatrix(2, 5) = "0";
	resMatrix(2, 7) = "-";

	resMatrix(3, 4) = "0";
	resMatrix(3, 5) = "0";
	resMatrix(3, 6) = "0";

	resMatrix(4, 5) = "0";
	resMatrix(4, 7) = "-";

	resMatrix(5, 5) = "0";
	resMatrix(5, 6) = "0";

	return (resMatrix);
}

BooleanMatrix		convertThreePointMatrixToDoublePointMatrix(const BooleanMatrix& matrix)
{
	BooleanMatrix resMatrix(1, kQuantityElements);
	uint_t iRes;

	iRes = 0;
	for (uint_t i = 0; i < kJ; i++)
	{
		for (uint_t j = 0; j < kQuantityElements; j++)
		{
			if (matrix(i, j) == "-")
			{

				resMatrix(i, j) = "1";
			}
			else
				resMatrix(i, j) = matrix(i, j);
		}
	}

	return (resMatrix);
}

BooleanMatrix		threePointMatrixInverse()
{
	BooleanMatrix resMatrix(kJInverse, kQuantityElements);

	for	(uint_t i = 0; i < kJInverse; i++)
	{
		for (uint_t j = 0; j < kQuantityElements; j++)
		{
			resMatrix(i, j) = "-";
		}
	}

	resMatrix(0, 0) = "0";
	resMatrix(1, 2) = "0";
	resMatrix(2, 3) = "0";
	resMatrix(3, 9) = "0";
	resMatrix(4, 1) = "0";
	resMatrix(4, 4) = "0";
	resMatrix(5, 4) = "0";
	resMatrix(5, 8) = "0";
	resMatrix(6, 1) = "0";
	resMatrix(6, 5) = "0";
	resMatrix(7, 5) = "0";
	resMatrix(7, 8) = "0";
	resMatrix(8, 5) = "0";
	resMatrix(8, 6) = "0";
	resMatrix(8, 7) = "0";

	return (resMatrix);
}


int main()
{
	BooleanMatrix inverseMatrix;
	BooleanMatrix matrix;

	inverseMatrix = threePointMatrixInverse();
	matrix = threePointMatrix();

	inverseMatrix.printMatrix();
	std::cout << std::endl;
	matrix.printMatrix();

	BooleanMatrix a(1, kQuantityElements);


	a.printMatrix();

	return (0);
}