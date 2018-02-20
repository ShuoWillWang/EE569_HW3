// EE 569 Homework #3
// date:	Mar. 24th, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//*********************************************************
// Further Improvement for P1_c (PCA and SVM enhancement)
//*********************************************************

#include <opencv2\opencv.hpp>
#include <opencv2\imgproc.hpp>
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream> 
//#include <iostream>

using namespace std;
using namespace cv;
using namespace cv::ml;

extern unsigned char Imagedata[100000000];
extern unsigned char Imagedataexp[100000000];
extern unsigned char ImagedataG[100000000];
extern unsigned char ImagedataG1[100000000];
extern double Imagedatatemp1[10000000];
extern double Imagedataexp1[10000000];
extern double Imagedatatempp[1000000][25];
extern double Imagedatatempp1[1000000][25];
double ImagedataSe[100000][25] = { 0 };

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
extern double maxi_absd(double *d, int cla);
extern void Ext_d(int BytesPerPixel, int Size1, int Size2, double *Imagedata, double *Imagedataex);
extern void CalNo_d(int BytesPerPixel, unsigned char *Imagedata, double *ImagedataOut, int Size1, int Size2, double *out);
extern void Deleavg(int BytesPerPixel, double *Imagedatatemp2, int Size1, int Size2, double *Imagedatatemp, int s);
extern void Lawout(int BytesPerPixel, unsigned char *ImagedataG, int Size1, int Size2, double *Imagedatatemp, int type1);
extern void RGB2G(int BytesPerPixel, unsigned char *Imagedata, unsigned char *ImagedataG, int Size1, int Size2);
extern void Cal25D23D(int BytesPerPixel, double Imagedatatempp[][25], int Size1, int Size2, double Imagedatatempp1[][25], double PCA[][25], int dim);


const int W = 590 / 10;
const int H = 350 / 10;

void P1_c_SVM(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2)
{
	FILE *file;

	double vec[18][25] = { 0 };
	double vec_3[18][3] = { 0 };
	double veco[10][25] = { 0 };
	double veco_3[10][3] = { 0 };
	int *classi = new int[Size1 * Size2];
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

	double *Imagedatatemp = new double[(Size1) * (Size2) * 25];

	Lawout(1, ImagedataG, Size1, Size2, Imagedatatemp, 3);

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

	double PCA[25][25] = { 0 };

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

	int dim = 11;
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
	for (int s = 0; s < dim; s++)
	{
		for (int i = 0; i < Size2; i++)
		{
			for (int j = 0; j < Size1; j++)
			{
				Imagedatatempp1[(Size1) * (i)+(j)][s] = (double)Imagedatatempp1[(Size1) * (i)+(j)][s] * max[0] / max[s];
			}
		}
	}

	kmean_25_s(Imagedatatempp1, 100, 3, classi, ((Size1) * (Size2)), cen, 2);
	//do the K-means after PCA
	// **************************************************************************************************************
	//int W = Size1 / 50;
	//int H = Size2 / 50;

	float trainingData[W * H][25] = { 0 };

	//float **trainingData = new float *[5];

	//for (int n = 0; n < 5; n++)
	//{
	//	trainingData[n] = new float[25];
	//}
	int labels[W * H] = { 0 };
	//int lables[1000] = { 0 };

	//select some samples from k-means
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			labels[W * i + j] = classi[(Size1) * (i * 10 + 5) + (j * 10 + 5)];
		}
	}

	for (int s = 0; s < 25; s++)
	{
		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				trainingData[W * i + j][s] = Imagedatatempp1[(Size1) * (i * 10 + 5) + (j * 10 + 5)][s];
			}
		}
	}

	//system("pause");

	int width = Size1;
    int height = Size2;
    cv::Mat image = cv::Mat::zeros(height, width, CV_8UC3);


	int ia;
	ia = W * H;
    // training data
    //int labels[5] = { 0,1,2,3,4 };
    //float trainingData[4][2] = { { 501, 10 }, { 255, 10 }, { 501, 255 }, { 10, 501 } };
    cv::Mat trainingDataMat(ia, 25, CV_32FC1, trainingData);
    cv::Mat labelsMat(ia, 1, CV_32SC1, labels);

    // initial SVM
    cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
    svm->setType(cv::ml::SVM::Types::C_SVC);
    svm->setKernel(cv::ml::SVM::KernelTypes::LINEAR);
    svm->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER, 100, 1e-6));

    // train operation
    svm->train(trainingDataMat, cv::ml::SampleTypes::ROW_SAMPLE, labelsMat);

	system("pause");

    // prediction
    cv::Vec3b aa2(0, 255, 0);
    cv::Vec3b aa1(255, 0, 0);
	cv::Vec3b aa3(0, 0, 255);
	cv::Vec3b aa4(255, 255, 0);
	cv::Vec3b aa5(255, 255, 255);
	cv::Vec3b aa6(0, 0, 0);
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            cv::Mat sampleMat = (cv::Mat_<float>(1, 25) << Imagedatatempp1[(Size1) * (i)+(j)][0], Imagedatatempp1[(Size1) * (i)+(j)][1], Imagedatatempp1[(Size1) * (i)+(j)][2]\
				, Imagedatatempp1[(Size1) * (i)+(j)][3], Imagedatatempp1[(Size1) * (i)+(j)][4], Imagedatatempp1[(Size1) * (i)+(j)][5], Imagedatatempp1[(Size1) * (i)+(j)][6]\
				, Imagedatatempp1[(Size1) * (i)+(j)][7], Imagedatatempp1[(Size1) * (i)+(j)][8], Imagedatatempp1[(Size1) * (i)+(j)][9], Imagedatatempp1[(Size1) * (i)+(j)][10]\
				, Imagedatatempp1[(Size1) * (i)+(j)][11], Imagedatatempp1[(Size1) * (i)+(j)][12], Imagedatatempp1[(Size1) * (i)+(j)][13], Imagedatatempp1[(Size1) * (i)+(j)][14]\
				, Imagedatatempp1[(Size1) * (i)+(j)][15], Imagedatatempp1[(Size1) * (i)+(j)][16], Imagedatatempp1[(Size1) * (i)+(j)][17], Imagedatatempp1[(Size1) * (i)+(j)][18]\
				, Imagedatatempp1[(Size1) * (i)+(j)][19], Imagedatatempp1[(Size1) * (i)+(j)][20], Imagedatatempp1[(Size1) * (i)+(j)][21], Imagedatatempp1[(Size1) * (i)+(j)][22]\
				, Imagedatatempp1[(Size1) * (i)+(j)][23], Imagedatatempp1[(Size1) * (i)+(j)][24]);
            float respose = svm->predict(sampleMat);
            if (respose == 0)
                image.at<cv::Vec3b>(i, j) = aa1;
            else if (respose == 1)
                image.at<cv::Vec3b>(i, j) = aa2;
			else if (respose == 2)
				image.at<cv::Vec3b>(i, j) = aa3;
			else if (respose == 3)
				image.at<cv::Vec3b>(i, j) = aa4;
			else if (respose == 4)
				image.at<cv::Vec3b>(i, j) = aa5;
			else if (respose == 5)
				image.at<cv::Vec3b>(i, j) = aa6;
        }
    }

    //imshow("SVM Simple Example", image);
    //waitKey(0);

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			Imagedata[3 * ((image.cols) * (i)+(j)) + 2] = image.at<cv::Vec3b>(i, j)[0];
			Imagedata[3 * ((image.cols) * (i)+(j)) + 1] = image.at<cv::Vec3b>(i, j)[1];
			Imagedata[3 * ((image.cols) * (i)+(j)) + 0] = image.at<cv::Vec3b>(i, j)[2];
		}
	}

	if (!(file = fopen("D:/EE569_Assignment/3/P1/kitten_SVM.raw", "wb"))) {
		cout << "Cannot open file: " << a2 << endl;
		exit(1);
	}
	fwrite(Imagedata, sizeof(unsigned char), Size2*Size1*BytesPerPixel, file);
	fclose(file);
	system("pause");
}