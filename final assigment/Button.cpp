#include "Button.h"

//button C'tor
Button::Button(int width) {
  this->width = width;
  this->height = 1;
  this->border = BorderType::Single;
  this->showed = true;
  this->value = "Submit";
}

void Button::draw(Graphics g, int x, int y, size_t z) {
  graphics.setBackground(this->background);
  graphics.setForeground(this->foreground);
  drawBackground();
  graphics.write(x, y, this->GetValue());
}

