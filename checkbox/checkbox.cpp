#include "checkbox.h"
#include <iostream>
#include <algorithm>

checkbox::checkbox(short x, short y, std::string value)
    : X(x), Y(y), value(value), isChecked(false),
      color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
      background(0) {}

void checkbox::toggle()
{
  isChecked = !isChecked;
  draw();
}

COORD getCursorPosition()
{
  CONSOLE_SCREEN_BUFFER_INFO info;
  auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
  GetConsoleScreenBufferInfo(handle, &info);
  return info.dwCursorPosition;
}

void checkbox::draw()
{
  COORD originalCursorPos = getCursorPosition();
  COORD coord = {X, Y};
  auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(handle, coord);

  if (isChecked)
    std::cout << "X\t" + value << std::endl;
  else
    std::cout << "O\t" + value << std::endl;

  SetConsoleCursorPosition(handle, originalCursorPos);
}