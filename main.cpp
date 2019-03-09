#include "matrix.h"

int main()
{
	matrix M(2, 3), N(3, 2);
	//matrix K(M);
	//matrix H(std::move(M));
	M.addrand();
	N.addrand();
	std::cout << M << "\n";
	std::cout << N << "\n";
	M = N * M;
	N = M.transpose_matrix();
	std::cout << M << "\n" << N;
	system("pause");
	return 0;
}