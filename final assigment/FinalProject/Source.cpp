#define _WIN32_WINNT 0x0500
#include "../Common/Graphics.h"
#include "../Common/EventEngine.h"
#include "../Common/Panel.h"
#include "../Common/TextBox.h"
#include "../Common/CheckList.h"
#include "../Common/MessageBox.h"
#include "../Common/ComboBox.h"
#include "../Common/NumericBox.h"
#include "../Common/RadioBox.h"

int main(int argc, char** argv)
{
    system("mode 101,31");
    HWND consoleWindow = GetConsoleWindow();
    SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	EventEngine e;

	Panel p(2, 0, 0, { 100,30 });

	Label radioBoxLabel(8, 3, "RadioBox");
	radioBoxLabel.setColor(Color::Cyan, Color::Purple);
	p.Add(&radioBoxLabel);

	RadioBox rc(1, (short)4, (short)4, { 15,10 }, { "TLV","JLM","NYC" });
	rc.setColor(Color::Purple, Color::Orange);
	p.Add(&rc);


    Label checkListLabel(29, 3, "CheckList");
    checkListLabel.setColor(Color::Cyan, Color::Purple);
    p.Add(&checkListLabel);

    CheckList cc(1, (short)25, (short)4, { 15,10 }, { "dog","cow","pig" });
    cc.setColor(Color::Orange, Color::Red);
    p.Add(&cc);

	Label textBoxLabel(57, 3, "TextBox");
	textBoxLabel.setColor(Color::Blue, Color::Purple);
	p.Add(&textBoxLabel);

	TextBox t(1, 50, 4, { 20,5 });
	t.setColor(Color::Blue, Color::White);
	p.Add(&t);


    Label comboBoxLabel(83, 3, "ComboBox");
    comboBoxLabel.setColor(Color::White, Color::Black);
    p.Add(&comboBoxLabel);

    ComboBox cb(1, 82, 4, { 7,2 }, { "Tree","Grass","Veg" });
    cb.setColor(Color::Cyan, Color::Purple);
    p.Add(&cb);

    Label buttonsLabel(19, 17, "Buttons");
    p.Add(&buttonsLabel);

    Button btn1(1, 7, 20, { 8,2 }, "Land");
    btn1.setColor(Color::Red, Color::White);
    p.Add(&btn1);

    Button btn2(1, 18, 20, { 8,2 }, "Sea");
    btn2.setColor(Color::Orange, Color::Black);
    p.Add(&btn2);

    Button btn3(1, 29, 20, { 8,2 }, "Rocks");
    btn3.setColor(Color::White, Color::Green);
    p.Add(&btn3);

    Label messageBoxLabel(56, 15, "MessageBox");
	messageBoxLabel.setColor(Color::Orange, Color::Green);
	p.Add(&messageBoxLabel);

	Message_Box mb(1, 50, 16, { 20,8 }, " Will you marry me?");
	mb.setColor(Color::White, Color::Blue);
	p.Add(&mb);

    Label numericBoxLabel(83, 17, "NumericBox");
    numericBoxLabel.setColor(Color::Cyan, Color::White);
    p.Add(&numericBoxLabel);

    NumericBox n(1, 80, 18, { 15,3 }, 3);
    n.setColor(Color::White, Color::Blue);
    p.Add(&n);

	e.run(p);

}