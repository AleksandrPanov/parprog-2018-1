#include <omp.h>
#include <string>
#include<iostream>
#include <vector>
#include "matrix.h"

using std::vector;
using std::string;

MatrixCCS MatrixMult(MatrixCCS &A, MatrixCCS &B);

int main(int argc, char * argv[])//������ �� ��������� �����, ��������� ���������, ����� � �������� ����
{
	int num_threads = 1;
    string path = "";
	string name = "matr";
	string number = "";
	string extensionIn = ".in";
	string extensionOut = ".user.ans";
	if (argc > 1)
	{
        path = argv[1];
        if (argc > 2)
        {
            num_threads = atoi(argv[2]);
            if (argc > 3)
            {
                number = argv[3];
            }
        }
	}

	int N;
	freopen((path + name + number + extensionIn).c_str(), "rb", stdin);
	freopen((path + name + number + extensionOut).c_str(), "wb", stdout);
	fread(&N, sizeof(N), 1, stdin);
    Matrix A(N, N), B(N, N), Res(N,N);
   
    fread(A.getP(), sizeof(Element), N * N, stdin);
    fread(B.getP(), sizeof(Element), N * N, stdin);

    MatrixCCS Acol(A), Bcol(B), ResCol;
    
    omp_set_num_threads(num_threads);
	
    double time = omp_get_wtime();	
    ResCol = MatrixMult(Acol, Bcol);
	time = omp_get_wtime() - time;

    ResCol.convertToMatrix(Res);

	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(Res.getP(), sizeof(Element), N * N, stdout);
	return 0;
}