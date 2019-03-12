#include <stdio.h>
#include <stdbool.h>
#include <math.h>

//function prototypes
bool numCheck (int tempNum[]);
void convert(int number, int phoneNumber[]);
void printNum(int number[], char letters[10][3]);

//main program
int main(void)
 {
	//datatypes
	int pNumber[7], phoneNum;
	char letterBox[10][3] = {
		{ '0','0','0' },{'0','0','0'},{ 'A','B','C' },
		{ 'D','E','F' },{ 'G','H','I' },{ 'J','K','L' },
		{ 'M','N','O' },{ 'P','R','S' },{ 'T','U','V' },
		{ 'W','X','Y' }
	};
	bool numBool = false;

	//prompt for user to enter a phone number. hint 7373328 will spell out the word PERFECT.
	printf_s("%s", "Please enter a 7 digit phone number for mnemonic creation(example, enter the number like 5551234): ");
	//capture for the phone number
	scanf_s("%d", &phoneNum);

	//this sends the number to be converted into an array
	convert(phoneNum, pNumber);
	//this sends the number array to check if there are 1's or 0's in it
	numBool = numCheck(pNumber);

	//while loop to keep prompting the user to input a number that does not have 0's or 1's
	while (numBool)
	{
		printf_s("%s", "\nThe inputted number cannot be converted, please input a phone number without 1's or 0's: ");
		scanf_s("%d", &phoneNum);
		convert(phoneNum, pNumber);
		numBool = numCheck(pNumber);
	}

	//this sends the number to check for mnemonic device
	printNum(pNumber, letterBox);
	

}//end main

//very simple function that checks for a 0 or a 1 and returns whether it was true or false
bool numCheck(int tempNum[])
{
	int i;

	for (i = 0; i < 7; i++) 
	{
		if (tempNum[i] == 0 || tempNum[i] == 1)
		{
			return true;
		}
	}

	return false;
}

//function to strip the phone number down into individual components instead of having just a giant int
void convert(int number, int phoneNumber[])
{
	int temp = 0, n = 0, i;

	for (i = 7; i > 0; i--) {
		temp = (int)(number / (pow(10, i-1)));
		phoneNumber[n] = temp;
		number = (int)(number - (temp * (pow(10, i - 1))));
		n++;
	}
}

//the function for checking the phone number against a dictionary
void printNum(int number[], char letters[10][3])
{
	//datatypes for the various places within the phone number array with an extra to see if it didn't ever match
	int a,b,c,d,e,f,g, z = 0;
	char temp[10];

	//creating the file manipulation pointers
	FILE *fRead;
	FILE *fWrite;

	//opening the save to file so that if there is more than one word match it will append to the end.
	fWrite = fopen("savedWords.txt", "w");

	//the 7 nested for loops so that every single place in the array can be incremented appropriatley and that every possible letter combination can be checked
	for (a = 0; a < 3; a++)
	{
		for (b = 0; b < 3; b++)
		{
			for (c = 0; c < 3; c++)
			{
				for (d = 0; d < 3; d++)
				{
					for (e = 0; e < 3; e++)
					{
						for (f = 0; f < 3; f++)
						{
							for (g = 0; g < 3; g++)
							{
								//so that every single combination can be checked every time the dictionary gets opened at the top of the for loops
								//it's a little slow because the dictionary is 22,000 lines long, and it is checked for every single letter combination
								//This means literally, that 29,465,451 lines of text are scanned
								//3 to the 7th power = 2187
								//13473 lines in the dictionary file
								//2187 * 13473 = 29,465,451
								fRead = fopen("dictionary.txt", "r");
								
								//loops until the end of the file is reached
								while (!feof(fRead))
								{
									//get a line from the dictionary
									fgets(temp, 8, fRead);

									//compare it to the listed combination
									if (letters[number[0]][a] == temp[0] &&
										letters[number[1]][b] == temp[1] &&
										letters[number[2]][c] == temp[2] &&
										letters[number[3]][d] == temp[3] &&
										letters[number[4]][e] == temp[4] &&
										letters[number[5]][f] == temp[5] &&
										letters[number[6]][g] == temp[6])
									{
										//writes the word to the file
										fprintf_s(fWrite, temp, "\n");
										//prints the word on the screen
										puts(temp);
										//increments the checker so that it is no longer 0, and the program can tell that atleast one word was found
										z++;
									}
								}

								//close the dictionary so that it can be searched from the beginning again
								fclose(fRead);
								
							}
						}
					}
				}
			}
		}
	}

	//if a word was found, z will no longer be 0, and it can output a message that no word was found
	if (z == 0)
	{
		puts("No mnemonic device found for inputted number");
	}
	//lets you know that the matched word was saved into the file.
	else {
		puts("Words saved to \"savedWords.txt\"");
	}
	//close the output file
	fclose(fWrite);
}