#include <iostream>
#include <string>
#include "TextBox.h"
using namespace std;

//constructor
TextBox::TextBox(int width)
{
    this->width = width;
    this->height = 1;
    this->border = BorderType::Single;
    this->showed = true;
}

//draw textbox
void TextBox::draw(Graphics g, int x, int y, size_t z)
{
    g.setBackground(this->background);
    g.setForeground(this->foreground);
    g.write(x, y, this->GetValue());
    g.setForeground(Color::White);
    g.setBackground(Color::Black);
}

//handle mouse press
void TextBox::mousePressed(int x, int y, DWORD btn)
{
    this->keyDown(1, 'v');
};

//handle key press
void TextBox::keyDown(int keyCode, char c)
{
    int position = this->getLeft() + this->GetValue().size();

    if (this->GetValue().empty())
        graphics.moveTo(position, this->getTop());
    else
        graphics.moveTo(position - 1, this->getTop());

    this->graphics.setCursorVisibility(true);
    string input = this->GetValue();
    int _char, i = 0;

    while (1)
    {
        _char = getchar();
        position++;

        if (position > this->getLeft() + this->getWidth() && _char != VK_BACK)
            break;

        input.push_back(_char);
        putchar(_char);

        if (_char == VK_BACK)
        {
            input.pop_back();
            if (!input.empty())
            {
                input.pop_back();
                position -= 2;
                graphics.moveTo(position, this->getTop());
                putchar(' ');
                graphics.moveTo(position, this->getTop());
            }
            else
                position -= 0;
        }

        if (_char == VK_TAB)
        {
            input.pop_back();
            break;
        }
    }

    this->SetValue(input);
}
