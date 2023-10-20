#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include "MP6.h"

using namespace std;
ifstream inFile;
string line;
char* lineToCharPtr;
char* tokenPtr;
char wordSearch[8][8];


void storeCharacters() //gets character from each line and stores them
{
	int row = 0;
	int column = 0;
	for (row = 0; row < 8; row++) {
		getline(inFile, line);
		lineToCharPtr = (char*)line.c_str();
		tokenPtr = strtok(lineToCharPtr, "\t");
		for (column = 0; column < 8; column++) {
			wordSearch[row][column] = *tokenPtr;
			cout << *tokenPtr << "\t";
			tokenPtr = strtok(NULL, "\t");
		}
		cout << endl;
	}
}

string findRest(int row, int column, string word) { //finds rest of letters 
	//horizontal
	for (int count = 1; count < word.length(); count++) {
		if (wordSearch[row][column + count] != toupper(word[count]))
			break;
		if (count == (word.length() - 1)) {
			return ("Horizontal");
		}
	}
	//vertical
	for (int count = 1; count < word.length(); count++) {
		if (wordSearch[row + count][column] != toupper(word[count]))
			break;
		if (count == (word.length() - 1)) {
			return ("Vertical");
		}
	}

	//diagonal
	for (int count = 1; count < word.length(); count++) {
		if (wordSearch[row + count][column + count] != toupper(word[count]))
			break;
		if (count == (word.length() - 1)) {
			return ("Diagonal");
		}
	}
	return "WRONG";

}

struct findWordResult {
	int row;
	int column;
	string direction;
	string word;
};

findWordResult findFirst(string word) //finds the first letter of each word and then calls function to find rest of word
{
	int row = 0;
	int column = 0;

		for (row = 0; row < 8; row++) {
			for (column = 0; column < 8; column++) {
				if (wordSearch[row][column] == word[0]) {
					string columnRow = findRest(row, column, word);
					if (columnRow != "WRONG")
						return findWordResult{ row, column, columnRow, word };
				}
			}	
		}
		return findWordResult{ -1, -1, "Not Found", word };
}




int main() {
	inFile.open("findwords.txt");
	if (inFile.fail()) {
		cout << "No file has been found! Oops!" << endl;
		return -1;
	}
	storeCharacters();
	while (!inFile.eof()) {
		getline(inFile, line);
		findWordResult result = findFirst(line);
		cout << setw(5) << result.word << setw(3) << setfill(' ') << result.row << setw(3) << setfill(' ') << result.column << setw(10) << setfill(' ') << result.direction << endl;
	}
}


