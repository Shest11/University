#include "vector.h"
#include "ctime"
#include <iostream>
using namespace std;

void iosif(int N, int k) {
  int step = k - 1;
  Array arr(N);
  for (int i = 0; i < N; i++)
    arr.insert(i + 1);

  for (int j = 0; j < N - 1; j++) {
    if (step >= arr.size) {
      step -= arr.size;
      cout << arr[step] << endl;
      arr.remove(step);
    }
    else {
      cout << arr[step] << endl;
      arr.remove(step);
    }
    step += k - 1;
  }
  cout << arr;

}

int main() {
  // setlocale(LC_ALL, "Russian");
  // Array arr(4);
  // for (int i=0; i<4; i++)
  //   arr.insert(i+1);
  // cout<<arr<<endl;
  // for (int i=0; i<8; i+=2)
  //   arr.insert(10+i,i);
  // cout<<arr<<endl;
  // for (int i=1; i<8; i+=2)
  //   arr[i]=20+i;
  // cout<<arr<<endl;
  // for (int i=6; i>=0; i-=3)
  //   arr.remove(i);
  // cout<<arr<<endl;

  // Задача Иосифа – Флавия
  int N, k, step;
  cout << "Введите  N: " << endl;
  cin >> N;
  cout << "Введите  k: " << endl;
  cin >> k;

  clock_t start = clock();

  iosif(N, k);

  clock_t end = clock();

  double time_taken = double(end - start) / CLOCKS_PER_SEC;
  cout << "\nВремя выполнения: " << time_taken << " секунд" << endl;
  cout << "Время выполнения: " << time_taken * 1000 << " мс" << endl;

}