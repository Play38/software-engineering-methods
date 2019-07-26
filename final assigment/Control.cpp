#include "Control.h"
#include <iostream>
#include <vector>

using namespace std;
Control *Control::focus = 0;

//set focus on specific control
void Control::setFocus(Control &control) {
  if (getFocus() != NULL) {
    getFocus()->SetForeground(Color::White);
    getFocus()->setLayer(0);
  }

  control.graphics.moveTo(control.getLeft(), control.getLeft());
  control.graphics.setCursorVisibility(true);
  focus = &control;
  control.setLayer(1);
  control.SetForeground(Color::Green);
}

//draw border to a specific control regarding his border type
void Control::drawBorder(BorderType border) {
  int i = this->getLeft() - 1, j = this->getTop() - 1;
  switch (border) {
  case BorderType::Double:
    graphics.setBackground(this->background);
    graphics.setForeground(this->foreground);

    graphics.write(i, j, "\xC9");
    
    for (int z = 0; z < this->width; ++z)
      graphics.write("\xCD");

    graphics.write("\xBB\n");
    
    for (int z = 1; z < this->height + 1; ++z) {
      graphics.write(i, j + z, "\xBA");
      graphics.write(i + this->width + 1, j + z, "\xBA\n");
    }

    graphics.write(i, j + this->height + 1, "\xC8");
    for (int i = 0; i < this->width; ++i)
      graphics.write("\xCD");

    graphics.write("\xBC");
    break;

  case BorderType::None:
    break;

  case BorderType::Single:
    graphics.write(i, j, "\xDA");
    for (int z = 0; z < this->width; ++z)
      graphics.write("\xC4");

    graphics.write("\xBF\n");

    for (int z = 1; z < this->height + 1; ++z) {
      graphics.write(i, j + z, "\xB3");
      graphics.write(i + this->width + 1, j + z, "\xB3\n");
    }

    graphics.write(i, j + this->height + 1, "\xC0");
    
    for (int i = 0; i < this->width; ++i)
      graphics.write("\xC4");
    
    graphics.write("\xD9");
    break;
  }
}

//set background to a specific control
void Control::SetForeground(Color color) {
  foreground = color;
  this->graphics.setForeground(color);
}

//draw background to a specific control regarding his background type
void Control::drawBackground() {
  graphics.setBackground(this->background);
  graphics.setForeground(this->foreground);
  for (int i = this->getTop(); i < this->getTop() + this->getHeight(); ++i)
    for (int j = this->getLeft(); j < this->getLeft() + this->getWidth(); ++j)
      graphics.write(j, i, " ");
}