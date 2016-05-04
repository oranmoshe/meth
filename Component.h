//Component.h

#ifndef __COMPONENT_H_INCLUDED__   // if x.h hasn't been included yet...
#define __COMPONENT_H_INCLUDED__   //   #define this so the compiler knows it has been included

#include <windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;


class COMPONENT {
protected:
	int length;
	COORD position;
public:
	COMPONENT(int x, int y, int length){
		position.X = x;
		position.Y = y;
		this->length=length;
	}
	void SetCursor(int x, int y);
	virtual bool IsClicked(COORD cursor) = 0;
	virtual bool IsEditable() = 0;
	COORD GetPosition(){ return position; }
	virtual void Draw() = 0;
	virtual void Handle(INPUT_RECORD *inpt, int i) = 0;
	virtual void SetFocus(COORD *coord) = 0;
};

#endif 