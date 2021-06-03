#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "dsexceptions.h"
#include <vector>

using namespace std;

template <typename Object>
class Vector
{
public:
  explicit Vector(int initSize = 0)
      : theSize{initSize}, theCapacity{initSize + SPARE_CAPACITY}
  {
    objects = new Object[theCapacity];
  }

  Vector(const Vector &rhs)
      : theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, objects{nullptr}

  {
    objects = new Object[theCapacity];
    for (int k = 0; k < theSize; ++k)
      objects[k] = rhs.objects[k];
  }

  Vector(int size, const Object &rhs)
      : theSize{size}, theCapacity{size + SPARE_CAPACITY}
  {
    objects = new Object[theCapacity];
    for (int i = 0; i < theSize; i++)
    {
      objects[i] = rhs;
    }
  }

  Vector(int size, const Object *rhs)
      : theSize{size}, theCapacity{size + SPARE_CAPACITY}
  {
    objects = new Object[theCapacity];
    for (int i = 0; i < theSize; i++)
    {
      objects[i] = rhs;
    }
  }

  Vector(Object *begin, Object *end)
  {
    theSize = end - begin;
    theCapacity = theSize + SPARE_CAPACITY;
    objects = new Object[theCapacity];
    for (size_t i = 0; i < theSize; i++)
    {
      objects[i] = *begin++;
    }
  }

  Vector &operator=(const Vector &rhs)
  {
    Vector copy = rhs;
    std::swap(*this, copy);
    return *this;
  }

  ~Vector()
  {
    delete[] objects;
  }

  Vector(Vector &&rhs)
      : theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, objects{rhs.objects}
  {
    rhs.objects = nullptr;
    rhs.theSize = 0;
    rhs.theCapacity = 0;
  }

  Vector &operator=(Vector &&rhs)
  {
    std::swap(theSize, rhs.theSize);
    std::swap(theCapacity, rhs.theCapacity);
    std::swap(objects, rhs.objects);

    return *this;
  }

  Vector(const vector<Object> &rhs)
  {
    theSize = rhs.size();
    theCapacity = theSize + SPARE_CAPACITY;
    if (theSize == 0)
      objects = 0;
    else
      objects = new Object[theCapacity];
    for (int i = 0; i < theSize; i++)
    {
      objects[i] = rhs[i];
    }
  }

  Vector &operator=(const vector<Object> &rhs)
  {
    delete[] objects;
    theSize = rhs.size();
    theCapacity = theSize + SPARE_CAPACITY;
    if (theSize == 0)
      objects = 0;
    else
      objects = new Object[theCapacity];
    for (int i = 0; i < theSize; i++)
    {
      objects[i] = rhs[i];
    }
    return *this;
  }

  bool empty() const
  {
    return size() == 0;
  }
  int size() const
  {
    return theSize;
  }
  int capacity() const
  {
    return theCapacity;
  }

  Object &operator[](int index)
  {
#ifndef NO_CHECK
    if (index < 0 || index >= size())
      throw ArrayIndexOutOfBoundsException{};
#endif
    return objects[index];
  }

  const Object &operator[](int index) const
  {
#ifndef NO_CHECK
    if (index < 0 || index >= size())
      throw ArrayIndexOutOfBoundsException{};
#endif
    return objects[index];
  }

  void resize(int newSize)
  {
    if (newSize > theCapacity)
      reserve(newSize * 2);
    if (newSize > theSize)
    {
      for (size_t i = theSize; i < newSize; i++)
      {
        objects[i] = 0;
      }
    }

    theSize = newSize;
  }

  void resize(int newSize, const Object &rhs)
  {
    if (newSize > theCapacity)
      reserve(newSize * 2);
    if (newSize > theSize)
    {
      for (size_t i = theSize; i < newSize; i++)
      {
        objects[i] = rhs;
      }
    }

    theSize = newSize;
  }

  void assign(int newSize, const Object &rhs)
  {
    resize(newSize);
    for (int i = 0; i < theSize; i++)
    {
      objects[i] = rhs;
    }
  }

  Vector operator+(const Vector &rhs) const
  {
    Vector<Object> result(theSize);
    if (rhs.size() != theSize)
    {
      cerr << "bad size ,can't add\n";
      return result;
    }
    else
    {
      for (int i = 0; i < theSize; i++)
      {
        result[i] = objects[i] + rhs[i];
      }
      return result;
    }
  }

  Vector operator-(const Vector &rhs) const
  {
    Vector<Object> result(theSize);
    if (rhs.size() != theSize)
    {
      cerr << "bad size ,can't sub\n";
      return result;
    }
    else
    {
      for (int i = 0; i < theSize; i++)
      {
        result[i] = objects[i] - rhs[i];
      }
      return result;
    }
  }

  Vector operator%(const Vector &rhs) const
  { //数组乘
    Vector<Object> result(theSize);
    if (rhs.size() != theSize)
    {
      cerr << "bad size ,can't multi\n";
      return result;
    }
    else
    {
      for (int i = 0; i < theSize; i++)
      {
        result[i] = objects[i] * rhs[i];
      }
      return result;
    }
  }

  //数乘
  Vector operator*(const Object &rhs) const
  {

    Vector<Object> result(theSize);
    for (int i = 0; i < theSize; i++)
    {
      result[i] = objects[i] * rhs;
    }
    return result;
  }

  friend Vector operator*(const Object &lhs, const Vector &rhs)
  {
    return rhs * lhs;
  }

  double norm2() const
  {
    double normValue = 0;
    for (int i = 0; i < theSize; i++)
    {
      normValue += objects[i] * objects[i];
    }
    return normValue;
  }

  void display(const string &text = "")
  {
    cout << endl;
    cout << text << endl;
    for (int i = 0; i < theSize; i++)
    {
      cout << objects[i] << endl;
    }
  }

  void reserve(int newCapacity)
  {
    if (newCapacity < theSize)
      return;

    Object *newArray = new Object[newCapacity];
    for (int k = 0; k < theSize; ++k)
      newArray[k] = std::move(objects[k]);

    theCapacity = newCapacity;
    std::swap(objects, newArray);
    delete[] newArray;
  }

  // Stacky stuff
  void push_back(const Object &x)
  {
    if (theSize == theCapacity)
      reserve(2 * theCapacity + 1);
    objects[theSize++] = x;
  }
  // Stacky stuff
  void push_back(Object &&x)
  {
    if (theSize == theCapacity)
      reserve(2 * theCapacity + 1);
    objects[theSize++] = std::move(x);
  }

  void pop_back()
  {
    if (empty())
      throw UnderflowException{};
    --theSize;
  }

  const Object &back() const
  {
    if (empty())
      throw UnderflowException{};
    return objects[theSize - 1];
  }

  const Object &front() const
  {
    if (empty())
      throw UnderflowException{};
    return objects[0];
  }

  void clear()
  {
    theSize = 0;
    delete[] objects;
    objects = new Object[theCapacity];
  }

  // Iterator stuff: not bounds checked
  typedef Object *iterator;
  typedef const Object *const_iterator;

  iterator begin()
  {
    return &objects[0];
  }
  const_iterator begin() const
  {
    return &objects[0];
  }
  iterator end()
  {
    return &objects[size()];
  }
  const_iterator end() const
  {
    return &objects[size()];
  }

  static const int SPARE_CAPACITY = 2;

private:
  int theSize;
  int theCapacity;
  Object *objects;
};

template <class Object>
class Matrix
{
public:
  explicit Matrix(int mm = 0, int nn = 0)
      : m{mm}, n{nn}
  {
    objects = (m > 0 ? new Object *[m] : (Object **)0);
    if (n > 0)
    {
      for (int i = 0; i < m; i++)
      {
        objects[i] = new Object[n];
        for (int j = 0; j < n; j++)
        {
          objects[i][j] = (Object)0;
        }
      }
    }
    else
    {
      for (int i = 0; i < m; i++)
      {
        objects[i] = (Object *)0;
      }
    }
  }

  Matrix(const Matrix &rhs)
      : m{rhs.m}, n{rhs.n}
  {
    objects = (m > 0 ? new Object *[m] : (Object **)0);
    if (n > 0)
    {
      for (int i = 0; i < m; i++)
      {
        objects[i] = new Object[n];
        for (int j = 0; j < n; j++)
        {
          objects[i][j] = rhs.objects[i][j];
        }
      }
    }
    else
    {
      for (int i = 0; i < m; i++)
      {
        objects[i] = (Object *)0;
      }
    }
  }

  Matrix(int mm, int nn, const Object &rhs)
      : m{mm}, n{nn}
  {
    objects = (m > 0 ? new Object *[m] : (Object **)0);
    if (n > 0)
    {
      for (int i = 0; i < m; i++)
      {
        objects[i] = new Object[n];
        for (int j = 0; j < n; j++)
        {
          objects[i][j] = rhs;
        }
      }
    }
    else
    {
      for (int i = 0; i < m; i++)
      {
        objects[i] = (Object *)0;
      }
    }
  }

  Matrix &operator=(const Matrix &rhs)
  {
    Matrix copy = rhs;
    std::swap(*this, copy);
    return *this;
  }

  ~Matrix()
  {
    for (int i = 0; i < m; i++)
    {
      delete[] objects[i];
    }

    delete[] objects;
  }

  Matrix(Matrix &&rhs)
      : m{rhs.m}, n{rhs.n}, objects{rhs.objects}
  {
    rhs.objects = nullptr;
    rhs.m = 0;
    rhs.n = 0;
  }

  Matrix &operator=(Matrix &&rhs)
  {
    std::swap(m, rhs.m);
    std::swap(n, rhs.n);
    std::swap(objects, rhs.objects);

    return *this;
  }

  inline int n_rows() const
  {
    return m;
  }
  inline int n_cols() const
  {
    return n;
  }

  Object *operator[](const int index)
  {
    return objects[index];
  }

  const Object *operator[](const int index) const
  {
    return objects[index];
  }

  void resize(int newm, int newn)
  {
    for (int i = 0; i < m; i++)
    {
      delete[] objects[i];
    }
    delete[] objects;
    n = newn;
    m = newm;
    objects = (m > 0 ? new Object *[m] : (Object **)0);
    if (n > 0)
    {
      for (int i = 0; i < m; i++)
      {
        objects[i] = new Object[n];
      }
    }
    else
    {
      for (int i = 0; i < m; i++)
      {
        objects[i] = (Object *)0;
      }
    }
  }

  void assign(int newm, int newn, const Object &rhs)
  {
    resize(m, n);
    if (objects && objects[0])
    {
      for (int i = 0; i < m; i++)
      {
        for (int j = 0; j < n; j++)
        {
          objects[i][j] = rhs;
        }
      }
    }
  }

  Matrix<double> inverse(void);

  Matrix trans(void)
  {
    Matrix<Object> Trans;
    Trans.resize(n, m);
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        Trans[j][i] = objects[i][j];
      }
    }
    return Trans;
  }

  Matrix operator+(const Matrix &rhs) const
  {
    Matrix<Object> result(m, n);
    if (m == rhs.n_rows() && n == rhs.n_cols())
    {
      for (int i = 0; i < m; i++)
      {
        for (int j = 0; j < n; j++)
        {
          result[i][j] = objects[i][j] + rhs[i][j];
        }
      }
      return result;
    }
    else
    {

      cerr << "bad size ,can't add\n";
      return result;
    }
  }

  Matrix operator-(const Matrix &rhs) const
  {
    Matrix<Object> result(m, n);
    if (m == rhs.n_rows() && n == rhs.n_cols())
    {
      for (int i = 0; i < m; i++)
      {
        for (int j = 0; j < n; j++)
        {
          result[i][j] = objects[i][j] - rhs[i][j];
        }
      }
      return result;
    }
    else
    {

      cerr << "bad size ,can't sub\n";
      return result;
    }
  }

  //数组乘
  Matrix operator%(const Matrix &rhs) const
  {
    Matrix<Object> result(m, n);
    if (m == rhs.n_rows() && n == rhs.n_cols())
    {
      for (int i = 0; i < m; i++)
      {
        for (int j = 0; j < n; j++)
        {
          result[i][j] = objects[i][j] * rhs[i][j];
        }
      }
      return result;
    }
    else
    {

      cerr << "bad size ,can't multi\n";
      return result;
    }
  }

  //数乘
  Matrix operator*(const Object &rhs) const
  {

    Matrix<Object> result(m, n);
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        result[i][j] = objects[i][j] * rhs;
      }
    }
    return result;
  }

  Matrix operator*(const Matrix &rhs) const
  {
    Matrix<Object> result(m, rhs.n_cols());
    if (n == rhs.n_rows())
    {
      for (int i = 0; i < m; i++)
      {
        for (int j = 0; j < rhs.n_cols(); j++)
        {
          result[i][j] = (Object)0;
          for (int k = 0; k < n; k++)
            result[i][j] += objects[i][k] + rhs[k][j];
        }
      }
      return result;
    }
    else
    {
      cerr << "bad size ,can't multi\n";
      return result;
    }
  }

  friend Matrix operator*(const Object &lhs, const Matrix &rhs)
  {
    return rhs * lhs;
  }

  Vector<Object> operator*(const Vector<Object> &rhs)
  {
    Vector<Object> result(m);
    if (n == rhs.size())
    {
      for (int i = 0; i < m; i++)
      {
        result[i] = (Object)0;
        for (int j = 0; j < n; j++)
        {
          result[i] += objects[i][j] * rhs[j];
        }
      }
      return result;
    }
    else
    {
      cerr << "bad size ,can't multi\n";
      return result;
    }
  }

  friend Vector<Object> operator*(const Vector<Object> &lhs, const Matrix &rhs)
  {
    return rhs * lhs;
  }
  void display(const string &text = "")
  {
    cout << endl;
    cout << text << endl;
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        cout << objects[i][j] << "\t";
      }
      cout << endl;
    }
  }

private:
  int m;
  int n;
  Object **objects;
};

Matrix<double> eye(int m, int n);
Matrix<double> ones(int m, int n);
Matrix<double> zeros(int m, int n);

typedef Vector<double> vec;
typedef Matrix<double> mat;

#endif