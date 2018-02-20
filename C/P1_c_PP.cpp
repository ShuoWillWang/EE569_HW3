// EE 569 Homework #3
// date:	Mar. 24th, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//*********************************************************
// Further Improvement for P1_c (Post Processing)
//*********************************************************

#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream> 

using namespace std;

extern unsigned char Imagedata[100000000];
extern unsigned char ImagedataPOut[100000000];

void PostP(int BytesPerPixel, unsigned char *Imagedata, int Size1, int Size2, int i1, int j1, int i2, int j2, int s, int ty)
//According to the visual result, we fill the small hole or delete the small region
{
	for (int i = i1; i <= i2; i++)
	{
		for (int j = j1; j <= j2; j++)
		{
			if (ty == 0)
			{
				Imagedata[3 * ((Size1) * (i)+(j)) + s] = 0;
			}
			else
			{
				Imagedata[3 * ((Size1) * (i)+(j)) + s] = 255;
			}
		}
	}
}

void P1_c_PP(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2)
{
	FILE *file;

	if (!(file = fopen(a1, "rb"))) {
		cout << "Cannot open file: " << a1 << endl;
		system("pause");
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);

	//red
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 47, 89, 80, 128, 0, 0);
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 93, 188, 113, 200, 0, 255);
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 93, 188, 120, 243, 0, 255);
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 57, 260, 72, 282, 0, 255);
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 45, 264, 62, 271, 0, 255);
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 60, 308, 92, 331, 0, 255);
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 33, 364, 43, 373, 0, 255);
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 71, 355, 106, 375, 0, 255);
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 68, 445, 116, 500, 0, 255);
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 114, 354, 181, 412, 0, 255);
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 97, 258, 122, 304, 0, 0);
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 113, 260, 141, 316, 0, 0);
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 138, 125, 168, 146, 0, 0);

	//green
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 9, 60, 180, 521, 1, 0);
	
	//blue
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 47, 89, 80, 128, 2, 255);
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 60, 308, 92, 331, 0, 0);
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 93, 188, 120, 243, 2, 0);
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 97, 258, 122, 304, 2, 255);
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 113, 260, 141, 316, 2, 255);
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 71, 355, 106, 375, 2, 0);
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 114, 354, 181, 412, 2, 0);
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 68, 445, 116, 500, 2, 0);
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 138, 125, 168, 146, 2, 255);
	//PostP(BytesPerPixel, Imagedata, Size1, Size2, 45, 264, 62, 271, 2, 0);
	PostP(BytesPerPixel, Imagedata, Size1, Size2, 57, 272, 69, 281, 2, 0);

	for (int i = 0; i <Size2; i++)
	{
		for (int j = 0; j <Size1; j++)
		{
			if (Imagedata[3 * ((Size1) * (i)+(j)) + 0] <= 50 && Imagedata[3 * ((Size1) * (i)+(j)) + 1] <= 50 && Imagedata[3 * ((Size1) * (i)+(j)) + 2] <= 50)
			{
				Imagedata[3 * ((Size1) * (i)+(j)) + 0] = 255;
			}
		}
	}

	if (!(file = fopen(a2, "wb"))) {
		cout << "Cannot open file: " << a2 << endl;
		exit(1);
	}
	fwrite(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);
	system("pause");
}