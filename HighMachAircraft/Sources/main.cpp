#include <iostream>
#include "highmachaircraft.hpp"
#include "Vector.h"
#include "ceshi.h"
using namespace std;

int main()
{
    cout << "Hello VSC" << endl;
    double a = 1;
    string s = "${workspaceFolder}";
    cout << 3 << endl;
    Vector<double> b(3);
    b[0] = 1;
    b[2] = b[1];
    b.push_back(4);
    TestVector1();
    TestVector2();
    Matrix<double> mat = ones(3, 3);
    int i = mat.n_cols();
    system("pause");
    return 0;
}