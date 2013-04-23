#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "draw.hpp"
#include "maze.hpp"
#include "pathfinding.hpp"
using namespace sf;

class Game {
private:
  Vector2i player;
  Draw *draw;
  Maze *gameGrid;
  Pathfinder pathfinder;
  std::vector<Vector2i> path;
public:
  void doInit(RenderWindow &window);
  void doUpdate(RenderWindow &window);
  void doDraw(RenderWindow &window);
};

void Game::doInit(RenderWindow &window) {
  draw = new Draw(&window);
  gameGrid = new Maze();
  gameGrid->generate(constants::gridWidth, constants::gridHeight);

  player.x = player.y = 1;
}

void Game::doUpdate(RenderWindow &window) {
  Event event;
  while(window.pollEvent(event)) {
    switch(event.type) {
    case Event::Closed:
      window.close();
      break;
    case Event::KeyPressed:
      switch(event.key.code) {
      case Keyboard::Escape:
	window.close();
	break;
      case Keyboard::Left:
	if(player.x > 0 && gameGrid->blocks[player.x - 1][player.y] == 0)
	  --player.x;
	break;
      case Keyboard::Right:
	if(player.x < gameGrid->width - 1 && gameGrid->blocks[player.x + 1][player.y] == 0)
	  ++player.x;
	break;
      case Keyboard::Up:
	if(player.y > 0 && gameGrid->blocks[player.x][player.y - 1] == 0)
	  --player.y;
	break;
      case Keyboard::Down:
	if(player.y < gameGrid->height - 1 && gameGrid->blocks[player.x][player.y + 1] == 0)
	  ++player.y;
	break;
      }
      break;
    case Event::MouseButtonPressed:
      switch(event.mouseButton.button) {
      case Mouse::Left:
	path = pathfinder.findPath(player, Vector2i(event.mouseButton.x / 16, event.mouseButton.y / 16), gameGrid->blocks, gameGrid->width, gameGrid->height);
	break;
      }
    }
  }
}

void Game::doDraw(RenderWindow &window) {
  for(int i = 0; i < gameGrid->width; ++i)
    for(int j = 0; j < gameGrid->height; ++j)
      if(gameGrid->blocks[i][j])
	draw->rectangle(Vector2f(i * 16, j * 16), Vector2f(16, 16), Color::Red);
  for(int i = 0; i < path.size(); ++i)
    draw->rectangle(Vector2f(path[i].x * 16, path[i].y * 16), Vector2f(16, 16), Color::Blue);
  draw->rectangle(Vector2f(player.x * 16, player.y * 16), Vector2f(16, 16), Color::Green);
}
