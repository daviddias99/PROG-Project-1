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
Modifies string by removing whitespaces from the beginning and end
@param s: passed by reference, string whose spaces we want to delete
*/
void removeSpacesFromEdges(string &s)
{
	while (isspace(s.at(0))) //Remove spaces at the beginning of the string
	{
		s.erase(0, 1);
		if (s == "")
			break;
	}
		
	
	if (s != "") 
	{
		int j = s.length() - 1;
		while (isspace(s.at(j))) //Remove spaces at the end of the string
		{
			s.erase(j, 1);
			j--;
			if (s == "")
				break;
		}
	}
}


/**
Checks if the string is a headline
@param line: string to be evaluated
@return value: true if string only contains uppercase letters ('A'-'Z') or the characters ' ' (space), ';' (semicolon), '-' (hyphen), or '\'' (apostrophe)
*/
bool isHeadline(string line)
{
	bool headline = true;

	if (line == "") return false;

	removeSpacesFromEdges(line);

	for (int i = 0; i < line.size(); i++)
	{
		char currentChar = line.at(i);

		if (isalpha(currentChar))
		{
			if (currentChar != toupper(currentChar)) //Check if char is alphabetic lower case
			{
				headline = false; //If char is lower case, return value is false and end loop

				break;
			}
		}
		else if ((currentChar != ' ') && (currentChar != '\'') && (currentChar != '-') && (currentChar != ';')) //If not letter and different than valid non alphabetic chars
		{
			headline = false;

			break;
		}
	}

	return headline;
}


/**
Checks if there's any non alphabetic char **WARNING** should use function removeSpacesFromEdges before using isSimpleWord
@param line: string to be evaluated
@return value: true if word is simple and valid to add to main vector
*/
bool isSimpleWord(string line)
{
	bool simpleWord = true;

	for (int i = 0; i < line.size(); i++)
	{
		if (!isalpha(line.at(i))) 
		{
			simpleWord = false;
			break; //breaks if a non alphabetic char is found and returns false
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
		if (line.at(i) == ';')
		{
			hasSemicolon = true; 
			break; //Ends loop if a semicolon is found, returning true
		}
	}

	return hasSemicolon;
}


/**
For headlines with multiple words: decomposes in single words/expressions and adds them to vector if they're simple words
@param wordVector: vector of words
@param line: string to be evaluated
*/
void addHeadline(vector<string>& wordVector, string line)
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


/**
Processes individual lines by checking if they're headlines and if so adding valid words to vector; also handles progress display
@param line: line to be processed
@param wordVector: vector that stores all the valid words
*/
void processLine(string line, vector<string>& wordVector, char& currentInitial, int& headlineCount)
{
	if (isHeadline(line))
	{
		removeSpacesFromEdges(line);

		if (line.at(0) != currentInitial) //If new initial is different than current initial changes currentInitial, displaying new initial on screen
		{
			currentInitial = line.at(0);
			cout << endl << currentInitial << endl;
		}

		//Increments headline counter and displays a dot on the screen if the counter is divisible by 100 ***WARNING its being divided by 5 for testing purposes***
		headlineCount++;
		if (headlineCount % 5 == 0)
			cout << '.';

		if (isSimpleWord(line))
		{
			addToVector(wordVector, line);
		}
		else
		{
			if (hasMultipleWords(line))
			{
				addHeadline(wordVector, line);
			}
		}
	}
}


/**
Reads the contents of the input File, line by line, calls the functions that process the line
@param iFile: address of the input file
*/
void readFile(ifstream& iFile, vector<string>& wordVector)
{
	string inputLine;

	char currentInitial = '\0';
	int headlineCount = 0;

	getline(iFile, inputLine);
	processLine(inputLine, wordVector, currentInitial, headlineCount);

	while (!iFile.eof()) //Test for eof
	{
		getline(iFile, inputLine);
		processLine(inputLine, wordVector, currentInitial, headlineCount);
	}
}


/**
Writes the contents of the word vector into de output file.
@param oFile: address of the output file
@param wordVector: vector with the contents to write on the file
@param fileName: name of the output file
*/
void writeFile(ofstream& oFile, vector<string>& wordVector, string fileName)
{
	oFile.open(fileName);

	for (int i = 0; i < wordVector.size(); i++)
	{
		oFile << wordVector.at(i) << endl;
	}

	oFile.close();
}


/**
Swaps two chosen elements from a vector
@param wordVector: reference to a vector
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
Uses bubble sort to sort and vector of strings, alphabetically. **It is entended for strings with only upper case letters.**
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
		//If a string is "bigger" than the following one, swap them and change the bool value
		for (unsigned int i = 1; i < vectorSize; i++)
		{
			if (wordVector.at(i - 1) > wordVector.at(i))
			{
				vectorSwap(wordVector, i, i - 1);
				didSwap = true;
			}
		}
	} while (didSwap); //Stops when no swaps occured
}


/**
Removes duplicate words from a sorted vector
@param wordVector: sorted array of upper case strings
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


//==============================================================================================================================================


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

	//Checks if file extension is correct
	while (inputFile_Name.substr(inputFile_Name.find_last_of('.'), 4) != ".txt")
	{
		cout << "Invalid file extension." << endl;
		cout << "Dictionary file ? ";
		cin >> inputFile_Name;
	}

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

	//Checks if file extension is correct
	while (outputFile_Name.substr(outputFile_Name.find_last_of('.'), 4) != ".txt")
	{
		cout << "Invalid file extension." << endl;
		cout << "Word list file ? ";
		cin >> outputFile_Name;
	}

	cout << endl;

	cout << "Extracting simple words from file " << inputFile_Name << "," << endl;
	cout << "beginning with letter ..." << endl;

	readFile(inputFile, wordVector);
	inputFile.close(); 

	cout << endl << endl;
	cout << "Number of simple words = " << wordVector.size() << endl;

	cout << "Sorting words ..." << endl;
	sortVector(wordVector);

	cout << "Removing duplicate words ..." << endl;
	removeDuplicates(wordVector);

	cout << "Number of non duplicate words = " << wordVector.size() << endl;

	cout << "Saving words into file " << outputFile_Name << " ..." << endl;
	writeFile(outputFile, wordVector, outputFile_Name);

	cout << "End of processing." << endl;


	return 0;
}

