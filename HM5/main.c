#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ALPHABET_SIZE 26
int letter_frequency()
{
    char filename[100];
    printf("Enter the file name: ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file.\n"); //
        return 0;
    }

    int letter_counts[ALPHABET_SIZE] = {0};

    char c;
    while ((c = fgetc(fp)) != EOF)
    {
        if (c >= 'A' && c <= 'Z')
        {
            c = c + ('a' - 'A'); // switching capital to lower
        }
        if (c >= 'a' && c <= 'z')
        {
            letter_counts[c - 'a']++; // counting letter
        }
    }

    fclose(fp);

    printf("Letter frequency:\n");
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        printf("%c: %d\n", 'A' + i, letter_counts[i]);
    }
    return 0;
}
enum Color
{
    RED,
    GREEN,
    BLUE,
    YELLOW,
    ORANGE
};

double colors[][3] = {
    {1, 0, 0},      // RED
    {0, 1, 0},      // GREEN
    {0, 0, 1},      // BLUE
    {0.5, 0.5, 0},  // YELLOW
    {0.5, 0.4, 0.2} // ORANGE
};

enum Color mixColors(enum Color c1, enum Color c2)
{
    double mixColor[3];
    for (int i = 0; i < 3; i++)
    {
        mixColor[i] = (colors[c1][i] + colors[c2][i]) / 2; // the mixed color is [(x1+y1)/2, (x2+y2)/2, (x3+yr)/2]
    }
    double minDist = INFINITY;
    enum Color closestColor = RED;
    double dist = 0;
    for (enum Color c = RED; c <= ORANGE; c++) //Euclidean distance.
    {
        dist = sqrt(pow(mixColor[0] - colors[c][0], 2) +
                    pow(mixColor[1] - colors[c][1], 2) +
                    pow(mixColor[2] - colors[c][2], 2));
        if (dist < minDist)
        {
            minDist = dist;
            closestColor = c;
        }
    }
    return closestColor;
}

int gameplay(char board[3][3])
{

    int player = 1;
    int row, col;
    char mark;
    int i, j;

    printf("\n");
    printf("Welcome to Tic Tac Toe!\n");

    // Game loop
    while (1)
    {
        // Printing board
        printf("\n");
        printf("%c %c %c\n", board[0][0], board[0][1], board[0][2]);
        printf("- - -\n");
        printf("%c %c %c\n", board[1][0], board[1][1], board[1][2]);
        printf("- - -\n");
        printf("%c %c %c\n", board[2][0], board[2][1], board[2][2]);
        printf("- - -\n");

        // Get player's move
        if (player == 1)
            printf("\nPlayer %d(X), enter your move (row-col): ", player);
        else
            printf("\nPlayer %d(Y), enter your move (row-col): ", player);

        scanf("%d%d", &row, &col);

        if (row < 0 || row > 2 || col < 0 || col > 2) // Checking if move is valid
        {
            printf("Invalid move. Please try again.\n");
            continue;
        }
        if (board[row][col] != ' ')
        {
            printf("That space is already occupied. Please try again.\n");
            continue;
        }

        mark = (player == 1) ? 'X' : 'O'; // Updating board
        board[row][col] = mark;

        for (i = 0; i < 3; i++) // Checking winner
        {
            if (board[i][0] == mark && board[i][1] == mark && board[i][2] == mark)
            {

                printf("%c %c %c\n", board[0][0], board[0][1], board[0][2]);
                printf("- - -\n");
                printf("%c %c %c\n", board[1][0], board[1][1], board[1][2]);
                printf("- - -\n");
                printf("%c %c %c\n", board[2][0], board[2][1], board[2][2]);
                printf("- - -\n");
                printf("\nPlayer %d wins!\n", player);
                printf("\n");
                return 0;
            }
            if (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark)
            {

                printf("%c %c %c\n", board[0][0], board[0][1], board[0][2]);
                printf("- - -\n");
                printf("%c %c %c\n", board[1][0], board[1][1], board[1][2]);
                printf("- - -\n");
                printf("%c %c %c\n", board[2][0], board[2][1], board[2][2]);
                printf("- - -\n");
                printf("\nPlayer %d wins!\n", player);
                printf("\n");
                return 0;
            }
        }
        if (board[0][0] == mark && board[1][1] == mark && board[2][2] == mark)
        {
            printf("\nPlayer %d wins!\n", player);
            return 0;
        }
        if (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark)
        {
            printf("\nPlayer %d wins!\n", player);
            return 0;
        }

        // Checking for tie situation
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                if (board[i][j] == ' ')
                {
                    break;
                }
            }
            if (board[i][j] == ' ')
            {
                break;
            }
        }
        if (i == 3 && j == 3)
        {
            printf("\nTie game!\n");
            return 0;
        }

        // Switch to other player
        player = (player == 1) ? 2 : 1;
    }

    return 0;
}

int main()
{ // part1
    letter_frequency();

    // part2
    char color1, color2;
    printf("Enter a Color 1 (r,g,b,y,o) : ");
    scanf(" %c", &color1);
    printf("Enter a Color 2 (r,g,b,y,o) : ");
    scanf(" %c", &color2);
    enum Color c1, c2;
    switch (color1)
    {
    case 'r':
        c1 = RED;
        break;
    case 'g':
        c1 = GREEN;
        break;
    case 'b':
        c1 = BLUE;
        break;
    case 'y':
        c1 = YELLOW;
        break;
    case 'o':
        c1 = ORANGE;
        break;
    default:
        printf("Invalid input for Color 1\n");
        return 1;
    }
    switch (color2)
    {
    case 'r':
        c2 = RED;
        break;
    case 'g':
        c2 = GREEN;
        break;
    case 'b':
        c2 = BLUE;
        break;
    case 'y':
        c2 = YELLOW;
        break;
    case 'o':
        c2 = ORANGE;
        break;
    default:
        printf("Invalid input for Color 2\n");
        return 1;
    }
    enum Color mixColor = mixColors(c1, c2);
    printf("Mixed Color : ");
    switch (mixColor)
    {
    case RED:
        printf("RED ");
        break;
    case GREEN:
        printf("GREEN ");
        break;
    case BLUE:
        printf("BLUE ");
        break;
    case YELLOW:
        printf("YELLOW ");
        break;
    case ORANGE:
        printf("ORANGE ");
        break;
    }
    printf("[%g,%g,%g]\n", colors[mixColor][0], colors[mixColor][1], colors[mixColor][2]);

    // part 3
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};

    gameplay(board);

    return 0;
}
