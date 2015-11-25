/* Mastermind by Michael Burdick
* This is an extremely simple version of the popular game Mastermind, which involves the computer randomly generating a series of four "pegs", all either white or black.
* The user then gets an alloted number of guesses to try and guess the series, referred to as the code. The only feedback the user recieves is two numbers: the number
* of pegs they have perfectly correct, and the number of pegs that are the right color, but in the wrong spot.
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

bool validGuess (string guess){ //validGuess is a simple function which determines if a player's guess is even in the realm of possible answers
	if(guess.length() != 8){//if the player inputted a guess that isn't four characters long, it's already wrong, so reject it
		return false;
	}
	for(int j = 0; j < 8; j++){//if the guess is four letters long, go through it letter by letter and make sure each letter is a w, W, b, or B
		if(toupper(guess[j]) != 'W' && toupper(guess[j]) != 'B'){
			return false;//if any letter of the guess isn't one of those four, the guess is invalid
		}
	}

	return true;//if we pass both of these checks, we have ourselves a valid guess from the player, so let the main method know
	
}

string upperCaseifier(string s){//really simple function to make every letter of an input string uppercase
	for(int x = 0; x < s.length(); x++){
		s[x] = toupper(s[x]);
	}

	return s;
}

bool hintGenerator(string guess, char* solution, int numW, int numB){//hintGenerator both creates the hints that the codebreaker will recieve, and also checks to see if the codebreaker has guessed the code
	bool exactlyAlike = true;//assume the guess is in fact correct until proven otherwise
	int rightColorAndPlacement = 0;//and also keep running totals of the number of pegs that are right color/right spot, and those that are right color/wrong spot, for use in the hints
	int rightColorWrongSpot = 0;
	for(int i = 0; i < 8; i++){//for every letter of the guess
		if(guess[i] == solution[i]){//check to see if it matches with the corresponding peg in the code. If it does
			rightColorAndPlacement++;//increment the number of perfectly right pegs by one
			if(guess[i] == 'W' && numW > 0){//We also need to keep track of if the perfectly correct peg is white or black, for use in the else statement
				numW--;
			}
			else if(guess[i]== 'B' && numB > 0){
				numB--;
			}
		}
		else{//if the peg in the guess and the corresponding peg in the code are not the same
			exactlyAlike = false;//then we have found a contradiction to the two codes being the same, and change exactlyAlike to reflect that
			if(guess[i] == 'W' && numW > 0){//then, what we do is we check to see if there are pegs of the same color as the incorrect guess peg somewhere in the code
				rightColorWrongSpot++;//if there are, then we need to keep track of that for the hint
				numW--;//this is why we had to keep track of the color of perfectly guessed pegs: to ensure that those pegs don't muddle this result
			}
			else if(guess[i]== 'B' && numB > 0){
				rightColorWrongSpot++;
				numB--;
			}
		}


	}

	cout << "You have " << rightColorAndPlacement << " pegs of the correct color and position." << endl;//Then we produce our two hints for the player
	cout << "You have " << rightColorWrongSpot << " pegs that are the right color, but in the wrong position." << endl << endl;

	return exactlyAlike;//and return whether or not their guess was spot-on
}


void main(){
	string choice = "";

	cout << "Welcome to Mastermind." << endl;
	
	cout << "Please select a difficulty level:" << endl;
	cout << "1 = Easy. 2 = Medium. 3 = Hard." << endl;//We greet the player, then prompt them to select a difficulty
	cin >> choice;

	while (choice != "1" && choice != "2" && choice != "3"){//if the choice that they select isn't a valid one, then we slap them on the wrist and ask again
		cout << "Invalid choice. Please enter a 1, 2, or 3: ";
		cin >> choice;
	}

	/* Most of my input validation takes the above form, where a single cin statement is followed by a while loop, with the conditional "as long as input isn't this or this or this or this"
	* I'm not 100% a fan of this, but it's a little cleaner to read than a do-while loop, because were I to use a do-while loop, I'd need another conditional inside to determine whether or not 
	* to show an error message. This way, everything involving the user inputting something correct is all nice and snug together in a single block of code
	*/

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
	}//The difficulty chosen determines the number of guesses the codebreaker has. We also acknowledge what difficulty option the player selected

	string learn = "";
	bool showTutorial = false;
	bool valid = false;
	
	cout << "Would you like to know how to play Mastermind? (y/n)" << endl;//there's a chance that the player actually has no idea how to play mastermind, so we offer to teach them
	cin >> learn;

	while(learn != "y" && learn != "Y" && learn != "n" && learn != "N"){//obviously, we have to validate this input, as well as reprompting every time the user gets it wrong
		cout << "Invalid input. Enter either 'y' or 'n': ";
		cin >> learn;
	}

	if (learn == "y" || learn == "Y"){//if the user wants a tutorial, we flip the switch to let them see it
		showTutorial = true;//if they don't due to the implementation, we actually don't have to do anything
	}

	if (showTutorial){
		cout << "I will generate a random sequence of pegs, 8 long." << endl;
		cout << "Each peg in the sequence is either black (B) or white (W)" << endl;
		cout << "You have " << guesses << " guesses to try and determine this sequence." << endl;
		cout << "Every time you guess, I'll tell you a bit of information." << endl;
		cout << "Specifically, I'll tell you how many pegs you have of the right color AND location" << endl;
		cout << "As well as how many pegs you have that are the right color, but wrong location." << endl;
		cout << "You'll input your guesses as a sequence of the letters B and W (ex. BBWW)." << endl;
		cout << "If you don't guess the sequence within your alloted guesses, I win!" << endl << endl;
	}//This is the admittedly verbose tutorial

	char solution [8];//Now we're hitting the game itself. First we initialize a solution character array of length 4
	bool repeat = true;//we also set up repeat, which will determine for how long players want to keep playing the game
	do{	//I'm using a do-while loop here to contain the game, since I know players will want to play at least once.
		int numBlack = 0;
		int numWhite = 0;//Set up counter variables to hold the number of black pegs and white pegs in the solution.
		srand(time(0));//Also, seed our random number generator using the time.

		for (int i = 0; i < 8; i++){//for every character in our code
			if(rand() % 2 == 0){//generate a random number, then determine if it's odd or even
				solution[i] = 'W';//using that data, we randomly assign every peg in the solution array to be white or black
				numWhite++;//we also adjust our counter variables accordingly
			}
			else{
				solution[i] = 'B';
				numBlack++;
			}
		}

		string guess;
		bool correct = false;
		int k = 0;
		//Now that the code has been generated by our codemaker, time to let the player have at it
		while (k < guesses && !correct){//this while loop is basically a for loop that players can break out of early if they guess the code
			//I guess a break statement would have allowed me to just use a for loop, but I like having all of the break conditions right there in my loop header
			cout << "Enter a guess: ";//Prompt the user for a guess
			cin >> guess;
			while (!validGuess(guess)){//Once we have a guess, we validate it using the validGuess function. If it's not valid, we keep prompting until we get one that is
				cout << "Invalid input. Please enter a four-character input consisting solely of B and W" << endl;
				cout << "Enter a guess: ";
				cin >> guess;
			}

			correct = hintGenerator(upperCaseifier(guess), solution, numWhite, numBlack);//now, take an all-uppercase version of the guess, the codemaker's code, and the total white and black pegs in the code
			//and run them through hintGenerator to create the hints, and also to determine if the codebreaker has successfully broken the code

			if(correct){//If they're right, then go ahead and tell them they one
				cout << "That's exactly it, you win!" << endl;
			}
			else{//If they're not right, let them know, and tell them how many guesses they have left
				cout << "That's not it, sadly! You have " << guesses-k << " guesses left!" << endl;
			}
			
			k++;//increment the iterator for our weird, janky for-loop
		}

		if(!correct){//if we ended up breaking out of the while loop due to running out of guesses, instead of by guessing correctly, print the loss statement
			cout << "You're all out of guesses! I win!" << endl;
		}

		cout << "Play again? (y/n) "; //Now that the game is complete, prompt the user to see if they want to play again
		string repeatchoice = "";
		cin >> repeatchoice;
		
		while(repeatchoice != "y" && repeatchoice != "Y" && repeatchoice != "n" && repeatchoice != "N"){//like all other user input, let's go ahead and validate this too
			cout << "Invalid input. Enter either 'y' or 'n': ";
			cin >> repeatchoice;
		}

		if(repeatchoice == "n" || repeatchoice == "N"){
			repeat = false;
		}//if our player says they don't wanna play anymore, we reverse repeat so we can break our do-while loop. If they do wanna continue, we do nothing, and let the loop...well, loop.

	}while(repeat);
}