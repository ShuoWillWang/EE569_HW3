// EE 569 Homework #3
// date:	Mar. 24th, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu
//*********************************************************
// Compiled on WINDOWS 10 with Visual C++ and Opencv 3.2
// solution for the question in Problem 2(b)
// Use the DOS command to open the program and run it by the README.txt
//*********************************************************
// Contour Detection with Structured Edge for P2_b 
//*********************************************************

#include <opencv2/ximgproc.hpp>
#include <opencv2/ximgproc/structured_edge_detection.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/core/utility.hpp"
#include <iostream>
#include <Windows.h>

unsigned char Imagedata[10000000] = { 0 };
unsigned char ImagedataOut[10000000] = { 0 };

using namespace std;
using namespace cv;
using namespace cv::ximgproc;

const char* keys =
{
	"{i || input image name}"
	"{m || model name}"
	"{o || output image name}"
};

int Percent = 0;

void ConvP2B(int BytesPerPixel, int Size1, int Size2, unsigned char *Imagedata, unsigned char *ImagedataG, double P)
{
	double prob;
	for (int i = 0; i < Size2; i++)
	{
		for (int j = 0; j < Size1; j++)
		{
			prob = (double)Imagedata[BytesPerPixel * ((Size1) * (i)+(j)) + 0] / 255;
			if (prob >= P)
			{
				ImagedataG[BytesPerPixel * ((Size1) * (i)+(j)) + 0] = 0;
			}
			else
			{
				ImagedataG[BytesPerPixel * ((Size1) * (i)+(j)) + 0] = 255;
			}
		}
	}
}

int main(int argc, const char** argv)
{
	FILE *file;
	bool printHelp = (argc == 1);
	printHelp = printHelp || (argc == 2 && std::string(argv[1]) == "--help");
	printHelp = printHelp || (argc == 2 && std::string(argv[1]) == "-h");

	if (printHelp)
	{
		printf("\nThis sample demonstrates structured forests for fast edge detection\n"
			"Call:\n"
			"    structured_edge_detection -i=in_image_name -m=model_name [-o=out_image_name]\n\n");
		return 0;
	}

	cv::CommandLineParser parser(argc, argv, keys);

	parser.printMessage();
	//system("pause");

	if (!parser.check())
	{
		parser.printErrors();
		system("pause");
		return -1;
	}

	std::string modelFilename = parser.get<std::string>("m");
	std::string inFilename = parser.get<std::string>("i");
	std::string outFilename = parser.get<std::string>("o");

	Mat image = imread(inFilename, 1);
	//system("pause");

	cv::Mat edgeout(image.size(), image.type());

	if (image.empty())
	{
		printf("Cannot read image file: %s\n", inFilename.c_str());
		system("pause");
		return -1;
	}

	image.convertTo(image, cv::DataType<float>::type, 1 / 255.0);

	cv::Mat edges(image.size(), image.type());
	system("pause");
	cv::Ptr<StructuredEdgeDetection> pDollar = createStructuredEdgeDetection("model.yml.gz");//modelFilename
	pDollar->detectEdges(image, edges);

	//cv::imshow("edge", edges);
	//waitKey(0);

	if (outFilename == "")
	{
		cv::namedWindow("edges", 1);
		cv::imshow("edges", edges);

		cv::waitKey(0);
	}
	else
		cv::imwrite(outFilename, 255 * edges);

	int type;
	cout << "Do which type: 1) bar 2)file: ";
	cin >> type;

	if (type == 1)
	{
		namedWindow("OutputGB", 0);
		createTrackbar("Percent:", "OutputGB", &Percent, 100, 0);
		char key;

		while (1)
		{
			key = waitKey(10);

			for (int i = 0; i < edges.rows; i++)
			{
				for (int j = 0; j < edges.cols; j++)
				{
					double Pe = ((double)Percent / 100);
					if (edges.at<float>(i, j) >= Pe)
						edgeout.at<uchar>(i, j) = 0;
					else
						edgeout.at<uchar>(i, j) = 255;
				}
			}

			imshow("OutputGB", edgeout);
			if (key == 27)
				break;
		}
	}
	else
	{
		double P;
		cout << "input the percentage (0 to 1): ";
		cin >> P;
		for (int i = 0; i < edges.rows; i++)
		{
			for (int j = 0; j < edges.cols; j++)
			{
				if (edges.at<float>(i, j) >= P)
					edgeout.at<uchar>(i, j) = 0;
				else
					edgeout.at<uchar>(i, j) = 255;
			}
		}
		for (int i = 0; i < edges.rows; i++)
		{
			for (int j = 0; j < edges.cols; j++)
			{
				ImagedataOut[((edges.cols) * (i)+(j)) + 0] = edgeout.at<uchar>(i, j);
			}
		}
		if (!(file = fopen("D:/EE569_Assignment/3/P3/BoatOF.raw", "wb"))) {
			cout << "Cannot open file: " << "kitten_SVM.raw" << endl;
			exit(1);
		}
		fwrite(ImagedataOut, sizeof(unsigned char), edges.rows * edges.cols * 1, file);
		fclose(file);
		system("pause");
	}


	for (int i = 0; i < edges.rows; i++)
	{
		for (int j = 0; j < edges.cols; j++)
		{
			Imagedata[((edges.cols) * (i)+(j)) + 0] = 255 * edges.at<float>(i, j);
		}
	}

	if (!(file = fopen("D:/EE569_Assignment/3/P3/BoatO.raw", "wb"))) {
		cout << "Cannot open file: " << "kitten_SVM.raw" << endl;
		exit(1);
	}
	fwrite(Imagedata, sizeof(unsigned char), edges.rows * edges.cols *1, file);
	fclose(file);
	system("pause");

	return 0;
}