#ifndef MGNU_BOOLEAN_MATRIX_BOOLEAN_MATRIX_HPP_
#define MGNU_BOOLEAN_MATRIX_BOOLEAN_MATRIX_HPP_

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
		BooleanMatrix			operator+=(const BooleanMatrix& matrix);
		bool					operator==(const BooleanMatrix& matrix);
		bool					operator!=(const BooleanMatrix& matrix);
		bool					operator==(const std::string& empty);
		bool					operator!=(const std::string& empty);
		std::string&			operator()(const uint_t i, const uint_t j);
		const std::string&		operator()(const uint_t i, const uint_t j) const;
		BooleanMatrix			negation();
		BooleanMatrix			orthogonalize();
		void					printMatrix();
		uint_t					rows() const;
		uint_t					cols() const;
		BooleanMatrix			row(uint_t index);
		BooleanMatrix			col(uint_t index);

	private:
		std::vector<std::vector<std::string>>	matrix_;
		uint_t									sizeRows_;
		uint_t									sizeCols_;
		const std::string						kEmpty = "empty matrix";

		void			addRows();
		void			addCols();
		std::string		product(const std::string& arg1, const std::string& arg2);
		bool			isProductOne(const std::string& arg1, const std::string& arg2);
		bool			isProductZero(const std::string& arg1, const std::string& arg2);
		bool			isProductDash(const std::string& arg1, const std::string& arg2);
		uint_t			calculateSizeRows_(uint_t sizeRows1, uint_t sizeRows2);
		BooleanMatrix	lineNegation(const BooleanMatrix& line);
		void			searchForOrthogonalVectors(const uint_t indexMaxDash, const uint_t indexMinDash);
		void			deleteRow(const uint_t index);
};

#endif
