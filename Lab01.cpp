// James Fantin
// Lab 01
// COSC 2030

#include <fstream>;
#include <iostream>;
#include <string>;
using std::cout;
using std::cin;
using std::string;
using std::ifstream;

int main()
{
	int count = 0;
	double firstNum, secondNum, secondLastNum, lastNum;
	bool done = false;
	ifstream myfile;
	string filename;

	// Open a filename from the user
	while (!done)
	{
		// Prompt user to enter a filename
		cout << "Enter a filename and I will display the first two numbers, the last two numbers, and a count of the total numbers.\n";
		cin >> filename;
		myfile.open(filename);

		// If the file is not properly open, tell the user and clear the file
		if (!myfile)
		{
			cout << "Cannot open input: " << filename << "\n";
			myfile.clear();
		}

		// If the file is open, then exit the while loop
		else
		{
			done = true;
		}
	}

	// Find the count for how many numbers are in the file
	done = false;
	while (!done) // While we have not found a valid number
	{
		myfile >> lastNum;
		if (!myfile.fail()) // If nothing goes wrong then there is a valid number so count it
		{
			count++;
		}
		else // If something goes wrong clear the stream and continue
		{
			myfile.clear();
			myfile.ignore();
		}
		if (myfile.eof()) // If it is the end of the file then stop
		{
			done = true;
		}
	}

	// Start from the beginning of the file again and get the first two numbers
	myfile.seekg(0);
	for (int i = 0; i < 2; i++)
	{
		done = false;
		while (!done) // While we have not found a valid number
		{
			if (i == 0) // If it is the first number in the file
			{
				myfile >> firstNum;
			}
			else // If it is the second number in the file
			{
				myfile >> secondNum;
			}
			if (!myfile.fail())
			{
				done = true;
			}
			else
			{
				myfile.clear();
				myfile.ignore();
			}
			if (myfile.eof())
			{
				done = true;
			}
		}
	}

	// Following code edited from 
	// https://stackoverflow.com/questions/11876290/c-fastest-way-to-read-only-last-line-of-text-file?answertab=votes#tab-top
	
	// Find the position for the second to last number
	myfile.seekg(-1, std::ios_base::end); // Go to one spot before the EOF
	int counting = 0;
	char ch1;
	char ch2;
	while (counting < 2)
	{
		myfile.get(ch1);                            // Get current byte's data
		myfile.seekg(-2, std::ios_base::cur);       // Go to two spots before
		myfile.get(ch2);

		// If the right most character is not a space and the leftmost character is a space, then there is an entry there
		if ((ch1 != '\n' && ch1 != ' ' && ch1 != '\t') && (ch2 == '\n' || ch2 == ' ' || ch2 == '\t'))
		{
			counting++; // Count this as a valid number
		}
		myfile.seekg(-1, std::ios_base::cur);
	}

	// Get the value of the second to last number
	myfile >> secondLastNum;

	// Display the numbers for the user.
	cout << "The total amount of numbers in the file is " << count << ".\n";
	cout << "The first two numbers are " << firstNum << " and " << secondNum << ".\n";
	cout << "The last two numbers are " << secondLastNum << " and " << lastNum << ".\n";

	return 0;
}
