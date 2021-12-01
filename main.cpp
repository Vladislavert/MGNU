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

bool		nextSet(std::vector<uint_t>& set, int n, int m)
{
	int i(m - 1);

	while (i >= 0 && set[i] == n)
		i--;
	if (i < 0)
		return (false);
	if (set[i] >= n)
		i--;
	set[i]++;
	if (i == m - 1)
		return (true);
	for (uint_t j = i + 1; j < m; j++)
		set[j] = 1;

	return (true);
}

void		addRowToDoubleMatrix(BooleanMatrix& matrix, const std::vector<std::string>& rowBuffer,
								const std::vector<uint_t>& rowBoolValues)
{
	uint_t lastRowIdx(matrix.rows());
	uint_t boolValsIdx(0);

	for (uint_t i = 0; i < rowBuffer.size(); i++)
	{
		if (rowBuffer[i] == "-")
			matrix(lastRowIdx, i) = std::to_string(rowBoolValues[boolValsIdx++] - 1);
		else
			matrix(lastRowIdx, i) = rowBuffer[i];
	}
}

BooleanMatrix		convertThreePointMatrixToDoublePointMatrix(const BooleanMatrix& matrix)
{
	constexpr uint_t n(2);
	BooleanMatrix resMatrix(1, kQuantityElements);
	std::vector<uint_t> set;
	std::vector<std::string> rowBuffer;
	uint_t iRes;
	uint_t dashCount;

	iRes = 0;
	for (uint_t i = 0; i < matrix.rows(); i++)
	{
		dashCount = 0;
		for (uint_t j = 0; j < matrix.cols(); j++)
		{
			if (matrix(i, j) == "-")
				dashCount++;
			rowBuffer.push_back(matrix(i, j));
		}
		if (dashCount > 0)
		{
			set = std::vector<uint_t>(dashCount, 1);
			while (nextSet(set, n, dashCount))
				addRowToDoubleMatrix(resMatrix, rowBuffer, set);
		}
		rowBuffer.clear();
	}

	return (resMatrix);
}

/**
 * @brief Проверка принадлежности к вершине
 * 
 * @param vertices вершина
 * @param vector вектор, который проверяется на принадлежность вершине
 * @return true принадлежит вершине
 * @return false не принадлежит вершине 
 */
bool		checkBelongVertices(BooleanMatrix vertices, BooleanMatrix vector)
{
	
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

	// BooleanMatrix a(1, kQuantityElements);


	// a.printMatrix();

	// BooleanMatrix a(1, kQuantityElements);
	// BooleanMatrix b(1, kQuantityElements);
	// BooleanMatrix res(1, kQuantityElements);

	BooleanMatrix a(1, kQuantityElements);
	BooleanMatrix b(1, kQuantityElements);
	BooleanMatrix res(1, kQuantityElements);

	// a(0, 0) = "1";
	// a(0, 1) = "-";
	// a(0, 2) = "1";
	// a(0, 3) = "1";
	// a(0, 4) = "1";
	// a(0, 5) = "1";
	// a(0, 6) = "-";
	// a(0, 7) = "-";
	// a(0, 8) = "-";
	// a(0, 9) = "1";

	// b(0, 0) = "1";
	// b(0, 1) = "-";
	// b(0, 2) = "1";
	// b(0, 3) = "1";
	// b(0, 4) = "1";
	// b(0, 5) = "1";
	// b(0, 6) = "-";
	// b(0, 7) = "-";
	// b(0, 8) = "-";
	// b(0, 9) = "1";

	// b(0, 0) = "1";
	// b(0, 1) = "0";
	// b(0, 2) = "1";
	// b(0, 3) = "1";
	// b(0, 4) = "1";
	// b(0, 5) = "1";
	// b(0, 6) = "-";
	// b(0, 7) = "-";
	// b(0, 8) = "0";
	// b(0, 9) = "1";


	a(0, 0) = "1";
	a(0, 1) = "1";
	a(0, 2) = "1";
	a(0, 3) = "1";
	a(0, 4) = "1";
	a(0, 5) = "1";
	a(0, 6) = "0";
	a(0, 7) = "0";
	a(0, 8) = "0";
	a(0, 9) = "1";

	b(0, 0) = "1";
	b(0, 1) = "1";
	b(0, 2) = "1";
	b(0, 3) = "1";
	b(0, 4) = "1";
	b(0, 5) = "1";
	b(0, 6) = "0";
	b(0, 7) = "0";
	b(0, 8) = "0";
	b(0, 9) = "1";

	res = a * b;
	std::cout << std::endl;
	res.printMatrix();


	BooleanMatrix testNegation(2, 3);


	testNegation(0, 0) = "0";
	testNegation(0, 1) = "1";
	testNegation(0, 2) = "-";
	testNegation(1, 0) = "1";
	testNegation(1, 1) = "-";
	testNegation(1, 2) = "0";

	testNegation.row(0).printMatrix();
	std::cout << std::endl;

	std::cout << "result:" << std::endl;

	testNegation.negation().printMatrix();

	return (0);
}