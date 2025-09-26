#include "iGraphics.h"
#include "menu.hpp"
#include "movement.hpp"
#include "trigger.h"
#include "boundary.hpp"
#include  "mud.hpp"



//////---------------------------------------for game over 

bool game1Over = false;
bool player1Won = false;
int game1Timer = 0;

//----------------------------------------------------------------------game state 2




//----------------------------------------------------------------------
// Game State 2: First Shooting Game Implementation
//----------------------------------------------------------------------

// Game 1 variables
int fightAreaX = 250, fightAreaY = 250, fightAreaWidth = 500, fightAreaHeight = 500;
int enemy1X = 500, enemy1Y = 400;
int enemy1DX = 5;
int enemy1Health = 200;
int enemy1MaxHealth = 200;
char enemy1Name[] = "Argse";
char enemy1Image[] = "img\\mudy3.bmp";

int enemyBullet1X[100], enemyBullet1Y[100], enemyBullet1Show[100];
char enemyBullet1Image[] = "img\\rock8.bmp";
int enemyBullet1Cooldown = 0;
const int ENEMY1_COOLDOWN_TIME = 70;

double char1X = 500, char1Y = 100;
int char1Width = 48, char1Height = 48;
int char1Health = 100;
int char1MaxHealth = 100;
char char1Image[] = "img\\l11.bmp";

int bullet1X[100], bullet1Y[100], bullet1Show[100];
char bullet1Image[] = "img\\fire1.bmp";
int bullet1Cooldown = 0;
const int COOLDOWN_TIME_1 = 5;

int score1 = 0;

void background1(){
	iShowBMP(0, 0, "img\\mud1.bmp");
}

void evre1(){
	// Draw enemy
	if (!game1Over) {
		// Normal game drawing
		background1();
		iShowBMP2(enemy1X - 40, enemy1Y - 18, enemy1Image, 0);
		iShowBMP2(char1X, char1Y, char1Image, 0);

		// Draw bullets
		for (int i = 0; i < 100; i++) {
			if (bullet1Show[i]) iShowBMP2(bullet1X[i], bullet1Y[i], bullet1Image, 0);
			if (enemyBullet1Show[i]) iShowBMP2(enemyBullet1X[i], enemyBullet1Y[i], enemyBullet1Image, 0);
		}
	

	// Health bars and UI for game 1
	int healthBarX = 100;
	int playerHealthBarWidth = 150;
	int enemyHealthBarWidth = 300;
	int healthBarHeight = 20;

	// Enemy health bar
	iSetColor(255, 255, 255);
	iText(healthBarX, 650, enemy1Name, GLUT_BITMAP_9_BY_15);
	iSetColor(255, 0, 0);
	iFilledRectangle(healthBarX, 630, enemyHealthBarWidth, healthBarHeight);
	iSetColor(0, 255, 0);
	iFilledRectangle(healthBarX, 630, (enemyHealthBarWidth * enemy1Health) / enemy1MaxHealth, healthBarHeight);
	iSetColor(255, 255, 255);
	iRectangle(healthBarX, 630, enemyHealthBarWidth, healthBarHeight);

	// Player health bar
	iSetColor(255, 255, 255);
	iText(healthBarX, 250, "Player", GLUT_BITMAP_9_BY_15);
	iSetColor(255, 0, 0);
	iFilledRectangle(healthBarX, 100, playerHealthBarWidth, healthBarHeight);
	iSetColor(0, 255, 0);
	iFilledRectangle(healthBarX, 100, (playerHealthBarWidth * char1Health) / char1MaxHealth, healthBarHeight);
	iSetColor(255, 255, 255);
	iRectangle(healthBarX, 100, playerHealthBarWidth, healthBarHeight);

	// Score and instructions
	char scoreStr[50];
	sprintf_s(scoreStr, sizeof(scoreStr), "Score: %d", score1);
	iText(10, 50, scoreStr, GLUT_BITMAP_9_BY_15);
	iText(10, 10, "A/D to move, F to fire", GLUT_BITMAP_9_BY_15);


}
	else {
		// Game over screen
		background1();
		iSetColor(255, 255, 255);

		if (player1Won) {
			iText(350, 400, "VICTORY! You defeated Argse!", GLUT_BITMAP_HELVETICA_18);
			
		}
		else {
			iText(350, 400, "DEFEAT! Argse was too strong!", GLUT_BITMAP_HELVETICA_18);
			iText(350, 350, "Better luck next time!", GLUT_BITMAP_HELVETICA_18);
		}

	
	}
}



void moveEnemy1() {
	if (game1Over) return;
	enemy1X += enemy1DX;
	if (enemy1X > fightAreaX + fightAreaWidth - 40 || enemy1X < fightAreaX + 40) {
		enemy1DX = -enemy1DX;
	}
}

void enemyFire1() {
	if (game1Over) return;
	if (enemyBullet1Cooldown > 0) {
		enemyBullet1Cooldown--;
	}
	else {
		for (int i = 0; i < 100; i++) {
			if (!enemyBullet1Show[i]) {
				enemyBullet1X[i] = enemy1X;
				enemyBullet1Y[i] = enemy1Y - 18;
				enemyBullet1Show[i] = 1;
				enemyBullet1Cooldown = ENEMY1_COOLDOWN_TIME;
				break;
			}
		}
	}
}

void moveBullets1() {
	if (game1Over) return;
	if (bullet1Cooldown > 0) bullet1Cooldown--;
	if (enemyBullet1Cooldown > 0) enemyBullet1Cooldown--;

	// Character bullets
	for (int i = 0; i < 100; i++) {
		if (bullet1Show[i]) {
			bullet1Y[i] += 8;

			// FIXED COLLISION DETECTION - More precise hitbox
			if (bullet1Show[i] &&
				bullet1X[i] + 5 >= enemy1X - 40 &&  // Bullet right edge vs enemy left edge
				bullet1X[i] <= enemy1X + 40 &&       // Bullet left edge vs enemy right edge
				bullet1Y[i] + 5 >= enemy1Y - 18 &&   // Bullet bottom vs enemy top
				bullet1Y[i] <= enemy1Y + 18) {       // Bullet top vs enemy bottom

				bullet1Show[i] = 0;
				enemy1Health -= 10;
				score1 += 10;
				if (enemy1Health <= 0) enemy1Health = 0;
				printf("HIT! Enemy Health: %d\n", enemy1Health); // Debug
			}

			if (bullet1Y[i] > 720) bullet1Show[i] = 0;
		}
	}

	// Enemy bullets - Also check this collision
	for (int i = 0; i < 100; i++) {
		if (enemyBullet1Show[i]) {
			enemyBullet1Y[i] -= 6;

			// FIXED PLAYER COLLISION DETECTION
			if (enemyBullet1Show[i] &&
				enemyBullet1X[i] + 5 >= char1X &&
				enemyBullet1X[i] <= char1X + char1Width &&
				enemyBullet1Y[i] + 5 >= char1Y &&
				enemyBullet1Y[i] <= char1Y + char1Height) {

				enemyBullet1Show[i] = 0;
				char1Health -= 10;
				if (char1Health <= 0) char1Health = 0;
				printf("PLAYER HIT! Health: %d\n", char1Health); // Debug
			}

			if (enemyBullet1Y[i] < 0) enemyBullet1Show[i] = 0;
		}
	}

	// Win/lose conditions
	if (enemy1Health <= 0 && !game1Over) {
		game1Over = true;
		player1Won = true;
		game1Timer = 0;
		printf("GAME OVER - PLAYER WON!\n");
	}

	if (char1Health <= 0 && !game1Over) {
		game1Over = true;
		player1Won = false;
		game1Timer = 0;
		printf("GAME OVER - PLAYER LOST!\n");
	}
}

void characterMovement1(){
	if (game1Over) return;
	if (isKeyPressed('a') || isKeyPressed('A') || isSpecialKeyPressed(GLUT_KEY_LEFT)) {
		char1X -= 5;
		if (char1X < fightAreaX) char1X = fightAreaX;
	}
	if (isKeyPressed('d') || isKeyPressed('D') || isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
		char1X += 5;
		if (char1X > fightAreaX + fightAreaWidth - char1Width) char1X = fightAreaX + fightAreaWidth - char1Width;
	}
	if ((isKeyPressed('f') || isKeyPressed('F')) && bullet1Cooldown == 0) {
		for (int i = 0; i < 100; i++) {
			if (!bullet1Show[i]) {
				bullet1X[i] = char1X + char1Width / 2 - 2;
				bullet1Y[i] = char1Y + char1Height;
				bullet1Show[i] = 1;
				bullet1Cooldown = COOLDOWN_TIME_1;
				break;
			}
		}
	}
}

void initShootingGame1() {
	enemy1Health = enemy1MaxHealth;
	char1Health = char1MaxHealth;
	score1 = 0;
	enemy1X = 500; enemy1Y = 400;
	char1X = 500; char1Y = 100;

	for (int i = 0; i < 100; i++) {
		bullet1Show[i] = 0;
		enemyBullet1Show[i] = 0;
	}
}

//----------------------------------------------------------------------
// Game State 3: Second Shooting Game Implementation
//----------------------------------------------------------------------
 /*int enemy2X, enemy2Y, enemy2DX, enemy2Health, enemy2MaxHealth;
 char enemy2Name[], enemy2Image[];

 int enemyBullet2X[100], enemyBullet2Y[100], enemyBullet2Show[100];
char enemyBullet2Image[];
int enemyBullet2Cooldown;
const int ENEMY2_COOLDOWN_TIME;

double char2X, char2Y;
int char2Width, char2Height, char2Health, char2MaxHealth;
char char2Image[];

extern int bullet2X[100], bullet2Y[100], bullet2Show[100];
extern char bullet2Image[];
extern int bullet2Cooldown;
extern const int COOLDOWN_TIME_2;

extern int score2;*/



bool game2Over = false;
bool player2Won = false;
int game2Timer = 0;

// Game 2 variables
int enemy2X = 400, enemy2Y = 500;
int enemy2DX = 3;
int enemy2Health = 300;
int enemy2MaxHealth = 300;
char enemy2Name[] = "Boss 2";
char enemy2Image[] = "img\\boss2.bmp";

int enemyBullet2X[100], enemyBullet2Y[100], enemyBullet2Show[100];
char enemyBullet2Image[] = "img\\fire.bmp";
int enemyBullet2Cooldown = 0;
const int ENEMY2_COOLDOWN_TIME = 90;

double char2X = 400, char2Y = 100;
int char2Width = 48, char2Height = 48;
int char2Health = 120;
int char2MaxHealth = 120;
char char2Image[] = "img\\hero.bmp";

int bullet2X[100], bullet2Y[100], bullet2Show[100];
char bullet2Image[] = "img\\bullet.bmp";
int bullet2Cooldown = 0;
const int COOLDOWN_TIME_2 = 20;

int score2 = 0;

void background2(){
	iShowBMP(0, 0, "img\\background2.bmp");
}

void evre2(){
	if (!game2Over) {
		// Similar to evre1() but with game 2 variables
		iShowBMP2(enemy2X - 40, enemy2Y - 18, enemy2Image, 0);
		iShowBMP2(char2X, char2Y, char2Image, 0);

		for (int i = 0; i < 100; i++) {
			if (bullet2Show[i]) iShowBMP2(bullet2X[i], bullet2Y[i], bullet2Image, 0);
			if (enemyBullet2Show[i]) iShowBMP2(enemyBullet2X[i], enemyBullet2Y[i], enemyBullet2Image, 0);
		}

		// Health bars for game 2 (different positions)
		int healthBarX = 600;
		int healthBarHeight = 20;

		iSetColor(255, 255, 255);
		iText(healthBarX, 510, enemy2Name, GLUT_BITMAP_9_BY_15);
		iSetColor(255, 0, 0);
		iFilledRectangle(healthBarX, 480, 300, healthBarHeight);
		iSetColor(0, 255, 0);
		iFilledRectangle(healthBarX, 480, (300 * enemy2Health) / enemy2MaxHealth, healthBarHeight);

		iSetColor(255, 255, 255);
		iText(healthBarX, 210, "Player", GLUT_BITMAP_9_BY_15);
		iSetColor(255, 0, 0);
		iFilledRectangle(healthBarX, 100, 150, healthBarHeight);
		iSetColor(0, 255, 0);
		iFilledRectangle(healthBarX, 180, (150 * char2Health) / char2MaxHealth, healthBarHeight);

		char scoreStr[50];
		sprintf_s(scoreStr, sizeof(scoreStr), "Score: %d", score2);
		iText(10, 50, scoreStr, GLUT_BITMAP_9_BY_15);
	}
	else {
		// Game over screen for game 2
		background2();
		iSetColor(255, 255, 255);

		if (player2Won) {
			iText(350, 400, "VICTORY! You defeated Boss 2!", GLUT_BITMAP_HELVETICA_18);
			
		}
		else {
			iText(350, 400, "DEFEAT! Boss 2 was victorious!", GLUT_BITMAP_HELVETICA_18);
			iText(350, 350, "Try again!", GLUT_BITMAP_HELVETICA_18);
		}

		
	}
}

void moveEnemy2() {
	if (game2Over) return;
	enemy2X += enemy2DX;
	if (enemy2X > fightAreaX + fightAreaWidth - 40 || enemy2X < fightAreaX + 40) {
		enemy2DX = -enemy2DX;
	}
}

void enemyFire2() {
	if (game2Over) return;
	if (enemyBullet2Cooldown > 0) {
		enemyBullet2Cooldown--;
	}
	else {
		for (int i = 0; i < 100; i++) {
			if (!enemyBullet2Show[i]) {
				enemyBullet2X[i] = enemy2X;
				enemyBullet2Y[i] = enemy2Y - 18;
				enemyBullet2Show[i] = 1;
				enemyBullet2Cooldown = ENEMY2_COOLDOWN_TIME;
				break;
			}
		}
	}
}

void moveBullets2() {
	if (game2Over) return;
	if (bullet2Cooldown > 0) bullet2Cooldown--;
	if (enemyBullet2Cooldown > 0) enemyBullet2Cooldown--;

	for (int i = 0; i < 100; i++) {
		if (bullet2Show[i]) {
			bullet2Y[i] += 20; // Faster bullets in game 2
			if (bullet2Show[i] && bullet2X[i] >= enemy2X - 40 && bullet2X[i] <= enemy2X + 40 &&
				bullet2Y[i] >= enemy2Y - 18 && bullet2Y[i] <= enemy2Y + 18) {
				bullet2Show[i] = 0;
				enemy2Health -= 15; // More damage in game 2
				score2 += 15;
				if (enemy2Health <= 0) enemy2Health = 0;
			}
			if (bullet2Y[i] > 720) bullet2Show[i] = 0;
		}

		if (enemyBullet2Show[i]) {
			enemyBullet2Y[i] -= 8; // Faster enemy bullets
			if (enemyBullet2Show[i] && enemyBullet2X[i] >= char2X && enemyBullet2X[i] <= char2X + char2Width &&
				enemyBullet2Y[i] >= char2Y && enemyBullet2Y[i] <= char2Y + char2Height) {
				enemyBullet2Show[i] = 0;
				char2Health -= 15; // More damage
				if (char2Health <= 0) char2Health = 0;
			}
			if (enemyBullet2Y[i] < 0) enemyBullet2Show[i] = 0;
		}
	}
	if (enemy2Health <= 0 && !game2Over) {
		game2Over = true;
		player2Won = true;
		game2Timer = 0;
	}

	if (char2Health <= 0 && !game2Over) {
		game2Over = true;
		player2Won = false;
		game2Timer = 0;
	}
}



void characterMovement2(){
	if (game2Over) return;
	if (isKeyPressed('a') || isKeyPressed('A') || isSpecialKeyPressed(GLUT_KEY_LEFT)) {
		char2X -= 6; // Faster movement
		if (char2X < fightAreaX) char2X = fightAreaX;
	}
	if (isKeyPressed('d') || isKeyPressed('D') || isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
		char2X += 6;
		if (char2X > fightAreaX + fightAreaWidth - char2Width) char2X = fightAreaX + fightAreaWidth - char2Width;
	}
	if ((isKeyPressed('f') || isKeyPressed('F')) && bullet2Cooldown == 0) {
		for (int i = 0; i < 100; i++) {
			if (!bullet2Show[i]) {
				bullet2X[i] = char2X + char2Width / 2 - 2;
				bullet2Y[i] = char2Y + char2Height;
				bullet2Show[i] = 1;
				bullet2Cooldown = COOLDOWN_TIME_2;
				break;
			}
		}
	}
}

void initShootingGame2() {
	enemy2Health = enemy2MaxHealth;
	char2Health = char2MaxHealth;
	score2 = 0;
	enemy2X = 400; enemy2Y = 500;
	char2X = 400; char2Y = 100;

	for (int i = 0; i < 100; i++) {
		bullet2Show[i] = 0;
		enemyBullet2Show[i] = 0;
	}
}



bool checkCollision(double nextX, double nextY, int charWidth, int charHeight);

// maps-----------------------------------------------------------------------------------
const int NUM_MAPS = 5;
char mapImages[NUM_MAPS][20] = { "img\\broom1.bmp", "img\\lroom1.bmp", "img\\b1.bmp","img\\maze.bmp"  ,"img\\b3.bmp" };
int currentMapIndex = 0;



struct Boundary {
	int x, y;
	int width, height;
};

// Map 1 obstacles
Boundary map1Obstacles[] = {
	{ 280, 220, 10, 400 },
	//{ 600, 100, 120, 150 },
	{ 280, 440, 520, 10 },
	{ 690, 210, 12, 450 },
	{ 200, 200, 520, 15 }
};
int numMap1Obstacles = 4;


// Map 2 obstacles
Boundary map2Obstacles[] = {
	{ 140, 113, 5, 500 },
	{ 140, 113, 500, 5 }, 
	{ 680, 113, 5, 500 },
	{ 140, 532, 500, 5 },
	
};
int numMap2Obstacles = 4;


// Map 3 obstacles
Boundary map3Obstacles[] = {
	{ 0, 600, 900, 600 },
	{ 500, 300, 200, 120 },
	{ 0, 200, 93, 182 },
	{ 270, 0, 400, 180 },
	{ 678, 280, 200, 500 },
	{ 112, 290, 100, 100 },
	{ 265, 282, 120, 110 },
	{ 315, 451, 120, 120 },
	{ 172, 460, 120, 120 },
	{ 172, 460, 50, 110 },
	{ 0, 0, 170, 170 }
};
int numMap3Obstacles = 11;

// Map 4 obstacles
Boundary map4Obstacles[] = {
	{ 200, 150, 100, 100 },
	{ 700, 200, 150, 200 },
	{ 400, 500, 120, 80 },
	{ 0, 0, 388, 720 },
	{ 513, 0, 900, 720 }
};
int numMap4Obstacles = 4;
//-------------------------------------------------------------------------------------------------OBSDONE 


//npc--------------------------------------------------------------------------------------------------------------------------NPCCC
/*struct NPC {
	double x, y;
	int width, height;
	int direction;
	int stepCounter;
};
NPC npc = { 400, 300, 48, 48, 0, 0 };
char npcSprite[4][20] = { "img\\u1.bmp", "img\\r1.bmp", "img\\d1.bmp", "img\\l1.bmp" };

void updateNPC() {
	int speed = 2;
	double nextX = npc.x, nextY = npc.y;

	if (npc.direction == 0) nextY += speed;
	else if (npc.direction == 1) nextX += speed;
	else if (npc.direction == 2) nextY -= speed;
	else if (npc.direction == 3) nextX -= speed;

	if (!checkCollision(nextX, nextY, npc.width, npc.height) &&
		nextX >= 0 && nextX + npc.width <= 1000 &&
		nextY >= 0 && nextY + npc.height <= 720) {
		npc.x = nextX;
		npc.y = nextY;
	}
	else {
		npc.direction = rand() % 4;
		npc.stepCounter = 0;
	}

	npc.stepCounter++;
	if (npc.stepCounter > 200) {
		npc.direction = rand() % 4;
		npc.stepCounter = 0;
	}
}


	int stillnpc;*/
//---------------------------------------------------------------------------------------------------NPS DONE





	bool checkCollision(double nextX, double nextY, int charWidth, int charHeight) {
		Boundary* activeObstacles = NULL;
		int numObstacles = 0;

		if (currentMapIndex == 0) {
			activeObstacles = map1Obstacles;
			numObstacles = numMap1Obstacles;
		}
		else if (currentMapIndex == 1) {
			activeObstacles = map2Obstacles;
			numObstacles = numMap2Obstacles;
		}
		else if (currentMapIndex == 2) {  // Map 3
			activeObstacles = map3Obstacles;
			numObstacles = numMap3Obstacles;
		}
		else if (currentMapIndex == 3) {  // Map 4
			activeObstacles = map4Obstacles;
			numObstacles = numMap4Obstacles;
		}
		else {
			// Fallback for any unexpected map index
			activeObstacles = map1Obstacles;
			numObstacles = numMap1Obstacles;
		}

		for (int i = 0; i < numObstacles; i++) {
			Boundary b = activeObstacles[i];
			if (nextX < b.x + b.width &&
				nextX + charWidth > b.x &&
				nextY < b.y + b.height &&
				nextY + charHeight > b.y) {
				return true;
			}
		}
		return false;
	}
	void drawObstacles() {
		Boundary* activeObstacles = NULL;
		int numObstacles = 0;

		if (currentMapIndex == 0) {
			activeObstacles = map1Obstacles;
			numObstacles = numMap1Obstacles;
		}
		else if (currentMapIndex == 1) {
			activeObstacles = map2Obstacles;
			numObstacles = numMap2Obstacles;
		}
		else if (currentMapIndex == 2) {  // Map 3
			activeObstacles = map3Obstacles;
			numObstacles = numMap3Obstacles;
		}
		else if (currentMapIndex == 3) {  // Map 4
			activeObstacles = map4Obstacles;
			numObstacles = numMap4Obstacles;
		}
		else {
			// Fallback for any unexpected map index
			activeObstacles = map1Obstacles;
			numObstacles = numMap1Obstacles;
		}

		for (int i = 0; i < numObstacles; i++) {
			iSetColor(255, 0, 0);
			iRectangle(activeObstacles[i].x, activeObstacles[i].y,
				activeObstacles[i].width, activeObstacles[i].height);
		}
	}
//  Draw Triggers (blue boxes for debug)
	void drawTriggers() {
		Trigger* activeTriggers;
		int numTriggers;

		if (currentMapIndex == 0) {
			activeTriggers = map1Triggers;
			numTriggers = numMap1Triggers;
		}
		else if (currentMapIndex == 1) {
			activeTriggers = map2Triggers;
			numTriggers = numMap2Triggers;
		}
		else if (currentMapIndex == 2) {  // Map 3
			activeTriggers = map3Triggers;
			numTriggers = numMap3Triggers;
		}
		else if (currentMapIndex == 3) {  // Map 4
			activeTriggers = map4Triggers;
			numTriggers = numMap4Triggers;
		}
		else {
			return; // No triggers for unexpected maps
		}

		for (int i = 0; i < numTriggers; i++) {
			iSetColor(0, 0, 255);
			iRectangle(activeTriggers[i].x, activeTriggers[i].y,
				activeTriggers[i].width, activeTriggers[i].height);
		}
	}

//  Check triggers
	void checkTriggers() {
		Trigger* activeTriggers;
		int numTriggers;

		if (currentMapIndex == 0) {
			activeTriggers = map1Triggers;
			numTriggers = numMap1Triggers;
		}
		else if (currentMapIndex == 1) {
			activeTriggers = map2Triggers;
			numTriggers = numMap2Triggers;
		}
		else if (currentMapIndex == 2) {
			activeTriggers = map3Triggers;
			numTriggers = numMap3Triggers;
		}
		else if (currentMapIndex == 3) {
			activeTriggers = map4Triggers;
			numTriggers = numMap4Triggers;
		}
		else {
			return;
		}

		for (int i = 0; i < numTriggers; i++) {
			Trigger t = activeTriggers[i];
			if (charX < t.x + t.width && charX + 48 > t.x &&
				charY < t.y + t.height && charY + 48 > t.y) {

				if (t.targetMap != -1) {
					currentMapIndex = t.targetMap;
					charX = t.targetX;
					charY = t.targetY;
				}
				if (t.targetGameState != -1) {
					game_page = t.targetGameState;

					// Initialize the appropriate shooting game
					if (game_page == 2) {
						initShootingGame1();
					}
					else if (game_page == 3) {
						initShootingGame2();
					}
				}
			}
		}
	}
	



// functions
void movementDraw();
void movementKey();
void iDraw();
void iMouseMove(int mx, int my);
void iPassiveMouseMove(int mx, int my);
void iMouse(int button, int state, int mx, int my);
void iKeyboard(unsigned char key);
void iSpecialKeyboard(unsigned char key);
void fixedUpdate();
bool checkCollision(double nextX, double nextY, int charWidth, int charHeight);

void movementDraw() {
	if (!idlePosition) {
		if (char_x_direction == 1) iShowBMP2(charX, charY, walkRight[charIndex], 0);
		else if (char_x_direction == -1) iShowBMP2(charX, charY, walkLeft[charIndex], 0);
		else if (char_y_direction == 1) iShowBMP2(charX, charY, walkUp[charIndex], 0);
		else if (char_y_direction == -1) iShowBMP2(charX, charY, walkDown[charIndex], 0);

		idleCounter++;
		if (idleCounter >= 1000) {
			idleCounter = 0;
			charIndex = 0;
			idlePosition = true;
			char_x_direction = 0;
			char_y_direction = 0;
		}
	}
	else {
		iShowBMP2(charX, charY, idle, 0);
	}
}

void movementKey()  {
	if (game_page == 1) {
		int screenWidth = 1000;
		int screenHeight = 720;
		int charWidth = 48;
		int charHeight = 48;

		if (isKeyPressed('w') || isSpecialKeyPressed(GLUT_KEY_UP)) {
			double nextY = charY + CHAR_SPEED;
			if (!checkCollision(charX, nextY, charWidth, charHeight) &&
				nextY + charHeight <= screenHeight) {
				charY = nextY;
				charIndex = (charIndex + 1) % 4;
				idlePosition = false;
				char_x_direction = 0;
				char_y_direction = 1;
			}
		}

		if (isKeyPressed('a') || isSpecialKeyPressed(GLUT_KEY_LEFT)) {
			double nextX = charX - CHAR_SPEED;
			if (!checkCollision(nextX, charY, charWidth, charHeight) &&
				nextX >= 0) {
				charX = nextX;
				charIndex = (charIndex + 1) % 4;
				idlePosition = false;
				char_x_direction = -1;
				char_y_direction = 0;
			}
		}

		if (isKeyPressed('s') || isSpecialKeyPressed(GLUT_KEY_DOWN)) {
			double nextY = charY - CHAR_SPEED;
			if (!checkCollision(charX, nextY, charWidth, charHeight) &&
				nextY >= 0) {
				charY = nextY;
				charIndex = (charIndex + 1) % 4;
				idlePosition = false;
				char_x_direction = 0;
				char_y_direction = -1;
			}
		}

		if (isKeyPressed('d') || isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
			double nextX = charX + CHAR_SPEED;
			if (!checkCollision(nextX, charY, charWidth, charHeight)) {
				charX = nextX;
				charIndex = (charIndex + 1) % 4;
				idlePosition = false;
				char_x_direction = 1;
				char_y_direction = 0;
			}
		}

		if (charX < 0) {
			currentMapIndex--;
			if (currentMapIndex < 0) {
				currentMapIndex = NUM_MAPS - 1;
			}
			charX = screenWidth - charWidth;
		}
		else if (charX + charWidth > screenWidth) {
			currentMapIndex++;
			if (currentMapIndex >= NUM_MAPS) {
			currentMapIndex = 0;
			}
			charX = 0;
		}
	}
}

void iDraw() {
	iClear();

	menu();
	if (game_page == 1) {
		iShowBMP(0, 0, mapImages[currentMapIndex]);
		//drawObstacles();
		//drawTriggers();
		movementDraw();
		//iShowBMP2(npc.x, npc.y, npcSprite[npc.direction], 0);
	}
	else if (game_page == 2) {
		background1();
		evre1();
	}
	else if (game_page == 3) {
		background2();
		evre2();
	}

}

void iMouseMove(int mx, int my) {
	selectedItem = -1;
	if (game_page == 0) {
		for (int i = 0; i < 3; i++) {
			if (mx >= menuX && mx <= menuX + menuWidth && my >= menuY + menuHeight - (i + 1) * buttonHeight && my <= menuY + menuHeight - i * buttonHeight) {
				selectedItem = i;
				break;
			}
		}
	}
}

void iPassiveMouseMove(int mx, int my) {
	iMouseMove(mx, my);
}

void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		printf("Mouse clicked at (%d, %d)\n", mx, my);
		Button();
	}
}

void iKeyboard(unsigned char key) {
	if (key == ' ' && game_page == 0) {
		mciSendString("play ggsong from 0", NULL, 0, NULL);
	}
}

void iSpecialKeyboard(unsigned char key) {}

	void fixedUpdate() {
		escape();

		if (game_page == 1) {
			movementKey();
			//updateNPC();
			checkTriggers();
		}
		else if (game_page == 2) {
			if (!game1Over) {
				characterMovement1();
				enemyFire1();
			}
			else {
				game1Timer++;
				if (game1Timer >= 300) { // 3 seconds delay
					game_page = 1; // Return to exploration

					if (player1Won) {
						// If player WON first shooting game, go to Map 4
						currentMapIndex = 3; // Map 4 (index 3)
						charX = 100; // Spawn position in Map 4
						charY = 100;
					}
					else {
						// If player LOST, go back to Map 3
						currentMapIndex = 2; // Map 3 (index 2)
						charX = 100; // Spawn position in Map 3
						charY = 100;
					}

					game1Over = false; // Reset for next time
				}
			}
		}
		else if (game_page == 3) {
			if (!game2Over) {
				characterMovement2();
				enemyFire2();
			}
			else {
				game2Timer++;
				if (game2Timer >= 300) { // 3 seconds
					game_page = 1; // Return to exploration
					currentMapIndex = 2; // Back to map 3 (or change if you want different)
					charX = 100;
					charY = 100;
					game2Over = false;
				}
			}
		}
	}

int main() {
	// Initialize all bullets as hidden (for shooting game)
	for (int i = 0; i < 100; i++) {
		bullet1Show[i] = 0; enemyBullet1Show[i] = 0;
		bullet2Show[i] = 0; enemyBullet2Show[i] = 0;
	}

	iSetTimer(10, fixedUpdate);
	iSetTimer(40, moveEnemy1);
	iSetTimer(20, moveBullets1);
	iSetTimer(350, moveEnemy2);
	iSetTimer(150, moveBullets2);

	iInitialize(900, 720, "Game Title");
	iStart();
	return 0;
}