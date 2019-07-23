#pragma once
#include "Control.h"

//checklist class
class CheckList : public Control {
protected:
	vector<string> options; 																					//options
	vector<size_t> checked; 																					//mark to mark as checked
public:
	CheckList(int, int, vector<string>);															//constructor
	vector<size_t> GetSelectedIndices()			{ return this->checked; } //get selected items
	bool canGetFocus()											{ return true; }					//this control can get focus
	void draw(Graphics, int, int, size_t);														//draw method
	void keyDown(int, char);																					//handle keypress
	void mousePressed(int, int, DWORD);																//handle mouse press
	void SelectIndex(size_t index)					{ this->checked[index] = 1; } //set selected index 
	void DeselectIndex(size_t index)				{ this->checked[index] = 0; }  //deselect index
};
