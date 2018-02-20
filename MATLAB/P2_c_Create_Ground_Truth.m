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
namepart1 = 'D:/EE569_Assignment/3/P3/Castle_gt';namepart10 = 'Castle_gt';
namepart2 = 'D:/EE569_Assignment/3/P3/Boat_gt';namepart20 = 'Boat_gt';
num = ['1' '2' '3' '4' '5' '6'];
for k = 1:size(num,2)
    Name1 = strcat(namepart1, num(k), '.jpg');
    image = imread(Name1);
    image1 = im2double(image);
    for i = 1:size(image1,1)
      for j = 1:size(image1,2)
          if(image1(i,j) <= 0.5)
              image1(i,j) = 0;
          else
              image1(i,j) = 1;
          end
       end
    end
    imshow(image1);
    groundTruth = cell(1);
    groundTruth{1,1}.Boundaries = logical(1 - image1);
    Name2 = strcat(namepart10, num(k), '.mat');
    save(Name2,'groundTruth');
end

for k = 1:size(num,2)
    Name1 = strcat(namepart2, num(k), '.jpg');
    image = imread(Name1);
    image1 = im2double(image);
    for i = 1:size(image1,1)
      for j = 1:size(image1,2)
          if(image1(i,j) <= 0.5)
              image1(i,j) = 0;
          else
              image1(i,j) = 1;
          end
       end
    end
    imshow(image1);
    groundTruth = cell(1);
    groundTruth{1,1}.Boundaries = logical(1 - image1);
    Name2 = strcat(namepart20, num(k), '.mat');
    save(Name2,'groundTruth');
end
