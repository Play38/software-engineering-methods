#pragma once
#include "Control.h"
#include "CheckList.h"

class RadioBox : public CheckList {
private:
	size_t toCheck = 0;

public:
	RadioBox(int, int, vector<string>);
	void draw(Graphics, int, int, size_t);
	void keyDown(int, char);
	void mousePressed(int, int, DWORD);
	inline size_t GetSelectedIndex()       { return this->toCheck; }
	inline void SetSelectedIndex(size_t i) { this->toCheck = i; }
};
