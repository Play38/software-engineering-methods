#include "Label.h"

Label::Label(int width) {
    this->width = width;
    this->height = 1;
    this->showed = true;
}

void Label::draw(Graphics g, int x, int y, size_t z) {
	//draw label as requested
    graphics.setBackground(this->background);
	graphics.setForeground(this->foreground);
	graphics.write(x, y, this->GetValue());
    //set default values
	graphics.setForeground(Color::White);
	graphics.setBackground(Color::Black);
}