// EE 569 Homework #3
// date:	Mar. 24th, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//*********************************************************
// Texture Classification for P1_a (Supervised 3-D)
//*********************************************************

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <fstream> 

using namespace std;

extern unsigned char Imagedata[100000000];
extern short ImagedataOut[100000000];
extern unsigned char Imagedataori[18][1000000];
extern unsigned char Imagedataexp[100000000];
extern unsigned char Imagedatatest[6][1000000];

extern void THVOut(int BytesPerPixel, unsigned char *Imagedata, int Size1, int Size2, double *ouc);
extern double Edis_d1(double *a, double *b, int dim);
extern double Edis_d(double *a, double *b, int dim);
extern double mini_d(double *d, int cla);
extern void Cal25D23D1(int BytesPerPixel, double Imagedatatempp[][25], int Size1, int Size2, double Imagedatatempp1[][25], double PCA[][25], int dim);

void P1_a_1_PCA(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2)
{
	FILE *file;

	double vec[18][25] = { 0 };
	double vec1[18][25] = { 0 };
	double vec2[18][25] = { 0 };
	double vec3[18][25] = { 0 };
	double vec_1[18][25] = { 0 };
	double vec_2[18][25] = { 0 };
	double vec_3[18][25] = { 0 };
	double veco[6][25] = { 0 };
	double veco_1[6][25] = { 0 };
	int classi[18] = { 0 };
	int classi_3[18] = { 0 };
	double cen[4][25] = { 0 };
	double cen_3[4][3] = { 0 };

	char *a[4] = { "D:/EE569_Assignment/3/P1/Texture1.raw", "D:/EE569_Assignment/3/P1/Texture4.raw",\
		"D:/EE569_Assignment/3/P1/Texture7.raw", "D:/EE569_Assignment/3/P1/Texture10.raw" };

	for (int k0 = 0; k0 < 4; k0++)
	{
		if (!(file = fopen(a[k0], "rb"))) {
			cout << "Cannot open file: " << a[k0] << endl;
			system("pause");
			exit(1);
		}
		fread(Imagedataori[k0], sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
		fclose(file);
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + 0] = Imagedataori[k0][BytesPerPixel * ((Size1) * (i)+(j)) + 0];
			}
		}
		THVOut(BytesPerPixel, Imagedata, Size1, Size2, vec1[k0]);
		memset(Imagedata, 0, (Size1 * Size2 * sizeof(unsigned char)));
	}

	char *a01[4] = { "D:/EE569_Assignment/3/P1/Texture2.raw", "D:/EE569_Assignment/3/P1/Texture5.raw",\
		"D:/EE569_Assignment/3/P1/Texture8.raw", "D:/EE569_Assignment/3/P1/Texture11.raw" };

	for (int k0 = 0; k0 < 4; k0++)
	{
		if (!(file = fopen(a01[k0], "rb"))) {
			cout << "Cannot open file: " << a01[k0] << endl;
			system("pause");
			exit(1);
		}
		fread(Imagedataori[k0], sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
		fclose(file);
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + 0] = Imagedataori[k0][BytesPerPixel * ((Size1) * (i)+(j)) + 0];
			}
		}
		THVOut(BytesPerPixel, Imagedata, Size1, Size2, vec2[k0]);
		memset(Imagedata, 0, (Size1 * Size2 * sizeof(unsigned char)));
	}

	char *a02[4] = { "D:/EE569_Assignment/3/P1/Texture3.raw", "D:/EE569_Assignment/3/P1/Texture6.raw",\
		"D:/EE569_Assignment/3/P1/Texture9.raw", "D:/EE569_Assignment/3/P1/Texture12.raw" };

	for (int k0 = 0; k0 < 4; k0++)
	{
		if (!(file = fopen(a02[k0], "rb"))) {
			cout << "Cannot open file: " << a02[k0] << endl;
			system("pause");
			exit(1);
		}
		fread(Imagedataori[k0], sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
		fclose(file);
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + 0] = Imagedataori[k0][BytesPerPixel * ((Size1) * (i)+(j)) + 0];
			}
		}
		THVOut(BytesPerPixel, Imagedata, Size1, Size2, vec3[k0]);
		memset(Imagedata, 0, (Size1 * Size2 * sizeof(unsigned char)));
	}

	double PCA[25][25] = { 0 };

	ifstream infile;
	//infile.open("D:/EE569_Assignment/3/MATLAB/data1.txt");
	infile.open("D:/EE569_Assignment/3/MATLAB/data1a.txt");//the PCA transformation saved
	double* ptr = &PCA[0][0];
	while (!infile.eof())
	{
		infile >> *ptr;
		ptr++;
	}
	infile.close();

	int dim = 4;
	Cal25D23D1(1, vec1, 1, 4, vec_1, PCA, dim);
	Cal25D23D1(1, vec2, 1, 4, vec_2, PCA, dim);
	Cal25D23D1(1, vec3, 1, 4, vec_3, PCA, dim);

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 25; j++)
			cen[i][j] = (double)1 / 3 * (vec_1[i][j] + vec_2[i][j] + vec_3[i][j]);

	char *a11[6] = { "D:/EE569_Assignment/3/P1/TextureA.raw", "D:/EE569_Assignment/3/P1/TextureB.raw",\
		"D:/EE569_Assignment/3/P1/TextureC.raw", "D:/EE569_Assignment/3/P1/TextureD.raw",\
		"D:/EE569_Assignment/3/P1/TextureE.raw", "D:/EE569_Assignment/3/P1/TextureF.raw" };

	for (int k0 = 0; k0 < 6; k0++)
	{
		if (!(file = fopen(a11[k0], "rb"))) {
			cout << "Cannot open file: " << a11[k0] << endl;
			system("pause");
			exit(1);
		}
		fread(Imagedatatest[k0], sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
		fclose(file);
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + 0] = Imagedatatest[k0][BytesPerPixel * ((Size1) * (i)+(j)) + 0];
			}
		}
		THVOut(BytesPerPixel, Imagedata, Size1, Size2, veco[k0]);
		memset(Imagedata, 0, (Size1 * Size2 * sizeof(unsigned char)));
	}

	double classiout_25[6] = { 0 };
	double classiout_3[6] = { 0 };

	Cal25D23D1(1, veco, 1, 6, veco_1, PCA, dim);

	for (int k0 = 0; k0 < 6; k0++)
	{
		double *d = new double[4];
		for (int c = 0; c < 4; c++)
		{
			d[c] = Edis_d1(veco_1[k0], cen[c], 3);
		}
		double dmin;
		dmin = mini_d(d, 4);
		for (int c = 0; c < 4; c++)
		{
			if (dmin == d[c])
			{
				classiout_25[k0] = c;
				break;
			}
		}
	}
	cout << "The classification result (Supervised 3-D) for testing A-F images is: " << endl;
	for (int k0 = 0; k0 < 6; k0++)
	{
		cout << classiout_25[k0] << '\t';
	}
	cout << endl;

	system("pause");
}