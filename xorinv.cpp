//SRM 649 DIV 2
#include<vector>
#include<queue>
#include<map>
#include<algorithm>
using namespace std; 
class XorSeqSol {
  int lowerBound; //lower bound
  int upperBound; 
  int mask;
  int curPos; //0001000
  int parent; 
  vector<int> pulse;
  bool first; //true for 1
public:
  static vector<int> A;
  static int lgN; 
  static map<int, int> lowerBoundMap; 
  static int bestLowerBound;
  static int bestMask; //mask corresponding to bestLowerBound
  bool possible; //two ``return values''
  vector<int> B;
  void pulsec() {
    first = mask >> (lgN - 1);
    for (int i = lgN - 1; i >= 0;) {
      j = 1; 
      while (A[i] & curPos == A[i-1] & curPos) j++;
      pulse.push_back(j);
      i += j; 
    } 
  }
  void lowerBound() {
    //quadratic time, can be optimized to linear time
    int sum = 0; 
    for (int i = first; i < pulse.size(); i += 2) {
      int term = 0;
      for (int j = i + 1; j < pulse.size(); j += 2)
	term += pulse[j];
      sum += pulse[i] * term; 
    }
    lowerBound = sum + lowerBoundMap[parent]; 
  }
  void upperBound() {
    for (int
  } 
  XorSeqSol(int _mask, int curpos, int _parent)
    : mask(_mask), curPos(curpos), possible(true), parent(_parent) {
    pulsec();
    lowerbound();
    upperbound();
    lowerBoundMap[mask] = lowerBound; 
    if (upperBound <= bestLowerBound) possible = false;
    else if (lowerBound > bestLowerBound) {
	bestLowerBound = lowerBound;
	bestMask = mask;
    } 
  }   
}; 

class XorSequenceEasy {
public:
  static int getmax(vector<int> A, int N) {
    XorSeqSol::bestLowerBound = 0;
    XorSeqSol::bestMask = 0; 
    XorSeqSol::A = A;
    int lgN = 1;
    for (m = N; m >>= 1; lgN++);
    XorSeqSol::lgN = lgN; 
    map<int, int> XorSeqSol::lowerBoundMap; 
    queue<int> unexplored(vector<int>{0, 1});
    while (!unexplored.empty()) {
      int n = unexplored.pop();
      int lgn = 1; 
      for (m = n; m >>= 1; lgn++);
      int curPos = 1 << (lgN - 1 - lgn);
      int mask = n << (lgN - lgn);
      XorSeqSol s(mask, curPos, (n >> 1) << (lgN + 1 - lgn));
      if (s.possible && lgn == lgN) {
	unexplored.push(n << 1);
	unexplored.push((n << 1) + 1); 
      }
      return bestLowerBound; 
    } 
  }
}; 
