#include "EventEngine.h"
#include <vector>
#include <algorithm>
#include "RadioBox.h"
#include "CheckList.h"
#include "Panel.h"

using namespace std;

EventEngine::EventEngine(DWORD input, DWORD output)
	: _console(GetStdHandle(input)), _graphics(output)
{
	GetConsoleMode(_console, &_consoleMode);
	SetConsoleMode(_console, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
}

void EventEngine::run(Control &c)
{
	int currentIndex = 0;
	Control* previousFocus;
	setFirstFocus(c);

	previousFocus = Control::getFocus();


	for (bool redraw = true;;)
	{
		if (redraw)
		{
			_graphics.clearScreen();
			_graphics.setCursorVisibility(false);
			for (size_t z = 0; z < 1; ++z)
			{
				c.draw(_graphics, c.getLeft(), c.getTop(), z);
			}
			_graphics.moveTo(c.getFocus()->getCurrentPosition().X, c.getFocus()->getCurrentPosition().Y);
			redraw = false;
		}
		INPUT_RECORD record;
		DWORD count;
		ReadConsoleInput(_console, &record, 1, &count);

		switch (record.EventType)
		{
		case KEY_EVENT:
		{
			auto f = Control::getFocus();

			if (f->IsCursorVisible())
				_graphics.setCursorVisibility(true);
			else
				_graphics.setCursorVisibility(false);

			if (f != nullptr && record.Event.KeyEvent.bKeyDown)
			{
				auto code = record.Event.KeyEvent.wVirtualKeyCode;
				auto chr = record.Event.KeyEvent.uChar.AsciiChar;
				if (code == VK_TAB)
				{
					if (previousFocus != f)
					{
						previousFocus->resetFocus();
					}

					if (isList(f))
					{
						if (f->setLocalFocus()) {
							f->keyDown(code, chr, _graphics);
						}
						else
						{
							previousFocus->resetFocus();
							previousFocus = f;

							moveFocus(c, f);
						}						
					}				
					else
					{
						previousFocus->resetFocus();
						previousFocus = f;

						moveFocus(c, f);
						currentIndex++;
					}
					
				}
				else
					f->keyDown(code, chr, _graphics);

				redraw = true;

			}
			break;
		}
		case MOUSE_EVENT:
		{
			auto button = record.Event.MouseEvent.dwButtonState;
			auto coord = record.Event.MouseEvent.dwMousePosition;
			auto x = coord.X - c.getLeft();
			auto y = coord.Y - c.getTop();
			if (button == FROM_LEFT_1ST_BUTTON_PRESSED || button == RIGHTMOST_BUTTON_PRESSED)
			{
				_graphics.setCursorVisibility(true);
				c.mousePressed(x, y, button == FROM_LEFT_1ST_BUTTON_PRESSED, _graphics);
				redraw = true;
			}
			break;
		}
		default:
			break;
		}
	}
}

EventEngine::~EventEngine()
{
	SetConsoleMode(_console, _consoleMode);
}

void EventEngine::moveFocus(Control &main, Control *focused)
{
	vector<Control*> controls;
	if (isPanel(focused))
	{
		if (focused->setLocalFocus())
		{
			Control::setFocus(*focused->getCurrentFocus());
			return;
		}

		moveFocus(*focused, focused->getCurrentFocus());
	}

	else
	{
		main.getAllControls(&controls);
		findAndSetFocusedItemInPanel(controls, focused);
	}
}

void EventEngine::findAndSetFocusedItemInPanel(vector<Control*> controls,Control *focused)
{
	static int embededPanels = 0;
	vector<Control*> temp;
	auto it = focused;
	int index = 0;
	for (index; index < controls.size(); ++index)
	{
		if (isPanel(controls[index]))
		{
			controls[index]->getAllControls(&temp);
			++embededPanels;
			findAndSetFocusedItemInPanel(temp, focused);
		}
			
		if (controls[index] == it)
		{
			for (int i = index + 1; i < controls.size(); ++i)
			{
				if (controls[i]->canGetFocus()) 
				{
					if (isPanel(controls[i]))
					{
						Control::setFocus(*controls[i]->getCurrentFocus());
					}
					else
						Control::setFocus(*controls[i]);	
					return;
				}
			}
		}
	}
	if (embededPanels == 0)
		setFocusInMainPanel(controls);

	else
		--embededPanels;
}
void EventEngine::setFocusInMainPanel(vector<Control*> controls)
{
	for (int i = 0; i < controls.size(); ++i)
	{
		if (controls[i]->canGetFocus())
		{
			Control::setFocus(*controls[i]);
			return;
		}			
	}

	Control::setFocus(*controls[0]);
}

bool EventEngine::isList(Control* control)
{
	if (dynamic_cast<RadioBox*>(control) != NULL || dynamic_cast<CheckList*>(control) != NULL)
		return true;
	return false;
}

bool EventEngine::isPanel(Control* control)
{
	if (dynamic_cast<Panel*> (control) != NULL)
		return true;
	return false;
}


void EventEngine::setFirstFocus(Control& control)
{
	vector <Control*> items;
	control.getAllControls(&items);
	for (int i = 0; i < items.size(); ++i)
	{
		if (items[i]->canGetFocus())
		{
			Control::setFocus(*items[i]);
			return;
		}
	}
}