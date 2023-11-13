// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size, T eq)
   {
      if (size <= 0 || size > MAX_VECTOR_SIZE)
          throw out_of_range("Vector size should be greater than zero");
      sz = size;
      pMem = new T[sz];
      for (int i = 0; i < sz; i++)
          pMem[i] = eq;
   }
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz <= 0 || sz >MAX_VECTOR_SIZE)
      throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      pMem = new T[sz]();
      for (int i = 0; i < sz; i++)
          pMem[i] = v.pMem[i]; //pMem[i] = v.pMem[i]
  }
  /*TDynamicVector(TDynamicVector&& v) noexcept
  {
      pMem = nullptr;
      swap(*this, v);
  }*/
  ~TDynamicVector()
  {
      if (pMem == nullptr)
          throw ("Error");
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (v == *this)
          return *this;
      delete[] pMem;
      sz = v.sz;
      pMem = new T[sz];
      for (int i = 0; i < sz; i++)
          pMem[i] = v.pMem[i]; //pMem[i] = v.pMem[i]
      return *this;
  }
 /*TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
     if (v == *this)
         return *this;
      swap(*this, v);
      return *this;
  }*/

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      if (ind < 0 || ind > sz)
          throw ("Error");
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      if (ind < 0 || ind > sz)
          throw ("Error");
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind < 0 || ind >= sz) 
          throw ("Error");
      else:
        return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind < 0 || ind >= sz)
          throw ("Error");
      else
        return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz)
          return 0;
      else
      {
          for (int i = 0; i < sz; i++)
              if (pMem[i] != v.pMem[i])
                  return 0;
          return 1;
      }
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return(!(*this == v));
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      for (size_t i = 0; i < sz; i++) 
          pMem[i] = pMem[i] + val;
      return *this;
  }
  TDynamicVector operator-(T val)
  {
      for (size_t i = 0; i < sz; i++)
          pMem[i] = pMem[i] - val;
      return *this;
  }
  TDynamicVector operator*(T val)
  {
      for (int i = 0; i < sz; i++)
          pMem[i] = pMem[i] * val;
      return*this;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz == v.sz)
      {
          TDynamicVector<T> tmp(sz);
          for (int i = 0; i < sz; i++)
              tmp[i] = pMem[i] + v[i];
          return(tmp);
      }
      else throw "Error";
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz == v.sz)
      {
          TDynamicVector<T> tmp(sz);
          for (int i = 0; i < sz; i++)
              tmp[i] = pMem[i] - v[i];
          return(tmp);
      }
      else throw "Error";
  }
  T operator*(const TDynamicVector& v)
  {
      if (sz == v.sz)
      {
          T tmp = 0;
          for (int i = 0; i < sz; i++)
              tmp += pMem[i] * v.pMem[i];
          return(tmp);
      }
      else throw "Error";
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (sz >= MAX_MATRIX_SIZE)
        throw("Error");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  void change_sz(int size)
  {
      if (size >= MAX_MATRIX_SIZE) throw ("Error");
      TDynamicMatrix<T> tmp(size);
      *this = tmp;
  }

  int size()
  {
      return(sz);
  }

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) return 0;
      else
      {
          for (int i = 0; i < sz; i++) 
              if (pMem[i] != m.pMem[i]) 
                  return false;
      }
      return true;
  }

  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
      return(!(*this == m));
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix<T> tmp(sz);
      for (size_t i = 0; i < sz; i++) 
          tmp[i] = pMem[i] * val;
      return ans;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.sz)
          throw ("Error");
      else
      {
          T tmp = 0;
          for (int i = 0; i < sz; i++)
              tmp += pMem[i] * v.pMem[i];
          return tmp;
      }
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) 
          throw ("Error");
      else
      {
          TDynamicMatrix<T> tmp(sz);
        for (int i = 0; i < sz; i++)
          tmp[i] = pMem[i] + m[i];
        return tmp;
      }
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz) 
          throw ("Error");
      else
      {
          TDynamicMatrix<T> tmp(sz);
          for (int i = 0; i < sz; i++) 
              tmp[i] = pMem[i] - m[i];
          return tmp;
      }
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz) 
          throw ("Error");
      else
      {
          TDynamicMatrix<T> tmp(sz);

          for (int i = 0; i < sz; i++)
          {
              for (int j = 0; j < sz; j++)
              {
                  T sum = 0;
                  for (int k = 0; k < sz; k++)
                      sum += pMem[i][k] * m.pMem[k][j];
                  tmp.pMem[i][j] = sum;
              }
          }
          return tmp;
      }
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; i++)
      {
          for (sint j = 0; j < v.sz;j++)
          {
              cin >> v[i][j];
          }
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; i++)
      {
          for (size_t j = 0; j < v.sz; j++)
          {
              cout << v[i][j] << " ";
          }
          cout << endl;
      }
      return ostr;
  }
};

#endif
