// EE 569 Homework #3
// date:	Mar. 24th, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//*********************************************************
// Bag of Words for P3_c
//*********************************************************

#include <opencv2/ximgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/core/utility.hpp"
#include <iostream>
#include <Windows.h>
#include <opencv2\xfeatures2d\nonfree.hpp>
#include <opencv2\features2d.hpp>

using namespace std;
using namespace cv;
using namespace cv::ximgproc;
using namespace cv::xfeatures2d;

extern void kmean_128(double vec[][128], int k, int cla, int *classi, int num, double cen[][128], int printornot);
extern double Edis_d(double *a, double *b, int dim);
extern double mini_d(double *d, int cla);
extern double maxi_d(double *d, int cla);

double f_descriptors_1[1000][128] = { 0 };
double f_descriptors_341[10000][128] = { 0 };
double f_descriptors_2[1000][128] = { 0 };
double f_descriptors_3[1000][128] = { 0 };
double f_descriptors_4[1000][128] = { 0 };

double cen_1[100][128] = { 0 };
double cen_341[100][128] = { 0 };
double cen_2[100][128] = { 0 };
double cen_3[100][128] = { 0 };
double cen_4[100][128] = { 0 };

int classi_1[1000] = { 0 };
int classi_341[10000] = { 0 };
int classi_2[1000] = { 0 };
int classi_3[1000] = { 0 };
int classi_4[1000] = { 0 };

int classi_o1[1000] = { 0 };
int classi_o341[10000] = { 0 };
int classi_o2[1000] = { 0 };
int classi_o3[1000] = { 0 };
int classi_o4[1000] = { 0 };

void P3_c(void)
{
	Mat img_11 = imread("D:/EE569_Assignment/3/P2/convertible_1.jpg", 1);
	Mat img_21 = imread("D:/EE569_Assignment/3/P2/convertible_2.jpg", 1);
	Mat img_31 = imread("D:/EE569_Assignment/3/P2/suv.jpg", 1);
	Mat img_41 = imread("D:/EE569_Assignment/3/P2/truck.jpg", 1);

	Mat img_1, img_2, img_3, img_4;
	cvtColor(img_11, img_1, CV_BGR2GRAY);
	cvtColor(img_21, img_2, CV_BGR2GRAY);
	cvtColor(img_31, img_3, CV_BGR2GRAY);
	cvtColor(img_41, img_4, CV_BGR2GRAY);

	cv::Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();//use the SIFT to do matching
	std::vector<KeyPoint> keypoints_1, keypoints_2, keypoints_3, keypoints_4;
	f2d->detect(img_1, keypoints_1);
	f2d->detect(img_2, keypoints_2);
	f2d->detect(img_3, keypoints_3);
	f2d->detect(img_4, keypoints_4);

	Mat descriptors_1, descriptors_2, descriptors_3, descriptors_4;//get key points
	f2d->compute(img_1, keypoints_1, descriptors_1);
	f2d->compute(img_2, keypoints_2, descriptors_2);
	f2d->compute(img_3, keypoints_3, descriptors_3);
	f2d->compute(img_4, keypoints_4, descriptors_4);

	cv::drawKeypoints(img_11, keypoints_1, img_11, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	cv::drawKeypoints(img_21, keypoints_2, img_21, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	cv::drawKeypoints(img_31, keypoints_3, img_31, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	cv::drawKeypoints(img_41, keypoints_4, img_41, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

	for (int i = 0; i < descriptors_1.rows; i++)
	{
		for (int j = 0; j < descriptors_1.cols; j++)
		{
			f_descriptors_1[i][j] = descriptors_1.at<float>(i, j);
			//cout << f_descriptors_1[i][j] << ", ";
		}
		//cout << endl;
	}

	for (int i = 0; i < descriptors_3.rows; i++)
	{
		for (int j = 0; j < descriptors_3.cols; j++)
		{
			f_descriptors_341[i][j] = descriptors_3.at<float>(i, j);
			//cout << f_descriptors_2[i][j] << ", ";
		}
		//cout << endl;
	}

	for (int i = 0; i < descriptors_4.rows; i++)
	{
		for (int j = 0; j < descriptors_4.cols; j++)
		{
			f_descriptors_341[i + descriptors_3.rows][j + descriptors_3.cols] = descriptors_4.at<float>(i, j);
		}
		//cout << endl;
	}

	for (int i = 0; i < descriptors_1.rows; i++)
	{
		for (int j = 0; j < descriptors_1.cols; j++)
		{
			f_descriptors_341[i + descriptors_3.rows + descriptors_4.rows][j + descriptors_3.cols + descriptors_4.cols] = descriptors_1.at<float>(i, j);
		}
		//cout << endl;
	}

	for (int i = 0; i < descriptors_2.rows; i++)
	{
		for (int j = 0; j < descriptors_2.cols; j++)
		{
			f_descriptors_2[i][j] = descriptors_2.at<float>(i, j);
			//cout << f_descriptors_2[i][j] << ", ";
		}
		//cout << endl;
	}

	for (int i = 0; i < descriptors_3.rows; i++)
	{
		for (int j = 0; j < descriptors_3.cols; j++)
		{
			f_descriptors_3[i][j] = descriptors_3.at<float>(i, j);
			//cout << f_descriptors_2[i][j] << ", ";
		}
		//cout << endl;
	}

	for (int i = 0; i < descriptors_4.rows; i++)
	{
		for (int j = 0; j < descriptors_4.cols; j++)
		{
			f_descriptors_4[i][j] = descriptors_4.at<float>(i, j);
			//cout << f_descriptors_2[i][j] << ", ";
		}
		//cout << endl;
	}
	
	kmean_128(f_descriptors_341, 500, 8, classi_341, descriptors_3.rows + descriptors_4.rows + descriptors_1.rows, cen_341, 2);
	//kmean_128(f_descriptors_2, 500, 8, classi_2, descriptors_2.rows, cen_2, 2);//do the k-means for the descriptors

	for (int k0 = 0; k0 < descriptors_1.rows; k0++)//justify the relationship between the descriptors and centroid
	{
		double *d = new double[8];
		for (int c = 0; c < 8; c++)
		{
			d[c] = Edis_d(f_descriptors_1[k0], cen_341[c], 128);
		}
		double dmin;
		dmin = mini_d(d, 8);
		for (int c = 0; c < 8; c++)
		{
			if (dmin == d[c])
			{
				classi_o1[k0] = c;
				break;
			}
		}
	}

	double cla1[8] = { 0 };

	for (int k0 = 0; k0 < descriptors_1.rows; k0++)
	{
		for (int c = 0; c < 8; c++)
		{
			if (classi_o1[k0] == c)
			{
				cla1[c] = cla1[c] + 1;
				break;
			}
		}
	}

	double clas1 = 0;
	for (int c = 0; c < 8; c++)
	{
		clas1 = clas1 + cla1[c];// * cla1[c]
	}
	//clas1 = sqrt(clas1);

	for (int c = 0; c < 8; c++)
	{
		cla1[c] = cla1[c] / clas1;
	}

	char *aaa1 = { "D:/EE569_Assignment/3/P2/cla1.txt" };//save the 12 25-D vectors in the txt to do the PCA in MATLAB

	ofstream outfile;
	outfile.open(aaa1);
	if (outfile.is_open())
	{
		for (int n = 0; n < 8; n++)
		{
			outfile << (int)100 * cla1[n] << endl;
		}
	}
	outfile.close();

	//for (int c = 0; c < 8; c++)
	//{
	//	cout << (cla1[c]) << '\t';
	//}
	//cout << endl;


	//*****************************************************************************************************************************

	for (int k0 = 0; k0 < descriptors_2.rows; k0++)
	{
		double *d = new double[8];
		for (int c = 0; c < 8; c++)
		{
			d[c] = Edis_d(f_descriptors_2[k0], cen_341[c], 128);
		}
		double dmin;
		dmin = mini_d(d, 8);
		for (int c = 0; c < 8; c++)
		{
			if (dmin == d[c])
			{
				classi_o2[k0] = c;
				break;
			}
		}
	}

	double cla2[8] = { 0 };

	for (int k0 = 0; k0 < descriptors_3.rows; k0++)
	{
		for (int c = 0; c < 8; c++)
		{
			if (classi_o2[k0] == c)
			{
				cla2[c] = cla2[c] + 1;
				break;
			}
		}
	}

	double clas2 = 0;
	for (int c = 0; c < 8; c++)
	{
		clas2 = clas2 + cla2[c];// * cla2[c]
	}
	//clas2 = sqrt(clas2);

	for (int c = 0; c < 8; c++)
	{
		cla2[c] = cla2[c] / clas2;

	}

	char *aaa2 = { "D:/EE569_Assignment/3/P2/cla2.txt" };//save the 12 25-D vectors in the txt to do the PCA in MATLAB

	outfile.open(aaa2);
	if (outfile.is_open())
	{
		for (int n = 0; n < 8; n++)
		{
			outfile << (int)100 * cla2[n] << endl;
		}
	}
	outfile.close();

	//for (int c = 0; c < 8; c++)
	//{
	//	cout << (cla2[c]) << '\t';
	//}
	//cout << endl;

	//*****************************************************************************************************************************

	for (int k0 = 0; k0 < descriptors_3.rows; k0++)
	{
		double *d = new double[8];
		for (int c = 0; c < 8; c++)
		{
			d[c] = Edis_d(f_descriptors_3[k0], cen_341[c], 128);
		}
		double dmin;
		dmin = mini_d(d, 8);
		for (int c = 0; c < 8; c++)
		{
			if (dmin == d[c])
			{
				classi_o3[k0] = c;
				break;
			}
		}
	}

	double cla3[8] = { 0 };

	for (int k0 = 0; k0 < descriptors_3.rows; k0++)
	{
		for (int c = 0; c < 8; c++)
		{
			if (classi_o3[k0] == c)
			{
				cla3[c] = cla3[c] + 1;
				break;
			}
		}
	}

	double clas3 = 0;
	for (int c = 0; c < 8; c++)
	{
		clas3 = clas3 + cla3[c];// * cla3[c]
	}
	//clas3 = sqrt(clas3);

	for (int c = 0; c < 8; c++)
	{
		cla3[c] = cla3[c] / clas3;

	}


	char *aaa3 = { "D:/EE569_Assignment/3/P2/cla3.txt" };//save the 12 25-D vectors in the txt to do the PCA in MATLAB

	outfile.open(aaa3);
	if (outfile.is_open())
	{
		for (int n = 0; n < 8; n++)
		{
			outfile << (int)100 * cla3[n] << endl;
		}
	}
	outfile.close();

	//for (int c = 0; c < 8; c++)
	//{
	//	cout << (cla3[c]) << '\t';
	//}
	//cout << endl;

	//*********************************************************************************************************************************

	for (int k0 = 0; k0 < descriptors_4.rows; k0++)
	{
		double *d = new double[8];
		for (int c = 0; c < 8; c++)
		{
			d[c] = Edis_d(f_descriptors_4[k0], cen_341[c], 128);
		}
		double dmin;
		dmin = mini_d(d, 8);
		for (int c = 0; c < 8; c++)
		{
			if (dmin == d[c])
			{
				classi_o4[k0] = c;
				break;
			}
		}
	}

	double cla4[8] = { 0 };

	for (int k0 = 0; k0 < descriptors_4.rows; k0++)
	{
		for (int c = 0; c < 8; c++)
		{
			if (classi_o4[k0] == c)
			{
				cla4[c] = cla4[c] + 1;
				break;
			}
		}
	}

	double clas4 = 0;
	for (int c = 0; c < 8; c++)
	{
		clas4 = clas4 + cla4[c];// * cla4[c]
	}
	//clas4 = sqrt(clas4);

	for (int c = 0; c < 8; c++)
	{
		cla4[c] = cla4[c] / clas4;

	}

	char *aaa4 = { "D:/EE569_Assignment/3/P2/cla4.txt" };//save the 12 25-D vectors in the txt to do the PCA in MATLAB

	outfile.open(aaa4);
	if (outfile.is_open())
	{
		for (int n = 0; n < 8; n++)
		{
			outfile << (int)100 * cla4[n] << endl;
		}
	}
	outfile.close();

	//*********************************************************************************************************************************

	double d1, d2, d3;
	d1 = Edis_d(cla3, cla2, 8);
	d2 = Edis_d(cla4, cla2, 8);
	d3 = Edis_d(cla1, cla2, 8);

	cout << "The distance between the Convertible_2 and suv are " << d1 << endl;
	cout << "The distance between the Convertible_2 and truck are " << d2 << endl;
	cout << "The distance between the Convertible_2 and Convertible_1 are " << d3 << endl;

	system("pause");
}