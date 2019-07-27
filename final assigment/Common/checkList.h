#ifndef CHECKLIST_H
#define CHECKLIST_H
#include "checkBox.h"


class CheckList : public Control {
private:
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	vector<CheckBox*> allCheckBoxes;
	int currentIndex;

	void HoverElement(Graphics &g, bool Up);

public:
	CheckList(int bordertype,short left, short top, COORD cord, vector<string> str);
	bool addSelectedItem(string item);
	bool removeSelectedItem(string item);
	vector<string> getSelectedCheckboxes();
	void draw(Graphics& g, int x, int y, size_t z);
	bool myPureFunction() { return true; };
	bool canGetFocus();

	bool setLocalFocus();

	void mousePressed(int x, int y, bool isLeft, Graphics &g);
	void keyDown(int keyCode, char character, Graphics &g);

	void getAllControls(vector<Control*>* controls);

	void resetFocus();


};

#endif //CHECKLIST_H