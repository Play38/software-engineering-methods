#pragma once
#include <vector>
#include "Graphics.h"

enum class BorderType				{ Single, Double, None };
enum class ForegroundColor	{ Red, Blue, Green, Purple, Yellow, White, Black };
enum class BackgroundColor	{ Red, Blue, Green, Purple, Yellow, White, Black };

class Control {

protected:
	int left, top, width, height;		
	bool showed;
	size_t layer = 0;
	static Control* focus;
	BorderType border = BorderType::None;
	Graphics graphics;
	Color foreground = Color::White, background = Color::Black;

public:
	Control()														{}
	~Control()													{}
	virtual void setValue(int)					{}
	inline void Show()									{ this->showed = true; }
	inline void Hide()									{ this->showed = false; }
	inline void setLeft(int left)				{ this->left = left; }
	inline void setTop(int top)					{ this->top = top; }
	inline void setLayer(size_t layer)	{ this->layer = layer; }
	inline int getLeft()								{ return this->left; }
	inline int getTop()									{ return this->top; }
	inline int getWidth()								{ return this->width; }
	inline int getHeight()							{ return this->height; }
	inline static Control* getFocus()		{ return focus; }
	inline bool getShowed()							{ return this->showed; }
	inline size_t getLayer()						{ return this->layer; }
	inline BorderType getBorder()				{ return this->border; }
	inline void SetBorder(BorderType border)				{ this->border = border; }
	inline virtual void setWidth(int width)					{ this->width = width; }
	inline virtual void SetBackground(Color color)	{ background = color; }
	virtual void getAllControls(vector <Control*>*) {}
	static void setFocus(Control&);
	void drawBorder(BorderType);
	void drawBackground();
	virtual void SetForeground(Color);
	virtual void draw(Graphics, int, int, size_t) = 0;
	virtual void mousePressed(int, int, DWORD) = 0;
	virtual void keyDown(int, char) = 0;
	virtual bool canGetFocus() = 0;
};