/*
 * UIFunctions.cpp
 *
 *  Created on: 15.03.2019
 *      Author: voyag
 */

#include "UIFunctions.h"

UI_Primitives draw;

UI_Functions::UI_Functions() {
	// TODO Auto-generated constructor stub

}

UI_Functions::~UI_Functions() {
	// TODO Auto-generated destructor stub
}

bool UI_Functions::Init(){
	draw.Init();
	draw.clearScreen();
	return true;
}

bool UI_Functions::FullUpdate(unsigned char mode){

}

bool UI_Functions::PartialUpdate(unsigned char area){

}

void UI_Functions::TestScreen(){
	draw.clearScreen();
	draw.SideButton(1, "test1", false);
	draw.SideButton(2, "test2", true);
	draw.SideButton(3, "test3", false);
	draw.SideButton(4, "test4", true);
	draw.SideButton(5, "test5", false);
}
