#include "textbox.h"


int main(int argc, char const *argv[])
{
    auto handle = GetStdHandle(STD_INPUT_HANDLE);
    DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),fdwMode);
    TextBox tb(12, 3, 3, "Text");
    tb.draw();
    
    while (1)
    {
        INPUT_RECORD ir;
        DWORD count;

        ReadConsoleInput(handle, &ir, 1, &count);

        if (count)
        {
            if (ir.EventType == KEY_EVENT)
            {
                tb.handleKeyboardEvent(ir.Event.KeyEvent);
            }
            if(ir.EventType == MOUSE_EVENT){
                if(ir.Event.MouseEvent.dwButtonState==1)
                    tb.handleMouseEvent(ir.Event.MouseEvent);
            }
        }
    }

    

    return 0;
}
