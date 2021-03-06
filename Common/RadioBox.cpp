#include "RadioBox.h"

RadioBox::RadioBox(int bord, short x, short y, COORD cor, vector<string> str)
	:Control::Control(bord, x, y, cor), currentIndex(0)
{
	for (int i = 0; i < str.size(); i++) 
	{
		allCheckBoxes.push_back(new CheckBox(x + 2, y + (i * 3), str[i]));
	}
}

void RadioBox::draw(Graphics& g, int x, int y, size_t z)
{
	g.setBackground(this->background);
	g.setForeground(this->foreground);
	bs->drawBorderType(x, y, cord ,g);
	for (size_t i = 0; i < allCheckBoxes.size(); ++i)
		allCheckBoxes[i]->draw(g, (short)(x + 3), (short)(y + 1 + (i * 3)), z);
}

bool RadioBox::canGetFocus() { return true; }

bool  RadioBox::getSelectedBox() {
	return 0;
};

bool RadioBox::addSelectedItem(string item) {
	for (auto it = allCheckBoxes.begin(); it != allCheckBoxes.end(); ) {
		if ((*it)->getCbValue() == item)
		{
			(*it)->setIsChecked(true);
			for (auto it2 = allCheckBoxes.begin(); it2 != allCheckBoxes.end();) {
				if ((*it2)->getCbValue() != item)
					(*it2)->setIsChecked(false);
			}
			return true;
		}
		else
			++it;
	}
	return false;
};

bool RadioBox::removeSelectedItem(string item) {
	for (auto it = allCheckBoxes.begin(); it != allCheckBoxes.end(); ) {
		if ((*it)->getCbValue() == item)
		{
			(*it)->setIsChecked(false);
			return true;
		}
		else
			++it;
	}
	return false;
}


void RadioBox::mousePressed(int x, int y, bool isLeft, Graphics &g)
{
	int checkBoxIndex = 0;
	for (auto child : allCheckBoxes)
	{
		if (y >= child->getTop() && y <= child->getTop() + child->getCord().Y)
		{
			if (x >= this->getLeft() && x <= this->getLeft() + this->getCord().X + 1)
			{
				this->allCheckBoxes[currentIndex]->setColor(Color::Black, Color::White);
				currentIndex = checkBoxIndex;
				this->allCheckBoxes[currentIndex]->setColor(Color::White, Color::Black);
			}
		}
		checkBoxIndex++;
		child->setIsChecked(false);
		child->mousePressed(x, y, isLeft, g);
	}
}

void RadioBox::keyDown(int keyCode, char character, Graphics &g)
{
	switch (keyCode)
	{
	case 40:	//down arrow 
	case 98:	//NUM2 key
		HoverElement(g, false);
		break;
	case 38:	// up arrow key
	case 104:	// NUM8 key
		HoverElement(g, true);
		break;

	case 32:	// Space key
	case 13:	// Enter key
		for (auto child : allCheckBoxes)
		{
			child->setIsChecked(true);
			child->keyDown(keyCode, character, g);
		}

		allCheckBoxes[currentIndex]->keyDown(keyCode, character, g);
		break;

	default:
		break;
	}
};

bool RadioBox::setLocalFocus()
{
	if (currentIndex == allCheckBoxes.size() - 1)
	{
		currentIndex = 0;
		return false;
	}

	++currentIndex;
	return true;
}

void RadioBox::getAllControls(vector<Control*>* controls)
{
	vector<Control*> items(allCheckBoxes.begin(), allCheckBoxes.end());
	*controls = items;
}


void RadioBox::HoverElement(Graphics &g, bool Up)
{
	if (Up)
	{
		if (currentIndex == 0)
		{
			this->allCheckBoxes[currentIndex]->setColor(Color::Black, Color::White);
			currentIndex = allCheckBoxes.size() - 1;
			this->allCheckBoxes[currentIndex]->setColor(Color::White, Color::Black);
		}

		else
		{
			this->allCheckBoxes[currentIndex]->setColor(Color::Black, Color::White);
			--currentIndex;
			this->allCheckBoxes[currentIndex]->setColor(Color::White, Color::Black);
		}
	}

	else
	{
		if (currentIndex == allCheckBoxes.size() - 1)
		{
			this->allCheckBoxes[currentIndex]->setColor(Color::Black, Color::White);
			currentIndex = 0;
			this->allCheckBoxes[currentIndex]->setColor(Color::White, Color::Black);
		}

		else
		{
			this->allCheckBoxes[currentIndex]->setColor(Color::Black, Color::White);
			++currentIndex;
			this->allCheckBoxes[currentIndex]->setColor(Color::White, Color::Black);
		}
	}
}



void RadioBox::resetFocus()
{
	for (auto it = allCheckBoxes.begin(); it != allCheckBoxes.end(); )
	{
		(*it)->setColor(Color::Black, Color::White);
		++it;
	}
}