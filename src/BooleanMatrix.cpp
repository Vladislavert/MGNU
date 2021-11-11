#include "BooleanMatrix.hpp"
#include <exception>

BooleanMatrix::BooleanMatrix(const uint_t sizeRows, const uint_t sizeCols)
 	: sizeRows_(sizeRows),
	  sizeCols_(sizeCols)
{
	for (uint_t i = 0; i < sizeRows; i++)
	{
		matrix_.push_back(std::vector<std::string>(sizeCols));
	}
	
}

BooleanMatrix::BooleanMatrix(const BooleanMatrix& matrix)
	: sizeRows_(matrix.sizeRows_),
	  sizeCols_(matrix.sizeCols_),
	  matrix_(matrix.matrix_)
{ }

class BooleanMatrix::OutOfBoundsException : public std::exception
{
	public:
		const char* what() const noexcept override
		{
			return ("Out of bounds");
		}
};

BooleanMatrix& BooleanMatrix::operator=(const BooleanMatrix& matrix)
{
	if (this != &matrix)
	{
		matrix_ = matrix.matrix_;
		sizeRows_ = matrix.sizeRows_;
		sizeCols_ = matrix.sizeCols_;
	}

	return (*this);
}

BooleanMatrix		BooleanMatrix::operator*(const BooleanMatrix& matrix)
{
	uint_t	i(0);
	uint_t	j(0);
	uint_t	resSizeRows = calculateSizeRows_(sizeRows_, matrix.sizeRows_);
	BooleanMatrix	resMatrix(resSizeRows, sizeCols_);
	std::vector<uint_t>			indexDelete;

	for (uint_t iRows = 0; iRows < sizeRows_; iRows++)
	{
		for (uint_t kRows = 0; kRows < matrix.sizeRows_; kRows++)
			for (uint_t jCols = 0, lCols = 0, j = 0; jCols < sizeCols_; jCols++, lCols++, j++)
			{
				resMatrix(i, j) = product(matrix_[iRows][jCols], matrix.matrix_[kRows][lCols]);
				// if (resMatrix(i, j) == "-1")
				// {
				// 	BooleanMatrix resEmptyMatrix(1, 1);
				// 	resEmptyMatrix(0, 0) = "empty matrix";
				// 	return (resEmptyMatrix);
				// }
				if (resMatrix(i, j) == "-1")
				{
					indexDelete.push_back(i);
				}
				else if (((kRows == 0 && lCols == matrix.sizeCols_ - 1) || (kRows == 1 &&lCols == matrix.sizeCols_ - 1)) && i < resSizeRows)
				{
					i++;
				}
			}
	}
	for (uint_t i = 0; i < indexDelete.size(); i++)
	{
		if (i == 0)
			resMatrix.matrix_.erase(resMatrix.matrix_.begin() + (indexDelete[i]));
		else
			resMatrix.matrix_.erase(resMatrix.matrix_.begin() + (indexDelete[i] - i));
	}
	resMatrix.sizeRows_ -= indexDelete.size();

	return (resMatrix);
}

/**
 * @brief 
 * 
 * @param matrix 
 * @return BooleanMatrix 
 */
BooleanMatrix		BooleanMatrix::operator+(const BooleanMatrix& matrix)
{
	BooleanMatrix	resMatrix(sizeRows_ + matrix.sizeRows_, 1);

	for (uint_t iRows = 0; iRows < sizeRows_; iRows++)
		resMatrix.matrix_[iRows] = matrix_[iRows];
	for (uint_t iRows = sizeRows_, iRowsNext = 0; iRowsNext < matrix.sizeRows_; iRows++, iRowsNext++)
		resMatrix.matrix_[iRows] = matrix.matrix_[iRowsNext];

	resMatrix.sizeRows_ = sizeRows_ + matrix.sizeRows_;
	resMatrix.sizeCols_ = sizeCols_;

	return (resMatrix);
}

/**
 * @brief 
 * 
 * @param i 
 * @param j 
 * @return std::string& 
 */
std::string&		BooleanMatrix::operator()(const uint_t i, const uint_t j)
{
	if (i >= sizeRows_)
	{
		sizeRows_++;
		addRows();
	}
	return (matrix_[i][j]);
}

const std::string& BooleanMatrix::operator()(const uint_t i, const uint_t j) const
{
	if (i >= sizeRows_ || j >= sizeCols_)
		throw OutOfBoundsException();
	
	return (matrix_[i][j]);
}

void		BooleanMatrix::printMatrix()
{
	for (uint_t i = 0; i < sizeRows_; i++)
	{
		for (uint_t j = 0; j < sizeCols_; j++)
		{
			std::cout << matrix_[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

/**
 * @brief 
 * 
 */
void		BooleanMatrix::addRows()
{
	matrix_.push_back(std::vector<std::string>(sizeCols_));
}

/**
 * @brief 
 * 
 */
void		BooleanMatrix::addCols()
{
	for (uint_t i = 0; i < sizeRows_; i++)
	{
		matrix_[i].push_back(std::string());
	}	
}

std::string		BooleanMatrix::product(const std::string& arg1, const std::string& arg2)
{
	std::string	resSymbol;

	if (isProductDash(arg1, arg2))
		resSymbol = "-";
	else if (isProductOne(arg1, arg2))
		resSymbol = "1";
	else if (isProductZero(arg1, arg2))
		resSymbol = "0";
	else
		resSymbol = "-1";

	return (resSymbol);
}

/**
 * @brief 
 * 
 * @param arg1 
 * @param arg2 
 * @return true 
 * @return false 
 */
bool		BooleanMatrix::isProductDash(const std::string& arg1, const std::string& arg2)
{
	if ((arg1 == "-") && (arg2 == "-"))
		return (true);
	return (false);
}

/**
 * @brief 
 * 
 * @param arg1 
 * @param arg2 
 * @return true 
 * @return false 
 */
bool		BooleanMatrix::isProductOne(const std::string& arg1, const std::string& arg2)
{
	if (((arg1 == "1") && ((arg2 == "1") || (arg2 == "-"))) ||
		((arg2 == "1") && ((arg1 == "-") || (arg1 == "1"))))
	{
		return (true);
	}
	return (false);
}

bool		BooleanMatrix::isProductZero(const std::string& arg1, const std::string& arg2)
{
	if (((arg1 == "0") && ((arg2 == "0") || (arg2 == "-"))) ||
		((arg2 == "0") && ((arg1 == "-") || (arg1 == "0"))))
	{
		return (true);
	}
	return (false);
}

uint_t		BooleanMatrix::calculateSizeRows_(uint_t sizeRows1, uint_t sizeRows2)
{
	uint_t	resSizeRows(0);

	for (uint_t i = 0; i < sizeRows1; i++)
	{
		resSizeRows += sizeRows2;
	}

	return (resSizeRows);
}
