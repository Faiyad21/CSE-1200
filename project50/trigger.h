#ifndef trgger_H
#define trgger_H



// Trigger Zones---------------------------------------------------------------------------------------TRIGGERS 
struct Trigger {
	int x, y;
	int width, height;
	int targetMap;      // -1 = no map change
	double targetX, targetY;
	int targetGameState; // -1 = no state change
};

// Map 1 triggers
Trigger map1Triggers[] = {
	{ 600, 400, 4, 40, 1, 154, 223, -1 },
	
};
int numMap1Triggers = 1;

// Map 2 triggers
Trigger map2Triggers[] = {
	{ 273, 124, 100, 5, 2, 366,400, -1},
	{ 170, 0, 100, 10, 2, 154, 223, -1 }
};
int numMap2Triggers = 2;

// Map 3 triggers
Trigger map3Triggers[] = {
	{ 720, 250, 40, 40, 0, 300, 400, -1 },
	{ 170, 0, 110, 4, -1, 0, 0, 2 }
};
int numMap3Triggers = 2;

Trigger map4Triggers[] = {
	{ 720, 250, 40, 40, 0, 300, 400, -1 },
	{ 400, 520, 40, 40, -1, 0, 0, 2 }
};
int numMap4Triggers = 2;








#endif