//SRM 650 DIV 2 250
#include<iostream>
#include<set>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
class TaroJiroDividing {
public:
  static set<int> getSet(int A) {
    set<int> a;
    for (int i = A; !(i & 1); i >>= 1) {
      a.insert(i);
    }
    return a;
  }
  
  static int getNumber(int A, int B) {
    set<int> a = getSet(A);
    set<int> b = getSet(B);
    int scale, n; 
    for (scale = 1, n = A + B; n >>= 1; ) scale++; 
    vector<int> c(scale);
    auto it = set_intersection(a.begin(), a.end(),
			       b.begin(), b.end(), c.begin());
    if (it == c.begin()) return 0; 
    return it - c.begin() + 1; 
  } 
};

void test() {
  int a[] = {8, 4, 12, 24};
  int b[] = {4, 7, 12, 96};
  int c[] = {3, 0, 3, 4};
  for (int i = 0; i < 4; i++) {
    cout << "Test " << i << endl;
    cout << "Input: " << a[i] << " " << b[i] << endl; 
    int ans = TaroJiroDividing::getNumber(a[i], b[i]);
    cout << "Correct answer: " << c[i] << endl;
    cout << "Program answer: " << ans << endl; 
    if (c[i] == ans) cout << "\033[1;34mSuccess!\033[0m " << endl;
    else cout << "\033[1;Failed\033[0m " << endl;
  }
} 

int main(void) {
  test();
  return 0;
} 
