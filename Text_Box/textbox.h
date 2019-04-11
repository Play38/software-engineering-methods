#include <string>
#include <windows.h>

using namespace std;
class TextBox
{
    
        short width;
        short top;
        short left;
        short cpos;
        bool hasBorder;
        bool isEnabled;
        WORD color;
        WORD background;
        std::string value;
        string pval;
    public:
        TextBox(short width, short top, short left, std::string value);
        void draw();
        void drawBorder(COORD coord);
        void handleKeyboardEvent(KEY_EVENT_RECORD&);
        void handleMouseEvent(MOUSE_EVENT_RECORD&);

};