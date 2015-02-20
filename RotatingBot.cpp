//TopCoder SRM 550 DIV 2
#include<iostream>
#include<vector>
#include<exception>
#include<cstring>
using namespace std;
class Dir { //direction
public:
  int d; //0 for E, 1 for N, 2 for W, 3 for S
  Dir(): d(0) {}
  void turn() {
    d = (d + 1) & 3;
  }
  operator int() const {
    return d;
  } 
};

class Point {
public:
  int x, y;
  Point(int xx = 55, int yy = 55): x(xx), y(yy) {}; 
  void inc(Dir d) {
    int ix[] = {1, 0, -1, 0};
    int iy[] = {0, 1, 0, -1};
    x += ix[d];
    y += iy[d]; 
  }
  Point test(Dir d) {
    Point p(x, y);
    p.inc(d);
    return p;
  }
  friend ostream& operator<<(ostream& out, const Point& p) {
    out << "(" << p.x << ", " << p.y << ")" << endl;
    return out;
  }
  bool& operator[](bool grid[110][110]) {
    return grid[x][y];
  }
  int& operator[](Dir d) {
    if (d & 1) return y;
    return x;
  } 
};

struct OccupiedException: public exception {};
struct InvalidException: public exception {};
struct FinalException: public exception {}; 

class BotGrid {
  bool Grid[110][110]; //false means available, true means stepped in
  Point p; //current position
  Dir d; //current direction
  int bounds[4]; //0 xmax, 1 ymax, 2 xmin, 3 ymin
  bool final; 
public:
  BotGrid() {
    for (int i = 0; i < 4; i++) bounds[i] = 55;
    memset(Grid, 0, sizeof(Grid)); 
    p.x = p.y = 55; 
    Grid[55][55] = true;
  }
  void go(int steps = 1) { //proceed next
    if (final) throw FinalException(); 
    for (int i = 0; i < steps; i++) {
      p.inc(d);
      if (p[Grid]) {
	throw OccupiedException(); //occupied
      }
      p[Grid] = true;
    }
    if (bounds[d] == 55) {
      if ((d > 1) && (bounds[d] < p[d])) final = true; 
      else bounds[d] = p[d]; 
    } else {
      if (!((bounds[d] == p[d]) //out of bounds
	    || (p.test(d)[Grid]))) //facing occupied spot
	throw InvalidException(); //irrational!
    }
    cerr << bounds[0] << " " << bounds[1] << " " << bounds[2]
	 << " " << bounds[3] << endl; 
  }

  void turn() { 
    d.turn();
  }
  
  int minArea() {
    return (bounds[0] - bounds[2] + 1) * (bounds[1] - bounds[3] + 1);
  }
}; 

class RotatingBot {
public:
  static int minArea(vector<int> moves) {
    try {
      BotGrid g;
      for (vector<int>::iterator it = moves.begin();
	   it != moves.end(); ++it) {
	g.go(*it);
	g.turn();
      }
      return g.minArea(); 
    } catch (exception& e) {
      return -1;
    } 
  }
};

void testDir() {
  Dir d; 
  for (int i = 0; i < 10; i++) {
    d.turn(); 
    cout << d;
  }
}

void testPoint() {
  Point p(10, 10); 
  Dir d; 
  for (int i = 0; i < 10; i++) {
    p.inc(d); 
    d.turn(); 
    cout << p << endl;
  }
}

void testBotGrid() {
  BotGrid g;
  g.go(10);
  g.turn(); 
  g.go(20);
  g.turn();
  g.go(30);
  g.turn();
  g.go(40);
  g.turn();
  g.go(30); 
}

void testRotBot() {
  int inputs[] = {5,4,5,3,3};
  vector<int> i(inputs, inputs + sizeof(inputs) / sizeof(int));
  cout << RotatingBot::minArea(i);
} 

int main(void) {
  testRotBot(); 
  return 0; 
} 
