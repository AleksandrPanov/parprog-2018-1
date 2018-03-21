#include <cstdio>
#include <cmath>
#include <string>
#include "../include/matrix.h"
using namespace std;
// ������������ ��� �������������� � ����������� ��������
////////////////////////////////////////////////////////////////////////////////////////////
/*
// Checker ����� ������������� ��� ��� ��� ��������:
AC = Accepted = ������� ����� ���������� ��������� �� ������ �����
WA = Wrong Answer = ������� ����� ������������ ��������� �� ������ �����
PE = Presentation Error = ������ ������� �������� ������
// ��������� �������� checker �� ����� �������������
NO = No verdict = ������� �����������
CE = Compilation Error = ������ ����������
ML = Memory Limit Exceeded = ��������� ����������� �� ������
TL = Time Limit Exceeded = ��������� ����������� �� ������� ������
RE = Runtime Error = ������ ������� ���������� ���������
IL = Idle Limit Exceeded = ��������� ����� ������� (�����������) ���������
DE = Deadly Error = ������ ����������� �������
*/
enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };

class Result
{
private:
    FILE * bur;
public:
    enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };
    Result(string path, string name, string extension,  bool read = false)
    {
        if (read) 
            bur = fopen((path + name + extension + ".txt").c_str(), "r");
        else 
            bur = fopen((path + name + extension + ".txt").c_str(), "w");
    }
    ~Result() { fclose(bur); }
    void write_type(ext_cls t) 
    { 
        fwrite(&t, sizeof(t), 1, bur);
    }
    // �������� ����������� �������, ��� ������� �������� ���� �� ��������� verdict
    void write_verdict(verdict v)
    {
        write_type(ext_cls::VERDICT); fwrite(&v, sizeof(v), 1, bur);
    }
    void write_message(string str)
    {
        write_type(ext_cls::MESSAGE); int l = str.size(); fwrite(&l, sizeof(l), 1, bur);
        fwrite(&str[0], sizeof(str[0]), l, bur);
    }
    // �������� ����������� ������� ����� ������ ��������� ���������,
    // ����������� � ������� before_code
    // x ����� ����������� 100 �� = 10 ^ (-7) ���
    void write_time(long long x)
    {
        write_type(ext_cls::TIME); fwrite(&x, sizeof(x), 1, bur);
    }
    // �������� ����������� �������, ������ ������������� ���������� ���������
    void write_memory(unsigned long long x)
    {
        write_type(ext_cls::MEMORY); fwrite(&x, sizeof(x), 1, bur);
    }
};

int main(int argc, char * argv[])
{
    string path = "";
    string path_result = "";
    string number = "";
    string name = "matr";
    string extensionIn = ".in";
    string extensionOutAnswer = ".ans";
    string extensionOutUserAnswer = ".user.ans";
    string extensionResult = ".result";
    if (argc > 1)
    {
        path = argv[1];
        path_result = path + "_result/";
        path += "/";
        if (argc > 2)
        {
            name = "";
            number = argv[2];
        }
    }
    if (number == "")
        extensionResult = "result";

    Result checker_result(path_result, number, extensionResult);
    // ��������� ���� ������� ������, ����� ���������, ���� �������� ������ c ������� ����
    FILE * bui = fopen((path + name + number + extensionIn).c_str(), "rb");
    FILE * buo = fopen((path_result + name + number + extensionOutUserAnswer).c_str(), "rb");
    FILE * bua = fopen((path + name + number + extensionOutAnswer).c_str(), "rb");
    int n;
    // ��������� ����������� ������
    fread(&n, sizeof(n), 1, bui);
    // �������� ������ ��� ������� ������ ���� � ������ ���������
    Matrix ans(n, n), res(n, n);

    double ans_time, res_time;
    // ��������� ����� ������ ��������� ��������� � ������� ���������
    fread(&res_time, sizeof(res_time), 1, buo);
    fread(res.getP(), sizeof(*res.getP()), n * n, buo);
    // ��������� ����� ������ ��������� � ������� ����
    //fread(&ans_time, sizeof(ans_time), 1, bua);
    fread(&n, sizeof(n), 1, bua);
    fread(ans.getP(), sizeof(*ans.getP()), n * n, bua);
    // ��������� ������, ��� ������� ����� �������� �������
    double diff = 0.0;
    for (int i = 0; i < n * n; i++)
        diff += (ans.vv[i] - res.vv[i]) * (ans.vv[i] - res.vv[i]);
    // ���������, ��� ������ ����, ����� ��������, ��� ������� ���������, ����� - �����������.
    if (diff < 1e-6)
    {
        checker_result.write_message("AC. Numbers are equal.");
        checker_result.write_verdict(verdict::AC);
    }
    else
    {
        checker_result.write_message("WA. Output is not correct.");
        checker_result.write_verdict(verdict::WA);
    }
    // ���������� ����� � ���������� ����������� (��������� �� 100 �� = 10 ^ (-7) ���).
    checker_result.write_time(res_time * 1e7);
    fclose(bua);
    fclose(buo);
    return 0;
}