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
    }
    n += inc[s][c];
    s = TT[s][c]; 
  }
  int count() {
    return n;
  } 
};

class TaroFillingAStringDiv1 {
public:
  int getNumber(int N, vector<int> position, string value) {
    string s = new string(N, '=');
    for (int i = 0; i < position.length(); i++) {
      s[position[i] - 1] = value[i];
    } 
    Machine m;
    for (auto c = s.begin(); c != s.end(); c++) {
      m.next((*c) % 3);
    }
    return m.count(); 
  } 
};

void test() {
  int a[] = {3, 4, 25, 305};
  vector<int> b[] = {
    {1, 3},
    {2, 1, 3, 4},
    {23, 4, 8, 1, 24, 9, 16, 17, 6, 2, 25, 15, 14, 7, 13},
    {183, 115, 250, 1, 188, 193, 163, 221, 144, 191, 92,
     192, 58, 215, 157, 187, 227, 177, 206, 15, 272, 232,
     49, 11, 178, 59, 189, 246}
  };
  string c[] = {
    "AB",
    "ABBA",
    "ABBBBABABBAAABA",
    "ABAABBABBAABABBBBAAAABBABBBA",
  };
  int d[] = {2, 1, 1, 43068480
} 

int main(void) {
  test();
  return 0;
} 
