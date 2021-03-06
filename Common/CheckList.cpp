#include "CheckList.h"

CheckList::CheckList(int bord, short x, short y, COORD cor, vector<string> str)
	:Control::Control(bord,x,y,cor) , currentIndex(0)
{
	for (int i = 0; i < str.size() ; i++)
	{
		allCheckBoxes.push_back(new CheckBox(x + 2,y + (i *3),str[i]));
	}
}

void CheckList::draw(Graphics& g, int x, int y, size_t z)
{
	g.setBackground(this->background);
	g.setForeground(this->foreground);
	bs->drawBorderType(x, y, cord ,g);
	for (size_t i = 0; i < allCheckBoxes.size(); ++i)
		allCheckBoxes[i]->draw(g, (short)(x + 3) ,(short)(y + 1 + (i * 3)) ,z);
}

bool CheckList::canGetFocus() 
{ 
	return true; 
}

void CheckList::mousePressed(int x, int y, bool isLeft, Graphics &g)
{
	int index = 0;
	for (auto child : allCheckBoxes)
	{
		if (y >= child->getTop() && y <= child->getTop() + child->getCord().Y)
		{
			if (x >= this->getLeft() && x <= this->getLeft() + this->getCord().X + 1)
			{
				this->allCheckBoxes[currentIndex]->setColor(Color::Black, Color::White);
				currentIndex = index;
				this->allCheckBoxes[currentIndex]->setColor(Color::White, Color::Black);
			}
		}
		index++;
		child->mousePressed(x, y, isLeft,g);
	}
}

void CheckList::keyDown(int keyCode, char character, Graphics &g)
{
	switch (keyCode)
	{
		case 40:	//down arrow
		case 98:	//NUM2 key		
			HoverElement(g,false);		
			break;

		case 38:	// up arrow key
		case 104:	// NUM8 key			
			HoverElement(g,true);
			break;

		case 32:	// Space key
		case 13:	// Enter key
			allCheckBoxes[currentIndex]->keyDown(keyCode, character, g);
			break;
		default:
			break;
	}
}


bool CheckList::addSelectedItem(string item)
{
	for (auto it = allCheckBoxes.begin(); it != allCheckBoxes.end(); ) {
		if ((*it)->getCbValue() == item)
		{
			(*it)->setIsChecked(true);
			return true;
		}
		else
			++it;
	}
	return false;
	
}
bool CheckList::removeSelectedItem(string item)
{
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


void CheckList::getAllControls(vector<Control*>* controls)
{
	vector<Control*> items(allCheckBoxes.begin(), allCheckBoxes.end());
	*controls = items;
}

void CheckList::HoverElement(Graphics &g, bool Up)
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

bool CheckList::setLocalFocus()
{
	if (currentIndex == allCheckBoxes.size() - 1)
	{
		currentIndex = 0;
		return false;
	}
	++currentIndex;
	return true;
}


vector<string> CheckList::getSelectedCheckboxes() {
	vector<string> tmpSelectedCheckBoxes;
	for (auto it = allCheckBoxes.begin(); it != allCheckBoxes.end(); ) {
		if ((*it)->getIsChecked())
		{
			tmpSelectedCheckBoxes.push_back((*it)->getCbValue());
		}
		else
			++it;
	}
	return tmpSelectedCheckBoxes;
}

void CheckList::resetFocus()
{
	for (auto it = allCheckBoxes.begin(); it != allCheckBoxes.end(); )
	{
		(*it)->setColor(Color::Black, Color::White);
		++it;
	}
}
