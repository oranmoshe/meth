//Label.h

#ifndef __LABEL_H_INCLUDED__   // if x.h hasn't been included yet...
#define __LABEL_H_INCLUDED__   //   #define this so the compiler knows it has been included

#include "Component.h"

class LABEL :COMPONENT {
	std::string value = "\0";	
	COORD position;	
public:
	LABEL(int x, int y, string value);
	void SetColors();
	void SetCursor(int x, int y);
	virtual void Draw();
	virtual void Handle(INPUT_RECORD *inpt, int i);
	virtual bool IsClicked(COORD cursor);
	virtual bool IsEditable();
	virtual void SetFocus(COORD *coord);
};

#endif 