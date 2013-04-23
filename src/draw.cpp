#include "draw.h"

#include <SFML/Graphics.hpp>
using namespace sf;

Draw::Draw(RenderWindow *win) {
  window = win;
}

void Draw::rectangle(Vector2f pos, Vector2f size, Color col) {
  RectangleShape rect(size);
  rect.setPosition(pos);
  rect.setFillColor(col);
  window->draw(rect);
}
