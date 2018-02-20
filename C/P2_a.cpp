// EE 569 Homework #3
// date:	Mar. 24th, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//*********************************************************
// Canny Edge Detector for P2_a
//*********************************************************

#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream> 
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

int g_nCurrValue = 0, g_nP = 0, g_nWay = 0;

int P2_a(int BytesPerPixel, char *a1, char *a2, int Size1, int Size2)
{
	Mat src = imread(a1);
	Mat src1 = src.clone();

	imshow("Origin", src);

	Mat edge, gray;
	cvtColor(src1, gray, CV_BGR2GRAY);

	namedWindow("OutputG", 0); // create the Track bar
	createTrackbar("Value:", "OutputG", &g_nCurrValue, 255, 0);//first threshold
	createTrackbar("P:", "OutputG", &g_nP, 255, 0);//second threshold
	createTrackbar("Gray/BGR", "OutputG", &g_nWay, 1, 0);

	edge.create(gray.size(), gray.type());

	char key;
	Mat resI;

	while (1)
	{
		key = waitKey(10);

		if (!g_nWay)
		{
			blur(gray, edge, Size(3, 3));
			Canny(edge, edge, (double)g_nCurrValue, (double)g_nP, 3);
			resI = Scalar::all(0);
			gray.copyTo(resI, edge);
		}
		else
		{
			blur(gray, edge, Size(3, 3));
			Canny(edge, edge, (double)g_nCurrValue, (double)g_nP, 3);
			resI = Scalar::all(0);
			src1.copyTo(resI, edge);
		}

		imshow("OutputGB", resI);
		if (key == 27)
			break;
	}
	return 0;
}
