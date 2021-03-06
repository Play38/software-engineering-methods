#include "Control.h"

Control* Control::focusObj = NULL;

Control::Control()
{
}

Control::Control(int borderType,short x, short y,COORD cor) 
	:left(x), top(y), cord(cor)
{
	switch (borderType) {
	case 0:
		bs = new NoBorder();
		break;
	case 1:
		bs = new SingleBorder();
		break;
	case 2:
		bs = new DoubleBorder();
		break;
	default:
		break;
	}

	background = Color::Black;
	foreground = Color::White;
}


void Control::setColor(Color bg, Color fg)
{
	this->background = bg;
	this->foreground = fg;
}



Control::~Control()
{
}
