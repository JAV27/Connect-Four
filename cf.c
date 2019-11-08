#include <stdio.h>

//Paramaters: 
//  gameState- multidimensional char array representing the state of the game
//Function: 
//  prints out the board in the console
void printBoard(char gameState[7][8]);

//Paramaters
//  gameState- multidimensional char array representing the state of the game
//  row and column- the corresponding row and column on the board where the peice is to be placed
//  turn- which turn is currently being played. Allows for function to correctly use X or O
//  gameHistory- log of every move up until that point
//  breakIndex- the number of moves that have been made over the course of the game
//Function: 
//  updates the board with an X or O at the right row and column 
void updateBoard(char gameState[7][8], int row, int col, int turn, char gameHistory[42], int breakIndex);

//Paramaters:
//  gameState- multidimensional char array representing the state of the game
//  turn- which turn is currently being played
//  gameHistory- log of every move up until that point
//  breakIndex- the number of moves that have been made over the course of the game
//Function: 
//  Prompts the player for a column to place there peice and determines the row and column where it would end up
void playerTurn(char gameState[7][8], int turn, char gameHistory[42], int breakIndex);

//Parameters: 
//  gameState- multidimensional char array representing the state of the game
//  turn- which turn is currently being played
//  gameHistory- log of every move up until that point
//  breakIndex- the number of moves that have been made over the course of the game
//Function: 
//  Determines whether the player has a chain of 3 anywhere in the game and blocks it if possible
//Returns:
//  1: If the AI blocks the player
//  0: If it does not
int AIDefense(char gameState[7][8], int turn, char gameHistory[42], int breakIndex);

//Paramters: 
//  gameState- multidimensional char array representing the state of the game
//  turn- which turn is currently being played
//  gameHistory- log of every move up until that point
//  breakIndex- the number of moves that have been made over the course of the game
//Function: 
//  Determines whether the AI has a chain of 3 anywhere and if possible places a piece to win
//Returns:
//  1: If the AI places a game winning piece
//  0: It does not
int AIGameWinner(char gameState[7][8], int turn, char gameHistory[42], int breakIndex);

//Parameters: 
//  gameState- multidimensional char array representing the state of the game
//  turn- which turn is currently being played
//  gameHistory- log of every move up until that point
//  breakIndex- the number of moves that have been made over the course of the game
//Function:
//  First tries to make a game winning move for the AI. If there is none it then makes sure to block any 
//  winning move of the player. If there are none then it fills out the board starting with column A and
//  moving right
void AITurn(char gameState[7][8], int turn, char gameHistory[42], int breakIndex);

//Paramters:
//  gameState- multidimensional char array representing the state of the game
//Function:
//  Checks whether either player has 4 in a row in the horizontal direction
//Returns:
//  1: If one of the players does
//  0: If neither player does
int horizontalCheck(char gameState[7][8]);

//Paramters:
//  gameState- multidimensional char array representing the state of the game
//Function:
//  Checks whether either player has 4 in a row in the vertical direction
//Returns:
//  1: If one of the players does
//  0: If neither player does
int verticalCheck(char gameState[7][8]);

//Paramters:
//  gameState- multidimensional char array representing the state of the game
//Function:
//  Checks whether either player has 4 in a row in the diagonal direction
//Returns:
//  1: If one of the players does
//  0: If neither player does
int diagCheck(char gameState[7][8]);

//Paramters:
//  gameState- multidimensional char array representing the state of the game
//Function:
//  Checks whether either player has won the game
//Returns:
//  1: If one of the players does
//  0: If neither player does
int checkWin(char gameState[7][8]);

//The function where the game is ran
void main() {
    //The initial state of the game board
    char gameState[7][8] = {
        {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G'},
        {'6', '-', '-', '-', '-', '-', '-', '-'},
        {'5', '-', '-', '-', '-', '-', '-', '-'},
        {'4', '-', '-', '-', '-', '-', '-', '-'},
        {'3', '-', '-', '-', '-', '-', '-', '-'},
        {'2', '-', '-', '-', '-', '-', '-', '-'},
        {'1', '-', '-', '-', '-', '-', '-', '-'},
    };

    //array of all past moves of the game
    char gameHistory[42];
    //The amount of game moves made over the course of the game
    int breakIndex = 0;

    //Whether the player chose to go first or second
    int playerGoesFirst;
    
    printf("Welcome to Josh's Connect Four\n");
    printf("------------------------------\n");

    while((playerGoesFirst != 0) && (playerGoesFirst != 1)) {
        printf("Would you like to go first or second? Type 0 for first, 1 for second\n");
        scanf("%i", &playerGoesFirst);
        if((playerGoesFirst != 0) && (playerGoesFirst != 1)) {
            printf("Sorry that was an invalid input.\n");
        }   
    }

    //Goes to 42 since there are at most 42 turns that will be played before the board fills
    for(int i=0;i<42;i++) {        
        if(i%2 == playerGoesFirst) {
            playerTurn(gameState, i%2, gameHistory, breakIndex); 
            breakIndex++;  
        } else {
            printf("The AI will now make its move:\n");
            AITurn(gameState, i%2, gameHistory, breakIndex);
            breakIndex++;
        }

        if(checkWin(gameState)) {
            if(i%2 == playerGoesFirst) {
                printf("You Won!\n");
            } else {
                printf("The AI Won!\n");
            }

            printf("All the game moves:\n");

            for(int i=0; i<breakIndex; i++) {
                printf("%c", gameHistory[i]);
            }

            printf("\n");

            return;
        }

    }

    //If after the board fills no one won it must be a tie
    printf("The Game was a Tie!");
    return;
}

void printBoard(char gameState[7][8]) {
    for(int i=0;i<7;i++) {
        for(int j=0;j<8;j++) {
            printf("%c ", gameState[i][j]);
        }
        printf("\n");
    }
}

void updateBoard(char gameState[7][8], int row, int col, int turn, char gameHistory[42], int breakIndex) {
    char charLog;

    if(col == 1) {
        charLog = 'A';
    } else if(col == 2) {
        charLog = 'B';
    } else if(col == 3) {
        charLog = 'C';
    } else if(col == 4) {
        charLog = 'D'; 
    } else if(col == 5) {
        charLog = 'E';
    } else if(col == 6) {
        charLog = 'F';
    } else if(col == 7) {
        charLog = 'G';
    }

    gameHistory[breakIndex] = charLog;

    if(turn == 0) {
        gameState[row][col] = 'X';
    } else if(turn == 1) {
        gameState[row][col] = 'O';
    }

    printBoard(gameState);
    return;
}

void playerTurn(char gameState[7][8], int turn, char gameHistory[42], int breakIndex) {
   
    //Infinite while loop makes sure the user must submit a valid column 
    while(1) {
        char col;
        int intCol = 0;

        while(intCol < 1 || intCol > 7) {
            printf("Type in the column you would like to place your piece. Please make sure to use caps.\n");
            //There is a space before the %c because otherwise the \n from the print gets rendered as the input
            scanf(" %c", &col);
            intCol = col - '0';
            intCol = intCol - 16;
            if(intCol < 1 || intCol > 7) {
                printf("Please enter a valid input\n");
            }
        }

        for(int i=6;i>0;i--) {
            if(gameState[i][intCol] == '-') {
                updateBoard(gameState, i, intCol, turn, gameHistory, breakIndex);
                return;
            }
        }

        //Still need to actually allow for funciton to repeat
        printf("Oops! That column is filled. Please pick another\n");
    }

}

int AIDefense(char gameState[7][8], int turn, char gameHistory[42], int breakIndex) {
   char oppChar;

    if(turn) {
        oppChar = 'X';
    } else {
        oppChar = 'O';
    }

    //Checks for horizontal blocks
    for(int i=1;i<7;i++) {
        for(int j=1;j<5;j++) {
            int charCounter = 0;
            int open = -1;

            for(int k=0;k<4;k++) {
                if(gameState[i][j+k] == oppChar) {
                    charCounter++;
                } else if(gameState[i][j+k] == '-') {
                    open = k;
                }
            }

            if(charCounter == 3 && open != -1) {
                if(i != 6) {
                    if(gameState[i+1][j+open] != '-') {
                        updateBoard(gameState, i, j+open, turn, gameHistory, breakIndex);
                        return 1;
                    }
                } else {
                    updateBoard(gameState, i, j+open, turn, gameHistory, breakIndex);
                    return 1;
                }
                
            }

        }

    }

    //Checks for vertical blocks
    for(int i=1;i<8;i++) {
        int numInARow = 0;

        for(int j=6;j>0;j--) {
            if(gameState[j][i] == oppChar) {
                numInARow++;
                if(numInARow == 3) {
                    if(gameState[j-1][i] == '-') {
                        updateBoard(gameState, j-1, i, turn, gameHistory, breakIndex);
                        return 1;
                    }
                    
                }
            } else {
                numInARow = 0;
            }
            
        }
    }

    //Checks for diagonal blocks

    //Right diagonal
    for(int i=1; i<7; i++) {
        for(int j=1; j<8; j++) {
            int charCounter = 0;
            int row = i;
            int col = j;
            int counter = 0;
            int open = -1;

            while(row > 0 && col < 8 && counter < 4) {
                if(gameState[i-counter][j+counter] == oppChar) {
                    charCounter++;
                } else if(gameState[i-counter][j+counter] == '-') {
                    open = counter;
                }
                counter++;               
            }

            if(charCounter == 3 && open != -1) {
                if(gameState[i-open+1][j+open] != '-') {
                    updateBoard(gameState, i-open, j+open, turn, gameHistory, breakIndex);
                    return 1;
                }         
            }

        }
    }

    //Left diagonal
    for(int i=1; i<7; i++) {
        for(int j=1; j<8; j++) {
            int charCounter = 0;
            int row = i;
            int col = j;
            int counter = 0;
            int open = -1;

            while(row > 0 && col > 0 && counter < 4) {
                if(gameState[i-counter][j-counter] == oppChar) {
                    charCounter++;
                } else if(gameState[i-counter][j-counter] == '-') {
                    open = counter;
                }
                counter++;               
            }

            if(charCounter == 3 && open != -1) {
                if(gameState[i-open+1][j-open] != '-') {
                    updateBoard(gameState, i-open, j-open, turn, gameHistory, breakIndex);
                    return 1;
                }
                
            }
        }
    }
    
    return 0;
}

int AIGameWinner(char gameState[7][8], int turn, char gameHistory[42], int breakIndex) {
    char AIchar;
    if(turn) {
        AIchar = 'O';
    } else {
        AIchar = 'X';
    }

    for(int i=1; i<7; i++) {
        for(int j=1; j<8; j++) {
            if(gameState[i][j] == AIchar) {
                //Check 3 in a row vertically
                if(gameState[i+1][j] == AIchar && gameState[i-1][j] == AIchar) {
                    if(i != 2 && gameState[i-2][j] == '-') {
                        updateBoard(gameState, i-2, j, turn, gameHistory, breakIndex);
                        return 1;
                    }               
                }                      

                //Check 3 in a row horizontally
                if(gameState[i][j-1] == AIchar && gameState[i][j+1] == AIchar) {        

                    if(j < 6) {
                        if(gameState[i+1][j+2] != '-' && gameState[i][j+2] == '-') {
                            updateBoard(gameState, i, j+2, turn, gameHistory, breakIndex);
                            return 1;   
                        } 
                    }     
                        
                    if(j > 2) {
                        if(gameState[i+1][j-2] != '-' && gameState[i][j-2] != '-') {
                            updateBoard(gameState, i, j-2, turn, gameHistory, breakIndex);
                            return 1;
                        }       
                    } 
                              
                }

                //Check 3 in a row right diagonal
                if(gameState[i-1][j+1] == AIchar && gameState[i+1][j-1] == AIchar) {
                    if(j < 6 && i > 2) {
                        if(gameState[i-1][j+2] != '-' && gameState[i-2][j+2] == '-') {
                            updateBoard(gameState, i-2, j+2, turn, gameHistory, breakIndex);
                            return 1;
                        }
                    }

                    if(j > 2 && i < 5) {
                        if(i == 4) {
                            if(gameState[i+2][j-2] == '-') {
                                updateBoard(gameState, i+2, j-2, turn, gameHistory, breakIndex);
                                return 1;
                            }
                        } 

                        if(gameState[i+3][j-2] != '-' && gameState[i+2][j-2] == '-') {
                            updateBoard(gameState, i+2, j-2, turn, gameHistory, breakIndex);
                            return 1;
                        }
                    }

                }

                //Check 3 in a row left diagonal
                if(gameState[i-1][j-1] == AIchar && gameState[i+1][j+1] == AIchar) {
                    if(i > 2 && j > 2) {
                        if(gameState[i-1][j-2] != '-' && gameState[i-2][j-2] == '-') {
                            updateBoard(gameState, i-2, j-2, turn, gameHistory, breakIndex);
                            return 1;
                        }
                    }

                    if(i < 5 && j < 6) {
                        if(i == 4) {
                            if(gameState[i+2][j+2] == '-') {
                                updateBoard(gameState, i+2, j+2, turn, gameHistory, breakIndex);
                                return 1;
                            }
                        }

                        if(gameState[i+3][j+2] != '-' && gameState[i+2][j+2] == '-') {
                            updateBoard(gameState, i+2, j+2, turn, gameHistory, breakIndex);
                            return 1;
                        }
                    }
                }

            }
        }
    }

    return 0;

}

void AITurn(char gameState[7][8], int turn, char gameHistory[42], int breakIndex) {

    if(AIGameWinner(gameState, turn, gameHistory, breakIndex)) {
        return;
    }

    if(AIDefense(gameState, turn, gameHistory, breakIndex)) {
        return;
    }

    for(int i=1; i<8; i++) {
        for(int j=6; j>0; j--) {
            if(gameState[j][i] == '-') {
                updateBoard(gameState, j, i, turn, gameHistory, breakIndex);
                return;
            }
        }
    }
}

int horizontalCheck(char gameState[7][8]) {
    for(int i=1;i<7;i++) {
        int numInARow = 1;
        char currChar = ' ';

        for(int j=1;j<8;j++) {
            if(gameState[i][j] == currChar) {
                numInARow++;
                if(numInARow >= 4) {
                    if(currChar != '-') {
                        return 1;
                    }
                }
            } else {
                numInARow = 1;
                currChar = gameState[i][j];
            }
        }
    }

    return 0;
}

int verticalCheck(char gameState[7][8]) {
    for(int i=1;i<8;i++) {
        int numInARow = 1;
        char currChar = ' ';

        for(int j=1;j<7;j++) {
            if(gameState[j][i] == currChar) {
                numInARow++;
                if(numInARow >= 4) {
                    if(currChar != '-') {
                        return 1;
                    }
                }
            } else {
                numInARow = 1;
                currChar = gameState[j][i];
            }
        }
    }

    return 0;
}

int diagCheck(char gameState[7][8]) {
    //Travels horizontally and checks for right diag
    for(int i=1;i<5;i++) {
        int numInARow = 1;
        char currChar = ' ';
        int row = 6;
        int col = i;

        //Keeps going up the diagonal until it hits the top row or rightmost column
        while(row > 0 && col < 8) {
            if(gameState[row][col] == currChar) {
                numInARow++;
                if(numInARow >= 4) {
                    if(currChar != '-') {
                        return 1;
                    }
                }

            } else {
                numInARow = 1;
                currChar = gameState[row][col];
            }
            row--;
            col++;
        }

    }

    //Travels horizontally and checks for left diag
    for(int i=7;i>3;i--) {
        int numInARow = 1;
        char currChar = ' ';
        int row = 6;
        int col = i;
        while(row > 0 && col > 0) {
            if(gameState[row][col] == currChar) {
                numInARow++;
                if(numInARow >= 4) {
                    if(currChar != '-') {
                        return 1;
                    }
                }
            } else {
                numInARow = 1;
                currChar = gameState[row][col];
            }

            row--;
            col--;
        }
    }

    //Travels vertically and checks for left diag
    for(int i=5;i>3;i--) {
        int col = 1;
        int row = i;
        char currChar = ' ';
        int numInARow = 1;

        while(row > 0) {
            if(gameState[row][col] == currChar) {
                numInARow++;
                if(numInARow >= 4) {
                    if(currChar != '-') {
                        return 1;
                    }
                }

            } else {
                numInARow = 1;
                currChar = gameState[i][col];
            }

            row--;
            col++;

        }

    }

    //Travels vertically and checks for right diag
    for(int i=5;i>3;i--) {
        int col = 7;
        int row = i;
        int numInARow = 1;
        char currChar = ' ';

        while(row > 0) {
            if(gameState[row][col] == currChar) {
                numInARow++;
                if(numInARow >= 4) {
                    if(currChar != '-') {
                        return 1;
                    }
                } 
            } else {
                currChar = gameState[row][col];
                numInARow = 1;
            }
            row--;
            col--;
        }

    }

    return 0;
}

int checkWin(char gameState[7][8]) {
    return (horizontalCheck(gameState) || verticalCheck(gameState) || diagCheck(gameState));
}
