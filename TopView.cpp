//TC SRM 550 DIV 2
#include<vector>
#include<string>
#include<iostream>
#include<map>
typedef int* ARR; 
using namespace std; 
class TopView {
public:
  static string findOrderAB(vector<string>& grid, int nc, 
			    int sl, map<char, ARR>& ab) {
    const int NA = 100;
    //preprocessing
    for (int i = 0; i < nc; i++) { //loop within vector<string>
      string row = grid[i]; 
      for (auto it = ab.begin(); it != ab.end(); it++) { 
	for (int j = 0; j < 2; j++) {
	  it->second[3*i + j] = NA;
	}
	it->second[3*i + 2] = 1; 
      } 
      for (int j = 0; j < sl; j++) { //loop within string
	char c = row[j];
	int* cinfo = ab[c]; 
	if (cinfo[3*i] == NA) {
	  cinfo[3*i] = j;
	} else if ((cinfo[3*i + 1] < j - 1)
		   && (row[j-1] != '#')) {
	  //not contiguous? 
	  cinfo[3*i + 2] = 0;
	}
	cinfo[3*i + 1] = j; 
      }
    }
    //check
    char c; 
    return findOrderAB(grid, nc, sl, ab) + c; 
  }

  
  static string findOrder(vector<string> grid) {
    //alphabet
    map<char, ARR> ab;
    int nc = grid.size();
    int sl = grid[0].length(); 
    ab['.'] = new int[nc * 3]();
    ab['#'] = new int[nc * 3](); 
    for (int i = 0; i < nc; i++) {
      for (auto c = grid[i].begin(); c != grid[i].end(); c++) {
	if (!ab.count(*c)) ab[*c] = new int[nc * 3]();
      }
    }
    return findOrderAB(grid, nc, sl, ab);  
  }
};

int main(void) {
  vector<string> i = {"..AA..",
		      ".CAAC.",
		      ".CAAC."};
  TopView::findOrder(i); 
  return 0;
} 
