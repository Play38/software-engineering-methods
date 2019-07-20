#pragma once
#include "Control.h"

class Button;

struct MouseListener{
  virtual void MousePressed(Button &b, int x, int y, bool isLeft) = 0;
};

class Button : public Control {

private:
  string value;
  MouseListener* listener;

public:
  Button(int);
  void SetValue(string value)         { this->value = value; }      //set button text
  string GetValue()                   { return this->value; }       //get button text
  bool canGetFocus()                  { return false; }             //buttons can't be focused by project's demand
  void keyDown(int, char)             { this->graphics.clearScreen(); }
  void AddListener(MouseListener &listener) { this->listener = &listener; }
  void mousePressed(int xPos, int yPos, DWORD button) { listener->MousePressed(*this, xPos, yPos, true); }
  void draw(Graphics, int, int, size_t);
};