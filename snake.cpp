#include <iostream>
#include <conio.h>
#include <string>

using namespace std;

bool isGameOver;

const int gridWidth = 20;
const int gridHeight = 17;

int headX, headY, foodX, foodY, playerScore;

int snakeBodyX[100], snakeBodyY[100]; // Snake's body coordinates
int snakeLength; // Length of the snake's body

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN }; // Snake movement directions
Direction snakeDirection;

string playerName; // Player's name

void initializeGame() {
	isGameOver = false;

	snakeDirection = STOP;

	headX = gridWidth / 2;
	headY = gridHeight / 2;

	foodX = rand() % gridWidth;  // Random position for food
	foodY = rand() % gridHeight;

	playerScore = 0;
	snakeLength = 0; // Initial snake length is 0

					 // Initialize snake's body to invalid positions
	for (int i = 0; i < 100; i++) {
		snakeBodyX[i] = -1;
		snakeBodyY[i] = -1;
	}
}

void drawGrid() {
	system("cls");

	// Top border
	for (int i = 0; i < gridWidth + 2; i++)
		cout << "*";
	cout << endl;

	// Grid with snake and food
	for (int i = 0; i < gridHeight; i++) {
		for (int j = 0; j < gridWidth; j++) {
			if (j == 0)
				cout << "*"; // Left wall

			if (i == headY && j == headX)
				cout << "O"; // Snake's head
			else if (i == foodY && j == foodX)
				cout << "F"; // Food
			else {
				bool isSnakeBody = false;
				for (int k = 0; k < snakeLength; k++) {
					if (snakeBodyX[k] == j && snakeBodyY[k] == i) {
						cout << "o"; // Snake's body
						isSnakeBody = true;
						break;
					}
				}
				if (!isSnakeBody) cout << " ";
			}

			if (j == gridWidth - 1)
				cout << "*"; // Right wall
		}
		cout << endl;
	}

	// Bottom border
	for (int i = 0; i < gridWidth + 2; i++)
		cout << "*";
	cout << endl;

	cout << "Player: " << playerName << " | Score: " << playerScore << endl;
}

void handleInput() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a': snakeDirection = LEFT; break;
		case 'd': snakeDirection = RIGHT; break;
		case 'w': snakeDirection = UP; break;
		case 's': snakeDirection = DOWN; break;
		case 'x': isGameOver = true; break; // Exit the game
		}
	}
}

void updateGameLogic() {
	int prevX = snakeBodyX[0];
	int prevY = snakeBodyY[0];
	int prev2X, prev2Y;

	snakeBodyX[0] = headX;
	snakeBodyY[0] = headY;

	for (int i = 1; i < snakeLength; i++) {
		prev2X = snakeBodyX[i];
		prev2Y = snakeBodyY[i];
		snakeBodyX[i] = prevX;
		snakeBodyY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (snakeDirection) {
	case LEFT: headX--; break;
	case RIGHT: headX++; break;
	case UP: headY--; break;
	case DOWN: headY++; break;
	default: break;
	}

	// Wrap around the grid
	if (headX >= gridWidth) headX = 0;
	else if (headX < 0) headX = gridWidth - 1;

	if (headY >= gridHeight) headY = 0;
	else if (headY < 0) headY = gridHeight - 1;

	// Check for collision with the snake's body
	for (int i = 0; i < snakeLength; i++) {
		if (snakeBodyX[i] == headX && snakeBodyY[i] == headY) {
			isGameOver = true;
			return; // End the function to avoid further logic execution
		}
	}


	// Check if the snake eats the food
	if (headX == foodX && headY == foodY) {
		playerScore += 10;
		foodX = rand() % gridWidth;
		foodY = rand() % gridHeight;
		snakeLength++;
	}
}

int main() {
	cout << "Enter your name: ";
	cin >> playerName;

	initializeGame();

	while (!isGameOver) {
		drawGrid();
		handleInput();
		updateGameLogic();
	}

	cout << "Game Over! " << playerName << "'s final score: " << playerScore << endl;

	system("pause");
	return 0;
}
