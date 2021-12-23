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
	: matrix_(matrix.matrix_),
	  sizeRows_(matrix.sizeRows_),
	  sizeCols_(matrix.sizeCols_)
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

/**
 * @brief Умножение
 * 
 * @param matrix 
 * @return BooleanMatrix 
 */
BooleanMatrix		BooleanMatrix::operator*(const BooleanMatrix& matrix)
{
	uint_t				i(0);
	uint_t				retSizeRows = calculateSizeRows_(sizeRows_, matrix.sizeRows_);
	BooleanMatrix		retMatrix(retSizeRows, sizeCols_);
	std::vector<uint_t>	indexDelete;

	for (uint_t iRows = 0; iRows < sizeRows_; iRows++) // перебор по строкам 1-ой матрицы
	{
		for (uint_t kRows = 0; kRows < matrix.sizeRows_; kRows++) // перебор по строкам 2-ой матрицы
			for (uint_t jCols = 0, lCols = 0, j = 0; jCols < sizeCols_; jCols++, lCols++, j++)
			{
				retMatrix(i, j) = product(matrix_[iRows][jCols], matrix.matrix_[kRows][lCols]);
				if (retMatrix(i, j) == "-1")
				{
					indexDelete.push_back(i);
					retMatrix.sizeRows_ -= 1;
					retMatrix.matrix_.erase(retMatrix.matrix_.end() - 1);

					break ;
				}
				// else if (((kRows == 0 && lCols == matrix.sizeCols_ - 1) || (kRows == 1 && lCols == matrix.sizeCols_ - 1)) && i < retSizeRows)
				else if ((lCols == matrix.sizeCols_ - 1) && i < retSizeRows)
				{
					i++;
				}
			}
	}
	if (retMatrix.sizeRows_ == 0)
	{
		BooleanMatrix retEmptyMatrix(1, 1);

		retEmptyMatrix(0, 0) = kEmpty;
		return (retEmptyMatrix);
	}
	retMatrix.orthogonalize();

	return (retMatrix);
}

BooleanMatrix&			BooleanMatrix::operator*=(const BooleanMatrix& matrix)
{
	BooleanMatrix		retMatrix;

	retMatrix = *this * matrix;

	*this = retMatrix;

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
	// retMatrix.orthogonalize();

	return (retMatrix);
}

BooleanMatrix		BooleanMatrix::operator+=(const BooleanMatrix& matrix)
{
	BooleanMatrix	retMatrix(sizeRows_ + matrix.sizeRows_, 1);

	retMatrix = *this + matrix;

	*this = retMatrix;

	return (*this);
}

bool		BooleanMatrix::operator==(const BooleanMatrix& matrix)
{
	//TOOD(vladilsavert): Добавить проверку на несоответствие размера
	for (uint_t iRows = 0; iRows < sizeRows_; iRows++)
	{
		for (uint_t jCols = 0; jCols < sizeCols_; jCols++)
		{
			if (this->matrix_[iRows][jCols] != matrix(iRows, jCols))
				return (false);
		}
	}

	return (true);
}

bool		BooleanMatrix::operator!=(const BooleanMatrix& matrix)
{
	return (!(*this == matrix));
}

bool		BooleanMatrix::operator==(const std::string& empty)
{
	if (this->matrix_[0][0] == empty)
		return (true);

	return (false);
}

bool		BooleanMatrix::operator!=(const std::string& empty)
{
	return (!(*this == empty));
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
 * @brief Нахождение отрицательной матрицы
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

//TODO(vladislavert): Протестировать работу метода
//TODO(vladislavert): Не всегда из отсутствия ортогональности
// следует вложенность векторов, пример: (1 -) * (- 1) = (1 1) - не ортогональны,
// но один не вложен в другой, (1 -; 0 -) - результат ортогонализации
/**
 * @brief Ортогонализация вектора
 * 
 */
BooleanMatrix		BooleanMatrix::orthogonalize()
{
	BooleanMatrix		retMatrix;
	uint_t				quantityDashOne = 0;
	uint_t				quantityDashSecond = 0;
	bool flag = true;

	for (uint_t iRows = 0; iRows < sizeRows_; /*iRows++*/)
	{
		for (uint_t jRows = iRows + 1; jRows < sizeRows_; jRows++)
		{
			if (this->row(iRows) * this->row(jRows) != kEmpty)
			{
				// если "-" больше, то удаляется другой вектор
				quantityDashOne = 0;
				quantityDashSecond = 0;
				for (uint_t iCols = 0; iCols < this->sizeCols_; iCols++)
				{
					if (this->matrix_[iRows][iCols] == "-")
						quantityDashOne++;
					if (this->matrix_[jRows][iCols] == "-")
						quantityDashSecond++;
				}
				if (quantityDashOne < quantityDashSecond)
					searchForOrthogonalVectors(iRows, jRows);
					// deleteRow(iRows);
				else
					searchForOrthogonalVectors(jRows, iRows);
					// deleteRow(jRows);
				flag = false;
			}
		}
		if (flag == true)
			iRows++;
		flag = true;
	}

	return (*this);
}

/**
 * @brief Вывод матрицы
 * 
 */
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
 * @brief Размер строки
 * 
 * @return uint_t 
 */
uint_t		BooleanMatrix::rows() const
{
	return (sizeRows_);
}

/**
 * @brief Размер столбцов
 * 
 * @return uint_t 
 */
uint_t		BooleanMatrix::cols() const
{
	return (sizeCols_);
}

/**
 * @brief возвращает строку матрицы по указанному индексу
 * 
 * @param index индекс строки
 * @return строка 
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

/**
 * @brief возвращает столбец матрицы по указанному индексу
 * 
 * @param index индекс столбца
 * @return столбец
 */
BooleanMatrix		BooleanMatrix::col(uint_t index)
{
	BooleanMatrix	retCol(sizeRows_, 1);

	for (uint_t i = 0; i < sizeRows_; i++)
	{
		retCol(i, 0) = matrix_[i][index];
	}

	return (retCol);
}

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

/**
 * @brief Умножение строк
 * 
 * @param arg1
 * @param arg2 
 * @return результат умножения строк
 */
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
 * @brief Проверка на получение "-" при умножении
 * 
 * @param arg1
 * @param arg2 
 * @return true если при умножении получается "-"
 * @return false 
 */
bool		BooleanMatrix::isProductDash(const std::string& arg1, const std::string& arg2)
{
	if ((arg1 == "-") && (arg2 == "-"))
		return (true);

	return (false);
}

/**
 * @brief Проверка на получении "1" при умножении
 * 
 * @param arg1 
 * @param arg2 
 * @return true если при умножении получается "1"
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
 * @brief Проверка на получении "0" при умножении
 * 
 * @param arg1 
 * @param arg2 
 * @return true если при умножении получается "0"
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

	//TODO(vladislavert): написать проверку на аргумент функции(должна быть строка)
	for (uint_t i = 0; i < line.cols(); i++)
		if (line(0, i) == "-")
			indexDash.push_back(i);
	for (uint_t i = 0; i < line.cols(); i++)
		if (line(0, i) == "1" || line(0, i) == "0")
			indexOneAndZero.push_back(i);
	sizeRows = line.cols() - indexDash.size();
	retMatrix(sizeRows, line.cols());
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

void			BooleanMatrix::searchForOrthogonalVectors(const uint_t indexMaxDash,
														  const uint_t indexMinDash)
{

}

//TODO(vladislavert): Добавить возможность удаления вне класса
void			BooleanMatrix::deleteRow(const uint_t index)
{
	this->matrix_.erase(this->matrix_.begin() + index);
	this->sizeRows_ -= 1;
}

vectUint_t		BooleanMatrix::searchNotDashIndexInCols(const uint_t indexRow)
{
	vectUint_t	retIndexNotDash;

	for (uint_t iCols = 0; iCols < sizeCols_; iCols++)
		if (this->matrix_[indexRow][iCols] != "-")
			retIndexNotDash.push_back(iCols);

	return (retIndexNotDash);
}