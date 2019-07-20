#pragma once
#include "Control.h"

class ComboBox : public Control {

private:
	vector<string> options;
	size_t selected;
	bool isOpened = false;

public:
	ComboBox(int, vector<string>);
	size_t GetSelectedIndex()						{ return this->selected; }
	void SetSelectedIndex(size_t index) { this->selected = index; }
	virtual bool canGetFocus()					{ return true; } //can be focused according to project's definition
	virtual void draw(Graphics, int, int, size_t);
	virtual void keyDown(int, char); 										// only Up and Down
	virtual void mousePressed(int, int, DWORD); 				// only Enter or Space
};