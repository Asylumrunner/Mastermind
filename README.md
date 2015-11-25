# Mastermind
A simple C++ implementation of the classic board game Mastermind.

## What is Mastermind?
Mastermind is a classic board game of codebreaking for two players (or, as this program shows, a player and a computer). There are two players, the *codemaker* and the *codebreaker*.

At the start of a game of Mastermind, the codemaker establishes a code, usually composed of colored pegs in a certain order. Only the codemaker knows this code.

The codebreaker then has a set number of turns to try and guess the codemaker's code. For every guess that the codebreaker makes, the codemaker must respond by telling them how many of their pegs are of the right color AND in the right spot, as well as how many pegs are of the right color, but NOT in the right spot.

For example, say this is the codemaker's code:

	BWBW

This represents a black peg, a white peg, a black peg, and a white peg, in that order. Now, let's say our codebreaker's first guess looks like this:

	WWBB

The codebreaker has the second and third pegs precisely correct. However, the other two pegs are wrong. The key observation, though, is that those incorrect pegs do exist elsewhere in the code: the wrong black peg exists in the first position, and the wrong white peg exists in the third position.

Thus, our codemaker might respond like this:

	Two perfectly correct
	Two right color, wrong spot

This is all the information the codemaker has to give. They do not have to say which pegs fall into which categories. It is up to the codebreaker to use logical thinking to figure it out.

Now, let's say instead of the previous example, the codebreaker guesses this:

	BBBB

Once again, two pegs of the codebreaker's guess are exactly right: the first and third pegs this time. However, not only are the other two pegs the wrong color, there aren't any spots in the code where they *would* be correct. So, our codemaker might respond like this:

	Two perfectly correct
	None right color, wrong spot

This process continues until the codebreaker successfully guesses the code, in which case the codebreaker wins, or until the codebreaker runs out of guesses, in which case the codemaker wins.

Learn more about Mastermind [here](https://en.wikipedia.org/wiki/Mastermind_(board_game))

## This Implementation of Mastermind
This particular implementation of the game is extremely simple. Each peg in the code can only be one of two colors, instead of the normal six. As a result, there are 2^8, or 256 codes. Our possibility space is far smaller than your typical game of Mastermind (which has 1296 possible codes). The objective of this program is not to make an unbreakable codemaking program. Rather, it is simply to demonstate the concept of the game