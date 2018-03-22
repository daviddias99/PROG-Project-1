#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/**
Adds a word to the word vector
@param wordVector: vector of strings
@param word: word to be added to the word vector
*/

void addToVector(vector<string>& wordVector, string word)
{
	wordVector.push_back(word);
}

/**
Modifies string to the same string without blank spaces
@param s: passed by reference, string whose spaces we want to delete
*/
void removeSpacesFromEdges(string &s)
{
	int i = 0;

	while (isspace(s.at(i))) // remove spaces at the beggining of the string
		s.erase(i, 1);

	int j = s.length() - 1;

	while (isspace(s.at(j))) // remove spaces at the end of the string
	{
		s.erase(j, 1);
		j--;
	}
}

/**
Checks if the string is a headline
@param line: string to be evaluated
@return value: true if string only contains uppercase letters ('A'-'Z') or the characters ' ' (space), ';' (semicolon), '-' (hyphen), or '\'' (apostrophe)
*/
bool isHeadline(string line)
{
	bool headline = true; // return value

	if (line == "") return false;

	removeSpacesFromEdges(line);

	for (int i = 0; i < line.size(); i++)
	{
		char currentChar = line.at(i);

		if (isalpha(currentChar))
		{
			if (currentChar != toupper(currentChar)) // check if char is alphabetic lower case
			{
				headline = false; // if char is lower case, return value is false and end loop

				break;
			}
		}
		else if ((currentChar != ' ') && (currentChar != '\'') && (currentChar != '-') && (currentChar != ';')) // if not letter and different than valid non alphabetic chars
		{
			headline = false;

			break;
		}
	}

	return headline;
}

/**
Checks if there's any non alphabetic char **WARNING** should use function  removeSpaces before using isSimpleWord
@param line: string to be evaluated
@return value: true if word is simple and valid to add to main vector
*/
bool isSimpleWord(string line)
{
	bool simpleWord = true;

	for (int i = 0; i < line.size(); i++)
	{
		char currentChar = line.at(i);

		if (!isalpha(currentChar))
		{
			simpleWord = false;
			break;
		}
	}

	return simpleWord;
}

/**
Checks if headline needs to be decomposed
@param line: string to be evaluated
@return value: true if word has semicolons(i.e. has multiple expressions/words) and needs to be decomposed
*/
bool hasMultipleWords(string line)
{
	bool hasSemicolon = false;

	for (int i = 0; i < line.size(); i++)
	{
		char currentChar = line.at(i);

		if (currentChar == ';')
		{
			hasSemicolon = true;

			break;
		}
	}

	return hasSemicolon;
}

/**
For headlines with multiple words: decomposes in single words/expressions and adds them to vector if they're simple words
@param line: string to be evaluated
@param wordVector: vector of words
*/
void addHeadline(string line, vector<string>& wordVector)
{
	string currentWord = "";

	for (int i = 0; i < line.length(); i++)
	{
		if (line.at(i) == ';')
		{
			removeSpacesFromEdges(currentWord);

			if (isSimpleWord(currentWord))
				addToVector(wordVector, currentWord);

			currentWord = "";
		}
		else
			currentWord.push_back(line.at(i));
	}

	removeSpacesFromEdges(currentWord);

	if (isSimpleWord(currentWord))
		addToVector(wordVector, currentWord);
}


//------------------------------------------------------------------------------------------------------------


void processLine(string line, vector<string>& wordVector)
{
	if (isHeadline(line))
	{
		removeSpacesFromEdges(line);


		if (isSimpleWord(line))
		{
			addToVector(wordVector, line);
		}
		else
		{
			if (hasMultipleWords(line))
			{
				addHeadline(line, wordVector);
			}
		}
	}

}


/**
Reads the contents of the input File, line by line, calls the functions that process the line, and updates the counters(for output purposes)
@param iFile: address of the input file
*/
void readFile(ifstream& iFile, vector<string>& wordVector)
{
	string inputLine;


	processLine(inputLine, wordVector);

	while (!iFile.eof()) // testar se chegou o eof
	{
		getline(iFile, inputLine);
		processLine(inputLine, wordVector);
	}
}


/**
.Swaps two chosen elements from a wordVector
@param wordVector: reference to a vector of strings
@param pos1: integer containing a index of a position in the vector
@param pos2: integer containing a index of a position in the vector
*/


void vectorSwap(vector<string>& wordVector, int pos1, int pos2)
{
	string temp = wordVector.at(pos1);

	wordVector.at(pos1) = wordVector.at(pos2);
	wordVector.at(pos2) = temp;
}

/**
.Uses bubble sort to sort and vector of strings, alphabetically. It is entended for strings with only upper case letters.
@param wordVector: reference to a vector
*/


void sortVector(vector<string>& wordVector)
{
	//Initialize variables
	unsigned int vectorSize = wordVector.size();
	bool didSwap;

	do
	{
		didSwap = false;
		//if a string is "bigger" than the following one, swap them and change the bool value
		for (unsigned int i = 1; i < vectorSize; i++)
		{
			if (wordVector.at(i - 1) > wordVector.at(i))
			{
				vectorSwap(wordVector, i, i - 1);
				didSwap = true;
			}
		}
	} while (didSwap); //stops when no swaps occured

}

/**
.Removes duplicate words from a sorted vector
@param wordVector: sorted array of upper case strinfs
*/

void removeDuplicates(vector<string>& wordVector)
{
	for (unsigned int j = 0; j < (wordVector.size() - 1); j++)
	{
		if (wordVector.at(j) == wordVector.at(j + 1))
		{
			wordVector.erase(wordVector.begin() + j);
			j--;
		}

	}
}

int main()
{

	ifstream inputFile;
	ofstream outputFile;

	string inputFile_Name, outputFile_Name;

	vector<string> wordVector;


	cout << " EXTRACTION OF WORD LIST FROM DICTIONARY" << endl;
	cout << " =======================================" << endl;
	cout << endl;

	//Gets the name of the input file
	cout << "Dictionary file ? ";
	cin >> inputFile_Name;

	//Opens the given file
	inputFile.open(inputFile_Name);

	//If the file is not open, give an error message and end the program
	if (!inputFile.is_open())
	{
		cerr << "ERROR: File not found, exiting..." << endl;
		exit(1);
	}

	//Store the output file's name
	cout << "Word list file ? ";
	cin >> outputFile_Name;

	cout << endl;

	cout << "Extracting simple words from file " << inputFile_Name << "," << endl;
	cout << "beginning with letter ..." << endl;

	readFile(inputFile, wordVector);
	sortVector(wordVector);
	removeDuplicates(wordVector);

	outputFile.open(outputFile_Name);

	for (int i = 0; i < wordVector.size(); i++)
	{
		outputFile << wordVector.at(i)<< endl;	
	}



	return 0;
}

