#include<iostream>
#include<fstream>
#include<vector>
#include<string>

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
void readFile(ifstream& file, vector<string>& words)
{
	string word;

	while (file >> word)
		words.push_back(word);
}


//======================================================================================================================================


int main()
{
	ifstream wordFile;
	vector<string> words;
	
	//Open word file
	while (!getWordFile(wordFile)); 


	//Save words into vector and close word file
	cout << "Reading word file ... " << endl;
	readFile(wordFile, words);
	wordFile.close();



	return 0;
}