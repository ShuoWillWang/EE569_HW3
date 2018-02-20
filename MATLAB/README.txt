% EE 569 Homework #2
% date:		Feb. 24th, 2017
% Name:		Shuo Wang
% ID:		8749390300
% email:	wang133@usc.edu
%************************************************************************************************************************************
% solution for Problem1(a)	Texture Classification
% objective:                for a series of 25-D vectors, we intend to acquire its PCA transformation matrix
% M-file name:              P1_a_PCA.m
% Usage                     P1_a_PCA
% Application Name: 		Image_Processing_HW3.exe
%************************************************************************************************************************************
% Method:                   When choose 1 in the question "Whether to print the points 1)Yes 2) No: ", 
%                           we can get the the origin 25-D vectors data, Then use this function to 
%                           acquire the PCA transform matrix
%************************************************************************************************************************************
% solution for Problem1(a)	Texture Segmentation
% objective:                for a series of 25-D vectors, we intend to
%                           acquire its PCA transformation matrix
% M-file name:              P1_b_PCA.m
% Usage                     P1_b_PCA
% Application Name: 		Image_Processing_HW3.exe
%************************************************************************************************************************************
% Method:                   When choose 1 in the question "Whether to print the points 1)Yes 2) No: ", 
%                           we can get the the origin 25-D vectors data, Then use this function to 
%                           acquire the PCA transform matrix
%************************************************************************************************************************************
% solution for Problem2(c)	Performance Evaluation -- Structured edge
% objective:                use the F-measures to evaluate the effect of
%                           the SE edge detection 
% M-file name:              P2_c_Structured_Edge.m
% Usage                     P2_c_Structured_Edge
% Application Name: 		Image_Processing_HW3.exe
%************************************************************************************************************************************
% Method: 
% 1     Please install the Pitor's toolbox and edge tool box first
% 2     use the Create_Ground_Truth.m to get the ground truth mat file
% 3     put the m file into the edge tool box folder and load the origin image to do the SE detection
% 4     load the ground truth mat file to evaluate the F parameter
% EE 569 Homework #3
% date:		Mar. 24th, 2017
% Name:		Shuo Wang
% ID:		8749390300
% email:	wang133@usc.edu
%************************************************************************************************************************************
% solution for Problem2(c)	Performance Evaluation -- Canny
% objective:                use the F-measures to evaluate the effect of
%                           the Canny edge detection 
% M-file name:              P2_c_Canny.m
% Usage                     P2_c_Canny
% Application Name: 		Image_Processing_HW3.exe
%************************************************************************************************************************************
% Method: 
% 1     Please install the Pitor's toolbox and edge tool box first
% 2     use the Create_Ground_Truth.m to get the ground truth mat file
% 3     put the m file into the edge tool box folder and load the origin image to do the canny detection
% 4     load the ground truth mat file to evaluate the F parameter
%************************************************************************************************************************************
% solution for Problem2(c)	Performance Evaluation -- Create Ground Truth
% objective:                create the ground truth files for the F measure
% M-file name:              P2_c_Create_Ground_Truth.m
% Usage                     P2_c_Create_Ground_Truth
% Application Name: 		Image_Processing_HW3.exe
%************************************************************************************************************************************
% Method: 
% 1     Change the path name in the namepart1 and 2 where the ground truth is.
% 2     If the number is not 6, change the num
% 3     click "run" to get the ground truth file