#pragma once
#include <iostream>

class matrix
{
	int** arr;
	int n;
	int m;

	friend std::ostream& operator<<(std::ostream& out, const matrix& X);
public:
	matrix(int n, int m);
	matrix& operator=(matrix const& M);
	matrix operator+(matrix const& X) const;
	matrix operator*(matrix const& X) const;
	matrix transpose_matrix() const;
	matrix(matrix const& ptr);
	matrix(matrix&& source) noexcept;
	void change_element(int x, int y, int el);
	int sum() const;
	int min() const;
	int max() const;
	int entries(int x) const;
	float avrg() const;
	void add(int x);
	void addrand();
	virtual ~matrix();
};
std::ostream& operator<<(std::ostream& out, const matrix& X);
