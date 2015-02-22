//SRM 650 DIV 2
#include<vector>
#include<set>
#include<iostream>
#include<algorithm>
#include<iterator>
#include<map>
using namespace std;
class TheKingsRoadsDiv2 {
public:
  static set<int> setDiff(set<int> a, set<int> b) {
    set<int> c;
    set_difference(a.begin(), a.end(), b.begin(), b.end(),
		   inserter(c, c.end())); 
    return c; 
  }
  static void eraseLeaves(map<int, set<int>>& adj, set<int> leav) {
    for (auto it = adj.begin(); it != adj.end(); it++) {
      prset(leav); 
      if (leav.find(it->first) == leav.end())
	it->second = setDiff(it->second, leav); 
    }
    for (int i: leav)
      adj.erase(i); 
    adj.erase(0); 
  }
  static bool validRec(int h, map<int, set<int>>& adj, set<int> leaves) {
    //validateSubTree* (* is matcher) function recursion
    eraseLeaves(adj, leaves);
    prset(leaves); 
    return validSubTree(h - 1, adj);
  }
  static bool validXRec(int h, map<int, set<int>>& adj, set<int> leaves) {
    //validateSubTree* (* is matcher) function recursion
    eraseLeaves(adj, leaves); 
    return validSubTreeX(h - 1, adj);
  }
  static set<int> findNodes(map<int, set<int>>& adj, int deg) {
    set<int> ret; 
    for (auto it = adj.begin(); it != adj.end(); it++) {
      if (it->second.size() == deg) ret.insert(it->first);
    }
    return ret; 
  }
  static bool quantity(int h, map<int, set<int>>& adj, bool x) {
    int sum = 0;
    for (auto &it: adj) 
      sum += it.second.size();
    int l = sum >> 1;
    int r = (1 << h) - 2 + x; 
    return (l == r); 
  } 
    
  static bool validSubTree(int h, map<int, set<int>>& adj) {
    if (!quantity(h, adj, false)) return false; 
    if (h == 1) {
      //base case
      return true;
    } 
    else { 
      //induction
      auto leaves = findNodes(adj, 1);
      if (leaves.size() != 1 << (h-1)) return false; 
      return validRec(h, adj, leaves); 
    } 
  } 
  static bool validSubTreeX(int h, map<int, set<int>>& adj) {
    if (!quantity(h, adj, true)) return false; 
    if (h == 2) {  
      //base case
      for (auto it = adj.begin(); it != adj.end(); it++) {
	if (it->second.size() != 2) return false; 
      }
      return true; 
    } else { 
      //induction
      set<int> leaves = findNodes(adj, 1); 
      if (leaves.size() == 1 << (h - 1)) {
	return validXRec(h, adj, leaves); 
      } else if (leaves.size() == (1 << (h-1)) - 1) {
	//miss 1 leaf, it should have 2 neighbors.
	set<int> two = findNodes(adj, 2); 
	if (two.size() == 1) { 
	  //if it connects to root, then 1 node has 2 nei.
	  leaves.insert(*two.begin());
	  return validRec(h, adj, leaves); 
	} else if (two.size() == 2) { 
	  //else, it and root has 2 nei.
	  auto it = two.begin();
	  set<int> l1(leaves);
	  set<int> l2(leaves);
	  map<int, set<int>> a1(adj);
	  map<int, set<int>> a2(adj); 
	  l1.insert(*it++);
	  l2.insert(*it);
	  return validRec(h, a1, l1) || validRec(h, a2, l2); 
	} else return false; 
      } else if (leaves.size() == (1 << (h-1)) - 2) {
	set<int> two = findNodes(adj, 2); 
	if (two.size() != 2) return false;
	else {
	  auto it = two.begin();
	  leaves.insert(*it++);
	  leaves.insert(*it);
	  return validRec(h, adj, leaves); 
	} 
      } else return false; 
    } 
  } 
  static string getAnswer(int h, vector<int> a, vector<int> b) {
    map<int, set<int>> adj;
    for (int i = 0; i < a.size(); i++) { 
      adj[a[i]].insert(b[i]);
      adj[b[i]].insert(a[i]);
    }
    //eliminate self-loop
    set<int> loop; 
    for (int i = 1; i < a.size() + 1; i++) {
      auto it = adj[i].find(i); 
      if (it != adj[i].end()) { 
	adj[i].erase(it);
	loop.insert(i); 
      } 
    }
    if (loop.size() > 1) return "Incorrect";
    bool correct = loop.size() ? validSubTree(h, adj)
      : validSubTreeX(h, adj);
    return correct ? "Correct" : "Incorrect"; 
  } 
}; 

void test() {
  int a[] = {3, 2, 3, 2, 3};
  vector<int> b[] = {
    {1, 2, 3, 7, 1, 5, 4}, 
    {1, 2, 3}, 
    {7, 1, 1, 2, 2, 3, 1}, 
    {1, 3, 3}, 
    {6, 5, 3, 3, 5, 5, 6}
  };
  vector<int> c[] = {
    {6, 7, 4, 3, 3, 1, 7},
    {2, 1, 3}, 
    {7, 1, 7, 4, 5, 2, 6},
    {2, 1, 2}, 
    {1, 5, 5, 6, 4, 7, 2}
  }; 
  string d[] = {
    "Correct",
    "Incorrect",
    "Incorrect",
    "Correct",
    "Correct"
  }; 
  for (int i = 0; i < 5; i++) { 
    cout << "Test " << i << endl;
    cout << "Input: " << endl; 
    auto ans = TheKingsRoadsDiv2::getAnswer(a[i], b[i], c[i]);
    cout << "Correct answer: " << d[i] << endl;
    cout << "Program answer: " << ans << endl; 
    if (d[i] == ans) cout << "\033[1;34mSuccess!\033[0m " << endl;
    else cout << "\033[1;35mFailed\033[0m " << endl;
  }    
} 

void testSD() {
  set<int> a = {1, 2, 3, 4, 5, 6};
  set<int> b = {1, 2, 9, 10};
  a = TheKingsRoadsDiv2::setDiff(a, b);
  for (int i: a)
    cout << i << endl;
  cout << "b: " << endl; 
  for (int i: b)
    cout << i << endl; 
} 

int main(void) {
  //testSD(); 
  test();
  return 0;
} 
