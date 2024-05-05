#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'

void drawRoom(int size, int x, int y);
void drawCharacterAndDoor(int size, int char_x, int char_y, int door_x, int door_y);

void drawCharacterAndDoor(int size, int char_x, int char_y, int door_x, int door_y)
{
    printf("\n");

    for (int a = 0; a < size; a++)//for writing --- lines at upper table
    {
        printf("--");
    }
    printf("-");
    printf("\n");
    for (int i = 0; i < size; i++)
    {

        for (int j = 0; j <= size; j++)
        {
            if (i == char_y && j == char_x) //if charx and chary equals which comes from menu function prints C
            {
                printf("|C");
            }
            else if (i == door_y && j == door_x)//if doorx and doory equals which comes from menu function prints D
            {
                printf("|D");
            }
            else
            {
                printf("| "); //spaces betwen columns
            }
        }

        printf("\n");
    }
    for (int a = 0; a < size; a++)
    {
        printf("--"); // //for writing --- lines at down of table
    }
    printf("-");
    printf("\n");
}
int move_character(int size, int char_x, int char_y, int door_x, int door_y)
{
    
    char direction;
    int moves = 0; //it is counter for moves

    while (char_x != door_x || char_y != door_y)
    {
        printf("Enter direction (w, a, s, d): \n");// move character by taking input from the user
        scanf(" %c", &direction);
        switch (direction)
        {
        case UP:
            if (char_y > 0)
            {
                char_y--;
                moves++;
            }
            else
                printf("!!!!WARNING!!!! You cannot go up more...");
            break;
        case LEFT:
            if (char_x > 0)
            {
                char_x--;
                moves++;
            }
            else
                printf("!!!!WARNING!!!! You cannot go left more...");
            break;
        case DOWN:
            if (char_y < size - 1)
            {
                char_y++;
                moves++;
            }
            else
                printf("!!!!WARNING!!!! You cannot go down more...");
            break;
        case RIGHT:
            if (char_x < size - 1)
            {
                char_x++;
                moves++;
            }
            else
                printf("!!!!WARNING!!!! You cannot go right more...");
            break;
        default:
            printf("Invalid input. Try again.\n");
        }

        drawCharacterAndDoor(size, char_x, char_y, door_x, door_y);
    }
    printf("\n\n----Congratulations! You have reached the door.----\n\n");
    printf("Total steps taken: %d\n", moves);
    return moves;
}

int menu(int option)
{
    int size; // Get user input for room size

    if (option == 1)
    {
        printf("Enter room size (5-10): ");
        scanf("%d", &size);

        // Check if size is true
        if (size < 5 || size > 10)
        {
            printf("Invalid room size!\n");
            return 1;
        }

        // Set seed for random number generator
        srand(time(NULL));

        // Generate random position for character and door
        int char_x = rand() % size;
        int char_y = rand() % size;
        int door_x = rand() % size;
        int door_y = rand() % size;

        // Draw the character and door
        drawCharacterAndDoor(size, char_x, char_y, door_x, door_y);
        move_character(size, char_x, char_y, door_x, door_y);
    }
    else if (option == 2)
    {
        printf("The character is able to move one space in any of the four cardinal directions:up,down,left,and right.The game ends when the character reaches the door.\n\n");
    }
    else if (option == 3)
    {
        return 0;
    }
}

int main()
{
    int option;

    do
    {
        printf("Welcome to the 2D puzzle game!\n");
        printf("1. New Game\n");
        printf("2. Help\n");
        printf("3. Exit\n");
        scanf("%d", &option);
        menu(option);
    } while (option != 3);

    return 0;
}
