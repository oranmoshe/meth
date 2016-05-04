//TextBox.h

#ifndef __TEXTBOX_H_INCLUDED__   // if x.h hasn't been included yet...
#define __TEXTBOX_H_INCLUDED__   //   #define this so the compiler knows it has been included

#include "Component.h"

class TEXTBOX :COMPONENT {
	std::string value = "\0";
	int valPtr;
	bool focus;
	COORD cursor;
	COORD position;
public:
	TEXTBOX(int x, int y, int length); 
	void SetColors();
	void PrintChar(char ch);
	bool PutChar(char ch);
	void BackSpace();
	void Delete();
	void Clear();
	void MoveLeft();
	void MoveRight();
	void FocusOnText(COORD cursor);

	virtual void SetFocus(COORD *coord);
	virtual bool IsClicked(COORD cursor);
	virtual bool IsEditable();
	virtual void Draw();
	virtual void Handle(INPUT_RECORD *inpt, int i);
};

#endif 