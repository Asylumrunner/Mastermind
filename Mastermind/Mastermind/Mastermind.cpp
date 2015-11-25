#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

bool validGuess (string guess){
	if(guess.length() != 4){
		return false;
	}
	for(int j = 0; j < 4; j++){
		if(toupper(guess[j]) != 'W' && toupper(guess[j]) != 'B'){
			return false;
		}
	}

	return true;
	
}

string upperCaseifier(string s){
	for(int x = 0; x < s.length(); x++){
		s[x] = toupper(s[x]);
	}

	return s;
}

bool hintGenerator(string guess, char* solution, int numW, int numB){
	bool exactlyAlike = true;
	int rightColorAndPlacement = 0;
	int rightColorWrongSpot = 0;
	for(int i = 0; i < 4; i++){
		if(guess[i] == solution[i]){
			rightColorAndPlacement++;
			if(guess[i] == 'W' && numW > 0){
				numW--;
			}
			else if(guess[i]== 'B' && numB > 0){
				numB--;
			}
		}
		else{
			exactlyAlike = false;
			if(guess[i] == 'W' && numW > 0){
				rightColorWrongSpot++;
				numW--;
			}
			else if(guess[i]== 'B' && numB > 0){
				rightColorWrongSpot++;
				numB--;
			}
		}


	}

	cout << "You have " << rightColorAndPlacement << " pegs of the correct color and position." << endl;
	cout << "You have " << rightColorWrongSpot << " pegs that are the right color, but in the wrong position." << endl << endl;

	return exactlyAlike;
}


int main(){
	string choice = "";

	cout << "Welcome to Mastermind." << endl;
	
	cout << "Please select a difficulty level:" << endl;
	cout << "1 = Easy. 2 = Medium. 3 = Hard." << endl;
	
	do {
		cout << "Enter choice: ";
		cin >> choice;
	}while (choice != "1" && choice != "2" && choice != "3");

	int guesses;
	if (choice == "1"){
		guesses = 12;
		cout << "Easy selected!" << endl;
	}
	else if (choice == "2"){
		guesses = 10;
		cout << "Medium selected!" << endl;
	}
	else{
		guesses = 8;
		cout << "Hard selected!" << endl;
	}

	string learn = "";
	bool showTutorial = false;
	bool valid = false;
	
	cout << "Would you like to know how to play Mastermind? (y/n)" << endl;
	
	do{
		cin >> learn;
		if (learn == "y" || learn == "Y"){
			showTutorial = true;
			valid = true;
		}
		else if (learn == "n" || learn == "N"){
			valid = true;
		}
		else{
			cout << "Invalid input." << endl;
		}

	}while(!valid);

	if (showTutorial){
		cout << "I will generate a random sequence of pegs, 4 long." << endl;
		cout << "Each peg in the sequence is either black (B) or white (W)" << endl;
		cout << "You have " << guesses << " guesses to try and determine this sequence." << endl;
		cout << "Every time you guess, I'll tell you a bit of information." << endl;
		cout << "Specifically, I'll tell you how many pegs you have of the right color AND location" << endl;
		cout << "As well as how many pegs you have that are the right color, but wrong location." << endl;
		cout << "You'll input your guesses as a sequence of the letters B and W (ex. BBWW)." << endl;
		cout << "If you don't guess the sequence within your alloted guesses, I win!" << endl << endl;
	}

	char solution [4];
	bool repeat = true;
	do{	
		int numBlack = 0;
		int numWhite = 0;
		srand(time(0));

		for (int i = 0; i < 4; i++){
			if(rand() % 2 == 0){
				solution[i] = 'W';
				numWhite++;
			}
			else{
				solution[i] = 'B';
				numBlack++;
			}
		}

		string guess;
		bool correct = false;
		int k = 0;

		while (k < guesses && !correct){
			cout << "Enter a guess: ";
			cin >> guess;
			while (!validGuess(guess)){
				cout << "Invalid input. Please enter a four-character input consisting solely of B and W" << endl;
				cout << "Enter a guess: ";
				cin >> guess;
			}

			correct = hintGenerator(upperCaseifier(guess), solution, numWhite, numBlack);
			k++;
			if(correct){
				cout << "That's exactly it, you win!" << endl;
			}
			else{
				cout << "That's not it, sadly! You have " << guesses-k << " guesses left!" << endl;
			}
		}

		if(!correct){
			cout << "You're all out of guesses! I win!" << endl;
		}

		cout << "Play again? (y/n) ";
		string repeatchoice = "";
		cin >> repeatchoice;

	}while(repeat);

	return 0;
}