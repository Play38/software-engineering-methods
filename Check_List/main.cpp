#include "checklist.h"
#include <iostream>

HANDLE handle;
DWORD fdwSaveOldMode;
void ErrorExit(LPSTR);
COORD getCursorPosition();
void handleMouseEvent(INPUT_RECORD ir, HANDLE output, checklist *cb1, checklist *cb2, checklist *cb3);
void handleKeyboardEvent(INPUT_RECORD ir, HANDLE output, checklist *cb1, checklist *cb2, checklist *cb3);

int main(int argc, char const *argv[])
{
  DWORD cNumRead, fdwMode;
  INPUT_RECORD ir;
  DWORD count;
  handle = GetStdHandle(STD_INPUT_HANDLE);
  HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

  if (handle == INVALID_HANDLE_VALUE)
    ErrorExit("GetStdHandle");

  // Save the current input mode, to be restored on exit.
  if (!GetConsoleMode(handle, &fdwSaveOldMode))
    ErrorExit("GetConsoleMode");

  // Enable the window and mouse input events.
  fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
  SetConsoleMode(handle, fdwMode);

  checklist cb1(2, 2, "bread");
  checklist cb2(2, 3, "milk");
  checklist cb3(2, 4, "eggs");
  cb1.draw();
  cb2.draw();
  cb3.draw();
  SetConsoleCursorPosition(output, {2, 2});

  while (1)
  {
    if (!ReadConsoleInput(
            handle,  // input buffer handle
            &ir,     // buffer to read into
            1,       // size of read buffer
            &count)) // number of records read
      ErrorExit("ReadConsoleInput");

    if (count) //if there was input, check what type of input and handle it
    {
      if (ir.EventType == KEY_EVENT && ir.Event.KeyEvent.bKeyDown)
      {
        handleKeyboardEvent(ir, output, &cb1, &cb2, &cb3);
      }
      if (ir.EventType == MOUSE_EVENT && ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
      {
        handleMouseEvent(ir, output, &cb1, &cb2, &cb3);
      }
    }
  }
  SetConsoleMode(handle, fdwSaveOldMode);
  return 0;
}

void handleMouseEvent(INPUT_RECORD ir, HANDLE output, checklist *cb1, checklist *cb2, checklist *cb3)
{
  COORD cursorPos = ir.Event.MouseEvent.dwMousePosition;
  if (cursorPos.X == 2 && cursorPos.Y == 2)
    cb1->toggle();
  else if (cursorPos.X == 2 && cursorPos.Y == 3)
    cb2->toggle();
  else if (cursorPos.X == 2 && cursorPos.Y == 4)
    cb3->toggle();

  SetConsoleCursorPosition(output, cursorPos);
}

void handleKeyboardEvent(INPUT_RECORD ir, HANDLE output, checklist *cb1, checklist *cb2, checklist *cb3)
{
  COORD cursorPos = getCursorPosition();
  switch (ir.Event.KeyEvent.wVirtualKeyCode)
  {
    case VK_SPACE: // space key to check \ uncheck box
      if (cursorPos.X == 2 && cursorPos.Y == 2)
        cb1->toggle();
      if (cursorPos.X == 2 && cursorPos.Y == 3)
        cb2->toggle();
      if (cursorPos.X == 2 && cursorPos.Y == 4)
        cb3->toggle();
      break;

    case VK_DOWN: // down key to navigate through the list
      if (cursorPos.Y > 3 || cursorPos.Y < 2)
        SetConsoleCursorPosition(output, {2, 2});        
      else if (cursorPos.Y == 2)
        SetConsoleCursorPosition(output, {2, 3});
      else if (cursorPos.Y == 3)
        SetConsoleCursorPosition(output, {2, 4});

      break;

    case VK_UP: // up key to navigate through the list
      if (cursorPos.Y > 4 || cursorPos.Y < 3)
        SetConsoleCursorPosition(output, {2, 4});        
      else if (cursorPos.Y == 3)
        SetConsoleCursorPosition(output, {2, 2});
      else if (cursorPos.Y == 4)
        SetConsoleCursorPosition(output, {2, 3});

      break;
  }
}

void ErrorExit(LPSTR lpszMessage)
{
  fprintf(stderr, "%s\n", lpszMessage);
  // Restore input mode on exit.
  SetConsoleMode(handle, fdwSaveOldMode);
  ExitProcess(0);
}