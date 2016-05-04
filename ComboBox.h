//ComboBox.h

#ifndef __COMBOBOX_H_INCLUDED__   // if x.h hasn't been included yet...
#define __COMBOBOX_H_INCLUDED__   //   #define this so the compiler knows it has been included

#include "Component.h"

class COMBOBOX :COMPONENT {
	bool focus;
	vector<string> options;
	std::string value = "\0";
	COORD cursor;
	COORD position;
	HANDLE h;
	string choice;
	int currentCursor;
	int size;
	
public:
	COMBOBOX(int x, int y, vector<string>, int width);
	~COMBOBOX(){};
	void Draw();
	void show();
	void COMBOBOX::PrintChar(char ch);
	bool COMBOBOX::PutChar(char ch);
	void hide();
	void Handle(INPUT_RECORD *inpt, int i);
	void SetCursor(int x, int y);
	bool IsClicked(COORD cursor);
	bool IsEditable();
    void SetFocus(COORD *coord);
	void MouseEvent(MOUSE_EVENT_RECORD event);
	void KeyEvent(KEY_EVENT_RECORD);
	void setColor(int ForgC);
	int getCurrentCursor();
};

#endif 