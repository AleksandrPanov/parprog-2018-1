#include <cstdio>
#include <random>
#include <ctime>
#include <chrono>
#include <iostream>
#include "../include/matrix.h"
using namespace std;
/*int n_tests[] = { 1, 2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 100, 200, 300, 400, 500,
600, 700, 800, 900, 1000 };*/
int main(int argc, char * argv[])
{
    string path = "./";
    string output = "matr";
    string number = "";
    string extensionOut = ".in";
    string extensionOutAnswer = ".ans";

    // ����� ������ ������
    // ���� �������� ����� ����� � ���������� ��������� ������, �� ���� ������ �� n_tests
    int n = 10;
    if (argc > 1)
    {
        path = argv[1];
        if (argc > 2)
        {
            n = atoi(argv[2]);
            if (argc > 3)
            {
                number = argv[3];
                output = "";
                if (argc > 4)
                {
                    output = argv[4];
                }
            }
        }
    }

    freopen((path + output + number + extensionOut).c_str(), "wb", stdout);
    // ������ ��������� ��������� ����� � seed ������ ���������� ������� � ������ �����
    default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
    // ������ ����������� ������������� ��������� �������� ���� double � ���������
    // [-10, 10]
    uniform_real_distribution <double> distribution(-1e1, 1e1);
  
    // ���������� � �������� ���� ����������� ������
    fwrite(&n, sizeof(n), 1, stdout);
    Matrix m1(n, n), m2(n, n);
    // ���������� ������ �������
    for (int i = 0; i < n*n; i++)
    {
        // ��������� ���������� ������� �� ������������ ������������� �������
        m1.vv[i] = distribution(generator);
    }
    fwrite(m1.getP(), sizeof(m1.vv[0]), n*n, stdout);
    // ���������� ���������� ������ �������
    for (int i = 0; i < n*n; i++)
    {
        // ��������� ���������� ������� �� ������������ ������������� �������
        m2.vv[i] = distribution(generator);
    }
    fwrite(m2.getP(), sizeof(m2.vv[0]), n*n, stdout);

    // ���������� �����
    Matrix ans = m1*m2;
    freopen((path + output + number + extensionOutAnswer).c_str(), "wb", stdout);
    fwrite(ans.getP(), sizeof(ans.vv[0]), n*n, stdout);
    return 0;
}