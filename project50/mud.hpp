#ifndef md_H
#define md_H

/*int screenWidth = 900, screenHeight = 720;

// Fighting area (500x500 in the center)
int fightAreaX = 250, fightAreaY = 250;
int fightAreaWidth = 500, fightAreaHeight = 500;

// Enemy - Argse (positioned at top)
int enemyX = 500, enemyY = 400;  // Top of fighting area
int enemyDX = 3;
int enemyHealth = 200;
int enemyMaxHealth = 200;
char enemyName[] = "Argse";
char enemyImage[] = "img\\mudy3.bmp";

// Enemy Bullets
int enemyBulletX[100], enemyBulletY[100], enemyBulletShow[100];
char enemyBulletImage[] = "img\\rock8.bmp";
int enemyBulletCooldown = 30;
const int ENEMY_COOLDOWN_TIME = 120;

// Character (positioned at bottom)
double charrX = 500, charrY = 100;  // Bottom of fighting area
int charWidth = 48, charHeight = 48;
int charHealth = 100;
int charMaxHealth = 100;
char charImage[] = "img\\rock8.bmp";

// Character Bullets
int bulletX[100], bulletY[100], bulletShow[100];
char bulletImage[] = "img\\rock8.bmp";
int bulletCooldown = 0;
const int COOLDOWN_TIME = 30;

// Score
int score = 0;

void background(){
	iShowBMP(0, 0, "img\\mud1.bmp");
}
void evre(){
	// Draw enemy - Argse (at top)
	iShowBMP2(enemyX - 40, enemyY - 18, enemyImage, 0);

	// Draw character (at bottom)
	iShowBMP2(charrX, charrY, charImage, 0);

	// Draw character bullets
	for (int i = 0; i < 100; i++) {
		if (bulletShow[i]) {
			iShowBMP2(bulletX[i], bulletY[i], bulletImage, 0);
		}
	}

	// Draw enemy bullets
	for (int i = 0; i < 100; i++) {
		if (enemyBulletShow[i]) {
			iShowBMP2(enemyBulletX[i], enemyBulletY[i], enemyBulletImage, 0);
		}
	}

	// HEALTH BARS ON RIGHT SIDE
	int healthBarX = 500;  // Right side of screen
	int playerHealthBarWidth = 150;  // Player health bar width
	int enemyHealthBarWidth = 300;   // Enemy health bar width (double the player's)
	int healthBarHeight = 20;

	// Enemy health bar (top right) - DOUBLE WIDTH
	iSetColor(255, 255, 255);
	iText(healthBarX, 700, enemyName, GLUT_BITMAP_9_BY_15);  // Enemy name
	iSetColor(255, 0, 0);
	iFilledRectangle(healthBarX, 650, enemyHealthBarWidth, healthBarHeight);
	iSetColor(0, 255, 0);
	iFilledRectangle(healthBarX, 650, (enemyHealthBarWidth * enemyHealth) / enemyMaxHealth, healthBarHeight);
	iSetColor(255, 255, 255);
	iRectangle(healthBarX, 650, enemyHealthBarWidth, healthBarHeight);

	// Enemy health text
	char enemyHealthStr[50];
	sprintf_s(enemyHealthStr, sizeof(enemyHealthStr), "%d/%d", enemyHealth, enemyMaxHealth);
	iText(healthBarX + enemyHealthBarWidth + 10, 885, enemyHealthStr, GLUT_BITMAP_9_BY_15);

	// Character health bar (bottom right) - REGULAR WIDTH
	iSetColor(255, 255, 255);
	iText(healthBarX, 170, "Player", GLUT_BITMAP_9_BY_15);  // Player name
	iSetColor(255, 0, 0);
	iFilledRectangle(healthBarX, 150, playerHealthBarWidth, healthBarHeight);
	iSetColor(0, 255, 0);
	iFilledRectangle(healthBarX, 150, (playerHealthBarWidth * charHealth) / charMaxHealth, healthBarHeight);
	iSetColor(255, 255, 255);
	iRectangle(healthBarX, 150, playerHealthBarWidth, healthBarHeight);

	// Character health text
	char healthStr[50];
	sprintf_s(healthStr, sizeof(healthStr), "%d/%d", charHealth, charMaxHealth);
	iText(healthBarX + playerHealthBarWidth + 10, 185, healthStr, GLUT_BITMAP_9_BY_15);

	// Cooldown indicator (left side)
	iSetColor(255, 255, 255);
	if (bulletCooldown > 0) {
		iText(10, 30, "Reloading...", GLUT_BITMAP_9_BY_15);
	}
	else {
		iText(10, 30, "Ready to fire!", GLUT_BITMAP_9_BY_15);
	}

	// Score display (left side)
	char scoreStr[50];
	sprintf_s(scoreStr, sizeof(scoreStr), "Score: %d", score);
	iText(10, 50, scoreStr, GLUT_BITMAP_9_BY_15);

	// Instructions (left side)
	iText(10, 10, "A/D to move, F to fire", GLUT_BITMAP_9_BY_15);
	iText(10, 70, "Fighting Area: 500x500 (Red Box)", GLUT_BITMAP_9_BY_15);
}


void moveEnemy() {
	enemyX += enemyDX;

	// Keep enemy within fighting area (top section)
	if (enemyX > fightAreaX + fightAreaWidth - 40 || enemyX < fightAreaX + 40) {
		enemyDX = -enemyDX;
	}
}

void enemyFire() {
	if (enemyBulletCooldown > 0) {
		enemyBulletCooldown--;
	}
	else {
		// Enemy fires at character
		for (int i = 0; i < 100; i++) {
			if (!enemyBulletShow[i]) {
				enemyBulletX[i] = enemyX;
				enemyBulletY[i] = enemyY - 18;
				enemyBulletShow[i] = 1;
				enemyBulletCooldown = ENEMY_COOLDOWN_TIME;
				break;
			}
		}
	}
}

void moveBullets() {
	// Update cooldowns
	if (bulletCooldown > 0) bulletCooldown--;
	if (enemyBulletCooldown > 0) enemyBulletCooldown--;

	// Move character bullets and check enemy collision
	for (int i = 0; i < 100; i++) {
		if (bulletShow[i]) {
			bulletY[i] += 8;

			// Check collision with enemy
			if (bulletShow[i] &&
				bulletX[i] >= enemyX - 40 && bulletX[i] <= enemyX + 40 &&
				bulletY[i] >= enemyY - 18 && bulletY[i] <= enemyY + 18) {
				bulletShow[i] = 0;
				enemyHealth -= 10;
				score += 10;
				if (enemyHealth <= 0) {
					enemyHealth = 0;
				}
			}

			if (bulletY[i] > screenHeight) bulletShow[i] = 0;
		}
	}

	// Move enemy bullets and check character collision
	for (int i = 0; i < 100; i++) {
		if (enemyBulletShow[i]) {
			enemyBulletY[i] -= 6;  // Enemy bullets move downward

			// Check collision with character
			if (enemyBulletShow[i] &&
				enemyBulletX[i] >= charrX && enemyBulletX[i] <= charrX + charWidth &&
				enemyBulletY[i] >= charrY && enemyBulletY[i] <= charrY + charHeight) {
				enemyBulletShow[i] = 0;
				charHealth -= 10;
				if (charHealth <= 0) {
					charHealth = 0;
				}
			}

			if (enemyBulletY[i] < 0) enemyBulletShow[i] = 0;
		}
	}
}
void charectermovement(){
	// Character movement (stays at bottom)
	if (isKeyPressed('a') || isKeyPressed('A') || isSpecialKeyPressed(GLUT_KEY_LEFT)) {
		charrX -= 5;
		if (charrX < fightAreaX) charrX = fightAreaX;
	}

	if (isKeyPressed('d') || isKeyPressed('D') || isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
		charrX += 5;
		if (charrX > fightAreaX + fightAreaWidth - charWidth) charrX = fightAreaX + fightAreaWidth - charWidth;
	}

	// Character fire
	if ((isKeyPressed('f') || isKeyPressed('F')) && bulletCooldown == 0) {
		for (int i = 0; i < 100; i++) {
			if (!bulletShow[i]) {
				bulletX[i] = charrX + charWidth / 2 - 2;
				bulletY[i] = charrY + charHeight;
				bulletShow[i] = 1;
				bulletCooldown = COOLDOWN_TIME;
				break;
			}
		}
	}

	// Enemy AI - fire at character
}*/
/////agaeme statet 2 ------------------------------------------------------------------------------------------------------------------



#endif