//-------------------------------------------------------------------------------------
// Author: Syed Emaad Shah
// Created a genetic algorithm in parallel using OpenMP
//-------------------------------------------------------------------------------------
#include <stdio.h>
#include <iostream>
#include <ctime>   
#include <string>
#include <cmath>
#include <fstream>
#include <omp.h>

using namespace std;

// Contains the genes
struct Node
{
	int x;
	int y;
	double fit;
	string xBin;
	string yBin;
};
typedef struct Node generation;
generation gen[10];


//  Minimize Function: x,y [-512, 512], integers, f(x,y) >= 0
double fitness(double x, double y)
{
	return x - 2 * y;
}

// Convert from decimal to binary
string binary(int number)
{
    if ( number == 0 ) return "0";
    if ( number == 1 ) return "1";

    if ( number % 2 == 0 )
        return binary(number / 2) + "0";
    else
        return binary(number / 2) + "1";
}

// Add zero's to make the string total of 10 bits
string normalize(string binary)
{
	int len = binary.length();
	len = 10 - len;
	while (len != 0)
	{
		binary = "0" + binary;
		len--;
	}
	return binary;
}

// Convert from binary to decimal
double decimal(string a)
{
	int n = atoi(a.c_str());
	double output = 0;
	double two = 2;
    for (int i = 0; n > 0; i++) 
	{
        if (n % 10 == 1) 
		{
            output += pow(two, i);
        }
        n /= 10;
    }
	return output;
}

void crossOverHelper(string &a, string &b)
{
	// Random number for cross over
	int c = rand() % 10;
	char tmp = '0';
	for (unsigned int i = c; i < a.length(); i++)
	{
		// Swap
		tmp = a[i];
		a[i] = b[i];
		b[i] = tmp;
	}
}

void crossOver()
{	
	#pragma omp parallel for
	for (int i = 0; i < 10; i += 2)
	{
		// Swap the X's
		crossOverHelper(gen[i].xBin, gen[i+1].xBin);
		// Swap the Y's
		crossOverHelper(gen[i].yBin, gen[i+1].yBin);
	}
}

// Random number function for mutation step
int randomNumber()
{
	int min = 9;
	int index = 0;
	int tmp;
	for (int i = 0; i < 10; i++)
	{
		tmp = rand() % 10;
		if (tmp <= min)
		{
			min = tmp;
			index = i;
		}
	}
	return index;
}

// Mutation stage of the genetic algorithm
void mutation()
{
	int index, index1;
	char bit, bit1;

	#pragma omp parallel for 
	for (int i = 0; i < 10; i++)
	{
		index = randomNumber();
		bit = gen[i].xBin[index];
		if (bit == '1')
			gen[i].xBin[index] = '0';
		else if (bit == '0')
			gen[i].xBin[index] = '1';
		
		index1 = randomNumber();
		bit1 = gen[i].yBin[index1];
		if (bit1 == '1')
			gen[i].yBin[index1] = '0';
		else if (bit == '0')
			gen[i].yBin[index1] = '1'; 
	}
}

// Prints the genes
void print(ofstream & out_data)
{
	#pragma omp parallel for 
	for (int i = 0; i < 10; i++)
	{	  
		out_data << "X: " << gen[i].xBin << endl;
		out_data << "Y: " << gen[i].yBin << endl;
		out_data << endl;
	}
}

int main() 
{
	ofstream out_data("output.txt");

	int iterations = 0;
	while (iterations < 5)
	{
		if (iterations == 0)
		{
			srand((unsigned int)time(0));
			for (int i = 0; i < 10; i++)
			{
				while (true)
				{
					gen[i].x = rand()%(1024)-512;
					gen[i].y = rand()%(1024)-512;
					gen[i].fit = fitness(gen[i].x,gen[i].y);
			
					if (gen[i].fit >= 0)
						break;
				}
				gen[i].xBin = binary(gen[i].x);
				gen[i].yBin = binary(gen[i].y);
				gen[i].xBin = normalize(gen[i].xBin);
				gen[i].yBin = normalize(gen[i].yBin);
			}	
		} 
		out_data << "Iteration: " << iterations << endl << endl;
		out_data << "Selection stage" << endl << endl;

		#pragma omp section
		print(out_data);

		out_data << "Cross-Over stage" << endl << endl;
		
		#pragma omp section
		// Cross-Over stage
		crossOver();
		print(out_data);

		out_data << "Mutation stage" << endl << endl;

		#pragma omp section
		// Mutation stage
		mutation();
		print(out_data);
		iterations++;
		out_data << "-------------" << endl;
	}
	out_data.close();
	system("pause");
	return 0;
}

