// EE 569 Homework #3
// date:	Mar. 24th, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//*********************************************************
// Texture Segmentation for P1_b 
//*********************************************************


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <fstream>

using namespace std;

extern unsigned char Imagedata[100000000];
extern unsigned char Imagedataexp[100000000];
unsigned char ImagedataG[100000000] = { 0 };
unsigned char ImagedataG1[100000000] = { 0 };
double Imagedatatemp1[10000000] = { 0 };
double Imagedataexp1[10000000] = { 0 };
double Imagedatatempp[1000000][25] = { 0 };
double Imagedatatempp1[1000000][25] = { 0 };

extern double L5[5];
extern double E5[5];
extern double S5[5];
extern double W5[5];
extern double R5[5];

extern double avg(int BytesPerPixel, int *ImagedataOut, int Size1, int Size2, int type);
extern void CreFil(double *out, double *L, double *R);
extern void kmean_25(double vec[][25], int k, int cla, int *classi, int num, double cen[][25], int printornot);
extern void kmean_25_s(double vec[][25], int k, int cla, int *classi, int num, double cen[][25], int printornot);
extern double Edis_d(double *a, double *b, int dim);
extern double mini_d(double *d, int cla);
extern void Ext_c(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata, unsigned char *Imagedataex);
extern void CalNo(int BytesPerPixel, unsigned char *Imagedata, int *ImagedataOut, int Size1, int Size2, double *out);
extern void DelMean(int BytesPerPixel, unsigned char *Imagedata, double *ImagedataOut, int Size1, int Size2);
extern void CalNo_dd(int BytesPerPixel, double *Imagedata, double *ImagedataOut, int Size1, int Size2, double *out);

double maxi_absd(double *d, int cla)
{
	double m = abs(d[0]);
	for (int c = 0; c < cla; c++)
	{
		if (m < abs(d[c]))
		{
			m = abs(d[c]);
		}
	}
	return m;
}

void Ext_d(int BytesPerPixel, int Size1, int Size2, double *Imagedata, double *Imagedataex)//extend the image from x*y to (x+2)*(y+2)(input is char output is char)
{
	if (BytesPerPixel == 3)
	{
		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				Imagedataex[3 * ((Size1 + 2) * (i + 1) + j + 1) + 0] = Imagedata[3 * (Size1 * i + j) + 0];
				Imagedataex[3 * ((Size1 + 2) * (i + 1) + j + 1) + 1] = Imagedata[3 * (Size1 * i + j) + 1];
				Imagedataex[3 * ((Size1 + 2) * (i + 1) + j + 1) + 2] = Imagedata[3 * (Size1 * i + j) + 2];
			}
		}
		for (int j = 0; j < Size1; j++)
		{
			Imagedataex[3 * ((Size1 + 2) * 0 + j + 1) + 0] = Imagedata[3 * (Size1 * 0 + j) + 0];
			Imagedataex[3 * ((Size1 + 2) * 0 + j + 1) + 1] = Imagedata[3 * (Size1 * 0 + j) + 1];
			Imagedataex[3 * ((Size1 + 2) * 0 + j + 1) + 2] = Imagedata[3 * (Size1 * 0 + j) + 2];
			Imagedataex[3 * ((Size1 + 2) * (Size2 + 1) + j + 1) + 0] = Imagedata[3 * (Size1 * (Size2 - 1) + j) + 0];
			Imagedataex[3 * ((Size1 + 2) * (Size2 + 1) + j + 1) + 1] = Imagedata[3 * (Size1 * (Size2 - 1) + j) + 1];
			Imagedataex[3 * ((Size1 + 2) * (Size2 + 1) + j + 1) + 2] = Imagedata[3 * (Size1 * (Size2 - 1) + j) + 2];
		}
		for (int i = 0; i < (Size2 + 2); i++)
		{
			Imagedataex[3 * ((Size1 + 2) * i + 0) + 0] = Imagedataex[3 * ((Size1 + 2) * i + 1) + 0];
			Imagedataex[3 * ((Size1 + 2) * i + 0) + 1] = Imagedataex[3 * ((Size1 + 2) * i + 1) + 1];
			Imagedataex[3 * ((Size1 + 2) * i + 0) + 2] = Imagedataex[3 * ((Size1 + 2) * i + 1) + 2];
			Imagedataex[3 * ((Size1 + 2) * i + (Size2 + 1)) + 0] = Imagedataex[3 * ((Size1 + 2) * i + Size2) + 0];
			Imagedataex[3 * ((Size1 + 2) * i + (Size2 + 1)) + 1] = Imagedataex[3 * ((Size1 + 2) * i + Size2) + 1];
			Imagedataex[3 * ((Size1 + 2) * i + (Size2 + 1)) + 2] = Imagedataex[3 * ((Size1 + 2) * i + Size2) + 2];
		}
	}
	else if (BytesPerPixel == 1)
	{
		for (int i = 0; i<Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				Imagedataex[1 * ((Size1 + 2) * (i + 1) + j + 1) + 0] = Imagedata[1 * (Size1 * i + j) + 0];
			}
		}
		for (int j = 0; j < Size1; j++)
		{
			Imagedataex[1 * ((Size1 + 2) * 0 + j + 1) + 0] = Imagedata[1 * (Size1 * 0 + j) + 0];
			Imagedataex[1 * ((Size1 + 2) * (Size2 + 1) + j + 1) + 0] = Imagedata[1 * (Size1 * (Size2 - 1) + j) + 0];
		}
		for (int i = 0; i < (Size2 + 2); i++)
		{
			Imagedataex[1 * ((Size1 + 2) * i + 0) + 0] = Imagedataex[1 * ((Size1 + 2) * i + 1) + 0];
		}
		for (int i = 0; i < Size2 + 2; i++)//
		{
			for (int j = Size1 + 1; j < Size1 + 2; j++)//1
			{
				Imagedataex[1 * ((Size1 + 2) * i + (j)) + 0] = Imagedataex[1 * ((Size1 + 2) * i + j - 1) + 0];
				//cout << j + 1 << '\t' << (double)Imagedataex[BytesPerPixel * ((Size1 + 2) * (i)+(j)) + 0] << endl;
			}
		}
	}
}

void avgWin(int BytesPerPixel, double *Imagedatatemp1, int Size1, int Size2, double *Imagedatatemp2, int type)
//Window-approach Processing
{
	if (type == 1)
	{
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				int l = 15;
				double temp = 0;
				for (int m = 0; m < l; m++)
				{
					for (int n = 0; n < l; n++)
					{
						temp = temp + (double)(Imagedatatemp1[BytesPerPixel * ((Size1 + 16) * (i + 8 + m - (l - 1) / 2) + (j + 8 + n - (l - 1) / 2)) + 0] / 255) / l / l;
					}
				}
				Imagedatatemp2[BytesPerPixel * ((Size1) * (i)+(j)) + 0] = temp;
			}
		}
	}
	else
	{
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				int l = 7;
				double temp = 0;
				for (int m = 0; m < l; m++)
				{
					for (int n = 0; n < l; n++)
					{
						temp = temp + (double)(Imagedatatemp1[BytesPerPixel * ((Size1 + 16) * (i + 8 + m - (l - 1) / 2) + (j + 8 + n - (l - 1) / 2)) + 0] / 255) * (Imagedatatemp1[BytesPerPixel * ((Size1 + 16) * (i + 8 + m - (l - 1) / 2) + (j + 8 + n - (l - 1) / 2)) + 0] / 255) / l / l;
					}
				}
				temp = sqrt(temp);
				Imagedatatemp2[BytesPerPixel * ((Size1) * (i)+(j)) + 0] = temp;
			}
		}
	}
}

void CalNo_d(int BytesPerPixel, unsigned char *Imagedata, double *ImagedataOut, int Size1, int Size2, double *out)
{
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			double temp = 0;
			for (int m = 0; m < 5; m++)
			{
				for (int n = 0; n < 5; n++)
				{
					temp = temp + out[5 * m + n] * Imagedata[BytesPerPixel * ((Size1 + 4) * (i + 2 + m - 2) + (j + 2 + n - 2)) + 0];
				}
			}
			ImagedataOut[BytesPerPixel * ((Size1) * (i)+(j)) + 0] = temp;
		}
	}
}

void DOut(int BytesPerPixel, double *Imagedatatemp2, int Size1, int Size2, double *Imagedatatemp, int s)
{
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			Imagedatatemp[25 * ((Size1) * (i)+(j)) + s] = Imagedatatemp2[BytesPerPixel * ((Size1) * (i)+(j)) + 0];// - sum
		}
	}
}

void Deleavg(int BytesPerPixel, double *Imagedatatemp2, int Size1, int Size2, double *Imagedatatemp, int s)
//delete the DC value in the image
{
	double sum = 0;
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			sum = sum + (double)Imagedatatemp2[BytesPerPixel * ((Size1) * (i)+(j)) + 0] / Size2 / Size1;
		}
	}
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			Imagedatatemp[25 * ((Size1) * (i)+(j)) + s] = Imagedatatemp2[BytesPerPixel * ((Size1) * (i)+(j)) + 0] - sum;//
		}
	}
}

void Lawout(int BytesPerPixel, unsigned char *ImagedataG, int Size1, int Size2, double *Imagedatatemp, int type1)
{
	double Lawfil[25][25] = { 0 };
	CreFil(Lawfil[0], L5, L5);CreFil(Lawfil[1], L5, E5);CreFil(Lawfil[2], L5, S5);CreFil(Lawfil[3], L5, W5);CreFil(Lawfil[4], L5, R5);
	CreFil(Lawfil[5], E5, L5);CreFil(Lawfil[6], E5, E5);CreFil(Lawfil[7], E5, S5);CreFil(Lawfil[8], E5, W5);CreFil(Lawfil[9], E5, R5);
	CreFil(Lawfil[10], S5, L5);CreFil(Lawfil[11], S5, E5);CreFil(Lawfil[12], S5, S5);CreFil(Lawfil[13], S5, W5);CreFil(Lawfil[14], S5, R5);
	CreFil(Lawfil[15], W5, L5);CreFil(Lawfil[16], W5, E5);CreFil(Lawfil[17], W5, S5);CreFil(Lawfil[18], W5, W5);CreFil(Lawfil[19], W5, R5);
	CreFil(Lawfil[20], R5, L5);CreFil(Lawfil[21], R5, E5);CreFil(Lawfil[22], R5, S5);CreFil(Lawfil[23], R5, W5);CreFil(Lawfil[24], R5, R5);

	Ext_c(BytesPerPixel, Size1, Size2, ImagedataG, Imagedataexp);
	Ext_c(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataexp, ImagedataG);
	
	for (int s = 0; s < 25; s++)
	{
		if (type1 == 2)
		{
			double *Imagedatatemp2 = new double[(Size1) * (Size2)];
			double *ImagedataOutp = new double[(Size1 + 4) * (Size2 + 4)];

			DelMean(BytesPerPixel, ImagedataG, ImagedataOutp, (Size1 + 4), (Size2 + 4));
			CalNo_dd(BytesPerPixel, ImagedataOutp, Imagedatatemp1, Size1, Size2, Lawfil[s]);

			Ext_d(BytesPerPixel, Size1, Size2, Imagedatatemp1, Imagedataexp1);
			Ext_d(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataexp1, Imagedatatemp1);
			Ext_d(BytesPerPixel, Size1 + 4, Size2 + 4, Imagedatatemp1, Imagedataexp1);
			Ext_d(BytesPerPixel, Size1 + 6, Size2 + 6, Imagedataexp1, Imagedatatemp1);
			Ext_d(BytesPerPixel, Size1 + 8, Size2 + 8, Imagedatatemp1, Imagedataexp1);
			Ext_d(BytesPerPixel, Size1 + 10, Size2 + 10, Imagedataexp1, Imagedatatemp1);
			Ext_d(BytesPerPixel, Size1 + 12, Size2 + 12, Imagedatatemp1, Imagedataexp1);
			Ext_d(BytesPerPixel, Size1 + 14, Size2 + 14, Imagedataexp1, Imagedatatemp1);
			avgWin(BytesPerPixel, Imagedatatemp1, Size1, Size2, Imagedatatemp2, 1);
			DOut(BytesPerPixel, Imagedatatemp2, Size1, Size2, Imagedatatemp, s);
		}
		if (type1 == 1)
		{
			double *Imagedatatemp2 = new double[(Size1) * (Size2)];

			CalNo_d(BytesPerPixel, ImagedataG, Imagedatatemp1, Size1, Size2, Lawfil[s]);

			Ext_d(BytesPerPixel, Size1, Size2, Imagedatatemp1, Imagedataexp1);
			Ext_d(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataexp1, Imagedatatemp1);
			Ext_d(BytesPerPixel, Size1 + 4, Size2 + 4, Imagedatatemp1, Imagedataexp1);
			Ext_d(BytesPerPixel, Size1 + 6, Size2 + 6, Imagedataexp1, Imagedatatemp1);
			Ext_d(BytesPerPixel, Size1 + 8, Size2 + 8, Imagedatatemp1, Imagedataexp1);
			Ext_d(BytesPerPixel, Size1 + 10, Size2 + 10, Imagedataexp1, Imagedatatemp1);
			Ext_d(BytesPerPixel, Size1 + 12, Size2 + 12, Imagedatatemp1, Imagedataexp1);
			Ext_d(BytesPerPixel, Size1 + 14, Size2 + 14, Imagedataexp1, Imagedatatemp1);
			avgWin(BytesPerPixel, Imagedatatemp1, Size1, Size2, Imagedatatemp2, 2);
			Deleavg(BytesPerPixel, Imagedatatemp2, Size1, Size2, Imagedatatemp, s);
		}
		if (type1 == 3)
		{
			double *Imagedatatemp2 = new double[(Size1) * (Size2)];
			double *ImagedataOutp = new double[(Size1 + 4) * (Size2 + 4)];

			DelMean(BytesPerPixel, ImagedataG, ImagedataOutp, (Size1 + 4), (Size2 + 4));
			CalNo_dd(BytesPerPixel, ImagedataOutp, Imagedatatemp1, Size1, Size2, Lawfil[s]);

			Ext_d(BytesPerPixel, Size1, Size2, Imagedatatemp1, Imagedataexp1);
			Ext_d(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataexp1, Imagedatatemp1);
			Ext_d(BytesPerPixel, Size1 + 4, Size2 + 4, Imagedatatemp1, Imagedataexp1);
			Ext_d(BytesPerPixel, Size1 + 6, Size2 + 6, Imagedataexp1, Imagedatatemp1);
			Ext_d(BytesPerPixel, Size1 + 8, Size2 + 8, Imagedatatemp1, Imagedataexp1);
			Ext_d(BytesPerPixel, Size1 + 10, Size2 + 10, Imagedataexp1, Imagedatatemp1);
			Ext_d(BytesPerPixel, Size1 + 12, Size2 + 12, Imagedatatemp1, Imagedataexp1);
			Ext_d(BytesPerPixel, Size1 + 14, Size2 + 14, Imagedataexp1, Imagedatatemp1);
			avgWin(BytesPerPixel, Imagedatatemp1, Size1, Size2, Imagedatatemp2, 2);
			DOut(BytesPerPixel, Imagedatatemp2, Size1, Size2, Imagedatatemp, s);
		}
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				//cout << Imagedatatemp[25 * ((Size1) * (i)+(j)) + s] << endl;
			}
		}
	}
}

void RGB2G(int BytesPerPixel, unsigned char *Imagedata, unsigned char *ImagedataG, int Size1, int Size2)
//Turn the color image into Gray image
{
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			double temp, temp1, temp2, temp3;
			temp1 = Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + 0];
			temp2 = Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + 1];
			temp3 = Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + 2];
			temp = 0.5870 * temp1 + 0.2989 * temp2 + 0.1140 * temp3;
			if (temp >= 255)
			{
				ImagedataG[1 * ((Size1) * (i)+(j)) + 0] = 255;
			}
			else
			{
				ImagedataG[1 * ((Size1) * (i)+(j)) + 0] = temp;
			}
		}
	}
}

void Cal25D23D(int BytesPerPixel, double Imagedatatempp[][25], int Size1, int Size2, double Imagedatatempp1[][25], double PCA[][25], int dim)
{
	for (int n = 0; n < (Size2 * Size1); n++)
	{
		for (int d0 = 0; d0 < 25; d0++)
		{
			double temp = 0;
			if (d0 < dim)
			{
				for (int d1 = 0; d1 < 25; d1++)
				{
					temp = temp + PCA[d0][d1] * Imagedatatempp[n][d1] / 1000;
				}
			}
			else
			{
				temp = 0;
			}
			Imagedatatempp1[n][d0] = temp;
		}
	}
}

void P1_b(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2)
{
	FILE *file;

	double vec[18][25] = { 0 };
	double vec_3[18][3] = { 0 };
	double veco[10][25] = { 0 };
	double veco_3[10][3] = { 0 };
	int *classi = new int [Size1 * Size2];
	int classi_3[18] = { 0 };
	double cen[10][25] = { 0 };
	double cen_3[10][3] = { 0 };
	double cen_8[10][8] = { 0 };

	if (!(file = fopen(a1, "rb"))) {
		cout << "Cannot open file: " << a1 << endl;
		system("pause");
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);

	RGB2G(BytesPerPixel, Imagedata, ImagedataG, Size1, Size2);

	if (!(file = fopen("D:/EE569_Assignment/3/P1/kitten_G.raw", "wb"))) {
		cout << "Cannot open file: " << a2 << endl;
		exit(1);
	}
	fwrite(ImagedataG, sizeof(unsigned char), Size2*Size1 * 1, file);
	fclose(file);

	double *Imagedatatemp = new double [(Size1) * (Size2) * 25];

	int type1 = 3;//use the AC value of the image and do the RMS
	//cout << "Which type do you want 1)DC first 2)AC first: ";
	//cin >> type1;

	Lawout(1, ImagedataG, Size1, Size2, Imagedatatemp, type1);

	for (int s = 0; s < 25; s++)
	{
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				Imagedatatempp[(Size1) * (i)+(j)][s] = (Imagedatatemp[25 * ((Size1) * (i)+(j)) + s]);
			}
		}
	}

	int printout;
	cout << "Whether to print the points 1)Yes 2) No: ";
	cin >> printout;

	if (printout == 1)
	{
		if (type1 == 1)
		{
			char *aaa = { "D:/EE569_Assignment/3/P1/KittyDC.txt" };
			//the Law filter result of use the origin value of the image and do the RMS

			ofstream outfile;
			outfile.open(aaa);
			if (outfile.is_open())
			{
				for (int n = 0; n < Size1 * Size2; n++)
				{
					for (int d = 0; d < 25; d++)
					{
						outfile << Imagedatatempp[n][d] << endl;
					}
				}
			}
			outfile.close();
			system("pause");
		}
		if (type1 == 2)
		{
			char *aaa = { "D:/EE569_Assignment/3/P1/KittyAC.txt" };
			//the Law filter result of use the AC value of the image and do the average

			ofstream outfile;
			outfile.open(aaa);
			if (outfile.is_open())
			{
				for (int n = 0; n < Size1 * Size2; n++)
				{
					for (int d = 0; d < 25; d++)
					{
						outfile << Imagedatatempp[n][d] << endl;
					}
				}
			}
			outfile.close();
			system("pause");
		}
		if (type1 == 3)
		{
			char *aaa = { "D:/EE569_Assignment/3/P1/KittyAC1.txt" };
			//the Law filter result of use the AC value of the image and do the RMS

			ofstream outfile;
			outfile.open(aaa);
			if (outfile.is_open())
			{
				for (int n = 0; n < Size1 * Size2; n++)
				{
					for (int d = 0; d < 25; d++)
					{
						outfile << Imagedatatempp[n][d] << endl;
					}
				}
			}
			outfile.close();
			system("pause");
		}
		exit(1);
	}

	int dimension;
	cout << "Which dimension do you want 1) 25 2) other: ";
	cin >> dimension;

	if (dimension == 1)
	{
		double *max = new double[25];

		for (int s = 0; s < 25; s++)
		{
			double *Imagedatatt = new double[(Size1) * (Size2)];
			for (int i = 0; i < Size2; i++)
			{
				for (int j = 0; j < Size1; j++)
				{
					Imagedatatt[(Size1) * (i)+(j)] = Imagedatatemp[25 * ((Size1) * (i)+(j)) + s];
				}
			}
			max[s] = maxi_absd(Imagedatatt, (Size1) * (Size2));
		}

		int Normal;
		cout << "Do which approach: 1) Normalization; 2) Own Solution: ";
		cin >> Normal;

		double *Imagedatatt = new double[(Size1) * (Size2)];

		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				Imagedatatt[(Size1) * (i)+(j)] = Imagedatatempp[((Size1) * (i)+(j))][0];
			}
		}

		for (int s = 0; s < 25; s++)
		{
			for (int i = 0; i < Size2; i++)
			{
				for (int j = 0; j < Size1; j++)
				{
					if (Normal == 2)
					{
						Imagedatatempp[(Size1) * (i)+(j)][s] = (double)Imagedatatempp[(Size1) * (i)+(j)][s] * max[0] / max[s];
					}
					else
					{
						Imagedatatempp[(Size1) * (i)+(j)][s] = (double)Imagedatatempp[(Size1) * (i)+(j)][s] * 1000 / (double)Imagedatatt[(Size1) * (i)+(j)];
					}
				}
			}
		}
		int classs;
		cout << "input the number of class you want: ";
		cin >> classs;
		kmean_25_s(Imagedatatempp, 100, classs, classi, (Size1 * Size2), cen, 2);
	}
	else
	{
		double PCA[25][25] = { 0 };

		if (type1 == 3)
		{
			ifstream infile;

			infile.open("D:/EE569_Assignment/3/MATLAB/dataAC1.txt");
			//the PCA Matrix for Law filter result of use the AC value of the image and do the RMS

			double* ptr = &PCA[0][0];

			while (!infile.eof())
			{
				infile >> *ptr;
				ptr++;
			}

			infile.close();
		}
		else if(type1 == 2)
		{
			ifstream infile;

			infile.open("D:/EE569_Assignment/3/MATLAB/dataAC.txt");
			//the PCA Matrix for the Law filter result of use the AC value of the image and do the average

			double* ptr = &PCA[0][0];

			while (!infile.eof())
			{
				infile >> *ptr;
				ptr++;
			}

			infile.close();
		}
		else
		{
			ifstream infile;

			infile.open("D:/EE569_Assignment/3/MATLAB/dataDC.txt");
			//the PCA Matrix for the Law filter result of use the origin value of the image and do the RMS

			double* ptr = &PCA[0][0];

			while (!infile.eof())
			{
				infile >> *ptr;
				ptr++;
			}

			infile.close();
		}

		int dim;//dimension of PCA
		cout << "Input the dimension: " << endl;
		cin >> dim;

		Cal25D23D(1, Imagedatatempp, Size1, Size2, Imagedatatempp1, PCA, dim);

		double *max = new double[25];

		for (int s = 0; s < dim; s++)
		{
			double *Imagedatatt = new double[(Size1) * (Size2)];
			for (int i = 0; i < Size2; i++)
			{
				for (int j = 0; j < Size1; j++)
				{
					Imagedatatt[(Size1) * (i)+(j)] = Imagedatatempp1[((Size1) * (i)+(j))][s];
				}
			}
			max[s] = maxi_absd(Imagedatatt, (Size1) * (Size2));
		}

		int Normal;
		cout << "Do which approach: 1) Normalization; 2) Own Solution: ";
		cin >> Normal;

		double *Imagedatatt = new double[(Size1) * (Size2)];

		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				Imagedatatt[(Size1) * (i)+(j)] = Imagedatatempp1[((Size1) * (i)+(j))][0];
			}
		}

		for (int s = 0; s < dim; s++)
		{
			for (int i = 0; i < Size2; i++)
			{
				for (int j = 0; j < Size1; j++)
				{
					if (Normal == 2)
					{
						Imagedatatempp1[(Size1) * (i)+(j)][s] = (double)Imagedatatempp1[(Size1) * (i)+(j)][s] * max[0] / max[s];
					}
					else
					{
						Imagedatatempp1[(Size1) * (i)+(j)][s] = (double)Imagedatatempp1[(Size1) * (i)+(j)][s] * 1000 / (double)Imagedatatt[(Size1) * (i)+(j)];
					}
				}
			}
		}

		kmean_25_s(Imagedatatempp1, 100, 3, classi, (Size1 * Size2), cen, 2);
	}
	
	//coloring the pixel with the same group
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			if (classi[(Size1) * (i)+(j)] == 0)
			{
				Imagedata[3 * ((Size1) * (i)+(j)) + 0] = 225;
				Imagedata[3 * ((Size1) * (i)+(j)) + 1] = 0;
				Imagedata[3 * ((Size1) * (i)+(j)) + 2] = 0;
			}
			if (classi[(Size1) * (i)+(j)] == 1)
			{
				Imagedata[3 * ((Size1) * (i)+(j)) + 0] = 0;
				Imagedata[3 * ((Size1) * (i)+(j)) + 1] = 255;
				Imagedata[3 * ((Size1) * (i)+(j)) + 2] = 0;
			}
			if (classi[(Size1) * (i)+(j)] == 2)
			{
				Imagedata[3 * ((Size1) * (i)+(j)) + 0] = 0;
				Imagedata[3 * ((Size1) * (i)+(j)) + 1] = 0;
				Imagedata[3 * ((Size1) * (i)+(j)) + 2] = 255;
			}
			if (classi[(Size1) * (i)+(j)] == 3)
			{
				Imagedata[3 * ((Size1) * (i)+(j)) + 0] = 0;
				Imagedata[3 * ((Size1) * (i)+(j)) + 1] = 0;
				Imagedata[3 * ((Size1) * (i)+(j)) + 2] = 0;
			}
			if (classi[(Size1) * (i)+(j)] == 4)
			{
				Imagedata[3 * ((Size1) * (i)+(j)) + 0] = 255;
				Imagedata[3 * ((Size1) * (i)+(j)) + 1] = 255;
				Imagedata[3 * ((Size1) * (i)+(j)) + 2] = 255;
			}
			if (classi[(Size1) * (i)+(j)] == 5)
			{
				Imagedata[3 * ((Size1) * (i)+(j)) + 0] = 0;
				Imagedata[3 * ((Size1) * (i)+(j)) + 1] = 255;
				Imagedata[3 * ((Size1) * (i)+(j)) + 2] = 255;
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