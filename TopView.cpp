//TC SRM 550 DIV 2
#include<vector>
#include<string>
#include<iostream>
#include<map>
#include<utility>
#include<algorithm>
typedef int* ARR; 
using namespace std; 
class TopView {
  struct UnavailableException: public exception {};
  struct ErrorException: public exception {}; 
public:
  static int abmax(int* cinfo, int offset, int nc) {
    int max = 0;
    const int NA = 100; 
    for (int i = 0; i < nc; i++) {
      if (cinfo[5*i + offset] != NA) {
	if (cinfo[5*i + offset] > max)
	  max = cinfo[5*i + offset];
      }
    }
    return max;
  }
  
  static int abmin(int* cinfo, int offset, int nc) {
    int min = 100;
    const int NA = 100; 
    for (int i = 0; i < nc; i++) {
      if (cinfo[5*i + offset] != NA) {
	if (cinfo[5*i + offset] < min) min = cinfo[5*i + offset];
      }
    }
    return min;
  }
  
  static string findOrderAB(vector<string>& grid, int nc, 
			    int sl, map<char, ARR>& ab) {
    const int NA = 100;
    //base case
    if (ab.size() == 2) return "";
    //induction
    //preprocessing
    for (int i = 0; i < nc; i++) { //loop within vector<string>
      string row = grid[i]; 
      for (auto it = ab.begin(); it != ab.end(); it++) { 
	for (int j = 0; j < 4; j++) {
	  it->second[5*i + j] = NA;
	}
	it->second[5*i + 4] = 1; 
      }
      vector<pair<int, int>> sharp;
      //for loop
      bool finished = true;
      string rr(row);
      rr.push_back('\0'); 
      for (int j = 0, start, end; j <= sl; j++) {
	//loop within string and process '#' first
	if (finished) {
	  if (row[j] == '#') {
	    start = j;
	    finished = false;
	  }
	} else {
	  if (row[j] != '#') {
	    end = j - 1;
	    finished = true;
	    sharp.push_back(make_pair(start, end));
	  }
	}
      }
      //make '#' table
      int* stt = new int[sl]; 
      int* end = new int[sl];
      //those positions with '#' in it won't make a difference. 
      for (int j = 0; j < sl; j++) {
	stt[j] = end[j] = j;
      }
      for (auto it = sharp.begin(); it != sharp.end(); it++) {
	int f = it->first;
	int s = it->second;
	if (f) end[f-1] = s;
	if (s < sl - 1) stt[s+1] = f;
      } 
      
      for (int j = 0; j < sl; j++) { //loop within string
	//process other chars
	char c = row[j];
	int* cinfo = ab[c]; 
	if (cinfo[5*i] == NA) {
	  cinfo[5*i] = j;
	} else if ((cinfo[5*i + 1] < j - 1)
		   && ((row[j-1] != '#')
		       || (stt[j] != cinfo[5*i + 1] + 1))) {
	  //not contiguous? 
	  cinfo[5*i + 4] = 0;
	}
	cinfo[5*i + 1] = j;
	//combine stat of each char with stat of '#'
	cinfo[5*i + 2] = stt[cinfo[5*i]];
	cinfo[5*i + 3] = end[cinfo[5*i + 1]]; 
      }
    }
    //check
    try { 
      for (auto it = ab.rbegin(); it != ab.rend(); it++) {
	//pass criterion:
	//all row stats compatible, and
	//rows contiguous
	//check if either criterion fails.
	try {
	  char c = it->first; 
	  int rmax = abmax(it->second, 1, nc); //need max
	  int rmin = abmin(it->second, 0, nc);
	  int amax = abmin(it->second, 3, nc); //allow max
	  int amin = abmax(it->second, 2, nc); 
	  //-------need--------------------------allow
	  if ((rmax > amax) || (rmin < amin))
	    throw UnavailableException();
	  int i = 0; 
	  for (bool stopped = false, beginned = false;
	       i < nc; i++) {
	    if (it->second[5*i + 4] == 0) throw UnavailableException(); 
	    if (stopped) {
	      if (it->second[5*i] != NA) throw UnavailableException();
	      //(rows, rows, rows) not contiguous
	    } else if (beginned) {
	      if (it->second[5*i] == NA) { 
		//on this row, if no this symbol and no '#', then stopped. 
		//naive search
		for (int j = rmin; j <= rmax; j++) {
		  if (grid[i][j] != '#') stopped = true; 
		} 
	      }
	    } else if (it->second[5*i] != NA) beginned = true;
	  }
	  throw it->first; 
	} catch (exception e) {} 
      }
      throw ErrorException(); 
    } catch (char c) {
      if ((c == '.') || (c == '#')) throw ErrorException();
      //prepare grid and ab for recursion
      ab.erase(c);
      for (int i = 0; i < nc; i++) {
	replace(grid[i].begin(), grid[i].end(), c, '#');
      } 
      return findOrderAB(grid, nc, sl, ab) + c;
    } 
  }

  
  static string findOrder(vector<string> grid) {
    //alphabet
    map<char, ARR> ab;
    int nc = grid.size();
    int sl = grid[0].length(); //each string length
    ab['.'] = new int[nc * 5]();
    ab['#'] = new int[nc * 5](); 
    for (int i = 0; i < nc; i++) {
      for (auto c = grid[i].begin(); c != grid[i].end(); c++) {
	if (!ab.count(*c)) ab[*c] = new int[nc * 5]();
      }
    }
    try { 
      return findOrderAB(grid, nc, sl, ab);
    } catch (ErrorException e) {
      return "ERROR!";
    }	
  }
};

int cnt; 

void judge(string a, string b) {
  cout << "Test " << cnt++ << endl << "correct answer: " << a
       << endl << "program answer: " << b << endl; 
  if (a == b) cout << "Success! " << endl;
  else cout << "Fail. " << endl;
} 

void firstTest() {
  vector<string> i = {"..AA..",
		      ".CAAC.",
		      ".CAAC."};
  judge("CA", TopView::findOrder(i)); 
};

void secondTest() {
  vector<string> A[] = { {"..47..",
			  "..74.."},
			 {"bbb666",
			  ".655X5",
			  "a65AA5",
			  "a65AA5",
			  "a65555"},
			 {"aabbaaaaaaaaaaaaaaaaaa",
			  "aabbccccccccccccccaaaa",
			  "aab11111ccccccccccaaaa",
			  "aab12221ccccccccccaaaa",
			  "aab12221ccccccccccaaaa",
			  "aab12221ccccccccccaaaa",
			  "aab12221ccccccccccaaaa",
			  "aab12221ccccccccccaaaa",
			  "aab12221ddddddddddaaaa",
			  "aab13331DDDDDDDDDDaaaa",
			  "aab13331DDDDDDDDDDaaaa",
			  "aa.11111DDDDDDDDDDaaaa",
			  "aaaaaaaaaaaaaaaaaaaaaa"},
			 {"AAAAA",
			  "bbbbA",
			  "..ccA",
			  "..ccA"},
			 {"AAAAA",
			  "bbbbA",
			  "ddccA",
			  "dzccA"}, 
			 {"AAAbA",
			  "bbbbA",
			  "..ccA",
			  "..ccA"}
  };
  string B[] = {"ERROR!", "65AXab", "ERROR!", "ERROR!",
		"Abcdz", "ERROR!"};
  for (int i = 0; i < 5; i++)
    judge(B[i],TopView::findOrder(A[i])); 
} 

int main(void) {
  cnt = 1;
  firstTest();
  secondTest(); 
  return 0;
} 
