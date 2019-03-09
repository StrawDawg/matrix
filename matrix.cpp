#include "matrix.h"
#include <random>
#include <chrono>

matrix::matrix(int n, int m)
{
	this->n = n;
	this->m = m;
	arr = new int*[n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = new int[m];
	}
}

matrix& matrix::operator=(matrix const& M)
{
	if (this != &M)
	{
		n = M.n;
		m = M.m;
		arr = new int*[n];
		for (auto i = 0; i < n; i++)
		{
			arr[i] = new int[m];
			for (auto j = 0; j < m; j++)
			{
				arr[i][j] = M.arr[i][j];
			}
		}
	}
	return *this;
}

matrix matrix::operator+(matrix const& X) const
{
	if (n == X.n && m == X.m)
	{
		std::unique_ptr<matrix> ptr(new matrix(n, m));
		for (auto i = 0; i < n; i++)
		{
			for (auto j = 0; j < m; j++)
			{
				(*ptr).change_element(i, j, (arr[i][j] + X.arr[i][j]));
			}
		}
		return *ptr;
	}
	throw std::exception("Invalid argument value: not equal dimensions");
}

matrix matrix::operator*(matrix const& X) const
{
	if (m == X.n)
	{
		std::unique_ptr<matrix> ptr(new matrix(n, m));
		auto sum = 0;
		for (auto i = 0; i < n; i++)
		{
			for (auto j = 0; j < m; j++)
			{
				for (auto l = 0; l < m; l++)
				{
					sum += arr[i][l] * X.arr[l][j];
				}
				(*ptr).change_element(i, j, sum);
				sum = 0;
			}
		}
		return *ptr;
	}
	throw std::exception("Invalid argument value: not suitable dimensions");
}

matrix matrix::transpose_matrix() const
{
	std::unique_ptr<matrix> ptr(new matrix(m, n));
	for (auto i = 0; i < m; i++)
	{
		for (auto j = 0; j < n; j++)
		{
			(*ptr).change_element(i, j, arr[j][i]);
		}
	}
	return *ptr;
}

matrix::matrix(matrix const& ptr)
{
	n = ptr.n;
	m = ptr.m;
	arr = new int*[n];
	for (auto i = 0; i < n; i++)
	{
		arr[i] = new int[m];
		for (auto j = 0; j < m; j++)
		{
			arr[i][j] = ptr.arr[i][j];
		}
	}
}

matrix::matrix(matrix&& source) noexcept
{
	n = source.n;
	m = source.m;
	arr = source.arr;
}

void matrix::change_element(int x, int y, int el)
{
	arr[x][y] = el;
}

int matrix::sum() const
{
	auto summ = 0;

	for (auto i = 0; i < n; i++)
	{
		for (auto j = 0; j < m; j++)
		{
			summ += arr[i][j];
		}
	}
	return(summ);
}

int matrix::min() const
{
	auto min = arr[0][0];
	for (auto i = 0; i < n; i++)
	{
		for (auto j = 0; j < m; j++)
		{
			if (min > arr[i][j])
			{
				min = arr[i][j];
			}
		}
	}
	return min;
}

int matrix::max() const
{
	auto max = arr[0][0];
	for (auto i = 0; i < n; i++)
	{
		for (auto j = 0; j < m; j++)
		{
			if (max < arr[i][j])
			{
				max = arr[i][j];
			}
		}
	}
	return max;
}

int matrix::entries(int x) const
{
	auto n = 0;
	for (auto i = 0; i < n; i++)
	{
		for (auto j = 0; j < m; j++)
		{
			if (arr[i][j] == x)
			{
				n++;
			}
		}
	}
	return n;
}

float matrix::avrg() const
{
	int summ = sum();
	return(static_cast<float>(summ) / (m*n));
}

void matrix::add(int x)
{
	for (auto i = 0; i < n; i++)
	{
		for (auto j = 0; j < m; j++)
		{
			arr[i][j] = x;
		}
	}
}

void matrix::addrand()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> distribution(-50, 50);
	for (auto i = 0; i < n; i++)
	{
		for (auto j = 0; j < m; j++)
		{
			arr[i][j] = distribution(generator);
		}
	}
}

matrix::~matrix()
{
	delete[] arr;
}
std::ostream& operator<<(std::ostream& out, const matrix& X)
{
	for (auto i = 0; i < X.n; i++)
	{
		for (auto j = 0; j < X.m; j++)
		{
			out << X.arr[i][j] << "  ";
		}
		out << std::endl;
	}
	return (out);
}