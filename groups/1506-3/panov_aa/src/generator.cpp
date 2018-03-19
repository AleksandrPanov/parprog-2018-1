#include <cstdio>
#include <random>
#include <ctime>
#include <chrono>
#include <iostream>
using namespace std;
int n_tests[] = { 1, 2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 100, 200, 300, 400, 500,
600, 700, 800, 900, 1000 };
int main(int argc, char * argv[])
{
    string path = "./tests/";
    string output = "matr";
    string number = "";
    string extensionOut = ".in";
    if (argc == 2)
    {
        number = argv[1];
        output = "";        
    }
    else
    {
        if (argc > 2)
        {
            number = argv[1];
            output = argv[2];           
        }
    }

    freopen((path + output + number + extensionOut).c_str(), "wb", stdout);

    // ������ ��������� ��������� ����� � seed ������ ���������� ������� � ������ �����
    default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
    // ������ ����������� ������������� ��������� �������� ���� double � ���������
    // [-10000, 10000]
    uniform_int_distribution <int> distribution(-100, 100);
    // ����� ������ ������
    int n = 10;
    // ���� �������� ����� ����� � ���������� ��������� ������, �� ���� ������ �� n_tests
    if (argc > 1)
        n = n_tests[atoi(argv[1])];
    // ���������� � �������� ���� ����������� ������
    fwrite(&n, sizeof(n), 1, stdout);
    // ������ ��������� ������ ��� ������ �������
    int * cur = new int[n];
    // ���������� ������ �������
    for (int i = 0; i < n; i++)
    {
        // ��������� ���������� ������� �� ������������ ������������� ��������� ������ �������
        for (int j = 0; j < n; j++)
            cur[j] = distribution(generator);
        // ���������� ������ � �������� ���� � ����
        fwrite(cur, sizeof(*cur), n, stdout);
    }
    // ���������� ���������� ������ �������
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cur[j] = distribution(generator);
        fwrite(cur, sizeof(*cur), n, stdout);
    }

    return 0;
}