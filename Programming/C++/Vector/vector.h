#pragma once
#include <iostream>
using namespace std;

const int DEFAULT_CAPACITY=10;
class ArrayException {

};

class Array {
public:
  int *ptr, capacity, size;
  explicit Array(int startCapacity=DEFAULT_CAPACITY);

  // Деструктор
  ~Array();

  // индексация
  int& operator[] (int index);

  // Вставка элемента
  void insert(int elem, int index);

  // Вставка элемента в конец массива
  void insert(int elem);

  // Удаление элемента
  void remove(int index);

  // Конструктор копирования
  Array(const Array& arr);

  Array& operator =(const Array& arr);

  int operator [](int index) const;

  // Увелечение capacity
  void increaseCapacity(int newCapacity);

  int getSize() const;

  friend ostream& operator <<(ostream& out, const Array& arr);
};
