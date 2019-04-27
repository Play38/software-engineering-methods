#include <string>
#include <windows.h>

class checklist
{
public:
  const short X;
  const short Y;
  const WORD color;
  const WORD background;
  bool isChecked;
  std::string value;

  checklist(short X, short Y, std::string value);
  void toggle();
  void draw();
};
