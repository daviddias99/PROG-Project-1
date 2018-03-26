#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<ctime>

using namespace std;


/**
Asks for the name of the file and trys to open the file
@param file: passed by reference, corresponds to the opened input file
@return value: true if the file is opened successfuly and false if the file doesn't exist or the file extension is invalid
*/
bool getWordFile(ifstream& file)
{
	string fileName;

	//Gets the name of the input file
	cout << "Word file ? ";
	cin >> fileName;

	//Checks if file extension is correct
	while (fileName.size() > 3 && fileName.substr(fileName.size() - 4, 4) != ".txt")
	{
		cout << "Invalid file extension." << endl;
		cout << "Word file ? ";
		cin >> fileName;
	}

	//Opens the given file
	file.open(fileName);

	//If the file is not open, give an error message and end the program
	if (!file.is_open())
	{
		cout << "File not found." << endl;
		return false;
	}
	else
		return true;
}


/**
Reads word file saving all words into a vector of strings
@param file: file to read
@param words: vector where words are stored
*/
void readFile(ifstream& file, vector<string>& wordVector)
{
	string word;

	while (file >> word)
		wordVector.push_back(word);
}


/**
Receives a string and returns it with all caps 
@param word: word we want to make all caps
@return value: same word, all caps
*/
string allCaps(string word)
{
	for (int i = 0; i < word.size(); i++)
	{
		word.at(i) = toupper(word.at(i));
	}

	return word;
}


/**
Uses binary search to see if a user entered word matches a word on the vector
@param wordVector: vector of words
@param word: user entered word 
@return value: true if the word matches a word on the vector, false if the word doesn't belong on the vector
*/
bool searchWord(vector<string> wordVector, string word)
{
	int lower = 0;
	int upper = wordVector.size() - 1;
	int mid;

	while (upper >= lower)
	{
		mid = (upper + lower) / 2;

		if (word == wordVector.at(mid))
			return true;
		else if (word > wordVector.at(mid))
			lower = mid + 1;
		else if (word < wordVector.at(mid))
			upper = mid - 1;
	}
	
	return false;
}


/**
Asks the user for a word and checks if it belongs on the list
@param wordvector: vector containing all words
*/
void wordExists(vector<string> wordVector)
{
	string inputWord;

	cout << "Enter a word: "; cin >> inputWord;

	if (searchWord(wordVector, allCaps(inputWord)))
		cout << "The word " << inputWord << " belongs on the list." << endl;
	else
		cout << "The word " << inputWord << " doesn't belong on the list." << endl;

}

/**
.Chooses a random integer between two numbers (Don't forget to seed the RNG in the main function)
@param n1: lower bound
@param n2: upper bound
@return: random between n1 and n2 (n1 and n2 included)
*/

int randomBetween(int n1, int n2)
{
	return n1 + rand() % (n2 - n1 + 1);
}

/**
.Receives a string and returns a scrambled version of that string
@param inputString
@return newString: scrambled version of inputString
*/

string scrambleString(string inputString)
{
	string newString = inputString;

	for (size_t i = 0; i < newString.size(); i++)
	{
		int randomPos = randomBetween(0, inputString.size() - 1);
		newString.at(i) = inputString.at(randomPos);
		inputString.erase(randomPos, 1);
	}
	return newString;
}

/*
.Outputs to the console a scrambled string, each letter (except the last one) is followed by a space. WARNING: MIGHT NEED NAME CHANGE
@param inputString
*/

void showScrambled(string inputString)
{
	for (size_t i = 0; i < inputString.size(); i++)
	{
		cout << inputString.at(i);
		if (i != inputString.size() - 1)
		{
			cout << " ";
		}
	}
}

/**
.Function that does the game "Guess Word", it chooses a random string from a given vector, outputs the scrambled word and gives the user three tries
to guess the original word.
@param wordVector
*/

void guessWord(vector<string>&  wordVector)
{
	string secretWord = wordVector.at(randomBetween(0, (int)wordVector.size() - 1));
	string scrambledWord = scrambleString(secretWord);
	string userInput;

	cout << "== GUESS WORD ==" << endl << endl;
	showScrambled(scrambledWord);
	cout << endl;

	for (int i = 1; i <= 3; i++)
	{
		cout << "Answer #" << i << ": ";
		cin >> userInput;

		if (allCaps(userInput) == secretWord)
		{
			cout << "Correct answer! " << endl;
			break;
		}

		cout << "Wrong answer... (" << 3 - i << " tries left)" << endl;

		if (i == 3)
		{
			cout << "The correct answer was \" " << secretWord << " \" " << endl;
		}

	}

	cout << "TEMPORARY: END OF FUNCTION" << endl;

}

//======================================================================================================================================


int main()
{
	ifstream wordFile;
	vector<string> wordVector;
	srand(time(NULL));

	
	//Open word file
	while (!getWordFile(wordFile)); 


	//Save words into vector and close word file
	cout << endl << "Reading word file ... " << endl;
	readFile(wordFile, wordVector);
	wordFile.close();
	cout << endl;


	//Does the word belong on the list? **first function**
	
	//wordExists(wordVector);
	guessWord(wordVector);
	



	return 0;
}