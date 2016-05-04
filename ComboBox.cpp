#include "ComboBox.h"

COMBOBOX::COMBOBOX(int x, int y, vector<string> options, int width) :COMPONENT(x, y, width){
	this->options = options;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD tempPosition = position;
	this->position.X = x;
	this->position.Y = y;
	size = options.size();
	focus = false;
	SetConsoleCursorPosition(h, tempPosition);
	Draw();
}
void COMBOBOX::Draw(){

		CONSOLE_SCREEN_BUFFER_INFO cbi;
		GetConsoleScreenBufferInfo(h, &cbi);
		DWORD wAttr2 = NULL;
		SetConsoleTextAttribute(h, 0);

		setColor(10);
		SetConsoleCursorPosition(h, position);
		printf("\xC9");
		for (int i = 0; i < length; i++)
		{
		printf("\xCD");
		}
		printf("\xBB");
		COORD crd1 = position;
		crd1.Y += 1;
		SetConsoleCursorPosition(h, crd1);
		for (int i = 0; i < 1; i++)
		{
		printf("\xBA");
		}
		COORD crd2 = crd1;
		crd2.X += length ;
		SetConsoleCursorPosition(h, crd2);
		printf(">");
		printf("\xBA");
		crd1.Y += 1;
		SetConsoleCursorPosition(h, crd1);
		printf("\xC8");
		for (int i = 0; i < length; i++)
		{
		printf("\xCD");
		}
		printf("\xBC");
		COORD crd3 = position;
		crd3.X++; crd3.Y++;
		SetConsoleCursorPosition(h, crd3);
}
void COMBOBOX::Handle(INPUT_RECORD *inpt, int i){
	int x = 0, y = 0;
	switch (inpt[i].EventType)
	{
	case KEY_EVENT: // keyboard input 
	{
						KEY_EVENT_RECORD ker = inpt[i].Event.KeyEvent;
						if (ker.bKeyDown && this->focus){
							switch (ker.wVirtualKeyCode){
							case VK_UP:{
										   if (x <= position.X + length && focus == true && y <= position.Y + size + 1 &&
											   x >= position.X && y >= position.Y){
											   if (currentCursor == 1){
												   currentCursor = size;
												   COORD tempPos = position;
												   tempPos.Y += 1 + size;
												   tempPos.X++;
												   SetConsoleCursorPosition(h, tempPos);
											   }
											   else{
												   COORD temp = { x, y - 1 };
												   SetConsoleCursorPosition(h, temp);
												   currentCursor--;
											   }
										   }
										   else{
											   show();
										   }
										   break;
							}
							case VK_DOWN:{
											 if (x <= position.X + length && focus == true && y <= position.Y + size && x >= position.X
												 && y >= position.Y && currentCursor <= size)
											 {
												 COORD tempPosition = { x, y + 1 };
												 SetConsoleCursorPosition(h, tempPosition);
												 currentCursor++;
											 }
											 else{
												 show();
											 }
											 break;
							}
							case VK_BACK:{
											 if (currentCursor){
												 COORD tempPosition = position;
												 tempPosition.X++; tempPosition.Y++;
												 choice = options[currentCursor - 1];
												 hide();
												 SetConsoleCursorPosition(h, tempPosition);
												 printf("%s", choice);
												 Draw();
											 }
											 break;
							}
							default:
								break;
							}
						}
	}
		break;

	case MOUSE_EVENT: // mouse input 
	{						 
						  MOUSE_EVENT_RECORD mer = inpt[i].Event.MouseEvent;
						  if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED){
							  if (focus == false){
								  if (mer.dwMousePosition.X <= (position.X + length) && mer.dwMousePosition.X >= position.X){
									  if (mer.dwMousePosition.Y <= (position.Y + 1) && mer.dwMousePosition.Y >= position.Y){
										  show();
									  }
								  }
							  }
							  else{
								  if (mer.dwMousePosition.X <= (position.X + length - 1) && mer.dwMousePosition.X >= position.X
									  + 2 && mer.dwMousePosition.Y>position.Y + 1)
								  {
									  int selection = mer.dwMousePosition.Y - position.Y - 2;
									  currentCursor = selection;
									  COORD tempPosition = position;
									  tempPosition.X++; tempPosition.Y++;
									  choice = options[currentCursor];
									  hide();
									  SetConsoleCursorPosition(h, tempPosition);
									  cout << choice;
									  Draw();
								  }
								  else
								  {
									  hide();
									  COORD tempPosition = position;
									  tempPosition.X++; tempPosition.Y++;
									  SetConsoleCursorPosition(h, tempPosition);
									  cout << choice;
									  Draw();
								  }

							  }
						  }
	}
		break;

	case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 	
		break;

	case FOCUS_EVENT:  // disregard focus events 

	case MENU_EVENT:   // disregard menu events 
		break;

	default:
		break;
	}

}
void COMBOBOX::SetCursor(int x, int y){}
bool COMBOBOX::IsClicked(COORD cursor){ return true; }
bool COMBOBOX::IsEditable(){ return true; }
void COMBOBOX::SetFocus(COORD *coord){}

void COMBOBOX::hide(){
	SetConsoleCursorPosition(h, position);
	COORD tempPosition = position;
	int i = 0, j = 0;
	focus = false;
	while (i < size+3)
	{
		j = 0;
		while (j < length + 2)
		{
			printf(" ");
			j++;
			tempPosition.X++;
		}
		i++;
		tempPosition = position;
		tempPosition.Y += i;
		SetConsoleCursorPosition(h, tempPosition);
	}
}
void COMBOBOX::show(){
	focus = true;
	COORD tempPosition = position;
	tempPosition.Y += 3;
	MOUSE_EVENT_RECORD mer;
	SetConsoleCursorPosition(h, tempPosition);
	for (unsigned i = 1; i < options.size(); i++, tempPosition.Y++, SetConsoleCursorPosition(h, tempPosition)){
		SetCursor(tempPosition.X, tempPosition.Y);
		setColor(10);
		PrintChar('\xBA');
		for (int j = 0; j < options[i].length(); j++){
			PrintChar(options[i][j]);
		}
		int j = options[i].length();
		while (length - j>0){
			cout << " ";
			++j;
		}
		cout << '\xBA';
	}
	cout << '\xC8';
	for (int i = 0; i < length; i++){
		cout << '\xCD';
	}
	cout << '\xBC';
	COORD tempPosition2 = position;
	tempPosition2.X++;
	tempPosition2.Y += 1;
	currentCursor = 1;
	SetConsoleCursorPosition(h, tempPosition2);
}
// Prints the given char on the cursor position.
void COMBOBOX::PrintChar(char ch){
	SetCursor(cursor.X, cursor.Y);
	printf("%c", ch);
	this->cursor.X++;
}

void COMBOBOX::setColor(int ForgC)
{
	WORD wColor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

int COMBOBOX::getCurrentCursor(){
	return currentCursor;
}

