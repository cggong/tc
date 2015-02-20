//SRM 650 DIV 1
#include<iostream>
#include<vector>
#include<map>
using namespace std;

enum State { INIT, NC, A, B, AM, BM };

class TaroFillingAStringDiv1 {
public:
  static int getNumber(int N, vector<int> position, string value) {
    map<int, char> L;
    for (int i = 0; i < position.size(); i++)
      L[position[i]] = value[i]; 
    long long int prod = 1;
    for (int i = 0; i < position.size(); i++) {
      auto i1 = L.find(position[i]);
      auto i2 = i1;
      i2++; 
      if ((i2 != L.end())
	  && (((i2->first - i1->first)
	       ^ (i2->second != i1->second))
	      & 1))
	prod *= i2->first - i1->first;
    }
    return prod; 
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
  int d[] = {2, 1, 1, 43068480};
  for (int i = 0; i < 4; i++) {
    cout << "Test: " << i << endl;
    cout << "Correct answer: " << d[i] << endl;
    int ans = TaroFillingAStringDiv1::getNumber(a[i], b[i], c[i]);
    cout << "Program answer: " << ans << endl;
    if (d[i] == ans) cout << "\033[1;34mSuccess!\033[0m " << endl;
    else cout << "\033[1;Failed\033[0m " << endl;
  } 
} 

int main(void) {
  test();
  return 0;
} 
