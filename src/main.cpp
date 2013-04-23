#include <SFML/Graphics.hpp>
#include "game.h"
#include "constants.h"
using namespace sf;

Game game;
RenderWindow window;

int main() {
  window.create(VideoMode(constants::windowBounds.x, constants::windowBounds.y), "Some game");

  Clock clock;
  const double dt = 0.01;
  float currentTime = clock.restart().asSeconds();
  double accumulator = 0.0;
  
  game.doInit(window);
  while(window.isOpen()) {
    float frameTime = clock.restart().asSeconds();
    accumulator += frameTime;
    
    while(accumulator >= dt) {
      game.doUpdate(window);
      accumulator -= dt;
    }
    
    window.clear();
    game.doDraw(window);
    window.display();
  }
  
  return 0;
}
