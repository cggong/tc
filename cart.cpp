#include<iostream>
using namespace std;

class CartInSupermarketEasy {
public:
  static int calc(int N, int K) {
    int logN = 0;
    for (int n = N; n >>= 1; logN++);
    logN += !(!(N - (1 << logN)));
    if (K >= logN) {
      //split to 1 1 2 2 2...
      return logN + 1;
    } else {
      //split to 1 << (logN - K)
      return K + (N + (1 << K) - 1) / (1 << K);
    } 
  } 
}; 
