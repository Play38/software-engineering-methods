#include "textbox.h"
#include <iostream>
#include <algorithm>
TextBox::TextBox(short width, short top, short left, std::string value) : 
    width(width), top(top), value(value), left(left), hasBorder(true),
    color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
    background(0),isEnabled(false),cpos(0) {}

void TextBox::handleKeyboardEvent(KEY_EVENT_RECORD& event)
{
    if(!isEnabled) return;
    if (!event.bKeyDown) return;

    if (event.wVirtualKeyCode >= 0x30 && event.wVirtualKeyCode <= 0x5a)
    {
        pval=value;
        if(value.length() < width){
            value.insert(cpos,1,event.uChar.AsciiChar);
            cpos++;
            if(cpos>width-1)cpos=width-1;
            draw();
        }
    }

    if (event.wVirtualKeyCode == VK_LEFT || event.wVirtualKeyCode == VK_RIGHT)
    {
        int textWidth = value.length();
        CONSOLE_SCREEN_BUFFER_INFO info;
        auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(handle, &info);
        auto offset = info.dwCursorPosition.X - this->left - 1;

        if (offset > 0 && event.wVirtualKeyCode == VK_LEFT)
        {
            SetConsoleCursorPosition(handle,{info.dwCursorPosition.X - 1, info.dwCursorPosition.Y });
            if(cpos > 0)
                cpos--;
        }

        if (offset < textWidth && event.wVirtualKeyCode == VK_RIGHT)
        {
            SetConsoleCursorPosition(handle,{info.dwCursorPosition.X + 1, info.dwCursorPosition.Y });
            if(cpos < textWidth){
                cpos++;
                if(cpos>width-1) cpos=width-1;
            }
        }
    }

    if (event.wVirtualKeyCode == VK_BACK)
    {
        pval=value;
        if(value.length() > 0){
            value.pop_back();
            cpos--;
        }
        if(cpos < 0) cpos = 0;
        if(pval != value)draw();
    }
}
void TextBox::handleMouseEvent(MOUSE_EVENT_RECORD& event){
    COORD c= event.dwMousePosition;
    if(c.X >= left && c.X <= left+width+1 && c.Y >= top && c.Y <= top+3){
        isEnabled = true;
        auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(handle, {top,c.X});
        cpos=c.X-left;
        if(cpos > value.length()) cpos = value.length();
        draw();
    }
    else {
    if(isEnabled)  draw();    
        isEnabled = false;
    }
}

void TextBox::drawBorder(COORD coord){
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
     std::cout << (char) 0xda;
    for (int i=0; i<width; i++)
        std::cout << (char) 0xc4;
    std::cout << (char) 0xbf;

    SetConsoleCursorPosition(handle, {coord.X, coord.Y+1});
    std::cout << (char) 0xb3;
    
    for (int i =0; i < width; i++)
        std::cout << (i >= value.length() ? ' ' : value[i]);
    
    SetConsoleCursorPosition(handle, { left + width + 1, top + 1 });
    std::cout << (char) 0xb3;

    SetConsoleCursorPosition(handle, { left, top + 2 });
    std::cout << (char) 0xc0;
    for (int i = 0; i < width; i++)
        std::cout << (char) 0xc4;
    std::cout << (char) 0xd9;
}

void TextBox::draw()
{
    COORD coord = { left, top };
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, coord);
    SetConsoleTextAttribute(handle, color | (background << 4));
    drawBorder(coord);
    SetConsoleCursorPosition(handle, { left + 1 + cpos, top + 1 });
}

