#ifndef MAZE_H
#define MAZE_H

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

#endif
