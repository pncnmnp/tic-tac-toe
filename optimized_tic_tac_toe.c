/*
 *<Tic_Tac_Toe - A basic tic tac toe game using minimax algorithm>
 *Copyright (C) 2018  Parth Parikh
 *
 *This program is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.
 *
 *This program is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.
 *
 *You should have received a copy of the GNU General Public License
 *along with this program.  If not, see <https://www.gnu.org/licenses/>.	
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int won = 0; /* Winning condition */

/* There won't be any double evaluation in a Tic Tac Toe game ;-) */
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) > (b)) ? (b) : (a))

/* For boolean values */
typedef enum { false, true } bool;

/* For player moves */
struct move {
	int x;
	int y;
}move;

/* Moves are defined as: */
char computer = 'X';
char user = 'O';

void rules () {	

	/* The basic instructions: */
	printf("TIC TAC TOE\n");
	printf("MULTIPLAYER GAME\n");
	printf("Rules are simple, 3 X's or O's in a row (vertical, horizontal and diagonal)\nEG: X wins belows\n");	
	printf("X\tO\tO\nX\tX\tX\nO\tO\tX\n");
}

void board_initialization (char board[3][3]) {

	/* To initialize every cell as '_' */
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i][j] = '_';
		}
	}
} 

void check_board (char board[3][3]) {	
	
	int i=0, j=0;

	char move[2] = {'X','O'};

	/* Checking all the 8 win conditions */
	for (int cntr = 0; cntr < 2; cntr++) {	
		if (((board[i][j]==move[cntr]) && (board[i][j+1]==move[cntr]) && (board[i][j+2]==move[cntr])) || ((board[i][j]==move[cntr]) && (board[i+1][j]==move[cntr]) && (board[i+2][j]==move[cntr])) || ((board[i][j]==move[cntr]) && (board[i+1][j+1]==move[cntr]) && (board[i+2][j+2]==move[cntr])) || ((board[i][j+2]==move[cntr]) && (board[i+1][j+1]==move[cntr]) && (board[i+2][j]==move[cntr])) || ((board[i][j+2]==move[cntr]) && (board[i+1][j+2]==move[cntr]) && (board[i+2][j+2]==move[cntr])) || ((board[i][j+1]==move[cntr]) && (board[i+1][j+1]==move[cntr]) && (board[i+2][j+1]==move[cntr])) || ((board[i+1][j]==move[cntr]) && (board[i+1][j+1]==move[cntr]) && (board[i+1][j+2]==move[cntr])) || ((board[i+2][j]==move[cntr]) && (board[i+2][j+1]==move[cntr]) && (board[i+2][j+2]==move[cntr]))) {		
			printf("\n%c WON\nCONGRATS %c\n", move[cntr], move[cntr]);
			won++;
			break;
		}
	}	
}

int is_valid (int move_x, int move_y, char board[3][3]) {
	
	/* Out-of-the-grid condition: */	
	if (move_x > 2 || move_x < 0 || move_y > 2 || move_y < 0) 
		return false;

	/* To prevent illegal move */
	if (board [move_x][move_y] == 'O' || board [move_x][move_y] == 'X')
		return false;

	/* Nothing illegal */
	return true;
}

void print_board (char board[3][3]) {	
	
	for(int i=0;i<3;i++) {
		for(int j=0;j<3;j++) {
			printf("%c\t",board[i][j]);
		}
		printf("\n");
	}		
}

int move_verification (char board[3][3]) {
	
	/* To check if any more moves can be made */
	for (int i = 0; i < 3; i++) 
		for (int j = 0; j < 3; j++) 
			if (board[i][j] == '_')
				return true;
	return false;
}

int evaluation (char board[3][3]) {

	/* checking ROWS for a victory */
	for (int row = 0; row < 3; row++) {
		if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
			if (board[row][0] == computer)
				return +10;
			else if (board[row][0] == user)
				return -10;
		}
	}

	/* checking COLUMNS for a victory */
	for (int col = 0; col < 3; col++) {
		if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
			if (board[0][col] == computer)
				return +10;
			else if (board[0][col] == user)
				return -10;
		}
	}

	/* checking DIAGONALS for a victory */
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
		if (board[0][0] == computer)
			return +10;
		else if (board[0][0] == user)
			return -10;
	}

	if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
		if (board[0][2] == computer)
			return +10;
		else if (board[0][2] == user)
			return -10;
	}

	/* None of the above conditions are matched */
	return 0;
}

int minimax (char board[3][3], int depth, int isMax) {

	/* Check for the terminal points ( will return 0 if the depth is yet to be reached ) */
	int score = evaluation(board);

	/* We will first check whether the game can be terminated with the current possible score */
	/* If maximizer has won */
	if (score == 10)
		return score;

	/* If minimizer has won */
	if (score == -10)
		return score;

	/* If no more moves can be made */
	if (move_verification(board) == false)
		return 0;

	/* If it is maximizer's move
	 * Remember that the goal of maximizer is to attain the highest possible score */
	if (isMax == 1) {

		/* Initialize a lowest point of comparision */
		int best = -1000;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j]=='_') {
					
					board[i][j] = computer; /* Make your move */
					
					/* We are traversing one more step in the tree and are making minimizer play the next move */
					best = max(best, minimax(board,depth+1,0)); /* Find the maximizer's move */
					
					board[i][j] = '_'; /* Undo your move */
				}
			}
		}
		return best; 
	}

	/* If it is minimizer's move 
	 * Remember that the goal of minimizer is to attain the lowest possible score */
	else {

		/* Initialize a lowest point of comparision */
		int best = 1000;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j]=='_') {
					
					board[i][j] = user; /* Make your move */
					
					/* We are traversing one more step in the tree and are making maximizer play the next move */
					best = min(best, minimax(board,depth+1,1)); /* Find the minimizer's move */
					
					board[i][j] = '_'; /* Undo your move */
				}
			}
		} 
		return best; 
	}
}

void computer_plays (char board[3][3]) {

	/* Initialize the computer moves */
	struct move play;
	play.x = -1;
	play.y = -1;

	/* Initialize a lowest point of comparision */
	int best_val = -1000;

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {

			/* If a move is valid, try it */ 
			if (board[i][j] == '_') {
				
				board[i][j] = computer; /* Make the move */

				int move_val = minimax(board, 0, 0); /* Find the value from the minimax function */

				board[i][j] = '_'; /* Undo the move */

				/* If the current move is better than the best move, then change the best move */
				if (move_val > best_val) {
					best_val = move_val;
					play.x = i;
					play.y = j;
				}
			}
		}
	}

	/* Finally make the Computer Move */
	board[play.x][play.y] = computer;
}

void user_plays (char board[3][3]) {

	/* Initialize the user moves */
	struct move play;
	play.x = -1;
	play.y = -1;

	/* Accept the moves from user */
	printf("\nEnter the x and y co-ordinate of your move: ");
	scanf("%d%d", &play.x, &play.y);

	/* Check for validity of the move */
	if (is_valid(play.x, play.y, board) == true) 
		board[play.x][play.y] = user;

	else {
		printf("Not A Valid Move!\n");
		user_plays(board);
	}
}

void computer_move (char board[3][3]) {

	/* A collection of computer's calls */
	printf("\nComputer is playing it's move ...\n");
	computer_plays(board);
	check_board(board);	
	print_board(board);
}

void user_move (char board[3][3]) {

	/* A collection of user's calls */
	user_plays(board);
	check_board(board);
	print_board(board);
}

int toss (void) {

	printf("Time for the toss: \n");
	
	/* A random number between 0 and 1 is accepted as the toss and returned back.
	 * Heads or Tails is decided by the computer. */
	srand(time(NULL));
	int toss = rand() % 2;

	if (toss == 0)
		printf("User wins the toss ! Play first MATE !\n");

	else if (toss == 1)
		printf("Computer wins the toss ! Let me begin by kicking your ass !\n");

	return toss;
}

void gameplay (char board[3][3], int toss) {

	/* Win condition should be 1 or moves should not be left to terminate the loop */
	while (won != 1 && move_verification(board) == true) {

		/* Checks for user's chance to play */
		if (toss == 0) {
			user_move(board);
			if (won == 1)
				break;
			toss = 1;
			continue;
		}		

		/* Checks whether any move is left on board */
		else if (move_verification(board) == false) {
			printf("It's a draw !\n");
			break;
		}

		/* Checks for computer's chance to play */
		else if (toss == 1) {
			computer_move(board);
			if (won == 1)
				break;
			toss = 0;
		}
	}

	/* checks whether computer played the last move */
	if (toss==0)
		printf("It's a draw !\n");
}

int main (void) {
	
	char board[3][3]; /* Tic Tac Toe board */	
	rules();
	board_initialization(board);
	print_board(board);
	gameplay(board, toss());

	return 0;
}
