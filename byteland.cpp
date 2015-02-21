#include<vector>
#include<set>
#include<iostream>
using namespace std;
class TheKingsRoadsDiv2 {
public:
  static string weirdcase(int h, vector<int>& a, vector<int>& b) {
    return "Incorrect"; 
  } 
  static string getAnswer(int h, vector<int> a, vector<int> b) {
    set<int> adj[1025]; 
    for (int i = 0; i < a.size(); i++) { 
      adj[a[i]].insert(b[i]);
      adj[b[i]].insert(a[i]);
    }
    //three possibilities: 1/2 3 3 4 4 3 3..
    //3 3 3 3 ...
    //1 3 3 4 4...
    //1 3 3 3 5 3...
    //detect self loop
    set<int> newedge; //newedge contains root and new edges
    set<int> loop; 
    for (int i = 1; i < a.size() + 1; i++) {
      if (!(adj[i].size() & 1)) newedge.insert(i);
      auto it = adj[i].find(i); 
      if (it != adj[i].end()) { 
	adj[i].erase(it);
	loop.insert(i); 
      } 
    }
    if (loop.size() * 2 + newedge.size() != 3) {
      //either incorrect, or new edge contains root
      if (newedge.size() == 1) return weirdcase(h, a, b); 
      return "Incorrect";
    } 
    //eliminate newedge
    auto it = newedge.begin(); 
    int u = *it++; 
    int w = *it; 
    adj[u].erase(w);
    adj[w].erase(u); 
    //find root
    int root; 
    try { 
      for (int i = 1; i < a.size() + 1; i++) {
	if (adj[i].size() == 2) throw i;
      }
      return "Incorrect";
    } catch (int i) {
      root = i;
    }
    //depth
    int d = h; 
    //bfs
    for (set<int> layer(&root, &root + 1),
	   explored; layer.size() <= d; ) {
      set<int> newlayer;
      for (auto it = layer.begin(); it != layer.end(); it++) {
	set<int> children; 
	for (auto v = adj[*it].begin(); v != adj[*it].end(); v++) {
	  if (explored.find(*v) != explored.end()) {
	    children.insert(*v);
	  }
	}
	if (children.size() != 2) return "Incorrect";
	for (auto it = children.begin(); it != children.end(); it++) 
	  newlayer.insert(*it);
	explored.insert(*it);
      }
    }
    return "Correct"; 
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
  for (int i = 3; i < 4; i++) {
    cout << "Test " << i << endl;
    cout << "Input: " << endl; 
    auto ans = TheKingsRoadsDiv2::getAnswer(a[i], b[i], c[i]);
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
