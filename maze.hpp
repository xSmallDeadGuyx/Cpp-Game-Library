#include <iostream>

class Maze {
public:
  bool **blocks;
private:
  bool **visited;
  void gen(int x, int y);
public:
  Maze();
  bool hasGenerated;
  int width;
  int height;
  void generate(int w, int h);
};

Maze::Maze() {
  hasGenerated = false;
  width = 0;
  height = 0;
}

void Maze::gen(int x, int y) {
  int bx = 2 * x + 1;
  int by = 2 * y + 1;
  int vx = x + 1;
  int vy = y + 1;

  std::cout << "x: " << x << " - y: " << y << std::endl;

  blocks[bx][by] = false;
  visited[vx][vy] = true;
  
  while(!(visited[vx - 1][vy] && visited[vx + 1][vy] && visited[vx][vy - 1] && visited[vx][vy + 1])) {
    int n = rand() % 4;
    if(n == 0 && !visited[vx - 1][vy]) {
      blocks[bx - 1][by] = false;
      gen(x - 1, y);
    }
    else if(n == 1 && !visited[vx + 1][vy]) {
      blocks[bx + 1][by] = false;
      gen(x + 1, y);
    }
    else if(n == 2 && !visited[vx][vy - 1]) {
      blocks[bx][by - 1] = false;
      gen(x, y - 1);
    }
    else if(n == 3 && !visited[vx][vy + 1]) {
      blocks[bx][by + 1] = false;
      gen(x, y + 1);
    }
  }
}

void Maze::generate(int w, int h) {
  width = w * 2 + 1;
  height = h * 2 + 1;

  blocks = new bool*[w * 2 + 1];
  for(int i = 0; i < w * 2 + 1; ++i)
    blocks[i] = new bool[h * 2 + 1];
  visited = new bool*[w + 2];
  for(int i = 0; i < w + 2; ++i)
    visited[i] = new bool[h + 2];
  
  for(int i = 0; i < w * 2 + 1; ++i)
    for(int j = 0; j < h * 2 + 1; ++j)
      blocks[i][j] = true;

  for(int i = 0; i < w + 2; ++i)
    for(int j = 0; j < h + 2; ++j)
      visited[i][j] = i == 0 || i == w + 1 || j == 0 || j == h + 1;

  gen(0, 0);
}
