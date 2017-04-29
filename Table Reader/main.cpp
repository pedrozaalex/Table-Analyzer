#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "inputOutput.h"

int main() {

	using namespace std;

	vector<double> values;
	do
	{
		values = tableReader();
		char uncertaintyType;
		double uncertaintyValue;
		double measuredValue = 0.0;

		// if the file hasn't been opened, the script can't go on
		if (values.size() == 0)
		{
			system("pause");
			return 0;
		}
		// we want 1/10 of the measured value, so this loop divides every value
		// in our vector for us

		for (vector<double>::iterator vvv = values.begin(); vvv < values.end(); ++vvv)
		{
			double period = ((*vvv) / 10);
			*vvv = period;
		}

		// this loop will determine the biggest and lowest values in ou vector

		double minValue = values[0];
		double maxValue = values[0];
		for (vector<double>::iterator vvv = values.begin(); vvv < values.end(); ++vvv)
		{
			if (*vvv > maxValue)
				minValue = *vvv;

			if (*vvv < minValue)
				maxValue = *vvv;
		}

		// helps us determine the type of uncertainty to use
		double ddd;
		ddd = ((maxValue - minValue) / 2);

		// for this experiment the resolution is .3
		// method will be properly generalized later

		double resolution = 0.01; // assuming values in centimeters
		if (ddd < resolution)
		{
			cout << "The uncertainty is of type A" << endl;
			uncertaintyType = 'a';
		}

		else
		{
			cout << "The uncertainty is of type B" << endl;
			uncertaintyType = 'b';
		}

		double averageValue = 0.0;
		int numValues = 0;
		for (vector<double>::iterator vvv = values.begin(); vvv < values.end(); ++vvv)
		{
			averageValue += *vvv;
			++numValues;
		}

		averageValue /= numValues;

		double squaredAverageValue{};
		squaredAverageValue = pow(averageValue, 2); // We want the squared values for the period;
		cout << "The squared average value is " << squaredAverageValue << endl;

		if (uncertaintyType == 'a')
		{
			double sum{ 0.0 };
			for (vector<double>::iterator vvv = values.begin(); vvv < values.end(); ++vvv)
			{
				sum += pow((*vvv - averageValue), 2);
			}

			sum = sum / (numValues*(numValues - 1));
			uncertaintyValue = sqrt(sum);

			uncertaintyValue *= 1.725; // Student's correction factor t

			uncertaintyValue = (2 * averageValue*uncertaintyValue); // Square error propagation
		}

		if (uncertaintyType == 'b')
		{
			uncertaintyValue = (resolution / sqrt(3));
		}

		cout << "The uncertainty is " << uncertaintyValue << endl;
		cout << "The result of your experiment is " << averageValue
			<< " +- " << uncertaintyValue << endl;


		cout << "Wanna read another file? (y/n)" << endl;
	} while (yesNoReader());

	system("pause");
	return 0;
}