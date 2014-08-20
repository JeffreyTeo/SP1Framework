// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <string>

using std :: string;
using std:: endl;
struct System_of //Shannon : Struct Draft
{
	int Value;
	COORD Location[3];
};
System_of Life; 
double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
COORD charLocation;
COORD enemyLocation[3];
COORD consoleSize;

int displayscore[10]={};
unsigned long score = 1000;
void init()
{
	// Set precision for floating point output
	std::cout << std::fixed << std::setprecision(3);

	// Get console width and height
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

	/* get the number of character cells in the current buffer */ 
	GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
	consoleSize.X = csbi.srWindow.Right + 1;
	consoleSize.Y = csbi.srWindow.Bottom;

	// set the character to be in the center of the screen.
	charLocation.X = consoleSize.X/8;
	charLocation.Y = consoleSize.Y + 47;

	// Shannon : Implement Dummy Enemy
	for (int i = 0; i < 3; ++i)
	{
		enemyLocation[i].X = consoleSize.X - 2*(i+20);
		enemyLocation[i].Y = consoleSize.Y - 2*(i-10);
	}

	//Shannon : Implement Life System
	Life.Value = 3;
	for (int i = 0; i < 3; ++i)
	{
		Life.Location[i].X = consoleSize.X - 4*(i+2);
		Life.Location[i].Y = consoleSize.Y-18;
	}

	elapsedTime = 0.0;
}

void shutdown()
{
	// Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED );
}

void getInput()
{    
	keyPressed[K_UP] = isKeyPressed(VK_UP);
	keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
}

void update(double dt)
{
	// get the delta time
	elapsedTime += dt;
	deltaTime = dt;

	// Updating the location of the character based on the key press

	if (keyPressed[K_UP] && charLocation.Y > 0)
	{
		Beep(1440, 30);
		charLocation.Y -= 2;
	}
	if (keyPressed[K_LEFT] && charLocation.X > 0)
	{
		Beep(1440, 30);
		charLocation.X -= 2; 
	}
	if (keyPressed[K_RIGHT] && charLocation.X < consoleSize.X - 35)
	{
		Beep(1440, 30);
		charLocation.X += 2; 
	}

	// quits the game if player hits the escape key
	if (keyPressed[K_ESCAPE])
		g_quitGame = true;    
}

void printBasket()
{
	gotoXY(charLocation.X, charLocation.Y-4);
	colour(0x0F);
	std::cout << "  .=========." << endl;

	gotoXY(charLocation.X, charLocation.Y-3);
	colour(0x0F);
	std::cout << " l/        /l" << endl;

	gotoXY(charLocation.X, charLocation.Y-2);
	colour(0x0F);
	std::cout << " l========lX:" << endl;

	gotoXY(charLocation.X, charLocation.Y-1);
	colour(0x0F);
	std::cout << " lXXXXXXXXl/" << endl;

	gotoXY(charLocation);
	colour(0x0F);
	std::cout << " ---------- ";
}

void render()
{
	// clear previous screen
	colour(0x000);
	cls();

	// render time taken to calculate this frame
	gotoXY(70, 0);
	colour(0x1A);
	std::cout << 1.0 / deltaTime << "f/s" << std::endl;

	gotoXY(0, 0);
	colour(0x59);
	std::cout << elapsedTime << "secs" << std::endl;

	if(score == 1000000000)
	{
		gotoXY(50, 20);
		colour(0xF6);
		std::cout << "Congrats!"<< "\nYou  won!";
	}

	else
	{
		gotoXY(62, 2);
		colour(0xF6);
		std::cout << "High Score:";
		gotoXY(62, 3);
		colour(0xF6);
		std::cout <<score;
	}

	for (int y = 2; y <= 71; y++)
	{
		gotoXY(60,y);
		colour(0x1A);
		std::cout << 'x';
	}

	// render character
	gotoXY(charLocation);
	printBasket();

	// Shannon : Render Enemy
	for (int i = 0; i < 3; ++i)
	{
		gotoXY(60,67);
		colour(0x1D);
		std::cout <<(char)1;
	}

	// Shannon : Render Life System
	for (int i = 0; i < 3; ++i)
	{
		if (Life.Value > i)
		{
			gotoXY(Life.Location[i]);
			colour(0x0C);
			std::cout <<(char)1;
		}
	}
}
