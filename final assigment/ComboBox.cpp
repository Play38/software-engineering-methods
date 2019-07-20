#include <iostream>
#include "ComboBox.h"

using namespace std;

ComboBox::ComboBox(int width, vector<string> options) {
  this->width = width;
  this->height = 1;
  this->options = options;
  this->showed = true;
}

void ComboBox::draw(Graphics g, int x, int y, size_t z) {
  graphics.setBackground(this->background);
  graphics.setForeground(this->foreground);
  drawBackground();

  switch (this->isOpened) {
  case false: //combobox closed
    graphics.write(x + this->width - 3, y, "\xBA"); // ||  border symbol - ascii table
    graphics.write(x + this->width - 1, y, "\xFB");
    graphics.write(x + 1, y, this->options[this->GetSelectedIndex()]);
    break;

  case true:  //combobox opened
    graphics.write(x + this->width - 3, y, "\xBA"); // || border symbol - ascii table
    graphics.write(x + this->width - 1, y, "\xFB");
    graphics.write(x + 1, y, this->options[this->GetSelectedIndex()]); //write the text of selected option 

    for (int i = 0; i < options.size(); ++i) {
      //handle the graphics of the selected option
      if (i == GetSelectedIndex()) {
        graphics.setBackground(Color::Blue);
        graphics.write(this->getLeft() + 1, this->getTop() + i + 1, this->options[i]);
        graphics.setBackground(this->background);
      }
      else
        graphics.write(this->getLeft() + 1, this->getTop() + i + 1, this->options[i]);
    }
  }
  graphics.setForeground(Color::White);
  graphics.setBackground(Color::Black);
}

void ComboBox::keyDown(int keyCode, char character) {
  int position = this->getTop() + this->GetSelectedIndex() + 1;
  int index = this->GetSelectedIndex();
  int iBefore = index;
  int c;
  while (1) {
    c = getchar();
    if (c == VK_UP) {
      if (position <= this->getTop() + 1) {}
      else {
        --position;
        --index;
      }
    }

    if (c == VK_DOWN) {
      if (position >= this->getTop() + this->options.size() + 1) {}
      else {
        ++position;
        ++index;
      }
    }
    if (c == VK_TAB || c == VK_RETURN) {
      break;
    }
  }
  this->SetSelectedIndex(index);
  if (index != iBefore)
    this->height -= options.size();
  this->isOpened = false;
}

void ComboBox::mousePressed(int x, int y, DWORD button) {
  int top = this->getTop();
  int left = this->getLeft();
  vector<string> options = this->options;

  switch (this->isOpened) {
  case false:
    this->height += options.size();
    this->isOpened = true;
    break;
  case true:
    for (int k = 0; k < options.size(); ++k) {
      if (y == top + k + 1) {
        this->selected = k;
        this->height -= options.size();
        this->isOpened = false;
        break;
      }
    }
  }
};

