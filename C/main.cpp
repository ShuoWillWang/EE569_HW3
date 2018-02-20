// EE 569 Homework #3
// date:	Mar. 24th, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

// Compiled on WINDOWS 10 with Visual C++ and Opencv 3.2
// solution for all questions in  Problem 1, Problem 2(a) and Problem 3
// Use the DOS command to open the program and run it by the README.txt

#include <stdio.h>
#include <iostream>
#include <stdlib.h> 
#include <Windows.h>

using namespace std;

unsigned char Imagedata[100000000] = { 0 };
short ImagedataOut[100000000] = { 0 };
unsigned char Imagedataori[18][1000000] = { 0 };
unsigned char Imagedata1[100000000] = { 0 };
unsigned char Imagedata2[100000000] = { 0 };
unsigned char Imagedataexp[100000000] = { 0 };
unsigned char Imagedataexp1[100000000] = { 0 };
unsigned char ImagedataPex[100000000] = { 0 };
unsigned char ImagedataPexM[100000000] = { 0 };
unsigned char ImagedataPOut[100000000] = { 0 };
unsigned char ImagedataP[100000000] = { 0 };

int main(int argc, char *argv[])
{
	// Define file pointer and variables
	int BytesPerPixel;
	int Size1 = 256, Size2 = 256, Size3 = 300, Size4 = 300;
	int Problem;
	char Part;

	cout << "Solve which problems: ";
	cin >> Problem;
	cout << "solve which part: ";
	cin >> Part;

	if (Problem == 1 || Problem == 2)
	{
		// Check for proper syntax
		if (argc < 3) {
			cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
			cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size1 = 256] [Size2 = 256]" << endl;
			return 0;
		}

		// Check if image is grayscale or color
		if (argc < 4) {
			BytesPerPixel = 1; // default is grey image
		}
		else {
			BytesPerPixel = atoi(argv[3]);
			// Check if size is specified
			if (argc >= 5) {
				Size1 = atoi(argv[4]);
				Size2 = atoi(argv[5]);
			}
		}
	}
	
	void P1_a(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2);
	void P1_a_1(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2);
	void P1_a_1_PCA(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2);
	void P1_b(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2);
	void P1_c_SVM(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2);
	void P1_c_PP(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2);
	int P2_a(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2);
	void P3_a(void);
	void P3_b(void);
	void P3_c(void);

	if (Problem == 1)
	{
		if (Part == 'A' || Part == 'a')
		{
			int type;
			cout << "1) unsupervised or 2) supervised: ";
			cin >> type;
			if (type == 1)
			{
				P1_a(BytesPerPixel, argv[1], argv[2], Size1, Size2);//Problem 1 (a) Unsupervised
			}
			else
			{
				int PON;
				cout << "1) 25-D; 2) PCA: ";
				cin >> PON;
				if (PON == 1)
				{
					P1_a_1(BytesPerPixel, argv[1], argv[2], Size1, Size2);//Problem 1 (a) Supervised 25-D
				}
				else
				{
					P1_a_1_PCA(BytesPerPixel, argv[1], argv[2], Size1, Size2);//Problem 1 (a) Supervised 3-D
				}
			}
		}
		else if (Part == 'b' || Part == 'B')
		{
			P1_b(BytesPerPixel, argv[1], argv[2], Size1, Size2);//Problem 1 (b)
		}
		else if (Part == 'c' || Part == 'C')
		{
			P1_c_SVM(BytesPerPixel, argv[1], argv[2], Size1, Size2);//Problem 1 (c) SVM solution
		}
		else if (Part == 'd' || Part == 'D')
		{
			P1_c_PP(BytesPerPixel, argv[1], argv[2], Size1, Size2);//Problem 1 (c) Post-processing
		}
	}
	if (Problem == 2)
	{
		if (Part == 'a' || Part == 'A')
		{
			P2_a(BytesPerPixel, argv[1], argv[2], Size1, Size2);//Problem 2 (a)
		}
	}
	if (Problem == 3)
	{
		if (Part == 'a' || Part == 'A')
		{
			P3_a();//Problem 3(a)
		}
		if (Part == 'b' || Part == 'B')
		{
			P3_b();//Problem 3(b)
		}
		if (Part == 'C' || Part == 'c')
		{
			P3_c();//Problem 3(c)
		}
	}
}