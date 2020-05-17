#include <iostream>
#include <string>
#include <vector>
#include "mastermind.hpp"

using namespace std;

bool over = false;

int main()
{
	Mastermind game;
	do
	{
		int a, b, c, d;
		vector<int> guess;
		pair<int, int> whiteBlack;
		bool valid_guess = true;
		game.print_board();
		do
		{
			cout << "Make Guess: ";
			cin >> a >> b >> c >> d;
			guess = { a,b,c,d };
			whiteBlack = game.make_guess(guess);
			if (whiteBlack == pair<int,int>(-1,-1) )
			{
				valid_guess = false;
				cout << "Colors out of range or improper input... Try again..." << endl;
			}
			else if (whiteBlack == pair<int, int>(-2, -2))
			{
				system("CLS");
				cout << "Out of turns... Here's the answer: " << endl;
				game.print_board();
				game.print_answer();
				over = true;
			}
			else
			{
				system("CLS");
			}
		} while (!valid_guess);
		if (whiteBlack.second == 4)
		{
			cout << "You win!" << endl;
			game.print_board();
			game.print_answer();
			over = true;
		}
	} while (!over);

	cin.ignore();
	cin.get();
	return 0;
}