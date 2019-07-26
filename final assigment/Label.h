#pragma once
#include "Control.h"

class Label : public Control
{
  private:
    int width;
    int height = 3;
    string value = "default value";

  public:
    Label(int);
    void SetValue(string value)         { this->value = value; }
    string GetValue()                   { return this->value; }
    bool canGetFocus()                  { return false; }
    void keyDown(int, char)             {};
    void mousePressed(int, int, DWORD)  {};
    void draw(Graphics, int, int, size_t);
};