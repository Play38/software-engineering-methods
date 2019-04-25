#include <string>
#include <windows.h>

class checkbox
{
public:
  const short X;
  const short Y;
  const WORD color;
  const WORD background;
  bool isChecked;
  std::string value;

  checkbox(short X, short Y, std::string value);
  void toggle();
  void draw();
};
