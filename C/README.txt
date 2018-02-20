// EE 569 Homework #3
// date:	Mar. 24th, 2017
// Name:	Shuo Wang
// ID:		8749390300
// email:	wang133@usc.edu
//*********************************************************
// Compiled on WINDOWS 10 with Visual C++ and Opencv 3.2
// solution for all questions in  Problem 1, Problem 2(a) and Problem 3
// Use the DOS command to open the program and run it by the README.txt

Problem 1:	Texture Analysis and Segmentation
(a) 	Texture Classification
The path of structure training and testing has been written in the source code. 
Open Method: {path_of_program_name path_of_One_training_image.raw path_of_one_of_tesing_image.raw BytesPerPixel Size1(Width) Size2(Height)}
Unsupervised
1. Save the 25-D vector
D:\EE569_Assignment\3\C++\Image_Processing_HW3\x64\Debug>D:\EE569_Assignment\3\C++\Image_Processing_HW3\x64\Debug\Image_Processing_HW3.exe D:\EE569_Assignment\3\P1\Texture1.raw D:\EE569_Assignment\3\P1\test.raw 1 128 128

***** VIDEOINPUT LIBRARY - 0.1995 - TFW07 *****

Solve which problems: 1
solve which part: a
1) unsupervised or 2) supervised: 1
Whether to print the points 1)Yes 2) No: 1
Press any key to continue . . .


2. Do the classification
D:\EE569_Assignment\3\C++\Image_Processing_HW3\x64\Debug>D:\EE569_Assignment\3\C++\Image_Processing_HW3\x64\Debug\Image_Processing_HW3.exe D:\EE569_Assignment\3\P1\Texture1.raw D:\EE569_Assignment\3\P1\test.raw 1 128 128

***** VIDEOINPUT LIBRARY - 0.1995 - TFW07 *****

Solve which problems: 1
solve which part: a
1) unsupervised or 2) supervised: 1
Whether to print the points 1)Yes 2) No: 2
Which type do you want to implement: 1) 25D 2) PCA: 1
The classification result (25-D) for training 1-12 images is:
Which Initialization method: 1) ramdom 2) maximum min-value 3) AS: 2
6
The classification result training 1-12 images is:
2       2       2       1       1       1       0       0       0       3       3       3
 The duration is 1.836
Do you want to contine: 1)Yes 2)No: 2
Press any key to continue . . .
The classification result (25-D) for testing A-F images is:
3       0       2       1       3       0
Press any key to continue . . .


Supervised
D:\EE569_Assignment\3\C++\Image_Processing_HW3\x64\Debug>D:\EE569_Assignment\3\C++\Image_Processing_HW3\x64\Debug\Image_Processing_HW3.exe D:\EE569_Assignment\3\P1\Texture1.raw D:\EE569_Assignment\3\P1\test.raw 1 128 128

***** VIDEOINPUT LIBRARY - 0.1995 - TFW07 *****

Solve which problems: 1
solve which part: a
1) unsupervised or 2) supervised: 2
The classification result (Supervised 25-D) for testing A-F images is:
3       2       0       1       3       2
Press any key to continue . . .

(b) 	Texture Segmentation
Open Method: {path_of_program_name path_of_color_image.raw path_of_segmentation_image.raw BytesPerPixel Size1(Width) Size2(Height)}
1. Save the 25-D vectors
D:\EE569_Assignment\3\C++\Image_Processing_HW3\x64\Debug>D:\EE569_Assignment\3\C++\Image_Processing_HW3\x64\Debug\Image_Processing_HW3.exe D:\EE569_Assignment\3\P1\kitten.raw D:\EE569_Assignment\3\P1\kitten_test_3.raw 3 590 350

***** VIDEOINPUT LIBRARY - 0.1995 - TFW07 *****

Solve which problems: 1
solve which part: b
Whether to print the points 1)Yes 2) No: 1
Press any key to continue . . .

2. Do the segmentation
D:\EE569_Assignment\3\C++\Image_Processing_HW3\x64\Debug>D:\EE569_Assignment\3\C++\Image_Processing_HW3\x64\Debug\Image_Processing_HW3.exe D:\EE569_Assignment\3\P1\kitten.raw D:\EE569_Assignment\3\P1\kitten_test_3.raw 3 590 350

***** VIDEOINPUT LIBRARY - 0.1995 - TFW07 *****

Solve which problems: 1
solve which part: b
Whether to print the points 1)Yes 2) No: 2
Which dimension do you want 1) 25 2) other: 1
input the number of class you want: 3
Which Initialization method: 1) ramdom 2) maximum min-value 3) AS: 2
Press any key to continue . . .

(c) 	Further Improvement
In this section, I will use the PCA in 1(b) and SVM in 1(c)
Open Method: {path_of_program_name path_of_color_image.raw path_of_segmentation_image.raw BytesPerPixel Size1(Width) Size2(Height)}
1. PCA
D:\EE569_Assignment\3\C++\Image_Processing_HW3\x64\Debug>D:\EE569_Assignment\3\C++\Image_Processing_HW3\x64\Debug\Image_Processing_HW3.exe D:\EE569_Assignment\3\P1\kitten.raw D:\EE569_Assignment\3\P1\kitten_test_3.raw 3 590 350

***** VIDEOINPUT LIBRARY - 0.1995 - TFW07 *****

Solve which problems: 1
solve which part: b
Whether to print the points 1)Yes 2) No: 2
Which dimension do you want 1) 25 2) other: 2
Input the dimension:
12
Which Initialization method: 1) ramdom 2) maximum min-value 3) AS: 2
Press any key to continue . . .

2. SVM
D:\EE569_Assignment\3\C++\Image_Processing_HW3\x64\Debug>D:\EE569_Assignment\3\C++\Image_Processing_HW3\x64\Debug\Image_Processing_HW3.exe D:\EE569_Assignment\3\P1\kitten.raw D:\EE569_Assignment\3\P1\kitten_test_3.raw 3 590 350

***** VIDEOINPUT LIBRARY - 0.1995 - TFW07 *****

Solve which problems: 1
solve which part: c
Which Initialization method: 1) ramdom 2) maximum min-value 3) AS: 2
13421
Press any key to continue . . .
Press any key to continue . . .



Problem 2:	Edge and Contour Detection
(a) 	Canny Edge Detector
the input and output image should be jpg image
Open Method: {path_of_program_name path_of_color_image.jpg path_of_segmentation_image.jpg BytesPerPixel Size1(Width) Size2(Height)}
D:\EE569_Assignment\3\C++\Image_Processing_HW3\x64\Debug>D:\EE569_Assignment\3\C++\Image_Processing_HW3\x64\Debug\Image_Processing_HW3.exe D:\EE569_Assignment\3\P3\Castle.jpg D:\EE569_Assignment\3\P3\Boat_a.jpg 3 481 321

***** VIDEOINPUT LIBRARY - 0.1995 - TFW07 *****

Solve which problems: 2
solve which part: a
Press any key to continue . . .


Problem 3:	Salient Point Descriptors and Image Matching
the path of input image and output image is written in the source code
(a) 	Extraction and Description of Salient Points
Open Method: {path_of_program_name}
D:\EE569_Assignment\3\C++\Image_Processing_HW3\x64\Debug>D:\EE569_Assignment\3\C++\Image_Processing_HW3\x64\Debug\Image_Processing_HW3.exe

***** VIDEOINPUT LIBRARY - 0.1995 - TFW07 *****

Solve which problems: 3
solve which part: a
Input the method: 1) SIFT 2) SURF: 1
If do the choose track bar: 1)yes 2)no: 2
Press any key to continue . . .

(b)	Image Matching
Open Method: {path_of_program_name}
D:\EE569_Assignment\3\C++\Image_Processing_HW3\x64\Debug>D:\EE569_Assignment\3\C++\Image_Processing_HW3\x64\Debug\Image_Processing_HW3.exe

***** VIDEOINPUT LIBRARY - 0.1995 - TFW07 *****

Solve which problems: 3
solve which part: b
Input the method: 1) SIFT 2) SURF: 2
If do the choose bar: 1)yes 2)no: 2
833
182
Press any key to continue . . .

(c)	Bag of Words
Open Method: {path_of_program_name}
D:\EE569_Assignment\3\C++\Image_Processing_HW3\x64\Debug>D:\EE569_Assignment\3\C++\Image_Processing_HW3\x64\Debug\Image_Processing_HW3.exe

***** VIDEOINPUT LIBRARY - 0.1995 - TFW07 *****

Solve which problems: 3
solve which part: c
Which Initialization method: 1) ramdom 2) maximum min-value 3) AS: 2
1405
The distance between the Convertible_2 and suv are 0.0698473
The distance between the Convertible_2 and truck are 0.101113
The distance between the Convertible_2 and Convertible_1 are 0.105167
Press any key to continue . . .