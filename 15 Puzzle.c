#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>
#include <conio.h>
#include <time.h>

//// UTILITY FUNCTIONS ////

/* returns a random number between min and max
   inclusive */
int random(int min, int max)
{
    return rand() % (max + 1) + min;
}

/* checks if number is in array
   1 is yes, 0 is no */
int number_in_array(int number, int array[], int array_length)
{
    for (int i = 0; i < array_length; i++)
    {
        if (array[i] == number)
        {
            return 1;
        }
    }

    return 0;
}

/* quits process with exit msg
   usage: return quit(); */
int quit(void)
{

    // print exit message
    printf("\n\nQuitting...");

    // wait before quitting
    usleep(500000);
    
    // exit code
    return 0;
}

//// GRID FUNCTIONS ////

// grid
int grid[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}};

/* checks if grid is finished
   1 is yes, 0 is no */
int check_grid(void)
{

    // efficient or not? XD
    if (grid[0][0] == 1 && grid[0][1] == 2 && grid[0][2] == 3 && grid[0][3] == 4 && grid[1][0] == 5 && grid[1][1] == 6 && grid[1][2] == 7 && grid[1][3] == 8 && grid[2][0] == 9 && grid[2][1] == 10 && grid[2][2] == 11 && grid[2][3] == 12 && grid[3][0] == 13 && grid[3][1] == 14 && grid[3][2] == 15 && grid[3][3] == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* simulates a move 
   0 is up, 1 is down,
   2 is left, 3 is right */
void move(int direction)
{

    // blank coordinates
    int blank[2];

    // find blank in grid
    for (int i = 0; i < 4; i++)
    {
        for (int i2 = 0; i2 < 4; i2++)
        {
            if (grid[i][i2] == 0)
            {
                blank[0] = i;
                blank[1] = i2;
                break;
            }
        }
    }

    // move according to direction
    switch (direction)
    {

        // up
        case 0:
            if (blank[0] != 3)
            {
                grid[blank[0]][blank[1]] = grid[blank[0] + 1][blank[1]];
                grid[blank[0] + 1][blank[1]] = 0;
            }
            break;
        
        // down

        case 1:
            if (blank[0] != 0)
            {
                grid[blank[0]][blank[1]] = grid[blank[0] - 1][blank[1]];
                grid[blank[0] - 1][blank[1]] = 0;
            }
            break;
        
        // left
        case 2:
            if (blank[1] != 3)
            {
                grid[blank[0]][blank[1]] = grid[blank[0]][blank[1] + 1];
                grid[blank[0]][blank[1] + 1] = 0;
            }
            break;
        
        // right
        case 3:
            if (blank[1] != 0)
            {
                grid[blank[0]][blank[1]] = grid[blank[0]][blank[1] - 1];
                grid[blank[0]][blank[1] - 1] = 0;
            }
            break;
        
        // invalid input
        default:
            break;
    }
}

/* shuffles grid */
void shuffle_grid()
{
    
    // do 500 random moves
    for (int i = 0; i < 500; i++)
    {
        move(random(0, 3));
    }
}

//// CONSOLE FUNCTIONS ////

/* prints title and gameboard */
void print_title_and_gameboard(void)
{

    // print title
    printf("15 Puzzle\nMade by Te Du.\nVersion 1.0.0\nCopyright (c) 2024 \u03A3igma Studios\n\n");
    
    // loop through rows
    for (int i = 0; i <= 3; i++)
    {

        // print row border
        printf("\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\n");

        // loop through squares in row
        for (int i2 = 0; i2 <= 3; i2++)
        {

            // print border
            printf("\u2588 ");

            // if 0 (blank), print two spaces
            if (grid[i][i2] == 0)
            {
                printf("  ");
            }

            // otherwise, print digit
            else
            {

                // if digit is in right spot, use green text color
                if (grid[i][i2] == 4 * i + i2 + 1)
                {
                    printf("\033[32m");
                }

                // print digit
                printf("%d ", grid[i][i2]);

                // reset color anyway
                printf("\033[97m");
            }

            // print padding
            char gridNum[3];
            sprintf(gridNum, "%d", grid[i][i2]);
            if (strlen(gridNum) == 1)
            {
                printf(" ");
            }
        }

        // print right border
        printf("\u2588\n");
    }

    // print bottom border
    printf("\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\n");
}

/* clears screen and then prints
   title and gameboard */
void refresh_screen(void)
{

    // ANSI escape codes
    printf("\033[H\033[J");

    // print title & gameboard
    print_title_and_gameboard();
}

//// MAIN ////

/* main */
int main(void)
{
    // enable ansi codes - Thanks ChatGPT
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hOut, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, mode);

    // configure random generator seed
    srand(time(NULL));

    // configure unicode, text color and print title and gameboard
    setlocale(LC_ALL, "en_US.UTF-8");
    printf("\033[97m");
    print_title_and_gameboard();

    // ask user what to do: shuffle or exit
    printf("\nPress any key to shuffle or ESC to quit: ");
    int option = getch();
    if (option != 27)
    {

        // shuffle board
        printf("\nShuffling...");
        shuffle_grid();
        
        // refresh screen
        refresh_screen();

        // ask user to start game or exit
        printf("\nPress any key to start game or ESC to quit: ");
        option = getch();
        if (option != 27)
        {

            // number of moves
            int moves = 0;

            // prompt user for moves until board is solved
            while (check_grid() == 0) {

                // refresh screen
                refresh_screen();

                // prompt for move
                printf("\n%d moves\n\nUse arrow keys to move the tiles or press ESC to exit: ", moves);
                option = getch();

                // if it is a special key, getch returns special codes
                if (option == 0 || option == 224) {

                    // increment moves
                    moves++;

                    // read actual key
                    option = getch();

                    // change option to be compatible with move()
                    switch (option) {

                        // up arrow
                        case 72:
                            option = 0;
                            break;
                        
                        // down arrow
                        case 80:
                            option = 1;
                            break;
                        
                        // left arrow
                        case 75:
                            option = 2;
                            break;
                        
                        // right arrow
                        case 77:
                            option = 3;
                            break;
                        
                        // invalid input
                        default:
                            moves--;
                            break;
                    }

                    // move
                    move(option);
                }

                // if user wants to exit
                else if (option == 27) {
                    return quit();
                }
            }

            // fill in blank
            grid[3][3] = 16;

            // refresh screen
            refresh_screen();

            // print congratulation message
            printf("\nCongrats, you won!");
            usleep(1000000);
        }
    }

    // quit
    return quit();
}