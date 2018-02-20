// EE 569 Homework #3
// date:	Mar. 24th, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu

//*********************************************************
// Image Matching for P3_b
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

extern int g_nnfeatures, g_nOctaveLayers;
extern int g_ncontrastThreshold, g_nedgeThreshold, g_nsigma;
int g_nOctaves = 0;

void P3_b(void)
{
	Mat img_11 = imread("D:/EE569_Assignment/3/P2/convertible_1.jpg", 1);
	//Mat img_21 = imread("D:/EE569_Assignment/3/P2/convertible_2.jpg", 1);
	//Mat img_21 = imread("D:/EE569_Assignment/3/P2/suv.jpg", 1);
	Mat img_21 = imread("D:/EE569_Assignment/3/P2/truck.jpg", 1);

	Mat img_1, img_2;
	//system("pause");
	cvtColor(img_11, img_1, CV_BGR2GRAY);
	cvtColor(img_21, img_2, CV_BGR2GRAY);
	//system("pause");

	int type;
	cout << "Input the method: 1) SIFT 2) SURF: ";
	cin >> type;
	if (type == 1)
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

				cv::Ptr<Feature2D> f2d = xfeatures2d::SIFT::create(0, g_nOctaveLayers + 1, (double)(g_ncontrastThreshold / 100.0), 10, 1.6);
				std::vector<KeyPoint> keypoints_1, keypoints_2;
				f2d->detect(img_1, keypoints_1);
				f2d->detect(img_2, keypoints_2);

				Mat descriptors_1, descriptors_2;
				f2d->compute(img_1, keypoints_1, descriptors_1);
				f2d->compute(img_2, keypoints_2, descriptors_2);

				BFMatcher matcher;//do the matching
				std::vector<DMatch> matches;
				matcher.match(descriptors_1, descriptors_2, matches);

				Mat imgMatches;
				drawMatches(img_11, keypoints_1, img_21, keypoints_2, matches, imgMatches, Scalar::all(-1), Scalar::all(-1), std::vector< char >(), DrawMatchesFlags::DEFAULT);
				imshow("Match_Out", imgMatches);
				if (key == 27)
					break;
			}
		}

		cv::Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();
		std::vector<KeyPoint> keypoints_1, keypoints_2;
		f2d->detect(img_1, keypoints_1);
		f2d->detect(img_2, keypoints_2);

		Mat descriptors_1, descriptors_2;
		f2d->compute(img_1, keypoints_1, descriptors_1);
		f2d->compute(img_2, keypoints_2, descriptors_2);

		float max_dist = 0;
		float min_dist = 1000;

		BFMatcher matcher;
		std::vector<DMatch> matches;
		matcher.match(descriptors_1, descriptors_2, matches);

		//cout << format(matches, Formatter::FMT_PYTHON) << endl;
		for (int i = 0; i < matches.size(); i++)
		{
			//cout<< matches[i].distance<<'\t';
			float dist = matches[i].distance;
			if (dist > max_dist)
				max_dist = dist;
			if (dist < min_dist)
				min_dist = dist;
		}

		//cout << max_dist << endl;
		//cout << min_dist << endl;

		std::vector<DMatch> Goodmatches;
		for (int i = 0; i < matches.size(); i++)
		{
			if (matches[i].distance < 0.6 * max_dist)
			{
				Goodmatches.push_back(matches[i]);
			}
		}

		cout << matches.size() << endl;
		cout << Goodmatches.size() << endl;

		Mat imgMatches;
		drawMatches(img_11, keypoints_1, img_21, keypoints_2, Goodmatches, imgMatches, Scalar::all(-1), Scalar::all(-1), std::vector< char >(), DrawMatchesFlags::DEFAULT);
		imwrite("D:/EE569_Assignment/3/P2/convertible_OutSIFT.jpg", imgMatches);
	}
	else
	{

		int bar;
		cout << "If do the choose bar: 1)yes 2)no: ";
		cin >> bar;

		if (bar == 1)
		{
			namedWindow("OutputG", 0);
			createTrackbar("Octave Layers:", "OutputG", &g_nOctaveLayers, 7, 0);
			createTrackbar("Octave numbers:", "OutputG", &g_nOctaves, 7, 0);

			char key;

			while (1)
			{
				key = waitKey(10);

				cv::Ptr<Feature2D> f2d = xfeatures2d::SURF::create(800, g_nOctaves + 1, g_nOctaveLayers + 1);
				std::vector<KeyPoint> keypoints_1, keypoints_2;
				f2d->detect(img_1, keypoints_1);
				f2d->detect(img_2, keypoints_2);

				Mat descriptors_1, descriptors_2;
				f2d->compute(img_1, keypoints_1, descriptors_1);
				f2d->compute(img_2, keypoints_2, descriptors_2);

				BFMatcher matcher;
				std::vector<DMatch> matches;
				matcher.match(descriptors_1, descriptors_2, matches);

				Mat imgMatches;
				drawMatches(img_11, keypoints_1, img_21, keypoints_2, matches, imgMatches, Scalar::all(-1), Scalar::all(-1), std::vector< char >(), DrawMatchesFlags::DEFAULT);
				imshow("Match_Out", imgMatches);
				if (key == 27)
					break;
			}
		}

		cv::Ptr<Feature2D> f2d = xfeatures2d::SURF::create(300);
		std::vector<KeyPoint> keypoints_1, keypoints_2;
		f2d->detect(img_1, keypoints_1);
		f2d->detect(img_2, keypoints_2);

		Mat descriptors_1, descriptors_2;
		f2d->compute(img_1, keypoints_1, descriptors_1);
		f2d->compute(img_2, keypoints_2, descriptors_2);
		
		BFMatcher matcher;
		std::vector<DMatch> matches;
		matcher.match(descriptors_1, descriptors_2, matches);

		float max_dist = 0;
		float min_dist = 1000;

		//cout << format(matches, Formatter::FMT_PYTHON) << endl;
		for (int i = 0; i < matches.size(); i++)
		{
			//cout<< matches[i].distance<<'\t';
			float dist = matches[i].distance;
			if (dist > max_dist)
				max_dist = dist;
			if (dist < min_dist)
				min_dist = dist;
		}

		//cout << max_dist << endl;
		//cout << min_dist << endl;

		std::vector<DMatch> Goodmatches;
		for (int i = 0; i < matches.size(); i++)
		{
			if (matches[i].distance < 0.4 * max_dist)
			{
				Goodmatches.push_back(matches[i]);
			}
		}

		cout << matches.size() << endl;
		cout << Goodmatches.size() << endl;

		Mat imgMatches;
		drawMatches(img_11, keypoints_1, img_21, keypoints_2, Goodmatches, imgMatches, Scalar::all(-1), Scalar::all(-1), std::vector< char >(), DrawMatchesFlags::DEFAULT);
		imwrite("D:/EE569_Assignment/3/P2/convertible_OutSURF.jpg", imgMatches);
		
	}

	system("pause");
}