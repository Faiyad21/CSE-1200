#ifndef MENU_H
#define MENU_H

int game_page = 0;


int menuX = 300, menuY = 200;
int menuWidth = 200, menuHeight = 200;
int buttonHeight = 60;
char* menuItems[] = { "START GAME", "OPTIONS", " EXIT" };
int selectedItem = -1;
//bool showMenu = true;

int obj_x = 250, obj_y = 150;
int objWidth = 100, objHeight = 100;

int normalColor[] = { 100, 100, 255 };
int hoverColor[] = { 150, 150, 255 };
int textColor[] = { 255, 255, 255 };





void menu(){


	if (game_page == 0){
	
			iShowBMP(0, 0, "img\\Sd.bmp");
			iSetColor(50, 50, 100);
			iFilledRectangle(menuX, menuY, menuWidth, menuHeight);
			for (int i = 0; i < 3; i++) {
				if (i == selectedItem) iSetColor(hoverColor[0], hoverColor[1], hoverColor[2]);
				else iSetColor(normalColor[0], normalColor[1], normalColor[2]);
				iFilledRectangle(menuX, menuY + menuHeight - (i + 1)*buttonHeight, menuWidth, buttonHeight);
				iSetColor(textColor[0], textColor[1], textColor[2]);
				iText(menuX + menuWidth / 2 - 30, menuY + menuHeight - (i + 1)*buttonHeight + 20, menuItems[i]);
			}
	}

}


// button part with capital B
void Button(){
	// This inner 'if' block is the part we are modifying
	if (selectedItem == 0) {
		// Action for the first button ("START GAME")
		game_page = 1;
	}
	else if (selectedItem == 1) {
		// Action for the second button ("OPTIONS")
		// This is now an empty block, ready for you to add code.
		// For example: game_page = 2; to go to an options screen.
	}
	else if (selectedItem == 2) {
		// Action for the third button ("EXIT")
		exit(0);
	}
}




void escape()
{
	if (game_page == 1)
	{
		if (isKeyPressed(GLUT_KEY_ESC))
		{
			game_page = 0;
		}
	}
}

























#endif
