// Sudoku.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_set>
using namespace std;

char digits[9] = { '1','2','3','4','5','6','7','8','9' };
//char cols[9] = { '1','2','3','4','5','6','7','8','9' };
//char rows[9] = { 'A','B','C','D','E','F','G','H','I' };
string cols = "123456789";
string rows = "ABCDEFGHI";
string colChunks[3] = { "123", "456", "789" };
string rowChunks[3] = { "ABC", "DEF", "GHI" };

vector<string> squares;
vector<vector<string>> unitList;
map<string, vector<vector<string>>> units;
map<string, unordered_set<string>> peers;


int main()
{
	int numPuzzles = 1;

	cout <<  "Enter the number of puzzles you would like and press [ENTER]: ";

	while (!(cin >> numPuzzles)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input.  Try again: ";
	}
	cout << "You enterd: " << numPuzzles << endl;

	for (size_t i = 0; i < numPuzzles; i++)
	{
		Solver::SolveSudoku(i);
	}
}

//Lucas
char** RandomPuzzle() {


}


namespace Solver {

	//started 
	void SolveSudoku(int puzzleNum) {
		
		//instantiate static variables from the class
		squares = Cross(rows, cols);
		unitList = BuildUnitList();
		map<string, vector<string>> units;
		for (string s : squares) {

			for (vector<string> u : unitList) {

				if (std::find(u.begin(), u.end(), s) != u.end()) {

					units[s] = u;
				}
				else {

					// This is wrong, but I'm not sure how to put a blank vector
					//units[s] = new vector<string>;

				}
			}

		}


	}

	//Finished, not tested
	vector<string> Cross(string c1, string c2) {
		vector<string> out;
		for (char i : c1) {

			for (char j : c2)
				out.push_back("" + i + j);
		}
		return out;

	}

	//finished, not tested
	vector<vector<string>> BuildUnitList() {
		vector<vector<string>> u1;
		for (char c: cols) {
			
			u1.push_back(Cross(rows, ("" + c)));
		}
		for (char r: rows) {
		
			u1.push_back(Cross(("" + r), cols));
		}
		for (string cc : colChunks) {

			for (string rc: rowChunks) {
			
				u1.push_back(Cross(rc, cc));
			}
		}
		return u1;
	}

	//Finished, untested
	vector<string> Shuffled(vector<string> seq) {
		if (seq.empty())
			return seq;
		else {

			// Make a copy of the thing to shuffle (so we don't mess up the original)
			vector<string> copy = seq;
			std::random_shuffle (copy.begin(), copy.end());
			return copy;
		}



	}

	map<string, string> Assign(map<string, string> values, string s, string d) {
		// Separate the values we want to eliminate (seems backwards, I know.)
		string altVals = values[s];
		if ((altVals.find(d) != std::string::npos)) {

			//so long as d is only ever a single char, this'll work
			altVals.erase(pointer to d);

		}
		

	}

	//Finished, especially untested.
	map<string, string> Eliminate(map<string, string> values, string s, string d) {
		if(!(values[s].find(d) != std::string::npos)) {

			return values;
		}

		//values.put(s, values.get(s).replace(d, "")); //Java code
		values[s] = (d + "");
		//THE ABOVE LINE MIGHT BE COMPLETELY WRONG

		if (values[s].length() == 0) {

			return;
		}
		else if (values[s].length() == 1) {

			string d2 = values[s];
			for (string s2 : peers[s]) {

				if (Eliminate(values, s2, d2).empty()) {

					return;
				}
			}
		}

		// List of all the places that digit d could have potentially been
		vector<string> dplaces;
		for (vector<string> u : units[s]) {

			u.clear();
			for (string s1 : u) {
				// If the square s1 has d as a possibility, add it to the list
				if (values[s].find(d) != std::string::npos) {

					dplaces.push_back(s1);
				}
			}

			// If somehow the value can't go anywhere, try again somewhere else
			if (dplaces.size() == 0) {

				return;
			}
			else if (dplaces.size() == 1) {

				// If there is exactly one place it can go, try to assign it to that spot and eliminate other values
				if (Assign(values, dplaces[0], d).empty()) {

					return;
				}
			}
		}

		return values;
	}

	//Finished, not tested
	map<string, string> Search(map<string, string> values) {
		
		if (values.empty())
			return;

		// If we have 81 squares with one digit each, we have a completed puzzle
		int tally = 0;
		for (string s : squares) {

			if (values[s].length() == 1) {

				tally++;
			}
		}

		if (tally == 81) { //solution!

			return values;
		}

		// Search for the sqare with the least possibilities 
		// (but more than one possible digit)
		string sq = "A1";
		int min = 9;
		for (string s : squares) {

			int tmp = values[s].length();
			if (tmp <= min && tmp > 1) {

				sq = s;
				min = tmp;
			}
		}

		// Make a copy of all the values and 
		// try one of the digits in the least populated square
		vector<map<string, string>> searchList;
		for (char d : values[sq]) {

			map<string, string> valCopy = values;
			searchList.push_back(Search(Assign(valCopy, sq, d + "")));
			return Some(searchList);
		}

		return Some(searchList);

	}

	//Finished, not tested
	map<string, string> Some(vector<map<string, string>> seq) {

		for (map <string, string> e : seq) {
			//make sure the map isn't empty, i.e. null check?
			if (!e.empty()) {

				return e;
			}
		}

		return;
	}
}


namespace Parser {

	map<string, string> ParseGrid(char** grid) {


	}

	map<string, string> ParseToPuzzle(char** grid) {


	}

	map<string, string> GridValues(string grid) {


	}
}

//Lucas
namespace Printer {

	void PrintPuzzle(map<string, string> values, const char* fileName) {


	}

	void PrintSolution(map<string, string> values, const char* fileName) {


	}
}