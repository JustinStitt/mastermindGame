#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>

using namespace std;

using matrix = vector<vector<int>>;

/*
	Mastermind board size is 12x4
	12 rows with 4 cols in each
	where each row is 1 turn
*/

const int ROWS = 12;
const int COLS = 4;
const int COLORS = 6;//number of colors to guess from

int turn = 0;

class Mastermind
{
private:
	matrix board;
	vector<int> answer;

	void gen_board(matrix& _board);
	void gen_answer(vector<int>& ans);
	pair<int, int> check_pins(vector<int> guess, vector<int> answer);
	vector<pair<int, int>> pins;
public:
	Mastermind();//default constructor

	pair<int, int> make_guess(vector<int>& guess);

	//display
	void print_board(matrix& _board);
	void print_board() { print_board(this->board); }
	void print_answer();
};

Mastermind::Mastermind()
{
	srand(time(0));//seed our PRNG with sys time
	gen_board(this->board);
	gen_answer(this->answer);
}

void Mastermind::gen_board(matrix& _board)
{
	for (int x{}; x < ROWS; ++x)
	{
		_board.push_back({});
		for (int y{}; y < COLS; ++y)
		{
			_board[x].push_back(0);
		}
	}
}

void Mastermind::gen_answer(vector<int>& ans)
{
	ans = { 3, 1, 4, 5 };
	/*ans.resize(4);
	int _r;
	for (int& cell : ans)
	{
		_r = rand() % COLORS + 1;//number of colors
		cell = _r;
	}*/
}

pair<int,int> Mastermind::make_guess(vector<int>& guess)
{
	if (turn > 11)//out of turns
		return pair<int, int>(-2, -2); 

	for (int x{}; x < 4; ++x)//validate guess
		if (guess[x] < 0 || guess[x] > COLORS)
			return pair<int,int>(-1,-1);
	for (int x{}; x < 4; ++x)//emplace guess
		this->board[turn][x] = guess[x];
	pair<int, int> white_black = check_pins(guess,this->answer);
	pins.push_back(white_black);
	turn++;
	return white_black;//we successfully emplaced our guess into board[turn]
}

pair<int, int> Mastermind::check_pins(vector<int> guess, vector<int> answer)
{
	/*
		black = correct cell and color
		white = wrong cell but correct color
	*/
	pair<int, int> _white_black(0, 0);
	int size = 4;
	for (int x{}; x < size;++x)//count black (same cell and color)
	{
		if (guess[x] == answer[x])
		{
			_white_black.second++;
			guess.erase(guess.begin() + x);
			answer.erase(answer.begin() + x);
			size--;
			x--;
		}
	}
	//check white
	int g_size = guess.size();
	int a_size = answer.size();
	for (int x{}; x < g_size;++x)
	{
		for (int y{}; y < a_size;++y)
		{
			if (guess[x] == answer[y] && guess[x] != -1)
			{
				_white_black.first++;
				guess[x] = -1;
				answer[y] = -1;
			}
		}
	}
	return _white_black;
}

void Mastermind::print_board(matrix& _board)
{
	cout << "Board: " << endl;
	for (int x{}; x < _board.size(); ++x)
	{
		for (int y{}; y < _board[x].size(); ++y)
		{
			if(pins.size() > x && pins[x].first != -1 && y == _board[x].size() - 1)
				cout << "  " << _board[x][y] << "\t W(" << pins[x].first << ") B(" << pins[x].second << ")";
			else
				cout << "  " << _board[x][y];
		}
		cout << endl;
	}

}

void Mastermind::print_answer()
{
	cout << "Answer: " << endl;
	for (const int& val : this->answer)
		cout << "  " << val;
	cout << endl;
}
