#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


/**
Checks if the string is a headline
@param line: string to be evaluated
@return value: true if string only contains uppercase letters ('A'-'Z') or the characters ' ' (space), ';' (semicolon), '-' (hyphen), or '\'' (apostrophe)
*/
bool isHeadline(string line)
{
	bool headline = true; // return value


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
Checks if there's any non alphabetic char
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

/*
[x] getline is working, all functions tested
[] decompose function
*/




//------------------------------------------------------------------------------------------------------------

/**

*/

void processLine(string line, vector<string>& wordVector)
{
	if (isHeadline(line))
	{
		if (isSimpleWord(line))
		{
			addToVector(line);
		}
		else
		{
			decomporlinha;
		}
	}

	break;
}


/**
Reads the contents of the input File, line by line, calls the functions that process the line, and updates the counters(for output purposes)
@param iFile: address of the input file
*/

void readFile(ifstream& iFile)
{
	string inputLine;


	tratarLinha();
	atualizar_contadores;

	while (!iFile.eof()) // testar se chegou o eof
	{
		getline(iFile, inputLine);
		tratarLinha();
		atualizar_contadores;
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

	readFile(inputFile);



	return 0;
}

