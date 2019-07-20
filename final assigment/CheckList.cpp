//Authors: Haim Elbaz ~ Roni Polisanov ~ Reut Leib
#pragma once
#include "CheckList.h"

//Checklist constructor
CheckList::CheckList(int height, int width, vector<string> options) {
	this->height = height;
	this->width = width;
	this->options = options;
	this->checked = { 0, 0, 0 };
	this->showed = true;
}

//checklist draw method
void CheckList::draw(Graphics g, int x, int y, size_t z) {
	graphics.setBackground(this->background);
	graphics.setForeground(this->foreground);

	for (int i = 0; i < this->options.size(); i++) {		//for each row in checklist
		if (this->checked[i] == 0) {
			graphics.write(x, y + i, "( )");					//if not selected - draw empty
			graphics.write(x + 7, y + i, this->options[i]);	
		}
		if (this->checked[i] == 1) {
			graphics.write(x, y + i, "(X)");					//if selected - draw full (X)
			graphics.write(x + 7, y + i, this->options[i]);	
		}
	}
}

//handle key click to change the option in checklist status
void  CheckList::keyDown(int keyCode, char c) {
	this->graphics.setCursorVisibility(true);

	for (int i = 0; i < this->options.size(); i++) {
		graphics.moveTo(this->getLeft() + 1, this->getTop() + i);
		int _char = getchar();

		do {
			if (_char == VK_TAB)
				break;
			switch (this->checked[i]) {
				case 1:
					this->checked[i] = 0;
					putchar(' ');
					break;
				case 0:
					this->checked[i] = 1;
					putchar('X');
					break;
			}
			break;
		} while (_char != VK_TAB);
	}
}

//handle mouse click to change the option in checklist status
void CheckList::mousePressed(int x, int y, DWORD btn) {
	for (int i = 0; i < this->getHeight(); i++) {
		if (x == (this->getLeft() + 1) && y == (this->getTop() + i)) {
			graphics.moveTo(this->getLeft() + 1, this->getTop() + i);
			switch (this->checked[i]) {
				case 1:						//if already checked, unchecked
					this->checked[i] = 0;
					putchar(' ');
					break;
				case 0:						//if unchecked, make it checked 
					this->checked[i] = 1;
					putchar('X');
					break;
			}
			break;
		}
	}
}
