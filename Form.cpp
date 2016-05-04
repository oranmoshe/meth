#include "Form.h"
// Add component to the form
FORM::FORM(){
}
void FORM::Add(COMPONENT* comp){
	comps.push_back(comp);
}
// Draw and setup the components
void FORM::Run(){
	// Prints Componnents.
	for (COMPONENT *n : comps) {
		n->Draw();
	}
	// Get the standard input handle. 
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");
	// Save the current input mode, to be restored on exit. 
	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ErrorExit("GetConsoleMode");
	// Enable the window and mouse input events. 
	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode");
	// Loop to read and handle the next input events. 
	while (true)
	{		
		if (!ReadConsoleInput(
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead)) // number of records read 
			ErrorExit("ReadConsoleInput");

		// Dispatch the events to the appropriate handler. 

		for (i = 0; i < cNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input 	
				// Iterate and print values of vector
				for (COMPONENT *n : comps) {
					n->Handle(irInBuf, i);
				}
				Handle(irInBuf, i); // asign form
				break;

			case MOUSE_EVENT: // mouse input 				
				for (COMPONENT*n : comps) {
					n->Handle(irInBuf, i);
				}
				Handle(irInBuf, i); // asign form
				break;

			case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
				break;

			case FOCUS_EVENT:  // disregard focus events 

			case MENU_EVENT:   // disregard menu events 
				break;

			default:
				ErrorExit("Unknown event type");
				break;
			}
		}
	}

	// Restore input mode on exit.
	SetConsoleMode(hStdin, fdwSaveOldMode);
}



bool FORM::NextEditableComponent(int start){
	int tempIndex = start;
	
	while (++tempIndex < this->comps.size()){
		if (this->comps.at(tempIndex)->IsEditable()){
			this->currentComponnent = tempIndex;
			return true;			
		}
		else if (this->comps.size()-1 == tempIndex){
			return false;
		}
	}
	return false;
}
// On error 
VOID FORM::ErrorExit(LPSTR lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);
	// Restore input mode on exit.
	SetConsoleMode(hStdin, fdwSaveOldMode);
	ExitProcess(0);
}

// Handle and events
void FORM::Handle(INPUT_RECORD *inpt, int i){
	switch (inpt[i].EventType)
	{
	case KEY_EVENT: // keyboard input 
	{
						KEY_EVENT_RECORD ker = inpt[i].Event.KeyEvent;
						switch (ker.wVirtualKeyCode){
						case VK_BACK:
							break;
						case VK_TAB:
							if (inpt[i].Event.KeyEvent.bKeyDown){
								// find next editable component
								if (!NextEditableComponent(this->currentComponnent)){
									NextEditableComponent(-1);
								}
								// cancel focus of all
								for (int i = 0; i < this->comps.size(); i++){
									this->comps[i]->SetFocus(NULL);
								}
								// set focus on current
								this->comps[currentComponnent]->SetFocus(&comps[this->currentComponnent]->GetPosition());
							}
							break;
						case VK_RIGHT:
						case VK_NUMPAD6:
							break;
						case VK_LEFT:
						case VK_NUMPAD4:
							break;
						case VK_RETURN:
							break;
						case VK_DELETE:
							break;
						default:
							break;
						}
	}
	}
}
