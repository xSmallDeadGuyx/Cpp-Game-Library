#ifndef DRAW_H
#define DRAW_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Draw {
private:
  RenderWindow* window;
public:
  Draw(RenderWindow *win);
  void rectangle(Vector2f pos, Vector2f size, Color col);
};

#endif
