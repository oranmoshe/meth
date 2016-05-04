#include "Component.h"

// Sets the cursor on given position
void COMPONENT::SetCursor(int x, int y){
	COORD c = { x, y };
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, c);
}