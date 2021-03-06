#include "ComboBox.h"

ComboBox::ComboBox(int bord, short x, short y, COORD cor, vector<string> comboOptions) 
	: Control::Control(bord,x,y,cor) , IsMenuOpenFlg(0), selectedIndex(0), keyPressIndex(0), intialComboBoxValue(""), Enablefocus(false)
{
	for (size_t i = 0; i < comboOptions.size(); i++) {
		items.push_back(new Label((short)(x + 1), (short)(y + cord.Y + 2 + i), comboOptions[i]));
	}
}

string ComboBox::getSelectedItem()
{
	if (selectedIndex == -1)
		return intialComboBoxValue;
	else
		return items[selectedIndex]->getValue();
}

void ComboBox::draw(Graphics& g, int x, int y, size_t z) 
{
	g.setBackground(this->background);
	g.setForeground(this->foreground);
	bs->drawBorderType(x, y, cord ,g);
	bs->drawBorderType((short)(x + cord.X + 1), y, { 2,2 } ,g);
	if (IsMenuOpenFlg == 1)
		bs->drawBorderType(x, (short)(y + cord.Y + 1), {cord.X, (short)(cord.Y + items.size())} ,g);

	if (selectedIndex == -1)
		g.write(x+1, y+1, intialComboBoxValue);
	else
		items[selectedIndex]->draw(g, x+1, y+1, 0);
	
	g.write(x + cord.X + 1 + 1, y + 1, "\x1F");
	if (IsMenuOpenFlg == 1) {
		for (short i = 0; i < (short)items.size(); i++) {
			items[i]->draw(g, x + 1, y + cord.Y + 2 + i, 0);
		}
	}
}

bool ComboBox::canGetFocus() { return Enablefocus; }

void ComboBox::mousePressed(int x, int y, bool isLeft, Graphics &g)
{
	if (x >= (left + cord.X + 1) && x <= (left + cord.X + 1) + 2 && y >= top && y <= top + cord.Y) 
	{
		if (IsMenuOpenFlg == 0) 
		{
			this->Enablefocus = true;
			IsMenuOpenFlg = 1;
			return;
		}
		if (IsMenuOpenFlg == 1) 
		{
			IsMenuOpenFlg = 0;
			return;
		}
	}
	if (IsMenuOpenFlg == 1) 
	{
		for (short i = 0; i < (short)items.size(); i++) {
				if(x >= (left+1) && x <= (left+cord.X) && y == (top + cord.Y + 2 + i)) {
					selectedIndex = i;
					IsMenuOpenFlg = 0;
			}		
		}
	}
}

void ComboBox::keyDown(int keyCode, char character, Graphics &g) {
	if (IsMenuOpenFlg == 1) {
		if (keyCode == 40 || keyCode == 98) {// down arrow or NUM2 key
			HoverElement(g, false);
		}
		else if (keyCode == 38 || keyCode == 104) {// up arrow or NUM8 key
			HoverElement(g, true);
		}
		else if (keyCode == 32 || keyCode == 13) {// Space or Enter key
			selectedIndex = keyPressIndex;
			IsMenuOpenFlg = 0;
		}
	}
}

void ComboBox::HoverElement(Graphics &g, bool Up) 
{
	if (Up)
	{
		if (keyPressIndex == 0)
		{
			this->items[keyPressIndex]->setColor(Color::Black, Color::White);
			keyPressIndex = items.size() - 1;
			this->items[keyPressIndex]->setColor(Color::White, Color::Black);
		}
		else
		{
			this->items[keyPressIndex]->setColor(Color::Black, Color::White);
			--keyPressIndex;
			this->items[keyPressIndex]->setColor(Color::White, Color::Black);
		}					
	}

	else
	{
		if (keyPressIndex == items.size() - 1)
		{
			this->items[keyPressIndex]->setColor(Color::Black, Color::White);
			keyPressIndex = 0;
			this->items[keyPressIndex]->setColor(Color::White, Color::Black);
		}
			
		else
		{
			this->items[keyPressIndex]->setColor(Color::Black, Color::White);
			++keyPressIndex;
			this->items[keyPressIndex]->setColor(Color::White, Color::Black);		
		}			
	}
}
