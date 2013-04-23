class Maze {
public:
  bool **blocks;
private:
  int vw;
  int vh;
  int ow;
  int oh;
  bool **visited;
  void gen(int x, int y);
public:
  Maze();
  ~Maze();
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

Maze::~Maze() {
  for(int i = 0; i < width; ++i)
    delete[] blocks[i];
  delete[] blocks;
  for(int i = 0; i < vw; ++i)
    delete[] visited[i];
  delete[] visited;
}

void Maze::gen(int x, int y) {
  int bx = 2 * x + 1;
  int by = 2 * y + 1;
  int vx = x + 1;
  int vy = y + 1;

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
  ow = w;
  oh = h;
  vw = w + 2;
  vh = h + 2;
  width = w * 2 + 1;
  height = h * 2 + 1;

  blocks = new bool*[width];
  for(int i = 0; i < width; ++i)
    blocks[i] = new bool[height];
  visited = new bool*[vw];
  for(int i = 0; i < vw; ++i)
    visited[i] = new bool[vh];
  
  for(int i = 0; i < w * 2 + 1; ++i)
    for(int j = 0; j < h * 2 + 1; ++j)
      blocks[i][j] = true;

  for(int i = 0; i < w + 2; ++i)
    for(int j = 0; j < h + 2; ++j)
      visited[i][j] = i == 0 || i == w + 1 || j == 0 || j == h + 1;

  gen(0, 0);
  hasGenerated = true;
}
