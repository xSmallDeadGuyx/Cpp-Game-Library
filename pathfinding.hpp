#include <SFML/Graphics.hpp>
#include <cmath>
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

int Pathfinder::calculateHeuristic(Vector2i pos) {
  return 10 * (abs(pos.x - end.x) + abs(pos.y - end.y));
}

int Pathfinder::distanceBetween(Vector2i pos1, Vector2i pos2) {
  return (int) (10 * sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2)));
}

Vector2i Pathfinder::getLowestCellIn(vector<Vector2i> list) {
  bool found = false;
  int lowest;
  Vector2i result;
  for(int i = 0; i < list.size(); ++i) {
    Vector2i p = list[i];
    Vector2i c = cameFrom[p.x][p.y];
    int dist = (c.x >= 0 && c.y >= 0 ? gScore[c.x][c.y] + distanceBetween(p, c) : 0) + calculateHeuristic(p);
    if(!found || dist <= lowest) {
      lowest = dist;
      result = p;
    }
  }
  return result;
}

vector<Vector2i> Pathfinder::getNeighbouringCells(Vector2i p) {
  vector<Vector2i> found;
  if(p.x > 0 && !map[p.x - 1][p.y]) found.push_back(Vector2i(p.x - 1, p.y));
  if(p.x < mapWidth - 1 && !map[p.x + 1][p.y]) found.push_back(Vector2i(p.x + 1, p.y));
  if(p.y > 0 && !map[p.x][p.y - 1]) found.push_back(Vector2i(p.x, p.y - 1));
  if(p.y < mapHeight - 1 && !map[p.x][p.y + 1]) found.push_back(Vector2i(p.x, p.y + 1));
  return found;
}

vector<Vector2i> Pathfinder::reconstructPath(Vector2i pos) {
  Vector2i c = cameFrom[pos.x][pos.y];
  if(c.x >= 0 && c.y >= 0) {
    vector<Vector2i> path = reconstructPath(c);
    path.push_back(pos);
    return path;
  }
  else {
    vector<Vector2i> path;
    return path;
  }
}

int Pathfinder::getCellIndexIn(Vector2i cell, vector<Vector2i> list) {
  for(int i = 0; i < list.size(); ++i)
    if(list[i] == cell)
      return i;
  return -1;
}

vector<Vector2i> Pathfinder::findPath(Vector2i startPos, Vector2i endPos, bool **tiles, int width, int height) {
  start = startPos;
  end = endPos;
  map = tiles;
  mapWidth = width;
  mapHeight = height;
  
  gScore = new int*[mapWidth];
  hScore = new int*[mapWidth];
  fScore = new int*[mapWidth];
  cameFrom = new Vector2i*[mapWidth];
  for(int i = 0; i < mapWidth; ++i) {
    gScore[i] = new int[mapHeight];
    hScore[i] = new int[mapHeight];
    fScore[i] = new int[mapHeight];
    cameFrom[i] = new Vector2i[mapHeight];
  }

  vector<Vector2i> open;
  vector<Vector2i> closed;
  
  open.push_back(start);
  gScore[start.x][start.y] = 0;
  hScore[start.x][start.y] = fScore[start.x][start.y] = calculateHeuristic(start);
  cameFrom[start.x][start.y] = Vector2i(-1, -1);

  while(open.size() > 0) {
    Vector2i cell = getLowestCellIn(open);
    if(cell == end) return reconstructPath(end);
    open.erase(open.begin() + getCellIndexIn(cell, open));
    closed.push_back(cell);
    
    vector<Vector2i> neighbours = getNeighbouringCells(cell);
    for(int i = 0; i < neighbours.size(); ++i) {
      Vector2i n = neighbours[i];
      if(getCellIndexIn(n, closed) > -1) continue;
      
      int possibleG = gScore[cell.x][cell.y] + distanceBetween(cell, n);
      if(getCellIndexIn(n, open) == -1 || possibleG < gScore[n.x][n.y]) {
	if(getCellIndexIn(n, open) == -1) {
	  open.push_back(n);
	}
	gScore[n.x][n.y] = possibleG;
	hScore[n.x][n.y] = calculateHeuristic(n);
	fScore[n.x][n.y] = gScore[n.x][n.y] + hScore[n.x][n.y];
	cameFrom[n.x][n.y] = cell;
      }
    }
  }

  vector<Vector2i> path;
  return path;
}

Pathfinder::~Pathfinder() {
  for(int i = 0; i < mapWidth; ++i) {
    delete[] gScore[i];
    delete[] fScore[i];
    delete[] hScore[i];
    delete[] cameFrom[i];
  }
  delete[] gScore;
  delete[] fScore;
  delete[] hScore;
  delete[] cameFrom;
}
