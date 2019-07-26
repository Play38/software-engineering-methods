#pragma once
#include "Control.h"
#include "Button.h"

class Messagebox : public Control {

private:
  string title = "";
  string text = "";
  vector <Button*> buttons;

public:
  Messagebox(int, int);
  void SetTitle(string title) { this->title = title; }
  string GetTitle()     { return this->title; }
  void SetText(string text) { this->text = text; }
  string GetText()      { return this->text; }
  bool canGetFocus()      { return false; }   //no focus according to task definition
  void draw(Graphics, int, int, size_t);
  void keyDown(int, char) {}
  void mousePressed(int, int, DWORD);
  void addButton(Button&, int, int);
};
