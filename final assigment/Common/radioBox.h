#ifndef RADIOBOX_H
#define RADIOBOX_H

#include "checkBox.h"

using namespace std;

class RadioBox : public Control {
private:
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	vector<CheckBox*> allCheckBoxes;
	int currentIndex;
	void HoverElement(Graphics &g, bool Up);

public:
	RadioBox(int bordertype, short left, short top, COORD cord, vector<string> str);
	bool addSelectedItem(string item);
	bool removeSelectedItem(string item);
	void draw(Graphics& g, int x, int y, size_t z);
	bool myPureFunction() { return true; };
	bool canGetFocus();

	void getAllControls(vector<Control*>* controls);
	bool setLocalFocus();


	bool getSelectedBox();
	bool selectBox();
	
	void mousePressed(int x, int y, bool isLeft, Graphics &g);
	void keyDown(int keyCode, char character, Graphics &g);

	void resetFocus();
};

#endif // !RADIOBOX_H
