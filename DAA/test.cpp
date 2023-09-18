#include <iostream>
using namespace std;

int equalize_water(int a, int b, int c) {
  int moves = 0;
  while (a != b) {
    if (a > b) {
      int x = min(a / c, b);
      a -= x * c;
      moves += 1;
    } else {
      int x = min(b / c, a);
      b -= x * c;
      moves += 1;
    }
  }
  return moves;
}

int main() {
  int a, b, c;
  int t;
      cin >> a >> b >> c;
      cout << equalize_water(a, b, c) << endl;
  return 0;
}