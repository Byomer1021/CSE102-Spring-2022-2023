#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct
{
	int row;
	int col;
} Point;

typedef struct
{
	char type;
	int value;
} Block;

Block ***init_board();
void draw_board(Block ***board);
char make_move();
int check_status(Block ***board, Point *snake, int y, int x);
int update(Block ***board, Point *snake, int move_count);
void generate_bait(Block ***board);
void update_obstacles(Block ***board);
void moveSnake(Point* snake, int len, int y, int x);
void play(Block ***board);


char last_move;  // Global variables
int length;


int main()
{
	Block ***board = init_board();
	play(board);
	return 0;
}


Block ***init_board()
{
	Block ***board = (Block ***)malloc(10 * sizeof(Block **));
	for (int i = 0; i < 10; i++)
	{
		board[i] = (Block **)malloc(10 * sizeof(Block *));
		for (int j = 0; j < 10; j++)
		{
			board[i][j] = (Block *)malloc(sizeof(Block));
			board[i][j]->type = 'e';
			board[i][j]->value = 0;
		}
	}

	// Generate obstacle and bait blocks
	srand(time(NULL));
	int obstacle_row, obstacle_col, bait_row, bait_col;
	obstacle_row = rand() % 10;
	obstacle_col = rand() % 10;
	do
	{
		bait_row = rand() % 10;
		bait_col = rand() % 10;
	} while (bait_row == obstacle_row && bait_col == obstacle_col);

	board[obstacle_row][obstacle_col]->type = 'o';
	board[obstacle_row][obstacle_col]->value = 1;

	board[bait_row][bait_col]->type = 'b';
	board[bait_row][bait_col]->value = 0;

	return board;
}

void draw_board(Block ***board)
{
	printf(" -----------------------\n");
	for (int i = 0; i < 10; i++)
	{
		printf(" | ");
		for (int j = 0; j < 10; j++)
		{
			if (board[i][j]->type == 'e')
			{
				printf("  ");
			}
			else if (board[i][j]->type == 'o')
			{
				printf("%2d", board[i][j]->value);
			}
			else if (board[i][j]->type == 'b')
			{
				printf(". ");
			}
			else if (board[i][j]->type == 'S')
			{
				printf("X ");
			}
			else if (board[i][j]->type == 'H')
			{
				printf("O ");
			}
		}
		printf("|\n");
	}
	printf(" -----------------------\n");
}

int check_status(Block ***board, Point *snake, int y, int x)
{
	int head_row = snake[0].row + y;
	int head_col = snake[0].col + x;

	// Check if the snake hits its own body
	for (int i = 1; i < length; i++)
	{
		if (snake[i].row == head_row && snake[i].col == head_col)
		{
			printf("Game over! You hit the snake's body.\n");
			return 1;
		}
	}

	// Check if the snake hits a wall
	if (head_row < 0 || head_row >= 10 || head_col < 0 || head_col >= 10)
	{
		printf("Game over! You hit a wall.\n");
		return 1;
	}

	// Check if the snake encounters an obstacle longer than itself
	if (board[head_row][head_col]->type == 'o' && board[head_row][head_col]->value > length)
	{
		printf("Game over! You encountered an obstacle longer than the snake.\n");
		return 1;
	}

	return 0; // Game is not over
}

void generate_bait(Block ***board)
{
	int row, col;

	// Find an empty block on the board for placing the bait
	do
	{
		row = rand() % 10;
		col = rand() % 10;
	} while (board[row][col]->type != 'e');

	// Set the block as bait
	board[row][col]->type = 'b';
	board[row][col]->value = 0;
}

char make_move()
{
	char move;
	printf("Enter your move (w/a/s/d): \n\n\033[A");
	scanf(" %c", &move);
	return move;
}

int update(Block ***board, Point *snake, int move_count)
{

	int len = length;

	int head_row = snake[0].row;
	int head_col = snake[0].col;

	// printf("%c",board[snake[0].row][snake[0].col]->type);

	for (int i = 0; i < 10; i++)
		for (int k = 0; k < 10; k++)
			if ((board[i][k]->type == 'S' || board[i][k]->type == 'H'))
			{
				board[i][k]->type = 'e';
				board[i][k]->value = 0;
			}

	// Update the head of the snake based on the last move
	Point temp = {snake[len -1].row, snake[len -1].col};
	// Point temp = snake[len -1];
	if (last_move == 'w')
	{
		if(check_status(board, snake, -1, 0))
			return 1;
		moveSnake(snake, len, -1, 0);
	}
	else if (last_move == 'a')
	{
		if(check_status(board, snake, 0, -1))
			return 1;
		moveSnake(snake, len, 0, -1);
	}
	else if (last_move == 's')
	{
		if(check_status(board, snake, 1, 0))
			return 1;
		moveSnake(snake, len, 1, 0);
	}
	else if (last_move == 'd')
	{
		if(check_status(board, snake, 0, 1))
			return 1;
		moveSnake(snake, len, 0, 1);
	}


	if (board[snake[0].row][snake[0].col]->type == 'b')
	{
		// Snake ate a bait, increase the length by 1
		snake[len].row = temp.row;
		snake[len].col = temp.col;
		generate_bait(board);
		len++;
	}


	for (int j = 0; j < len; j++)
	{

		// printf("0 snake[%d]: (%d, %d)\n",j , snake[j].row, snake[j].col);
		int row= snake[j].row;
		int col= snake[j].col;
		// printf("1 snake[%d]: (%d, %d)\n",j , snake[j].row, snake[j].col);
		if(j == 0){
			board[row][col]->type = 'H';
			board[row][col]->value = 0;
		}
		else{
			board[row][col]->type = 'S';
			board[row][col]->value = 0;
		}
		// printf("2 snake[%d]: (%d, %d)\n",j , snake[j].row, snake[j].col);
	}

	// Update obstacles every 5 moves
	if (move_count % 5 == 0)
	{
		update_obstacles(board);
	}
	
	length = len;
	// printf("length = %d len: %d\n", length, len);

	return 0;

}

void moveSnake(Point* snake, int len, int y, int x) {
	
	for(int i = len - 2; i >= 0; i--)
	{
		snake[i + 1].row = snake[i].row;
		snake[i + 1].col = snake[i].col;
	}
	snake[0].row += y;
	snake[0].col += x;
}

void update_obstacles(Block ***board)
{
	int obstacle_count = 0;

	// Count the number of existing obstacles on the board
	for (int row = 0; row < 10; row++)
	{
		for (int col = 0; col < 10; col++)
		{
			if (board[row][col]->type == 'o')
			{
				obstacle_count++;
			}
		}
	}

	// Add new obstacles if the count is less than 3
	if (obstacle_count < 3)
	{
		int remaining_obstacles = 3 - obstacle_count;
		for (int i = 0; i < remaining_obstacles; i++)
		{
			int row, col;

			// Find an empty block on the board for placing the obstacle
			do
			{
				row = rand() % 10;
				col = rand() % 10;
			} while (board[row][col]->type != 'e');

			// Set the block as an obstacle
			board[row][col]->type = 'o';
			board[row][col]->value = 1; // Initial obstacle height is 1
		}
	}

	// Increase the height of existing obstacles
	for (int row = 0; row < 10; row++)
	{
		for (int col = 0; col < 10; col++)
		{
			if (board[row][col]->type == 'o')
			{
				// Increase the height of the obstacle by adding a new nested block
				board[row][col]->value++;
			}
		}
	}

	// Add new obstacles if the count is less than 3
	if (obstacle_count < 3)
	{
		int remaining_obstacles = 3 - obstacle_count;
		for (int i = 0; i < remaining_obstacles; i++)
		{
			int row, col;

			// Find an empty block on the board for placing the obstacle
			do
			{
				row = rand() % 10;
				col = rand() % 10;
			} while (board[row][col]->type != 'e');

			// Set the block as an obstacle
			board[row][col]->type = 'o';
			board[row][col]->value = 1; // Initial obstacle height is 1
		}
	}

	// Increase the height of existing obstacles
	for (int row = 0; row < 10; row++)
	{
		for (int col = 0; col < 10; col++)
		{
			if (board[row][col]->type == 'o')
			{
				// Increase the height of the obstacle by adding a new nested block
				board[row][col]->value++;
			}
		}
	}
}

void play(Block ***board)
{
	// Initialize the snake with a length of 1 block at the top-left of the board
	Point snake[100]; // Assuming a maximum length of 100
	snake[0].row = 3;
	snake[0].col = 3;
	int move_count = 0;
	bool game_over = false;
	length = 1;

	// Game loop
	while (!game_over)
	{
		draw_board(board);
		last_move=make_move();
		printf("\033[14A");
		game_over = update(board, snake, move_count);
		move_count++;
		// printf("%d", length);
	}
}
