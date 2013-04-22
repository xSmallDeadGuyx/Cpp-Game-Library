#include <SFML/Graphics.hpp>
using namespace sf;

class Draw {
private:
  RenderWindow* window;
public:
  Draw(RenderWindow *win);
  void rectangle(Vector2f pos, Vector2f size, Color col);
};

Draw::Draw(RenderWindow *win) {
  window = win;
}

void Draw::rectangle(Vector2f pos, Vector2f size, Color col) {
  RectangleShape rect(size);
  rect.setPosition(pos);
  rect.setFillColor(col);
  window->draw(rect);
}
