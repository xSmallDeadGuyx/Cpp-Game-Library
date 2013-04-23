#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "draw.h"
#include "maze.h"
#include "pathfinding.h"

class Game {
private:
  Vector2i player;
  Draw *draw;
  Maze *gameGrid;
  Pathfinder pathfinder;
  std::vector<sf::Vector2i> path;
public:
  ~Game();
  void doInit(sf::RenderWindow &window);
  void doUpdate(sf::RenderWindow &window);
  void doDraw(sf::RenderWindow &window);
};

#endif
