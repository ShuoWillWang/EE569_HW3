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

I = imread('D:/EE569_Assignment/3/C++/Image_Processing_HW3_P2_b/x64/Debug/Castle.jpg');
Ia = imread('D:/EE569_Assignment/3/C++/Image_Processing_HW3_P2_b/x64/Debug/Boat.jpg');
Ig = rgb2gray(I);
BW = edge(Ig,'canny',[0.18 0.23]);
figure;
imshow(BW);
Iga = rgb2gray(Ia);
BWa = edge(Iga,'canny',[0.18 0.23]);
figure;
imshow(BWa);

namepart1 = 'D:/EE569_Assignment/3/P3/Castle_gt';namepart10 = 'Castle_gt';
namepart2 = 'D:/EE569_Assignment/3/P3/Boat_gt';namepart20 = 'Boat_gt';
num = ['1' '2' '3' '4' '5' '6'];

R = []; P = [];
for k = 1:size(num,2)
	Parameter = struct('out','','thrs',1,'maxDist',.0075,'thin',1);
	Name2 = strcat(namepart10, num(k), '.mat');
	[thrs,cntR,sumR,cntP,sumP,V] = edgesEvalImg( BW, Name2, Parameter );
	R = [R cntR / sumR];
	P = [P cntP / sumP];
end
re = mean(R);
pre = mean(P);
F = 2 * (re * pre) / (re + pre);

Ra = []; Pa = [];
for k = 1:size(num,2)
	Parameter = struct('out','','thrs',1,'maxDist',.0075,'thin',1);
	Name2 = strcat(namepart20, num(k), '.mat');
	[thrs,cntR,sumR,cntP,sumP,V] = edgesEvalImg( BWa, Name2, Parameter );
	Ra = [Ra cntR / sumR];
	Pa = [Pa cntP / sumP];
end
rea = mean(Ra);
prea = mean(Pa);
Fa = 2 * (rea * prea) / (rea + prea);