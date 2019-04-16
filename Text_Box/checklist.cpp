#include "checklist.h"
#include <iostream>
#include <algorithm>
Checklist::Checklist(short top, short left, std::string value) : 
    top(top), value(value), left(left), hasBorder(true),
    color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
    background(0),isEnabled(false),cpos(0) {}
/*
void Checklist::handleKeyboardEvent(KEY_EVENT_RECORD& event)
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
void Checklist::handleMouseEvent(MOUSE_EVENT_RECORD& event){
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
*/
void Checklist::drawBorder(COORD coord){
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
     std::cout << (char) 0xda;
    for (int i=0; i<width; i++)
        std::cout << (char) 0xc4;
    std::cout << (char) 0xbf; //making upper right corner

    SetConsoleCursorPosition(handle, {coord.X, coord.Y+1}); // reseting cursor to cetner left
    std::cout << (char) 0xb3; // making the left center collum
    
   // for (int i =0; i < width; i++)
     //   std::cout << (i >= value.length() ? ' ' : value[i]); // here guttman is printing the word
    
    SetConsoleCursorPosition(handle, { left + width + 1, top + 1 }); // restting cursor to center right
    std::cout << (char) 0xb3; // making the right ctner collum

    SetConsoleCursorPosition(handle, { left, top + 1 }); // setting the crusor to down area, and making the down part
    std::cout << (char) 0xc0;
    for (int i = 0; i < width; i++)
        std::cout << (char) 0xc4;
    std::cout << (char) 0xd9;
}

void Checklist::draw()
{
    COORD coord = { left, top };
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, coord);
    SetConsoleTextAttribute(handle, color | (background << 4));
    drawBorder(coord);
    SetConsoleCursorPosition(handle, { left + 1 + cpos, top + 1 });
}

