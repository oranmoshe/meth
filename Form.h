//Form.h

#ifndef __FORM_H_INCLUDED__   // if x.h hasn't been included yet...

#define __FORM_H_INCLUDED__   //   #define this so the compiler knows it has been included

#include "TextBox.h"
#include "Label.h"

class FORM {
	HANDLE hStdin;
	DWORD fdwSaveOldMode;
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	char value[100];
	int valLength = 0;
	void FORM::ErrorExit(LPSTR lpszMessage);
	vector<COMPONENT*> comps;
	int currentComponnent = 0;
	bool NextEditableComponent(int start);

public:
	FORM();
	void Add(COMPONENT*);
	void Run();
	void Handle(INPUT_RECORD *inpt, int i);
};
#endif