#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "inputOutput.h"


// this function does the file opening and returns a vector object
// already filled with the values from the file

vector<double> tableReader()
{

	using namespace std;

	fstream table;
	cout << "What is the file name?" << endl;
	table.open(fileNameReader(), ios::in);

	if (!table.is_open())
	{
		cout << "Couldn't open file!" << endl;
		cout << "Want to try again? (y/n)" << endl;

		while (yesNoReader()) // Loops until file is open or user wants to quit
		{
			cout << "What is the file name?" << endl;
			table.open(fileNameReader(), ios::in);
			if (table.is_open())
				break;
			else
				cout << "Couldn't open file!" << endl;
			cout << "Want to try again? (y/n)" << endl;
		}

	}

	vector<double> values;

	double num = 0.0;
	//keep storing values from the text file so long as data exists:
	while (table >> num) {
		values.push_back(num);
	}

	table.close();

	return values;
}