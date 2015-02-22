//SRM 649 DIV 2
#include<iostream>
using namespace std;

class DecipherabilityEasy {
public:
  static string check(string s, string t) {
    for (int i = 0; i < s.size(); i++) {
      string ss(s);
      ss.erase(i, 1); 
      if (ss == t) return "Possible";
    }
    return "Impossible"; 
  }
};

void test() {
  string a[] = {
    "sunuke",
    "snuke"
  };
  string b[] = {
    "snuke",
    "skue"
  }; 
  string d[] = {
    "Possible",
    "Impossible"
  }; 
  for (int i = 0; i < 2; i++) { 
    cout << "Test " << i << endl;
    cout << "Input: " << endl; 
    auto ans = DecipherabilityEasy::check(a[i], b[i]);
    cout << "Correct answer: " << d[i] << endl;
    cout << "Program answer: " << ans << endl; 
    if (d[i] == ans) cout << "\033[1;34mSuccess!\033[0m " << endl;
    else cout << "\033[1;35mFailed\033[0m " << endl;
  }    
} 

int main(void) {
  test();
  return 0;
} 
