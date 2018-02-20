// EE 569 Homework #3
// date:	Mar. 24th, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//*********************************************************
// Texture Classification for P1_a (Unsupervised)
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
unsigned char Imagedatatest[6][1000000] = { 0 };

double L5[5] = { 1,4,6,4,1 };
double E5[5] = { -1,-2,0,2,1 };
double S5[5] = { -1,0,2,0,-1 };
double W5[5] = { -1,2,0,-2,1 };
double R5[5] = { 1,-4,6,-4,1 };

extern double maxi_absd(double *d, int cla);
extern void CalNo_d(int BytesPerPixel, unsigned char *Imagedata, double *ImagedataOut, int Size1, int Size2, double *out);
extern void Deleavg(int BytesPerPixel, double *Imagedatatemp2, int Size1, int Size2, double *Imagedatatemp, int s);
extern void RGB2G(int BytesPerPixel, unsigned char *Imagedata, unsigned char *ImagedataG, int Size1, int Size2);

void Ext_c(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata, unsigned char *Imagedataex)//extend the image from x*y to (x+2)*(y+2)(input is char output is char)
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

void CreFil(double *out, double *L, double *R)//create the Law filter
{
	int col = 5;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			out[col * i + j] = L[i] * R[j];
		}
	}
}

void CalNo(int BytesPerPixel, unsigned char *Imagedata, int *ImagedataOut, int Size1, int Size2, double *out)
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

void CalNo_dd(int BytesPerPixel, double *Imagedata, double *ImagedataOut, int Size1, int Size2, double *out)
//calculate the output of law filter
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

void DelMean(int BytesPerPixel, unsigned char *Imagedata, double *ImagedataOut, int Size1, int Size2)
{
	double avg = 0;
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			avg = avg + (double)Imagedata[BytesPerPixel * ((Size1) * (i) + (j)) + 0] / (Size1 * Size2);
		}
	}
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			ImagedataOut[BytesPerPixel * ((Size1) * (i)+(j)) + 0] = (double)Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + 0] - avg;
		}
	}
}

double avg_dd(int BytesPerPixel, double *ImagedataOut, int Size1, int Size2, int type)
{
	double avg, sum = 0;
	if (type == 1)
	{
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				sum = sum + ((double)ImagedataOut[BytesPerPixel * ((Size1) * (i)+(j)) + 0] / 255);
			}
		}
		avg = sum / Size1 / Size2;
		return avg;
	}
	else if(type == 2)
	{
		sum = 0;
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				sum = sum + (double)((double)ImagedataOut[BytesPerPixel * ((Size1) * (i)+(j)) + 0] / 255) * ((double)ImagedataOut[BytesPerPixel * ((Size1) * (i)+(j)) + 0] / 255) / Size1 / Size2;
			}
		}
		avg = sqrt(sum);
		return avg;
	}
	else if (type == 3)
	{
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				sum = sum + abs((double)ImagedataOut[BytesPerPixel * ((Size1) * (i)+(j)) + 0] / 255);
			}
		}
		avg = sum / Size1 / Size2;
		return avg;
	}
}

double avg(int BytesPerPixel, int *ImagedataOut, int Size1, int Size2, int type)
{
	double avg, sum = 0;
	if (type == 1 || type == 2)
	{
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				sum = sum + ((double)ImagedataOut[BytesPerPixel * ((Size1) * (i)+(j)) + 0]);
			}
		}
		avg = sum / Size1 / Size2;
		if (type == 1)
		{
			return avg;
		}
		else if (type == 2)
		{
			int *Imagedatatemp = new int[(Size1) * (Size2)];
			for (int i = 0; i < Size2; i++)
			{
				for (int j = 0; j < Size1; j++)
				{
					Imagedatatemp[BytesPerPixel * ((Size1) * (i)+(j)) + 0] = ((double)ImagedataOut[BytesPerPixel * ((Size1) * (i)+(j)) + 0]) - avg;
				}
			}
			sum = 0;
			for (int i = 0; i < Size2; i++)
			{
				for (int j = 0; j < Size1; j++)
				{
					sum = sum + (double)(Imagedatatemp[BytesPerPixel * ((Size1) * (i)+(j)) + 0]) * (Imagedatatemp[BytesPerPixel * ((Size1) * (i)+(j)) + 0]) / Size1 / Size2;
				}
			}
			avg = sqrt(sum);
			return avg;
		}
	}
	else if (type == 3)
	{
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				sum = sum + abs((double)ImagedataOut[BytesPerPixel * ((Size1) * (i)+(j)) + 0]);
			}
		}
		avg = sum / Size1 / Size2;
		return avg;
	}
}

void THVOut(int BytesPerPixel, unsigned char *Imagedata, int Size1, int Size2, double *ouc)
{
	double Lawfil[25][25] = { 0 };
	CreFil(Lawfil[0], L5, L5);CreFil(Lawfil[1], L5, E5);CreFil(Lawfil[2], L5, S5);CreFil(Lawfil[3], L5, W5);CreFil(Lawfil[4], L5, R5);
	CreFil(Lawfil[5], E5, L5);CreFil(Lawfil[6], E5, E5);CreFil(Lawfil[7], E5, S5);CreFil(Lawfil[8], E5, W5);CreFil(Lawfil[9], E5, R5);
	CreFil(Lawfil[10], S5, L5);CreFil(Lawfil[11], S5, E5);CreFil(Lawfil[12], S5, S5);CreFil(Lawfil[13], S5, W5);CreFil(Lawfil[14], S5, R5);
	CreFil(Lawfil[15], W5, L5);CreFil(Lawfil[16], W5, E5);CreFil(Lawfil[17], W5, S5);CreFil(Lawfil[18], W5, W5);CreFil(Lawfil[19], W5, R5);
	CreFil(Lawfil[20], R5, L5);CreFil(Lawfil[21], R5, E5);CreFil(Lawfil[22], R5, S5);CreFil(Lawfil[23], R5, W5);CreFil(Lawfil[24], R5, R5);

	Ext_c(BytesPerPixel, Size1, Size2, Imagedata, Imagedataexp);
	Ext_c(BytesPerPixel, Size1 + 2, Size2 + 2, Imagedataexp, Imagedata);

	double avg0[25];

	double *Imagedatatemp = new double[(Size1) * (Size2)];
	double *ImagedataOutp = new double[(Size1 + 4) * (Size2 + 4)];

	for (int s = 0; s < 25; s++)
	{
		DelMean(BytesPerPixel, Imagedata, ImagedataOutp, (Size1 + 4), (Size2 + 4));
		CalNo_dd(BytesPerPixel, ImagedataOutp, Imagedatatemp, Size1, Size2, Lawfil[s]);
		avg0[s] = avg_dd(BytesPerPixel, Imagedatatemp, Size1, Size2, 2);//do the Root Mean square
		ouc[s] = avg0[s];
	}
}

double Edis_d(double *a, double *b, int dim)//calculate the distance (do not consider the first dimension)
{
	double sum = 0;
	for (int s = 1; s < dim; s++)
	{
		sum = sum + (a[s] - b[s]) * (a[s] - b[s]);
	}
	sum = sqrt(sum);
	return sum;
}

double Edis_d1(double *a, double *b, int dim)//calculate the distance (Consider the first dimension)
{
	double sum = 0;
	for (int s = 0; s < dim; s++)
	{
		sum = sum + (a[s] - b[s]) * (a[s] - b[s]);
	}
	sum = sqrt(sum);
	return sum;
}

void avg_25(double *a, double vec[][25], int *classi, int l, int cla, int num)//average for 25-D vectors
{
	double sum[25] = { 0 };
	for (int sa = 0; sa < num; sa++)
	{
		if (classi[sa] == cla)
		{
			for (int s = 0; s < 25; s++)
			{
				sum[s] = sum[s] + vec[sa][s];
			}
		}
	}
	for (int s = 0; s < 25; s++)
	{
		a[s] = sum[s] / l;
	}
}

void avg_128(double *a, double vec[][128], int *classi, int l, int cla, int num)//average for 128-D vectors
{
	double sum[128] = { 0 };
	for (int sa = 0; sa < num; sa++)
	{
		if (classi[sa] == cla)
		{
			for (int s = 0; s < 128; s++)
			{
				sum[s] = sum[s] + vec[sa][s];
			}
		}
	}
	for (int s = 0; s < 128; s++)
	{
		a[s] = sum[s] / l;
	}
}

double mini_d(double *d, int cla)
{
	double m = d[0];
	for (int c = 0; c < cla; c++)
	{
		if (m > d[c])
		{
			m = d[c];
		}
	}
	return m;
}

double maxi_d(double *d, int cla)
{
	double m = d[0];
	for (int c = 0; c < cla; c++)
	{
		if (m < d[c])
		{
			m = d[c];
		}
	}
	return m;
}

void randge(int *ind, int classi, int num)//random number generator
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < classi; i++)
	{
		ind[i] = rand() % num;
		for (int j = 0; j < i; j++)
		{
			if (ind[i] == ind[j])
			{
				ind[i] = rand() % num;
				j = 0;
			}
		}
	}
	for (int i = 0; i < classi; i++)
	{
		cout << ind[i] << endl;
	}
}

void kmean_128(double vec[][128], int k, int cla, int *classi, int num, double cen[][128], int printornot)
//K-means for 128-D vector
{
	double **a = new double*[cla];
	for (int c = 0; c < cla; c++)
	{
		a[c] = new double[128];
	}

	int method;
	cout << "Which Initialization method: 1) ramdom 2) maximum min-value 3) AS: ";
	cin >> method;

	if (method == 1)//random initialzation method
	{
		int *ind = new int[cla];

		randge(ind, cla, num);

		for (int c = 0; c < cla; c++)
		{
			for (int s = 0; s < 128; s++)
			{
				int ii = ind[c];
				a[c][s] = vec[ii][s];
			}
		}
	}
	else if (method == 2)//maximum min-value initialzation method
	{
		for (int c = 0; c < cla; c++)
		{
			int ii;
			double *dmin = new double[num];
			double dmax;
			if (c == 0)
			{
				int ind[1];
				randge(ind, 1, num);
				ii = ind[0];
			}
			else
			{
				for (int n = 0;n < num; n++)
				{
					double *d = new double[c];
					for (int c0 = 0; c0 < c; c0++)
					{
						d[c0] = Edis_d(a[c0], vec[n], 128);
					}
					dmin[n] = mini_d(d, c);
				}
				dmax = maxi_d(dmin, num);
				for (int n = 0; n < num; n++)
				{
					if (dmax == dmin[n])
					{
						ii = n;
					}
				}
			}
			for (int s = 0; s < 128; s++)
			{
				a[c][s] = vec[ii][s];
			}
		}
	}
	else if (method == 3)
	{
		for (int c = 0; c < cla; c++)
		{
			int ii;
			double *dmin = new double[num];
			double dmax;
			if (c == 0)
			{
				for (int s = 0; s < 128; s++)
				{
					double ttemp = 0;
					for (int n = 0; n < num; n++)
					{
						ttemp = ttemp + (double)vec[n][s] / num;
					}
					a[c][s] = ttemp;
				}
			}
			else
			{
				for (int n = 0;n < num; n++)
				{
					double *d = new double[c];
					for (int c0 = 0; c0 < c; c0++)
					{
						d[c0] = Edis_d(a[c0], vec[n], 128);
					}
					dmin[n] = mini_d(d, c);
				}
				dmax = maxi_d(dmin, num);
				for (int n = 0; n < num; n++)
				{
					if (dmax == dmin[n])
					{
						ii = n;
					}
				}
				for (int s = 0; s < 128; s++)
				{
					a[c][s] = vec[ii][s];
				}
			}
		}
	}

	//system("pause");

	int *l = new int[cla];
	for (int kk = 0; kk < k; kk++)
	{
		for (int c = 0; c < cla; c++)
		{
			l[c] = 0;
		}
		for (int sa = 0; sa < num; sa++)
		{
			double *d = new double[cla];
			for (int c = 0; c < cla; c++)
			{
				d[c] = Edis_d(a[c], vec[sa], 128);
			}
			double dmin;
			dmin = mini_d(d, cla);
			for (int c = 0; c < cla; c++)
			{
				if (dmin == d[c])
				{
					classi[sa] = c;
					l[c] = l[c] + 1;
					break;
				}
			}
		}

		for (int c = 0; c < cla; c++)
		{
			avg_128(a[c], vec, classi, l[c], c, num);
		}
	}

	if (printornot == 1)
	{
		for (int as = 0; as < num; as++)
		{
			cout << classi[as] << '\t';
		}
		cout << endl;
	}

	for (int c = 0; c < cla; c++)
	{
		for (int s = 0; s < 128; s++)
		{
			cen[c][s] = a[c][s];
		}
	}
}

void kmean_25(double vec[][25], int k, int cla, int *classi, int num, double cen[][25], int printornot)
//K-means for 25-D vector (without consider the first dimension)
{
	double **a = new double*[cla];
	for (int c = 0; c < cla; c++)
	{
		a[c] = new double[25];
	}

	int method;
	cout << "Which Initialization method: 1) ramdom 2) maximum min-value 3) AS: ";
	cin >> method;

	if (method == 1)
	{
		int *ind = new int[cla];

		randge(ind, cla, num);

		for (int c = 0; c < cla; c++)
		{
			for (int s = 0; s < 25; s++)
			{
				int ii = ind[c];
				a[c][s] = vec[ii][s];
			}
		}
	}
	else if (method == 2)
	{
		for (int c = 0; c < cla; c++)
		{
			int ii;
			double *dmin = new double [num];
			double dmax;
			if (c == 0)
			{
				int ind[1];
				randge(ind, 1, num);
				ii = ind[0];
			}
			else
			{
				for (int n = 0;n < num; n++)
				{
					double *d = new double[c];
					for (int c0 = 0; c0 < c; c0++)
					{
						d[c0] = Edis_d(a[c0], vec[n], 25);
					}
					dmin[n] = mini_d(d, c);
				}
				dmax = maxi_d(dmin, num);
				for (int n = 0; n < num; n++)
				{
					if (dmax == dmin[n])
					{
						ii = n;
					}
				}
			}
			for (int s = 0; s < 25; s++)
			{
				a[c][s] = vec[ii][s];
			}
		}
	}
	else if (method == 3)
	{
		for (int c = 0; c < cla; c++)
		{
			int ii;
			double *dmin = new double[num];
			double dmax;
			if (c == 0)
			{
				for (int s = 0; s < 25; s++)
				{
					double ttemp = 0;
					for (int n = 0; n < num; n++)
					{
						ttemp = ttemp + (double)vec[n][s] / num;
					}
					a[c][s] = ttemp;
				}
			}
			else
			{
				for (int n = 0;n < num; n++)
				{
					double *d = new double[c];
					for (int c0 = 0; c0 < c; c0++)
					{
						d[c0] = Edis_d(a[c0], vec[n], 25);
					}
					dmin[n] = mini_d(d, c);
				}
				dmax = maxi_d(dmin, num);
				for (int n = 0; n < num; n++)
				{
					if (dmax == dmin[n])
					{
						ii = n;
					}
				}
				for (int s = 0; s < 25; s++)
				{
					a[c][s] = vec[ii][s];
				}
			}
		}
	}

	//system("pause");
	
	int *l = new int[cla];
	for (int kk = 0; kk < k; kk++)
	{
		for (int c = 0; c < cla; c++)
		{
			l[c] = 0;
		}
		for (int sa = 0; sa < num; sa++)
		{
			double *d = new double[cla];
			for (int c = 0; c < cla; c++)
			{
				d[c] = Edis_d(a[c], vec[sa], 25);
			}
			double dmin;
			dmin = mini_d(d, cla);
			for (int c = 0; c < cla; c++)
			{
				if (dmin == d[c])
				{
					classi[sa] = c;
					l[c] = l[c] + 1;
					break;
				}
			}
		}
		
		for (int c = 0; c < cla; c++)
		{
			avg_25(a[c], vec, classi, l[c], c, num);
		}
	}
	
	if (printornot == 1)
	{
		cout << "The classification result training 1-12 images is: " << endl;
		for (int as = 0; as < num; as++)
		{
			cout << classi[as] << '\t';
		}
		cout << endl;
	}
	
	for (int c = 0; c < cla; c++)
	{
		for (int s = 0; s < 25; s++)
		{
			cen[c][s] = a[c][s];
		}
	}
}

void kmean_25_s(double vec[][25], int k, int cla, int *classi, int num, double cen[][25], int printornot)
//K-means for 25-D vector (consider all dimension)
{
	double **a = new double*[cla];
	for (int c = 0; c < cla; c++)
	{
		a[c] = new double[25];
	}

	int method;
	cout << "Which Initialization method: 1) ramdom 2) maximum min-value 3) AS: ";
	cin >> method;

	if (method == 1)
	{
		int *ind = new int[cla];

		randge(ind, cla, num);

		for (int c = 0; c < cla; c++)
		{
			for (int s = 0; s < 25; s++)
			{
				int ii = ind[c];
				a[c][s] = vec[ii][s];
			}
		}
	}
	else if (method == 2)
	{
		for (int c = 0; c < cla; c++)
		{
			int ii;
			double *dmin = new double[num];
			double dmax;
			if (c == 0)
			{
				int ind[1];
				randge(ind, 1, num);
				ii = ind[0];
			}
			else
			{
				for (int n = 0;n < num; n++)
				{
					double *d = new double[c];
					for (int c0 = 0; c0 < c; c0++)
					{
						d[c0] = Edis_d(a[c0], vec[n], 25);
					}
					dmin[n] = mini_d(d, c);
				}
				dmax = maxi_d(dmin, num);
				for (int n = 0; n < num; n++)
				{
					if (dmax == dmin[n])
					{
						ii = n;
					}
				}
			}
			for (int s = 0; s < 25; s++)
			{
				a[c][s] = vec[ii][s];
			}
		}
	}
	else if (method == 3)
	{
		for (int c = 0; c < cla; c++)
		{
			int ii;
			double *dmin = new double[num];
			double dmax;
			if (c == 0)
			{
				for (int s = 0; s < 25; s++)
				{
					double ttemp = 0;
					for (int n = 0; n < num; n++)
					{
						ttemp = ttemp + (double)vec[n][s] / num;
					}
					a[c][s] = ttemp;
				}
			}
			else
			{
				for (int n = 0;n < num; n++)
				{
					double *d = new double[c];
					for (int c0 = 0; c0 < c; c0++)
					{
						d[c0] = Edis_d(a[c0], vec[n], 25);
					}
					dmin[n] = mini_d(d, c);
				}
				dmax = maxi_d(dmin, num);
				for (int n = 0; n < num; n++)
				{
					if (dmax == dmin[n])
					{
						ii = n;
					}
				}
				for (int s = 0; s < 25; s++)
				{
					a[c][s] = vec[ii][s];
				}
			}
		}
	}

	//system("pause");

	int *l = new int[cla];
	for (int kk = 0; kk < k; kk++)
	{
		for (int c = 0; c < cla; c++)
		{
			l[c] = 0;
		}
		for (int sa = 0; sa < num; sa++)
		{
			double *d = new double[cla];
			for (int c = 0; c < cla; c++)
			{
				d[c] = Edis_d1(a[c], vec[sa], 25);
			}
			double dmin;
			dmin = mini_d(d, cla);
			for (int c = 0; c < cla; c++)
			{
				if (dmin == d[c])
				{
					classi[sa] = c;
					l[c] = l[c] + 1;
					break;
				}
			}
		}

		for (int c = 0; c < cla; c++)
		{
			avg_25(a[c], vec, classi, l[c], c, num);
		}
	}

	if (printornot == 1)
	{
		cout << "The classification result training 1-12 images is: " << endl;
		for (int as = 0; as < num; as++)
		{
			cout << classi[as] << '\t';
		}
		cout << endl;
	}

	for (int c = 0; c < cla; c++)
	{
		for (int s = 0; s < 25; s++)
		{
			cen[c][s] = a[c][s];
		}
	}
}

void Cal25D23D1(int BytesPerPixel, double Imagedatatempp[][25], int Size1, int Size2, double Imagedatatempp1[][25], double PCA[][25], int dim)
//Use the PCA Matrix to decrease the dimension
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
					temp = temp + (double)PCA[d0][d1] * Imagedatatempp[n][d1] / 1000;
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

void P1_a(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2)
{
	FILE *file;

	// Read image (filename specified by first argument) into image data matrix
	
	double vec[18][25] = { 0 };
	double vec_n[18][25] = { 0 };
	double veco[6][25] = { 0 };
	double veco_3[6][25] = { 0 };
	double veco_3n[6][25] = { 0 };
	int classi[18] = { 0 };
	int classi_3[18] = { 0 };
	double cen[4][25] = { 0 };
	double cen_n[4][25] = { 0 };

	char *a[16] = { "D:/EE569_Assignment/3/P1/Texture1.raw", "D:/EE569_Assignment/3/P1/Texture2.raw",\
		"D:/EE569_Assignment/3/P1/Texture3.raw", "D:/EE569_Assignment/3/P1/Texture4.raw",\
		"D:/EE569_Assignment/3/P1/Texture5.raw", "D:/EE569_Assignment/3/P1/Texture6.raw",\
		"D:/EE569_Assignment/3/P1/Texture7.raw", "D:/EE569_Assignment/3/P1/Texture8.raw", \
		"D:/EE569_Assignment/3/P1/Texture9.raw", "D:/EE569_Assignment/3/P1/Texture10.raw", \
		"D:/EE569_Assignment/3/P1/Texture11.raw", "D:/EE569_Assignment/3/P1/Texture12.raw"};

	for (int k0 = 0; k0 < 12; k0++)
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
		THVOut(BytesPerPixel, Imagedata, Size1, Size2, vec[k0]);
		memset(Imagedata, 0, (Size1 * Size2 * sizeof(unsigned char)));
	}

	int printout;
	cout << "Whether to print the points 1)Yes 2) No: ";
	cin >> printout;
	
	if (printout == 1)
	{
		char *aaa = { "D:/EE569_Assignment/3/P1/Textureout.txt"};//save the 12 25-D vectors in the txt to do the PCA in MATLAB

		ofstream outfile;
		outfile.open(aaa);
		if (outfile.is_open())
		{
			for (int n = 0; n < 12; n++)
			{
				for (int d = 0; d < 25; d++)
				{
					outfile << vec[n][d] << endl;
				}
			}
		}
		outfile.close();
		system("pause");
		return;
	}

	int AllOPCA;
	cout << "Which type do you want to implement: 1) 25D 2) PCA: ";
	cin >> AllOPCA;

	if (AllOPCA == 1)
	{
		int opt = 1;
		do
		{
			clock_t start, finish;
			double duration;
			start = clock();
			cout << "The classification result (25-D) for training 1-12 images is: " << endl;
			kmean_25(vec, 50, 4, classi, 12, cen, 1);
			finish = clock();
			duration = (double)(finish - start) / CLOCKS_PER_SEC;
			cout <<" The duration is "<< duration << endl;
			cout << "Do you want to contine: 1)Yes 2)No: ";
			cin >> opt;
		} while (opt == 1);//repeat until get the good result
		system("pause");

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

		for (int k0 = 0; k0 < 6; k0++)
		{
			double *d = new double[4];
			for (int c = 0; c < 4; c++)
			{
				d[c] = Edis_d(veco[k0], cen[c], 25);
			}
			double dmin;
			dmin = mini_d(d, 4);
			for (int c = 0; c < 4; c++)
			{
				if (dmin == d[c])
				{
					classiout_25[k0] = c;
				}
			}
		}
		cout << "The classification result (25-D) for testing A-F images is: " << endl;
		for (int k0 = 0; k0 < 6; k0++)
		{
			cout << classiout_25[k0] << '\t';
		}
		cout << endl;
		system("pause");
	}
	else
	{
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
		Cal25D23D1(1, vec, 1, 12, vec_n, PCA, dim);

		int opt = 1;
		do
		{
			clock_t start, finish;
			double duration;
			start = clock();
			cout << "The classification result (PCA) for training 1-12 images is: " << endl;
			kmean_25_s(vec_n, 200, 4, classi, 12, cen_n, 1);
			finish = clock();
			duration = (double)(finish - start) / CLOCKS_PER_SEC;
			cout << " The duration is " << duration << endl;
			cout << "Do you want to contine: 1)Yes 2)No: ";
			cin >> opt;
		} while (opt == 1);
		system("pause");

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
		Cal25D23D1(1, veco, 1, 6, veco_3, PCA, dim);

		double classiout_3[6] = { 0 };

		for (int k0 = 0; k0 < 6; k0++)
		{
			double *d = new double[4];
			for (int c = 0; c < 4; c++)
			{
				d[c] = Edis_d1(veco_3[k0], cen_n[c], 3);
			}
			double dmin;
			dmin = mini_d(d, 4);
			for (int c = 0; c < 4; c++)
			{
				if (dmin == d[c])
				{
					classiout_3[k0] = c;
				}
			}
		}
		cout << "The classification result (PCA) for testing A-F images is: " << endl;
		for (int k0 = 0; k0 < 6; k0++)
		{
			cout << classiout_3[k0] << '\t';
		}
		cout << endl;
		system("pause");
	}
}