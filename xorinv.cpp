#include<vector>
#include<algorithm>
using namespace std; 
class XorSeqSol {
  int lowerBound; //lower bound from previous recursion
  int desired; //if can't reach desired value, discard
  bool enabled; //flip (curPos) bit
  int origMask;
  int curPos; //0001000
  vector<int> pulse;
  bool first; //true for 1
  int alb[2];
  int aub[2];
  static int bestLowerBound; 
public:
  static vector<int> A;
  bool possible; //two ``return values''
  int max;
  vector<int> B; 
  XorSeqSol(int mask, int curpos, int lb, int d, bool en)
    : lowerBound(lb), origMask(mask), curPos(curpos), desired(d),
      possible(false), enabled(en) {
    computePulse();
    computeALB(); //additional lower bound non-flip
    computeALU();
    for (int i = 0; i < 2; i++) {
      if (lowerBound + aub[i] < bestLowerBound) continue;
      if (lowerBound + aub[i] > bestLowerbound)
	bestLowerBound = lowerBound + alu[i]; 
      int oneMask = (!curPos) - 1;
      int newMask = origMask | (curPos & oneMask);
      XorSeqSol s(newMask, curPos >> 1, lowerBound + alb[i],
		  lowerBound + alb[!i],
		  //if you cannot reach the lower bound of
		  //the other option, then no need.
		  i);
      if (!s.possible) continue;
      
    }
  }   
} 

class XorSequenceEasy {
public:
  static int getmax(vector<int> A, int N) {
  }
}; 
