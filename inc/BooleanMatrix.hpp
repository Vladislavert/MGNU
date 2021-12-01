#ifndef SYMBOLIC_BOOLEAN_OPERATIONTS_ON_MATRIX_BOOLEAN_MATRIX_HPP
#define SYMBOLIC_BOOLEAN_OPERATIONTS_ON_MATRIX_BOOLEAN_MATRIX_HPP

#include <iostream>
#include <string>
#include <vector>

#include "typesData.hpp"

class BooleanMatrix
{
	public:
		BooleanMatrix() = default;
		BooleanMatrix(const uint_t sizeRows, const uint_t sizeCols);
		BooleanMatrix(const BooleanMatrix& matrix);
		~BooleanMatrix() = default;

		class OutOfBoundsException;

		BooleanMatrix&			operator=(const BooleanMatrix& matrix);
		BooleanMatrix			operator*(const BooleanMatrix& matrix);
		BooleanMatrix&			operator*=(const BooleanMatrix& matrix);
		BooleanMatrix			operator+(const BooleanMatrix& matrix);
		std::string&			operator()(const uint_t i, const uint_t j);
		const std::string&		operator()(const uint_t i, const uint_t j) const;
		BooleanMatrix			negation();
		void					printMatrix();
		uint_t					rows() const;
		uint_t					cols() const;
		BooleanMatrix			row(uint_t index);
		BooleanMatrix			col(uint_t index);

	private:
		std::vector<std::vector<std::string>>	matrix_;
		uint_t									sizeRows_;
		uint_t									sizeCols_;

		void			addRows();
		void			addCols();
		std::string		product(const std::string& arg1, const std::string& arg2);
		bool			isProductOne(const std::string& arg1, const std::string& arg2);
		bool			isProductZero(const std::string& arg1, const std::string& arg2);
		bool			isProductDash(const std::string& arg1, const std::string& arg2);
		uint_t			calculateSizeRows_(uint_t sizeRows1, uint_t sizeRows2);
		BooleanMatrix	lineNegation(const BooleanMatrix& line);
};

#endif
