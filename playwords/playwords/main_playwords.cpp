#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstring>
#include<ctime>
#include<ios>
#include<limits>

using namespace std;



/**
Asks for the name of the file and trys to open the file
@param file: passed by reference, corresponds to the opened input file
@return value: true if the file is opened successfuly and false if the user enters ctrl+z
*/
bool getWordFile(ifstream& file)
{
	bool successfulyRead;
	string fileName;

	do 
	{
	//Gets the name of the input file
	cout << "Word file ? ";
	cin >> fileName;

	//Checks if file extension is correct
	while ((fileName.size() > 3 && fileName.substr(fileName.size() - 4, 4) != ".txt") || cin.eof())
	{
		if (cin.eof())
		{
			cin.clear();
			return false;
		}

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
		successfulyRead = false;
	}
	else
		successfulyRead = true;
	} while (!successfulyRead);

	return successfulyRead;
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
	for (size_t i = 0; i < word.size(); i++)
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
FIND WORD
Asks the user for a word and checks if it belongs on the list
@param wordvector: vector containing all words
*/
void func1(vector<string> wordVector)
{
	string playAgainAns;
	bool playAgain;

	do
	{
		system("cls"); //Clear screen
		cout << "=============================================" << endl;
		cout << "====              FIND WORD              ====" << endl;
		cout << "=============================================" << endl;
		cout << endl << endl;


		string inputWord;

		cout << "Enter a word: "; cin >> inputWord;

		if (searchWord(wordVector, allCaps(inputWord)))
			cout << "The word \"" << allCaps(inputWord) << "\" belongs on the list." << endl;
		else
			cout << "The word \"" << allCaps(inputWord) << "\" doesn't belong on the list." << endl;

		cout << endl;
		cout << "Do you want to play again? (Yes/No) ";
		cin >> playAgainAns;

		while (cin.eof() || cin.fail() || (toupper(playAgainAns.at(0)) != 'Y' && toupper(playAgainAns.at(0)) != 'N'))
		{
			if (cin.eof())
			{
				cin.clear();
				playAgain = false;
				break;
			}

			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}


			cout << "Invalid answer. Answer must be Yes or No. Try again: ";
			cin >> playAgainAns;
		}

		if (playAgainAns != "")
			playAgain = toupper(playAgainAns.at(0)) == 'Y' ? true : false;

	} while (playAgain);
}


/**
Chooses a random integer between two numbers (Don't forget to seed the RNG in the main function)
@param n1: lower bound
@param n2: upper bound
@return value: random between n1 and n2 (n1 and n2 included)
*/
int randomBetween(int n1, int n2)
{
	return n1 + rand() % (n2 - n1 + 1);
}


/**
Receives a string and returns a scrambled version of that string
@param inputString
@return value: scrambled version of inputString
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


/**
Outputs to the console a scrambled string, each letter (except the last one) is followed by a space. WARNING: MIGHT NEED NAME CHANGE
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
GUESS WORD
Function that does the game "Guess Word", it chooses a random string from a given vector, outputs the scrambled word and gives the user three tries
to guess the original word.
@param wordVector
*/
void func2(vector<string>&  wordVector)
{
	string playAgainAns;
	bool playAgain;

	do
	{
		const unsigned int NUM_TRIES = 3;

		system("cls");
		cout << "=============================================" << endl;
		cout << "====              GUESS WORD             ====" << endl;
		cout << "=============================================" << endl;
		cout << endl << endl;


		string secretWord = wordVector.at(randomBetween(0, (int)wordVector.size() - 1));
		string scrambledWord = scrambleString(secretWord);
		string userInput;

		showScrambled(scrambledWord);
		cout << endl << endl;

		for (int i = 1; i <= NUM_TRIES; i++)
		{
			cout << "Answer #" << i << ": ";
			cin >> userInput;

			if (allCaps(userInput) == secretWord)
			{
				cout << "Correct answer! " << endl;
				break;
			}

			cout << "Wrong answer... (" << NUM_TRIES - i << " tries left)" << endl;

			if (i == NUM_TRIES)
			{
				cout << endl;
				cout << "The correct answer was \"" << secretWord << "\" " << endl;
			}

			cout << endl;
		}

		cout << endl;
		cout << "Do you want to play again? (Yes/No) ";
		cin >> playAgainAns;

		while (cin.eof() || cin.fail() || (toupper(playAgainAns.at(0)) != 'Y' && toupper(playAgainAns.at(0)) != 'N'))
		{
			if (cin.eof())
			{
				cin.clear();
				playAgain = false;
				break;
			}

			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}


			cout << "Invalid answer. Answer must be Yes or No. Try again: ";
			cin >> playAgainAns;
		}

		if (playAgainAns != "")
			playAgain = toupper(playAgainAns.at(0)) == 'Y' ? true : false;

	} while (playAgain);
}


//======================================FUNCAO_3========================================================================================


/**
Normalizes a word making all its chars alphabetically ordered and upper case
@param word: word to normalize
@return value: string corresponding to the normalized word
*/
string normalizeWord(string word)
{
	string normWord = allCaps(word);

	unsigned int wordSize = word.size();
	bool didSwap;

	do
	{
		didSwap = false;

		for (unsigned int i = 1; i < wordSize; i++)
		{
			if (normWord.at(i - 1) > normWord.at(i))
			{
				iter_swap(normWord.begin() + i, normWord.begin() + i - 1);
				didSwap = true;
			}
		}
	} while (didSwap);

	return normWord;
}


/**
Asks user for a set of letters
@return value: string with all the valid alphabetic chars given by the user
*/
string userLetters()
{
	string userStr;
	bool validStr;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	do
	{
		validStr = true;

		cout << "Enter a set of letters: ";
		getline(cin, userStr);

		for (size_t i = 0; i < userStr.size(); i++)
		{
			if (!isalpha(userStr.at(i)))
			{
				if (isspace(userStr.at(i)))
				{
					userStr.erase(i, 1);
					i--;
				}
				else
				{
					validStr = false;
					cout << "Invalid set of letters(only alphabetic chars and spaces allowed)." << endl << endl;
					break;
				}
			}
		}
	} while (!validStr);

	return userStr;
}


/**
Searchs the wordVector for the valid words using the set of letters given by the user
@param wordVector: vector containing the dictionary
@param letterString: string containing the set of letters
@return value: vector of strings containing all the valid words
*/
vector<string> getValidWords(vector<string> wordVector, string letterString)
{
	vector<string> validWords;
	size_t numDictionaryWords = wordVector.size();
	int setSize = letterString.size();

	for (size_t i = 0; i < numDictionaryWords; i++)
	{
		if (setSize == wordVector.at(i).size())
			if (letterString == normalizeWord(wordVector.at(i)))
				validWords.push_back(wordVector.at(i));
	}

	return validWords;
}


/**
Displays all the elements from a vector, followed by a newline
@param vec: vector we want to display
*/
void showVector(vector<string> vec)
{
	cout << vec.at(0);

	for (size_t i = 1; i < vec.size(); i++)
	{
		cout << "; " << vec.at(i);
	}
}


/**
WORD BUILDING
Ask the user a set of N letters and show all the words present in the dictionary that can be built using the set of the given letters or any subset of them
@param wordVector: dictionary vector
*/
void func3(vector<string> wordVector)
{
	cout << "=============================================" << endl;
	cout << "====           WORD BUILDING             ====" << endl;
	cout << "=============================================" << endl;
	cout << endl << endl;


	string letterString = normalizeWord(userLetters());

	vector<string> validWords = getValidWords(wordVector, letterString);

	cout << endl;

	if (validWords.size() > 0)
	{
		cout << "All the valid words using that set of letters are:" << endl;
		showVector(validWords);
		cout << endl;
	}
	else
		cout << "No possible words using the given set of letters." << endl;
}


//==========================================FUNCAO_4================================================================================


/**
Rounds a given number to a chosen number of decimal places
@param x
@param n: number of decimal places
@return rounded version of x
*/
double roundNum(double x, int n)
{
	return floor(x*pow(10, n) + 0.5) / pow(10, n);
}


/**
Resizes a vector eliminating a "tail" of a vector that only contains null chars.
@param vectorInput: a given vector of chars
*/
void normalizeVector(vector<char>& vectorInput)
{
	for (size_t i = 0; i < vectorInput.size(); i++)
	{
		if (vectorInput.at(i) == '\0')
		{
			vectorInput.erase(vectorInput.begin() + i, vectorInput.end());
		}
	}
}


/**
Gives the value of the sum of the values of the elements of a vector
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


/**
Goes through the chars of a given string and updates the count of those chars in the "charCount" vector
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


/**
Goes through each word in the word vector and updates the charCount vector
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


/**
Takes the number of occurences of each letter and calculates it's relative frequency, then, given a sample Size, calculates the number of times
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
		charFreq.at(i) = floor((double)charCount.at(i) / sum * SAMPLE_SIZE);
	}

}


/**
Builds a sample of chars using the quantities that come in charFreq vector
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


/**
Chooses randomly,  a set of N chars from a given vector and outputs them to the screen
@param sampleVector
@param N: number of letters
*/
void outputNLetters(vector<char>& sampleVector, int N)
{
	for (size_t i = 1; i <= N; i++)
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


//==========================================FUNCAO_5====================================================================================


//////////////////////////////////////////////////////////////////////////
// WildcardMatch
// str - Input string to match
// strWild - Match mask that may contain wildcards like ? and *
//
// A ? sign matches any character, except an empty string.
// A * sign matches any string inclusive an empty string.
// Characters are compared caseless.
//
// ADAPTED FROM:
// https://www.codeproject.com/Articles/188256/A-Simple-Wildcard-Matching-Function
bool wildcardMatch(const char *str, const char *strWild)
{
	// We have a special case where string is empty ("") and the mask is "*".
	// We need to handle this too. So we can't test on !*str here.
	// The loop breaks when the match string is exhausted.
	while (*strWild)
	{
		// Single wildcard character
		if (*strWild == '?')
		{
			// Matches any character except empty string
			if (!*str)
				return false;
			// OK next
			++str;
			++strWild;
		}
		else if (*strWild == '*')
		{
			// Need to do some tricks.
			// 1. The wildcard * is ignored.
			// So just an empty string matches. This is done by recursion.
			// Because we eat one character from the match string,
			// the recursion will stop.
			if (wildcardMatch(str, strWild + 1))
				// we have a match and the * replaces no other character
				return true;
			// 2. Chance we eat the next character and try it again,
			// with a wildcard * match. This is done by recursion.
			// Because we eat one character from the string,
			// the recursion will stop.
			if (*str && wildcardMatch(str + 1, strWild))
				return true;
			// Nothing worked with this wildcard.
			return false;
		}
		else
		{
			// Standard compare of 2 chars. Note that *str might be 0 here,
			// but then we never get a match on *strWild
			// that has always a value while inside this loop.
			if (toupper(*str++) != toupper(*strWild++))
				return false;
		}
	}
	// Have a match? Only if both are at the end...
	return !*str && !*strWild;
}


/**
Checks if a string is a valid wildcard
@param str: string we want to test
@return value: true if the string is a valid wildcard
*/
bool isWildCard(string str)
{
	bool isWild = true;

	for (size_t i = 0; i < str.size(); i++)
	{
		if (!isalpha(str.at(i)) && str.at(i) != '?' && str.at(i) != '*')
		{
			isWild = false;
			break;
		}
	}

	return isWild;
}


/**
Reads a stl string corresponding to a wildcard from the user
@param MAX_STR_SIZE: max size for the string so that it doesn't give an error when converting to c string
@return value: wildcard stl string
*/
string readWildCard(const unsigned int MAX_STR_SIZE)
{
	string wildCard;

	cout << "Enter a wildcard: "; cin >> wildCard;

	while (cin.fail() || !isWildCard(wildCard) || wildCard.size() > MAX_STR_SIZE)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout << "Not a wildcard. Try again: ";
		cin >> wildCard;
	}

	return wildCard;
}


/**
WILDCARDS
Read a string containing one or more wildcard characters ('*' or '?') and show all the words in the dictionary that match the given string
@param wordVector: dictionary vector
*/
void func5(vector<string> wordVector)
{
	cout << "=============================================" << endl;
	cout << "====              WILDCARDS              ====" << endl;
	cout << "=============================================" << endl;
	cout << endl << endl;


	const unsigned int MAX_STR_SIZE = 50;

	vector<string> validWords;

	string wildCard = readWildCard(MAX_STR_SIZE);

	char cWildPointer[MAX_STR_SIZE + 1];
	char cWordPointer[MAX_STR_SIZE + 1];

	strcpy_s(cWildPointer, wildCard.c_str());

	for (size_t i = 0; i < wordVector.size(); i++)
	{
		strcpy_s(cWordPointer, wordVector.at(i).c_str());

		if (wildcardMatch(cWordPointer, cWildPointer))
		{
			validWords.push_back(wordVector.at(i));
		}
	}

	cout << endl << "All the valid words are: " << endl;
	showVector(validWords);
}


//======================================================================================================================================


/**
Game menu: calls each game according to user input
@param wordVector: vector containing dictionary words
@param startMode: if menu is called with startMode = true, shows the PLAYWORDS headline
*/
void menuHub(vector<string> wordVector, bool startMode = false)
{
	int userInput;

	//Clear screen
	system("cls");

	cout << "=============================================" << endl;
	cout << "====              PLAYWORDS              ====" << endl;
	cout << "=============================================" << endl;
	cout << endl << endl;
	cout << "Please choose the game you want to play: " << endl << endl;
	cout << "1 - Find Word " << endl;
	cout << "2 - Scrambled Word" << endl;
	cout << "3 - Word Building" << endl;
	cout << "4 - Valid Words" << endl;
	cout << "5 - Wildcards" << endl;
	cout << "0 - Exit" << endl;

	while (true)
	{

		cout << "* ";
		cin >> userInput;

		if (cin.fail() || userInput > 5 || userInput < 0)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please try again..." << endl;
		}
		else
			break;
	}


	switch (userInput)
	{
	case 0:
		cout << endl << "GOOD BYE!" << endl;
		break;
	case 1:
		cout << endl;
		func1(wordVector);
		menuHub(wordVector);
		break;
	case 2:
		cout << endl;
		func2(wordVector);
		menuHub(wordVector);
		break;
	case 3:
		cout << endl;
		func3(wordVector);
		menuHub(wordVector);
		break;
	case 4:
		//func4(); break;
	case 5:
		cout << endl;
		func5(wordVector);
		menuHub(wordVector);
		break;
	}
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
	srand((unsigned int)time(NULL));

	//Open word file
	if (!getWordFile((wordFile)))
	{
		cerr << "Exiting... " << endl;
		return 1;
	};


	//Save words into vector and close word file
	cout << endl << "Reading word file ... " << endl;
	readFile(wordFile, wordVector);
	wordFile.close();
	cout << endl;

	//Starts game with menu for the player to choose the game he wants to play
	menuHub(wordVector, true);

	return 0;
}