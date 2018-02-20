// EE 569 Homework #3
// date:	Mar. 24th, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//*********************************************************
// Extraction and Description of Salient Points for P3_a
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

int g_nnfeatures = 0, g_nOctaveLayers = 0;
int g_ncontrastThreshold = 0, g_nedgeThreshold = 0, g_nsigma = 0;
extern int g_nOctaves;

void P3_a(void)
{
	Mat img_21 = imread("D:/EE569_Assignment/3/P2/truck.jpg", 1);//load image
	Mat img_11 = imread("D:/EE569_Assignment/3/P2/suv.jpg", 1);

	Mat img_1, img_2;
	//system("pause");
	cvtColor(img_11, img_1, CV_BGR2GRAY);//convert to gray
	cvtColor(img_21, img_2, CV_BGR2GRAY);
	//system("pause");

	int type;
	cout << "Input the method: 1) SIFT 2) SURF: ";
	cin >> type;
	if (type == 1)//SIFT
	{
		int bar;
		cout << "If do the choose track bar: 1)yes 2)no: ";
		cin >> bar;

		if (bar == 1)//choose the track bar
		{
			namedWindow("Control", 0);
			createTrackbar("Octave Layers:", "Control", &g_nOctaveLayers, 5, 0);
			createTrackbar("Contrast Threshold:", "Control", &g_ncontrastThreshold, 10, 0);

			char key;

			while (1)
			{
				key = waitKey(10);

				cv::Ptr<Feature2D> f2d = xfeatures2d::SIFT::create(0, g_nOctaveLayers + 1, (double)(g_ncontrastThreshold / 100.0), 10, 1.6);
				std::vector<KeyPoint> keypoints_1;
				f2d->detect(img_1, keypoints_1);

				Mat img210;
				Mat descriptors_1;
				f2d->compute(img_1, keypoints_1, descriptors_1);

				cv::drawKeypoints(img_11, keypoints_1, img210, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

				imshow("suv_Out", img210);
				if (key == 27)
					break;
			}
		}

		//not use the track bar
		cv::Ptr<Feature2D> f2d = xfeatures2d::SIFT::create(0, 6, 0.18, 10, 1.6);
		std::vector<KeyPoint> keypoints_1, keypoints_2;
		f2d->detect(img_1, keypoints_1);
		f2d->detect(img_2, keypoints_2);

		Mat descriptors_1, descriptors_2;
		f2d->compute(img_1, keypoints_1, descriptors_1);
		f2d->compute(img_2, keypoints_2, descriptors_2);

		cv::drawKeypoints(img_11, keypoints_1, img_11, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
		cv::drawKeypoints(img_21, keypoints_2, img_21, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

		//imshow("suv_Out", img_11);
		//waitKey();
		imwrite("D:/EE569_Assignment/3/P2/suv_Out.jpg", img_11);
		imwrite("D:/EE569_Assignment/3/P2/truck_Out.jpg", img_21);
	}
	else//SURF
	{
		int bar;
		cout << "If do the choose bar: 1)yes 2)no: ";
		cin >> bar;

		if (bar == 1)
		{
			namedWindow("OutputG", 0);
			createTrackbar("Octave Layers:", "OutputG", &g_nOctaveLayers, 5, 0);
			createTrackbar("Contrast Threshold:", "OutputG", &g_ncontrastThreshold, 10, 0);

			char key;

			while (1)
			{
				key = waitKey(10);

				cv::Ptr<Feature2D> f2d = xfeatures2d::SURF::create(100, g_nOctaves + 1, g_nOctaveLayers + 1);
				std::vector<KeyPoint> keypoints_1;
				f2d->detect(img_1, keypoints_1);

				Mat img110;
				Mat descriptors_1;
				f2d->compute(img_1, keypoints_1, descriptors_1);

				cv::drawKeypoints(img_11, keypoints_1, img110, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

				imshow("suv_Out", img110);
				if (key == 27)
					break;
			}
		}

		cv::Ptr<Feature2D> f2d = xfeatures2d::SURF::create();
		std::vector<KeyPoint> keypoints_1, keypoints_2;
		f2d->detect(img_1, keypoints_1);
		f2d->detect(img_2, keypoints_2);

		Mat descriptors_1, descriptors_2;
		f2d->compute(img_1, keypoints_1, descriptors_1);
		f2d->compute(img_2, keypoints_2, descriptors_2);

		cv::drawKeypoints(img_11, keypoints_1, img_11, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
		cv::drawKeypoints(img_21, keypoints_2, img_21, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
		imshow("suv_Out_su", img_11);
		waitKey();
		imwrite("D:/EE569_Assignment/3/P2/suv_Out_su.jpg", img_11);
		imwrite("D:/EE569_Assignment/3/P2/truck_Out_su.jpg", img_21);
	}

	system("pause");
}