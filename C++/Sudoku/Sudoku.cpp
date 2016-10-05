// Sudoku.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_set>
using namespace std;

char digits[9] = { '1','2','3','4','5','6','7','8','9' };
char cols[9] = { '1','2','3','4','5','6','7','8','9' };
char rows[9] = { 'A','B','C','D','E','F','G','H','I' };
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
	cout << "You entered: " << numPuzzles << endl;

	for (size_t i = 0; i < numPuzzles; i++)
	{
		Solver::SolveSudoku(i);
	}
}


namespace Solver {

	void SolveSudoku(int puzzleNum) {


	}

	vector<vector<char>> RandomPuzzle() {

		int n = 17;
		map<string, string> values;

		for (string s : squares) {

			values[s] = string(digits);
		}

		for (string s : squares) {

			int rando = rand() % 9 + 1;

			if (Solver::Assign(values, s, to_string(rando)).empty()) {

				break;
			}

			if (values.find(s)->second.length() == 1) {

				map<string, string> ds;
				for (string s1 : squares) {

					string valueTemp = values.find(s1)->second;
					if (valueTemp.length() == 1) {

						ds[s1] = valueTemp;
					}
				}

				if (ds.size() >= n) {

					unordered_set<string> set;
					for (string s1 : squares) {

						if (set.size >= 8) { break; }

						if (ds.find(s1) != ds.end() && (ds.find(s1)->second.length() == 1)) {

							set.insert(ds.find(s1)->second);
						}
					}

					if (set.size() >= 8) {

						if (values.find(s)->second.length() == 1) {

							map<string, char> tmp;
							for (string s1 : squares) {

								if (ds.find(s1) != ds.end() && ds.find(s1)->second.length() == 1) {

									char charTemp = ds.find(s1)->second.at(0);
									tmp[s1] = charTemp;
								}
								else {

									tmp[s1] = '.';
								}
							}

							vector<vector<char>> outerino; //CHECK HOW SQUARES IS ORGANIZED
							vector<char> hold;

							for (string s1 : squares) {

								hold.push_back(tmp.find(s1)->second);

								if (hold.size() == 9) {

									outerino.push_back(hold);
									hold.clear();
								}
							}

							return outerino;
						}
					}
				}
			}
		}

		return RandomPuzzle();
	}

	vector<string> Cross(char* c1, char* c2) {


	}

	vector<vector<string>> BuildUnitList() {


	}

	vector<string> Shuffled(vector<string> seq) {


	}

	map<string, string> Assign(map<string, string> values, string s, string d) {


	}

	map<string, string> Eliminate(map<string, string> values, string s, string d) {


	}

	map<string, string> Search(map<string, string> values) {


	}

	map<string, string> Some(vector<map<string, string>> seq) {


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


namespace Printer {

	void PrintPuzzle(map<string, string> values, const char* fileName) {

		ofstream puzzleOut;
		puzzleOut.open(fileName);

		string coord;
		for (char r : rows) {

			for (char c : cols) {

				if (c == '1') {

					puzzleOut << " ";
				}

				coord = ("" + r + c);
				string temp = values.find(coord)->second;

				puzzleOut << (temp);

				if (c == '3' || c == '6') {

					puzzleOut << ("| ");
				}
			}

			puzzleOut << '\n';

			if (r == 'C' || r == 'F') {

				puzzleOut << ("-------+-------+-------");
			}
		}
		puzzleOut << '\n';

		puzzleOut.close();
	}
}