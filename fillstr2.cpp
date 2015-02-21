//SRM 650 DIV 1
#include<iostream>
#include<vector>
using namespace std;

enum State { INIT, NC, A, B, AM, BM };

class Machine {
  State s;
  int n;
public:
  Machine(): s(INIT), n(0) {}
  void next(int c) {
    State TT[][3] = {//B as 0, = as 1, A as 2
      {B, NC, A}, //INIT
      {B, NC, A}, //NC
      {B, AM, A}, //A
      {B, BM, A}, //B
      {B, BM, A}, //AM
      {B, AM, A}  //BM
    };
    int inc[][3] = {
      {0, 0, 0}, //INIT
      {0, 0, 0}, //NC
      {0, 0, 1}, //A
      {1, 0, 0}, //B
      {1, 0, 0}, //AM
      {0, 0, 1}  //BM
    }; 
    n += inc[s][c];
    s = TT[s][c]; 
  }
  int count() {
    return n;
  } 
};

class TaroFillingAStringDiv2 {
public:
  static int getNumber(string S) {
    Machine m;
    for (auto c = S.begin(); c != S.end(); c++) {
      m.next((*c == '?') ? 1 : (*c % 3));
    }
    return m.count(); 
  } 
};

void test() {
  string a[] = {
    "ABAA",
    "??",
    "A?A",
    "A??B???AAB?A???A",
    "?BB?BAAB???BAB?B?AAAA?ABBA????A?AAB?BBA?A?"
  };
  int d[] = {1, 0, 0, 3, 10};
  for (int i = 0; i < 5; i++) {
    cout << "Test " << i << endl;
    cout << "Input: " << endl; 
    int ans = TaroFillingAStringDiv2::getNumber(a[i]);
    cout << "Correct answer: " << d[i] << endl;
    cout << "Program answer: " << ans << endl; 
    if (d[i] == ans) cout << "\033[1;34mSuccess!\033[0m " << endl;
    else cout << "\033[1;Failed\033[0m " << endl;
  }    
} 

int main(void) {
  test();
  return 0;
} 
