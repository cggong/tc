//SRM 654 DIV 2
#include<string>
#include<iostream>
using namespace std;
class SquareScoreDiv2 {
public:
  static int getscore(string s1) {
    string s = s1 + '\n'; 
    char prev_c = '\0';
    int len_chunk = 1;
    int score = 0; 
    for (char& c: s) { 
      if (prev_c == c) {
	len_chunk++;
      } else {
	score += len_chunk * (len_chunk + 1) / 2;
	len_chunk = 1;
      }
      prev_c = c; 
    }
    return score - 1; 
  } 
};
void test() {
  string a[] = {
    "aaaba",
    "zzzxxzz",
    "abcdefghijklmnopqrstuvwxyz"
  }; 
  int b[] = {8, 12, 26}; 
  for (int i = 0; i < 3; i++) { 
    cout << "Test " << i << endl;
    cout << "Input: " << endl; 
    auto ans = SquareScoreDiv2::getscore(a[i]);
    cout << "Correct answer: " << b[i] << endl;
    cout << "Program answer: " << ans << endl; 
    if (b[i] == ans) cout << "\033[1;34mSuccess!\033[0m " << endl;
    else cout << "\033[1;35mFailed\033[0m " << endl;
  }    
} 
int main(void) {
  test();
  return 0;
} 
