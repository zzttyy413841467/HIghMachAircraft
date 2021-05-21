#include "Vector.h"
void TestVector1()
{
    Vector<int> v1;
    Vector<int> v2(10, 6);
    cout << v2.size() << endl;
    cout << v2.capacity() << endl;
    for (auto e : v2)
        cout << e << " ";
    cout << endl;
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    Vector<int> v3(array, array + sizeof(array) / sizeof(array[0]));
    for (auto e : v3)
        cout << e << " ";
    cout << endl;
}
void TestVector2()
{

    Vector<int> v;
    v.reserve(10);
    cout << v.size() << endl;
    cout << v.capacity() << endl;
    v.reserve(5);
    cout << v.size() << endl;
    cout << v.capacity() << endl;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    cout << v.size() << endl;

    cout << v.back() << endl;
    cout << v[1] << endl;
    for (auto e : v)
        cout << e << " ";
    cout << endl;
    v.pop_back();
    cout << v.size() << endl;
    for (auto e : v)
        cout << e << " ";
    cout << endl;

    v.pop_back();
    cout << v.back() << endl;

    v.resize(5, 8);
    cout << v.size() << endl;
    cout << v.capacity() << endl;
    for (auto e : v)
        cout << e << " ";
    cout << endl;

    v.resize(20);
    cout << v.size() << endl;
    cout << v.capacity() << endl;
    for (auto e : v)
        cout << e << " ";
    cout << endl;

    v.resize(10);
    cout << v.size() << endl;
    cout << v.capacity() << endl;
    for (auto e : v)
        cout << e << " ";
    cout << endl;

    v.clear();
    cout << v.size() << endl;
    cout << v.capacity() << endl;
}
