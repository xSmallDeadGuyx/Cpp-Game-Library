#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Pathfinder {
private:
  int mapWidth;
  int mapHeight;
  bool **map;
  Vector2i start;
  Vector2i end;
  int **gScore;
  int **hScore;
  int **fScore;
  Vector2i **cameFrom;
  
  int calculateHeuristic(Vector2i pos);
  int distanceBetween(Vector2i pos1, Vector2i pos2);
  Vector2i getLowestCellIn(vector<Vector2i> list);
  vector<Vector2i> getNeighbouringCells(Vector2i pos);
  vector<Vector2i> reconstructPath(Vector2i pos);
  int getCellIndexIn(Vector2i cell, vector<Vector2i> list);
public:
  ~Pathfinder();
  vector<Vector2i> findPath(Vector2i startPos, Vector2i endPos, bool **tiles, int width, int height);
};

#endif
