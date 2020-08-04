#include <iostream>
#include <string>
#include <utility>
#include <cctype>

using namespace std;

//Checks for winner
char winnerCheck(char board[][3]){
	//Checking rows
	for(int i = 0; i < 3; i++){
		if(board[i][0] != '.' && board[i][0] == board[i][1] && board[i][0] == board[i][2]){
			return board[i][0];
		}
	}

	//Checking columns
	for(int i = 0; i < 3; i++){
		if(board[0][i] != '.' && board[0][i] == board[1][i] && board[0][i] == board[2][i]){
			return board[0][i];
		}
	}
		
	//Checking diagonal 1
	if(board[0][0] != '.' && board[0][0] == board[1][1] && board[0][0] == board[2][2]){
		return board[0][0];
	}

	//Checking diagonal 2
	if(board[0][2] != '.' && board[0][2] == board[1][1] && board[0][2] == board[2][0]){
		return board[0][2];
	}

	//Returning NULL if there is no winner
	return '\0';
}

//Prints the game board
void printBoard(char board[][3]){
	cout << "\n              || # 1 2 3 ||\n";
	for(int i = 0; i < 3; i++){
		cout << "              || " << (char)(i + 'a') << " ";
		for(int j = 0; j < 3; j++){
			cout << board[i][j] << " ";
		}
		cout << "||\n";
	}
	cout << "\n";
}

//Chooses the best move for the computer
int decide(char board[][3], char computer, char player, char whoPlays, int turn){
	char winner = winnerCheck(board);

	if(winner == computer){
		return 10;
	}

	else if(winner == player){
		return -10;
	}

	else if(turn == 10){
		return 0;
	}

	//Maximize the possible score if its the turn of computer
	if(whoPlays == computer){
		int score = -1000;
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				if(board[i][j] == '.'){
					board[i][j] = computer;
					int tempValue = decide(board, computer, player, player, turn + 1);
					board[i][j] = '.';
					score = max(score, tempValue);
				}
			}
		}

		return score - turn; //Subtracts depth to use less number of moves for maximizing
	}

	//Minimize the possible score if its the turn of player
	else{
		int score = 1000;
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				if(board[i][j] == '.'){
					board[i][j] = player;
					int tempValue = decide(board, computer, player, computer, turn + 1);
					board[i][j] = '.';
					score = min(score, tempValue);
				}
			}
		}

		return score + turn; //Adds depth to use less number of moves for minimizing
	}
}

//Returns the best possible move for computer
pair<int, int> computerTurn(char board[][3], char computer, char player, int turn){
	pair<int, pair<int, int>> bestScore;
	bestScore.first = -1000;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(board[i][j] == '.'){
				board[i][j] = computer;
				int tempValue = decide(board, computer, player, player, turn + 1);
				board[i][j] = '.';
				if(tempValue > bestScore.first){
					bestScore.first = tempValue;
					bestScore.second.first = i;
					bestScore.second.second = j;
				}
			}
		}
	}

	return {bestScore.second.first, bestScore.second.second};
}

int main(){
	char board[3][3] = {{'.', '.', '.'}, {'.', '.', '.'}, {'.', '.', '.'}}, row, winner, player = '\0', computer;
	int column = 8;

	cout << "\n=========================================\n";
	cout << "        Unbeatable Tic Tac Toe AI        \n";
	cout << "=========================================\n\n";

	while(true){
		cout << "=========================================\n";
		cout << "Select your character (X or O): ";
		cin >> player;
		cout << "=========================================\n";
		player = toupper(player);
		if(player != 'O' && player != 'X'){
			cout << "\nYou can't select this character, please try again.\n\n";
		}
		else{
			break;
		}
	}

	computer = player == 'X' ? 'O' : 'X';

	printBoard(board);

	for(int turn = 1; turn <= 9; turn++){
		if((turn % 2 == 1 && computer == 'X') || (turn % 2 == 0 && computer == 'O')){
			pair<int, int> computerMove = computerTurn(board, computer, player, turn);
			board[computerMove.first][computerMove.second] = computer;
			cout << "=========================================\n";
			cout << "Move of the computer ( " << computer << " ): " << (char)(computerMove.first + 'a') << computerMove.second + 1 << "\n";
			cout << "=========================================\n";
		}

		else{
			while(true){
				string playerMove;
				cout << "=========================================\n";
				cout << "Move of the player ( " << player << " ): \nType row and column (e.g. \"b2\"): ";
				cin >> playerMove;
				if(isalpha(playerMove[0]) && isdigit(playerMove[1])){
					row = tolower(playerMove[0]);
					column = playerMove[1] - '0';
				}
				cout << "=========================================\n";
				if((row >= 'a' && row <= 'c') && (column >= 1 && column <= 3) && (board[row - 'a'][column - 1] == '.')){
					break;
				}
				else{
					cout << "\nYou can't place here, please try again.\n\n";
					cout << "=========================================\n";
					printBoard(board);
				}
			}
			board[row - 'a'][column - 1] = player;
		}

		printBoard(board);
		winner = winnerCheck(board);

		if(winner != '\0'){
			cout << "=========================================\n";
			cout << "Winner is " << (winner == player ? "player(" : "computer(") << winner << ")\n";
			cout << "=========================================\n";
			return 0;
		}
	}
	cout << "=========================================\n";
	cout << "It's a draw.\n";
	cout << "=========================================\n";
}
