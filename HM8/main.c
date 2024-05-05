#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BOARD_SIZE 3
#define MAX_MOVES 300000

typedef struct
{
	int board[BOARD_SIZE][BOARD_SIZE];
} Puzzle;

int isMoveValid(const Puzzle *puzzle, int emptyRow, int emptyCol, char move);
void findEmptyTile(const Puzzle *puzzle, int *row, int *col);
void shuffleMoves(char *moves, int numMoves);

void initializeBoard(Puzzle *puzzle)
{
	int numbers[BOARD_SIZE * BOARD_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
	int numIndices = BOARD_SIZE * BOARD_SIZE;

	// Shuffle the numbers randomly using Fisher-Yates algorithm
	for (int i = numIndices - 1; i > 0; --i)
	{
		int j = rand() % (i + 1);
		int temp = numbers[i];
		numbers[i] = numbers[j];
		numbers[j] = temp;
	}

	// Assign the shuffled numbers to the puzzle board
	int index = 0;
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			puzzle->board[i][j] = numbers[index++];
		}
	}
}

void printBoard(const Puzzle *puzzle)
{
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			if (puzzle->board[i][j] == 0)
			{
				printf("  - "); // Print a dash for the empty tile
			}
			else
			{
				printf("%3d ", puzzle->board[i][j]);
			}
		}
		printf("\n");
	}
}

int makeMove(Puzzle *puzzle, int number, char direction)
{
	int emptyRow = -1;
	int emptyCol = -1;

	// Find the row and column of the empty tile (0)
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			if (puzzle->board[i][j] == 0)
			{
				emptyRow = i;
				emptyCol = j;
				break;
			}
		}
		if (emptyRow != -1)
		{
			break;
		}
	}

	int row = -1;
	int col = -1;

	// Find the row and column of the number to move
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			if (puzzle->board[i][j] == number)
			{
				row = i;
				col = j;
				break;
			}
		}
		if (row != -1)
		{
			break;
		}
	}

	// Check if the move is valid based on the direction
	switch (direction)
	{
	case 'U':
		if (row > 0 && puzzle->board[row - 1][col] == 0)
		{
			puzzle->board[row - 1][col] = number;
			puzzle->board[row][col] = 0;
			return 1;
		}
		break;
	case 'D':
		if (row < BOARD_SIZE - 1 && puzzle->board[row + 1][col] == 0)
		{
			puzzle->board[row + 1][col] = number;
			puzzle->board[row][col] = 0;
			return 1;
		}
		break;
	case 'L':
		if (col > 0 && puzzle->board[row][col - 1] == 0)
		{
			puzzle->board[row][col - 1] = number;
			puzzle->board[row][col] = 0;
			return 1;
		}
		break;
	case 'R':
		if (col < BOARD_SIZE - 1 && puzzle->board[row][col + 1] == 0)
		{
			puzzle->board[row][col + 1] = number;
			puzzle->board[row][col] = 0;
			return 1;
		}
		break;
	}

	return 0; // Invalid move
}

int makecomputerMove(Puzzle *puzzle, int number, char direction)
{
	int emptyRow = -1;
	int emptyCol = -1;

	// printf("%d number :\n", number);

	// Find the row and column of the empty tile (0)
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			if (puzzle->board[i][j] == 0)
			{
				emptyRow = i;
				emptyCol = j;
				break;
			}
		}
		if (emptyRow != -1)
		{
			break;
		}
	}

	int row = -1;
	int col = -1;

	// Find the row and column of the number to move
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			if (i != 0 && j != 0) // Skip the diagonal elements
			{
				continue;
			}
			if (emptyRow + i >= 0 && emptyRow + i < BOARD_SIZE && emptyCol + j >= 0 && emptyCol + j < BOARD_SIZE &&
				puzzle->board[emptyRow + i][emptyCol + j] == number)
			{
				row = emptyRow + i;
				col = emptyCol + j;
				break;
			}
		}
		if (row != -1)
		{
			break;
		}
	}
	// printf("\n%d   %d  \n", row, col);

	// printf("\ndirec: %c\n", direction);

	// Check if the move is valid based on the direction
	switch (direction)
	{
	case 'U':
		if (row > 0 && puzzle->board[row - 1][col] == 0)
		{
			puzzle->board[row - 1][col] = number;
			puzzle->board[row][col] = 0;
			return 1;
		}
		break;
	case 'D':
		if (row < BOARD_SIZE - 1 && puzzle->board[row + 1][col] == 0)
		{
			puzzle->board[row + 1][col] = number;
			puzzle->board[row][col] = 0;
			return 1;
		}
		break;
	case 'L':
		if (col > 0 && puzzle->board[row][col - 1] == 0)
		{
			puzzle->board[row][col - 1] = number;
			puzzle->board[row][col] = 0;
			return 1;
		}
		break;
	case 'R':
		if (col < BOARD_SIZE - 1 && puzzle->board[row][col + 1] == 0)
		{
			puzzle->board[row][col + 1] = number;
			puzzle->board[row][col] = 0;
			return 1;
		}
		break;
	}

	return 0; // Invalid move
}

int isBoardSolved(const Puzzle *puzzle)
{
	int expectedValue = 1;

	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			if (i == BOARD_SIZE - 1 && j == BOARD_SIZE - 1)
			{
				if (puzzle->board[i][j] != 0)
				{
					return 0; // Last tile should be empty (0)
				}
			}
			else
			{
				if (puzzle->board[i][j] != expectedValue)
				{
					return 0; // Tile value is not as expected
				}
				expectedValue++;
			}
		}
	}

	return 1; // Board is solved
}

void printf_txt(int score)
{
	FILE *ptr;

	ptr = fopen("best_score.txt", "a+");

	fprintf(ptr, "%d\n", score);

	fclose(ptr);
}

int playGameAsUser()
{
	Puzzle puzzle;
	initializeBoard(&puzzle);
	printBoard(&puzzle);

	int moves = 0;
	int score = 0;
	int number, validMove;
	char direction;

	while (!isBoardSolved(&puzzle))
	{
		printf("Enter your move (number-direction, e.g., 2-R): ");
		scanf("%d", &number);
		scanf(" %c", &direction);

		validMove = makeMove(&puzzle, number, direction);

		if (validMove)
		{
			moves++;
			score = 1000 - 10 * moves;
			printBoard(&puzzle);
			// Save the updated state of the board to a txt file
		}
		else
		{
			printf("Invalid move. Please try again.\n");
		}
	}
	printf_txt(score);

	printf("Congratulations! You solved the puzzle.\n");
	printf("Total number of moves: %d\n", moves);
	printf("Score: %d\n", score);

	// Code to check if the score is the best and save it to a txt file if it is

	return moves;
}

int getRandomNumberToMove(const Puzzle *puzzle)
{
	int row, col;
	int number;

	do
	{
		row = rand() % BOARD_SIZE;
		col = rand() % BOARD_SIZE;
		number = puzzle->board[row][col];
	} while (number == 0);

	return number;
}

void autoFinish(Puzzle *puzzle, int moves)
{
	if (moves == MAX_MOVES || isBoardSolved(puzzle))
	{
		printf("Total number of moves taken: %d\n", moves);
		return;
	}

	// Generate a list of valid moves
	char validMoves[4] = {'U', 'D', 'L', 'R'};
	int numValidMoves = 4;

	// Randomly shuffle the valid moves
	shuffleMoves(validMoves, numValidMoves);

	// Find the current empty tile position
	int emptyRow, emptyCol;
	findEmptyTile(puzzle, &emptyRow, &emptyCol);

	// Try each valid move
	for (int i = 0; i < numValidMoves; ++i)
	{
		char move = validMoves[i];

		// Find the new position of the empty tile based on the move
		int newRow = emptyRow, newCol = emptyCol;
		if (move == 'U')
			newRow++;
		else if (move == 'D')
			newRow--;
		else if (move == 'L')
			newCol++;
		else if (move == 'R')
			newCol--;

		// Check if the move is valid
		if (isMoveValid(puzzle, newRow, newCol, move))
		{
			int number = puzzle->board[newRow][newCol];

			if (number < 9)
			{
				// Make the move
				makecomputerMove(puzzle, number, move);
				printf("Moved number %d %c\n\n", number, move);
				printBoard(puzzle);
				printf("\n\n");
				autoFinish(puzzle, moves + 1);

				// Check if the puzzle is solved after the recursive call
				if (isBoardSolved(puzzle))
					return;

				// Undo the move
				switch (move)
				{
				case 'U':
					makecomputerMove(puzzle, number, 'D');
					break;
				case 'D':
					makecomputerMove(puzzle, number, 'U');
					break;
				case 'L':
					makecomputerMove(puzzle, number, 'R');
					break;
				case 'R':
					makecomputerMove(puzzle, number, 'L');
					break;
				}
			}
		}
	}
}

void shuffleMoves(char *moves, int numMoves)
{

	// Shuffle the array of moves using the Fisher-Yates algorithm
	for (int i = numMoves - 1; i > 0; --i)
	{
		int j = rand() % (i + 1);
		char temp = moves[i];
		moves[i] = moves[j];
		moves[j] = temp;
	}
}

int isMoveValid(const Puzzle *puzzle, int emptyRow, int emptyCol, char move)
{
	// Check if the specified move is valid based on the current position of the empty tile
	// Return 1 if the move is valid, 0 otherwise
	switch (move)
	{
	case 'U':
		return emptyRow > 0;
	case 'D':
		return emptyRow < BOARD_SIZE - 1;
	case 'L':
		return emptyCol > 0;
	case 'R':
		return emptyCol < BOARD_SIZE - 1;
	default:
		return 0;
	}
}

void findEmptyTile(const Puzzle *puzzle, int *row, int *col)
{
	// Find the position of the empty tile (0) in the puzzle board
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			if (puzzle->board[i][j] == 0)
			{
				*row = i;
				*col = j;
				return;
			}
		}
	}
	*row = -1; // If there is no empty tile it setted up as -1
	*col = -1;
}

void finishGameWithPC()
{
	Puzzle puzzle;
	initializeBoard(&puzzle);
	printBoard(&puzzle);
	printf("\n\n");

	autoFinish(&puzzle, 0);

	// Code to return to the main menu
}
void showBestScore()
{
	FILE *file = fopen("best_score.txt", "r");
	if (file == NULL)
	{
		printf("No best score available.\n");
		return;
	}

	int bestScore[100] = {};
	int i = 0;
	int satir = 0;

	while (!feof(file))
	{
		// printf("333\n");
		fscanf(file, "%d", &bestScore[i]);
		i++;
		satir++;
	}
	// printf("sadsad\n");
	// printf("%d", satir);
	fclose(file);

	// for (int i = 0; i < satir; i++)
	// {
	// 	printf("->%d\n", bestScore[i]);
	// }

	int temp_int = bestScore[i];
	for (int i = 1; i < satir; i++)
	{
		if (bestScore[i] > temp_int)
		{
			temp_int = bestScore[i];
		}
	}

	printf("Best score: %d\n", temp_int);
}

int main()
{
	int choice;
	srand(time(NULL));

	do
	{
		printf("Main Menu:\n");
		printf("1. Play game as a user\n");
		printf("2. Finish the game with PC\n");
		printf("3. Show the best score\n");
		printf("4. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			playGameAsUser();
			break;
		case 2:
			finishGameWithPC();
			break;
		case 3:
			showBestScore();
			break;
		case 4:
			printf("Exiting the program. Goodbye!\n");
			break;
		default:
			printf("Invalid choice. Please try again.\n");
		}
	} while (choice != 4);

	return 0;
}