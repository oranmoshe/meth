#include <windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include "Form.h"
#include "ComboBox.h"
using namespace std;

int main(void) {
	
	// Creation of form
	FORM * form = new FORM();

	// Creation of textboxes
	LABEL *lb1 = new LABEL(0, 0, "First Name:");
	TEXTBOX *tb2 = new TEXTBOX(0, 2, 20);
	LABEL *lb2 = new LABEL(0, 6, "Last Name:");
	TEXTBOX *tb1 = new TEXTBOX(0, 8, 15);
	vector<string> options;
	options.push_back(" ");
	options.push_back("Tel Aviv");
	options.push_back("------------------------------");
	options.push_back("Ramat Gan");
	options.push_back("------------------------------");
	options.push_back("Haifa");
	options.push_back("------------------------------");
	options.push_back("Jerusalem");
	options.push_back("------------------------------");
	options.push_back("Eilat");
	options.push_back("------------------------------");
	COMBOBOX *c= new COMBOBOX(0,15,options,30);

	// Relates components the form 
	form->Add((COMPONENT*)lb1);
	form->Add((COMPONENT*)lb2);
	form->Add((COMPONENT*)tb1);
	form->Add((COMPONENT*)tb2);
	form->Add((COMPONENT*)c);

	// Running
	form->Run();

}