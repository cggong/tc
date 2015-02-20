#include<string>
#include<iostream>
using namespace std; 
class EasyConversionMachine {
public:
  static int diff(string a, string b) {
    int ret = 0;
    for (string::iterator i = a.begin(), j = b.begin();
	 i != a.end(); ++i, ++j) {
      if (*i != *j) ret++;
    }
    return ret; 
  }
  
  static string isItPossible(string originalWord, string finalWord, int k) {
    if (originalWord.length() != finalWord.length()) return "IMPOSSIBLE"; 
    int d = diff(originalWord, finalWord);
    cout << d << endl; 
    if ((d > k) 
	||((k - d) & 1)) return "IMPOSSIBLE";
    return "POSSIBLE"; 
  }
};

int main(void) {
  while (true) {
    string a, b;
    int k;
    cin >> a >> b >> k; 
    cout << EasyConversionMachine::isItPossible(a, b, k) << endl;
  } 
} 
