#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

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
Reads the contents of the input File, line by line, calls the functions that process the line, and updates the counters(for output purposes).
@param iFile address of the input file
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

