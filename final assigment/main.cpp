#include "Common/graphics.h"
#include "Common/eventEngine.h"
#include "Common/panel.h"
#include "Common/textBox.h"
#include "Common/checkList.h"
#include "Common/messageBox.h"
#include "Common/comboBox.h"
#include "Common/numericBox.h"
#include "Common/radioBox.h"

int main(int argc, char** argv)
{
	EventEngine e;

	Panel p(2, 0, 0, { 130,45 });

	Label mainPanelLabel(65, 1, "Main Panel");
	mainPanelLabel.setColor(Color::White, Color::Blue);
	p.Add(&mainPanelLabel);

	Label checkListLabel(10, 3, "CheckList");
	checkListLabel.setColor(Color::Cyan, Color::Purple);
	p.Add(&checkListLabel);

	CheckList cc(1, (short)4, (short)4, { 15,10 }, { "dog","cow","pig" });
	cc.setColor(Color::Orange, Color::Red);
	p.Add(&cc);

	Label radioBoxLabel(30, 3, "RadioBox");
	radioBoxLabel.setColor(Color::Cyan, Color::Purple);
	p.Add(&radioBoxLabel);

	RadioBox rc(1, (short)25, (short)4, { 15,10 }, { "TLV","JLM","NYC" });
	rc.setColor(Color::Purple, Color::Orange);
	p.Add(&rc);

	Label textBoxLabel(57, 3, "TextBox");
	textBoxLabel.setColor(Color::Blue, Color::Purple);
	p.Add(&textBoxLabel);

	TextBox t(1, 50, 4, { 20,5 });
	t.setColor(Color::Blue, Color::White);
	p.Add(&t);

	Label numericBoxLabel(53, 15, "NumericBox");
	numericBoxLabel.setColor(Color::Cyan, Color::White);
	p.Add(&numericBoxLabel);

	NumericBox n(1, 50, 16, { 15,3 }, 5);
	n.setColor(Color::White, Color::Blue);
	p.Add(&n);


	Label buttonsLabel(16, 17, "Buttons");
	p.Add(&buttonsLabel);

	Button btn1(1, 4, 20, { 8,2 }, "Land");
	btn1.setColor(Color::Red, Color::White);
	p.Add(&btn1);

	Button btn2(1, 15, 20, { 8,2 }, "Sea");
	btn2.setColor(Color::Orange, Color::Black);
	p.Add(&btn2);

	Button btn3(1, 26, 20, { 8,2 }, "Rocks");
	btn3.setColor(Color::White, Color::Green);
	p.Add(&btn3);


	Panel p2(1, 80, 3, { 48,40 });
	p2.setColor(Color::Purple , Color::Green);
	p.Add(&p2);

	Label seconderyPanelLabel(96, 4, "Second Panel");
	seconderyPanelLabel.setColor(Color::Cyan, Color::Blue);
	p2.Add(&seconderyPanelLabel);

	Label comboBoxLabel(84, 7, "ComboBox");
	comboBoxLabel.setColor(Color::White, Color::Black);
	p2.Add(&comboBoxLabel);

	ComboBox cb(1, 82, 8, { 10,2 }, { "Tree","Grass","Veg" });
	cb.setColor(Color::Cyan, Color::Purple);
	p2.Add(&cb);

	Label messageBoxLabel(92, 17, "MessageBox");
	messageBoxLabel.setColor(Color::Orange, Color::Green);
	p2.Add(&messageBoxLabel);

	Message_Box mb(1, 82, 18, { 30,8 }, "Heya, I'm a message box (:");
	mb.setColor(Color::White, Color::Blue);
	p2.Add(&mb);

	Label radioBoxLabel2(85, 29, "RadioBox");
	radioBoxLabel2.setColor(Color::Cyan, Color::Blue);
	p2.Add(&radioBoxLabel2);

	RadioBox rc2(1, (short)82, (short)30, { 15,10 }, { "Rachel","Domby","Bloom" });
	rc2.setColor(Color::Orange, Color::Blue);
	p2.Add(&rc2);

	e.run(p);

}