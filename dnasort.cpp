#include<iostream>
#include<string>
#include<stdlib.h>
using namespace std; 
int invcnt(string& s, int a, int b) {
  string ret = "";
  if (a == b) return 0; 
  int m = (a + b) / 2;
  int fir = invcnt(s, a, m); 
  int sec = invcnt(s, m + 1, b);
  int inv = fir + sec; 
  int i = a, j = m + 1;
  while (true) {
    if (s[i] <= s[j]) ret.push_back(s[i++]);
    else {
      inv += m - i + 1; 
      ret.push_back(s[j++]);
    } 
    if (i == m + 1) {
      for (int t = j; t <= b; t++) ret.push_back(s[t]);
      break; 
    }
    if (j == b + 1) {
      for (int t = i; t <= m; t++) ret.push_back(s[t]);
      break; 
    }
  }
  s.replace(a, b + 1 - a, ret);
  return inv;
}

int invcnttop(string s) {
  return invcnt(s, 0, s.length() - 1);
}

int naiveinvcnt(string s) {
  int ret = 0; 
  for (int i = 0; i < s.length(); i++)
    for (int j = i + 1; j < s.length(); j++) {
      if (s[i] > s[j]) ret++;
    }
  return ret;
} 

int main(void) {
  //string s = "FDZA";//"FDZA";
  for (int i = 20000; i < 20001; i++)
    for (int j = 0; j < 3; j++) {
      string s = ""; 
      for (int k = 0; k < i; k++) {
	s.push_back(static_cast<char>('A' + rand() % 20));
      }
      cout << "\033[1;32mStart Invc\033[0m " << endl;
      int invc = invcnttop(s);
      cout << "\033[1;34mFinish Invc\033[0m " << endl;
      cout << "\033[1;32mStart Naiv\033[0m " << endl;
      int naiv = naiveinvcnt(s);
      cout << "\033[1;34mFinish Naiv\033[0m " << endl;
      if (invc != naiv) { 
	cout << "For input " << s << ", clever algorithm outputs "
	     << invcnttop(s) << ", while naive algorithm outputs "
	     << naiveinvcnt(s) << ". " << endl;
      } else {
	cout << "\033[1;34mSuccess!\033[0m " << endl;
      } 
    }
  return 0;
} 
