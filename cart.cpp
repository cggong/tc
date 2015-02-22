//SRM 649 DIV 2 500
#include<iostream>
#include<algorithm>
using namespace std;

class CartInSupermarketEasy {
  static int f[101][101]; 
public:
  static int cf(int N, int K) {
    if (f[N][K] != -1) return f[N][K];
    if (K == 0) return N;
    if (N == 1) return 1;
    int min = N; 
    for (int i = 0; i <= K-1; i++)
      for (int j = 1; j < N; j++) {
	int m = max(cf(j, i), cf(N - j, K-1-i)) + 1; 
	if (m < min) min = m;
      }
    f[N][K] = min; 
    return min; 
  } 
  static int calc(int N, int K) {
    for (int i = 0; i <= 100; i++)
      for (int j = 0; j <= 100; j++)
	f[i][j] = -1;
    return cf(N, K); 
  } 
}; 

void test() {
  int a[] = {5, 5, 15, 45, 7, 100, 100}; 
  int b[] = {0, 2, 4, 5, 100, 100, 89}; 
  int d[] = {5, 4, 6, 11, 4, 8}; 
  for (int i = 0; i < 6; i++) { 
    cout << "\033[1;34mTest " << i << "\033[0m "<< endl;
    cout << "Input: " << endl; 
    auto ans = CartInSupermarketEasy::calc(a[i], b[i]);
    cout << "Correct answer: " << d[i] << endl;
    cout << "Program answer: " << ans << endl; 
    if (d[i] == ans) cout << "\033[1;32mSuccess!\033[0m " << endl;
    else cout << "\033[1;35mFailed\033[0m " << endl;
  }    
} 

int CartInSupermarketEasy::f[101][101] = {}; 

int main(void) {
  test();
  return 0;
} 
