#pragma
#include "Control.h"
#include <string>

class TextBox : public Control
{

  private:
	string value = "";

  public:
	TextBox(int);
	void SetValue(string _value) 	{ this->value = _value; }
	string GetValue() 						{ return this->value; }
	bool canGetFocus() 						{ return true; }
	int getWidth() 								{ return this->width; }
	int getHeight() 							{ return this->height; }
	void draw(Graphics, int, int, size_t);
	void keyDown(int, char);
	void mousePressed(int, int, DWORD);
};