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
	uint_t				i(0);
	uint_t				j(0);
	uint_t				retSizeRows = calculateSizeRows_(sizeRows_, matrix.sizeRows_);
	BooleanMatrix		retMatrix(retSizeRows, sizeCols_);
	std::vector<uint_t>	indexDelete;

	for (uint_t iRows = 0; iRows < sizeRows_; iRows++)
	{
		for (uint_t kRows = 0; kRows < matrix.sizeRows_; kRows++)
			for (uint_t jCols = 0, lCols = 0, j = 0; jCols < sizeCols_; jCols++, lCols++, j++)
			{
				retMatrix(i, j) = product(matrix_[iRows][jCols], matrix.matrix_[kRows][lCols]);
				if (retMatrix(i, j) == "-1")
				{
					indexDelete.push_back(i);
				}
				else if (((kRows == 0 && lCols == matrix.sizeCols_ - 1) || (kRows == 1 && lCols == matrix.sizeCols_ - 1)) && i < retSizeRows)
				{
					i++;
				}
			}
	}
	for (uint_t i = 0; i < ((indexDelete.size() > retSizeRows) ? retSizeRows : indexDelete.size()); i++)
	{
		if (i == 0)
			retMatrix.matrix_.erase(retMatrix.matrix_.begin() + (indexDelete[i]));
		else
			retMatrix.matrix_.erase(retMatrix.matrix_.begin() + (indexDelete[i] - i));
	}
	if (indexDelete.size() > retSizeRows)
		retMatrix.sizeRows_ -= 1;
	else
		retMatrix.sizeRows_ -= indexDelete.size();

	if (retMatrix.sizeRows_ == 0)
	{
		BooleanMatrix retEmptyMatrix(1, 1);

		retEmptyMatrix(0, 0) = "empty matrix";
		return (retEmptyMatrix);
	}

	return (retMatrix);
}

BooleanMatrix&			BooleanMatrix::operator*=(const BooleanMatrix& matrix)
{
	uint_t				i(0);
	uint_t				j(0);
	uint_t				retSizeRows = calculateSizeRows_(sizeRows_, matrix.sizeRows_);
	BooleanMatrix		retMatrix(retSizeRows, sizeCols_);
	std::vector<uint_t>	indexDelete;

	for (uint_t iRows = 0; iRows < sizeRows_; iRows++)
	{
		for (uint_t kRows = 0; kRows < matrix.sizeRows_; kRows++)
			for (uint_t jCols = 0, lCols = 0, j = 0; jCols < sizeCols_; jCols++, lCols++, j++)
			{
				retMatrix(i, j) = product(matrix_[iRows][jCols], matrix.matrix_[kRows][lCols]);
				if (retMatrix(i, j) == "-1")
				{
					indexDelete.push_back(i);
				}
				else if (((kRows == 0 && lCols == matrix.sizeCols_ - 1) || (kRows == 1 && lCols == matrix.sizeCols_ - 1)) && i < retSizeRows)
				{
					i++;
				}
			}
	}
	for (uint_t i = 0; i < ((indexDelete.size() > retSizeRows) ? retSizeRows : indexDelete.size()); i++)
	{
		if (i == 0)
			retMatrix.matrix_.erase(retMatrix.matrix_.begin() + (indexDelete[i]));
		else
			retMatrix.matrix_.erase(retMatrix.matrix_.begin() + (indexDelete[i] - i));
	}
	if (indexDelete.size() > retSizeRows)
		retMatrix.sizeRows_ -= 1;
	else
		retMatrix.sizeRows_ -= indexDelete.size();

	if (retMatrix.sizeRows_ == 0)
	{
		BooleanMatrix retEmptyMatrix(1, 1);

		retEmptyMatrix(0, 0) = "empty matrix";
		if (this != &retEmptyMatrix)
		{
			matrix_ = retEmptyMatrix.matrix_;
			sizeRows_ = retEmptyMatrix.sizeRows_;
			sizeCols_ = retEmptyMatrix.sizeCols_;
		}
		return (*this);
	}
	if (this != &retMatrix)
	{
		matrix_ = retMatrix.matrix_;
		sizeRows_ = retMatrix.sizeRows_;
		sizeCols_ = retMatrix.sizeCols_;
	}
	return (*this);
}

BooleanMatrix		BooleanMatrix::operator+(const BooleanMatrix& matrix)
{
	BooleanMatrix	retMatrix(sizeRows_ + matrix.sizeRows_, 1);

	for (uint_t iRows = 0; iRows < sizeRows_; iRows++)
		retMatrix.matrix_[iRows] = matrix_[iRows];
	for (uint_t iRows = sizeRows_, iRowsNext = 0; iRowsNext < matrix.sizeRows_; iRows++, iRowsNext++)
		retMatrix.matrix_[iRows] = matrix.matrix_[iRowsNext];

	retMatrix.sizeRows_ = sizeRows_ + matrix.sizeRows_;
	retMatrix.sizeCols_ = sizeCols_;

	return (retMatrix);
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

const		std::string& BooleanMatrix::operator()(const uint_t i, const uint_t j) const
{
	if (i >= sizeRows_ || j >= sizeCols_)
		throw OutOfBoundsException();
	
	return (matrix_[i][j]);
}

/**
 * @brief Нахождение отрицания
 * 
 * @return отрицательная матрица 
 */
BooleanMatrix		BooleanMatrix::negation()
{
	BooleanMatrix	retMatrix(1, sizeCols_);
	BooleanMatrix	tempMatrix(sizeRows_, sizeCols_);

	tempMatrix.matrix_ = matrix_;

	retMatrix = lineNegation(tempMatrix.row(0));
	for (uint_t i = 1; i < sizeRows_; i++)
	{
		retMatrix *= lineNegation(tempMatrix.row(i));
	}

	return (retMatrix);
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

uint_t		BooleanMatrix::rows() const
{
	return (sizeRows_);
}

uint_t		BooleanMatrix::cols() const
{
	return (sizeCols_);
}

/**
 * @brief возвращает строку матрицы по указанному индексу
 * 
 * @param index 
 * @return BooleanMatrix 
 */
BooleanMatrix		BooleanMatrix::row(uint_t index)
{
	BooleanMatrix	retLine(1, sizeCols_);

	for (uint_t i = 0; i < sizeCols_; i++)
	{
		retLine(0, i) = matrix_[index][i];
	}
	
	return (retLine);
}

// uint_t BooleanMatrix::cols() const
// {
// 	return (sizeCols_);
// }

/**
 * @brief добавление строк
 * 
 */
void		BooleanMatrix::addRows()
{
	matrix_.push_back(std::vector<std::string>(sizeCols_));
}

/**
 * @brief добавление столбцов
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
	std::string	retSymbol;

	if (isProductDash(arg1, arg2))
		retSymbol = "-";
	else if (isProductOne(arg1, arg2))
		retSymbol = "1";
	else if (isProductZero(arg1, arg2))
		retSymbol = "0";
	else
		retSymbol = "-1";

	return (retSymbol);
}

/**
 * @brief Проверка на получение - при умножении
 * 
 * @param arg1
 * @param arg2 
 * @return true если при умножении получается -
 * @return false 
 */
bool		BooleanMatrix::isProductDash(const std::string& arg1, const std::string& arg2)
{
	if ((arg1 == "-") && (arg2 == "-"))
		return (true);

	return (false);
}

/**
 * @brief Проверка на получении 1 при умножении
 * 
 * @param arg1 
 * @param arg2 
 * @return true если при умножении получается 1
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

/**
 * @brief Проверка на получении 0 при умножении
 * 
 * @param arg1 
 * @param arg2 
 * @return true если при умножении получается 0
 * @return false 
 */
bool		BooleanMatrix::isProductZero(const std::string& arg1, const std::string& arg2)
{
	if (((arg1 == "0") && ((arg2 == "0") || (arg2 == "-"))) ||
		((arg2 == "0") && ((arg1 == "-") || (arg1 == "0"))))
	{
		return (true);
	}
	return (false);
}

/**
 * @brief Рассчёт кол-ва строк, которое получаем при умножении
 * 
 * @param sizeRows1 размер строки первого множителя
 * @param sizeRows2 размер строки второго множителя
 * @return uint_t 
 */
uint_t		BooleanMatrix::calculateSizeRows_(uint_t sizeRows1, uint_t sizeRows2)
{
	uint_t	retSizeRows(0);

	for (uint_t i = 0; i < sizeRows1; i++)
	{
		retSizeRows += sizeRows2;
	}

	return (retSizeRows);
}

/**
 * @brief нахождение отрицание для троичной строки
 * 
 * @param line троичная строка
 * @return матрицы отрицания для троичной строки
 */
BooleanMatrix		BooleanMatrix::lineNegation(const BooleanMatrix& line)
{
	BooleanMatrix		retMatrix(1, sizeCols_);
	uint_t				sizeRows = 0;
	std::vector<uint_t>	indexDash;
	std::vector<uint_t> indexOneAndZero;

	//TODO(vladislavert): написать проверку, на аргумент функции(должна быть строка)

	for (uint_t i = 0; i < line.cols(); i++)
		if (line(0, i) == "-")
			indexDash.push_back(i);
	for (uint_t i = 0; i < line.cols(); i++)
		if (line(0, i) == "1" || line(0, i) == "0")
			indexOneAndZero.push_back(i);
	sizeRows = line.cols() - indexDash.size();
	retMatrix(sizeRows, line.cols());
	// for (uint_t i = 0; i < sizeRows; i++)
	// {
	// 	if (i == indexOneAndZero[0])
	// 		retMatrix(0, i) = line(0, indexOneAndZero[0]);
	// 	else
	// 		retMatrix(0, i) = "-";
	// }
	for (uint_t i = 0; i < sizeRows; i++)
	{
		for (uint_t j = 0; j < line.cols(); j++)
		{
			if (j == indexOneAndZero[i])
				retMatrix(i, j) = line(0, indexOneAndZero[i]) == "1" ? "0" : "1";
			else
				retMatrix(i, j) = "-";
		}
	}

	return (retMatrix);
}