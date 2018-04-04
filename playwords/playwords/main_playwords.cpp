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

/*
.Rounds a given number to a chosen number of decimal places
@param x
@param n: number of decimal places
@return rounded version of x
*/

double roundNum(double x, int n)
{
	return floor(x*pow(10, n) + 0.5) / pow(10, n);
}

/*
.Resizes a vector eliminating a "tail" of a vector that only contains null chars.
@param vectorInput: a given vector of chars
*/

void normalizeVector(vector<char>& vectorInput)
{
	for (int i = 0; i < vectorInput.size(); i++)
	{
		if (vectorInput.at(i) == '\0')
		{
			vectorInput.erase(vectorInput.begin() + i, vectorInput.end());
		}
	}

}

/*
.Gives the value of the sum of the values of the elements of a vector
@param dataVector: vector of integers
@return result: sum of the elements
*/

int vectorSum(vector<int> dataVector)
{
	int result = 0;

	for (size_t i = 0; i < dataVector.size(); i++)
	{
		result += dataVector.at(i);
	}

	return result;
}

/*
.Goes through the chars of a given string and updates the count of those chars in the "charCount" vector
@param word
@param charCount: vector that keeps that of the quantities of a given char
*/

void updateCharCount(string word, vector<int>& charCount)
{
	for (size_t j = 0; j < word.size(); j++)
	{
		char currentChar = word.at(j);
		int charAscii = (int)currentChar;
		int alphaPositon = charAscii % 65; //corresponding position of a char in the charCount vector WARNING: CHANGE TO 65

		charCount.at(alphaPositon)++;
	}
}

/*
.Goes through each word in the word vector and updates the charCount vector
@param wordVector
@param charCount
*/

void charCountBuild(const vector<string>& wordVector, vector<int>& charCount)
{
	for (size_t i = 0; i < wordVector.size(); i++)
	{
		string currentWord = wordVector.at(i);
		updateCharCount(currentWord, charCount);
	}
}

/*
.Takes the number of occurences of each letter and calculates it's relative frequency, then, given a sample Size, calculates the number of times
each char must appear in that sample in order do emulate the relative frequency of the original set.
@param charCount: vector containing the absolute values of the number of occurences of each char
@param charFreq: vector containting the  number of occurences of each char in a set of SAMPLE_SIZE letters (THIS FUNCTION "BUILDS" THIS VECTOR)
@param SAMPLE_SIZE

*/


void charFreqBuild(vector<int>& charCount, vector<int>& charFreq, int SAMPLE_SIZE)
{

	int sum = vectorSum(charCount);


	for (size_t i = 0; i < charFreq.size(); i++)
	{
		charFreq.at(i) =  floor((double)charCount.at(i) / sum * SAMPLE_SIZE);
	}

}

/*
.Builds a sample of chars using the quantities that come in charFreq vector
@param sampleVector
@param charFreq
*/

void buildSample(vector<char>& sampleVector, vector<int>& charFreq)
{
	int globalCount = 0;

	for (size_t j = 0; j < charFreq.size(); j++)
	{
		for (size_t i = 0; i < charFreq.at(j); i++)
		{
			sampleVector.at(globalCount) = (char)(j + 65);
			globalCount++;
		}
	}

	normalizeVector(sampleVector);
}


/*
.Choosesm randomly,  a set of N chars from a given vector and outputs them to the screen
@param sampleVector
@param N: number of letters
*/

void outputNLetters(vector<char>& sampleVector, int N)
{
	for (int i = 1; i <= N; i++)
	{
		int randNum = randomBetween(0, sampleVector.size() - 1);
		cout << sampleVector.at(randNum) << " ";
	}

}


void wordSetFunction(vector<string>& wordVector, vector<int>& charCount, vector<int>& charFreq, vector<char>& sampleVector, const int sampleSize)
{
	int letterQuant;
	string userAnswer;
	charCountBuild(wordVector, charCount);
	charFreqBuild(charCount, charFreq, sampleSize);
	buildSample(sampleVector, charFreq);

	cout << "How many letters do you want the word to contain? ";
	cin >> letterQuant;

	cout << "Input a words that contains the following letters: " << endl;
	outputNLetters(sampleVector, letterQuant);
	cout << endl;
	cin >> userAnswer;
	
	if (searchWord(wordVector, allCaps(userAnswer)))
	{
		cout << "The entered word exists in the file..." << endl;
	}
	else
		cout << "The entered word does NOT exist in the file..." << endl;

}




//======================================================================================================================================
int main()
{
	ifstream wordFile;
	vector<string> wordVector;

	//Used in wordSetFunction
	const int SAMPLE_SIZE = 1350; 
	vector<char> sampleVector(SAMPLE_SIZE);
	vector<int> charCount(26);
	vector<int> charFreq(26);

	//Seed for random number generation
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
	//guessWord(wordVector);

	wordSetFunction(wordVector, charCount, charFreq, sampleVector, SAMPLE_SIZE);
	




	return 0;
}