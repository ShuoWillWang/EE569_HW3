% EE 569 Homework #3
% date:		Mar. 24th, 2017
% Name:		Shuo Wang
% ID:		8749390300
% email:	wang133@usc.edu
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


% Demo for Structured Edge Detector (please see readme.txt first).

%% set opts for training (see edgesTrain.m)
opts=edgesTrain();                % default options (good settings)
opts.modelDir='models/';          % model will be in models/forest
opts.modelFnm='modelBsds';        % model name
opts.nPos=5e5; opts.nNeg=5e5;     % decrease to speedup training
opts.useParfor=0;                 % parallelize if sufficient memory

%% train edge detector (~20m/8Gb per tree, proportional to nPos/nNeg)
tic, model=edgesTrain(opts); toc; % will load model if already trained

%% set detection parameters (can set after training)
%In the Problem 2 (b), we will cahnge those parameters to get the change of the SE detector
model.opts.multiscale=0;%0          % for top accuracy set multiscale=1
model.opts.sharpen=2;%2             % for top speed set sharpen=0
model.opts.nTreesEval=4;%4          % for top speed set nTreesEval=1
model.opts.nThreads=4; %4           % max number threads for evaluation
model.opts.nms=0; %0                % set to true to enable nms

%% evaluate edge detector on BSDS500 (see edgesEval.m)
if(0), edgesEval( model, 'show',1, 'name','' ); end

%% detect edge and visualize results
I = imread('D:/EE569_Assignment/3/C++/Image_Processing_HW3_P2_b/x64/Debug/Castle.jpg');%import the origin image
Ia = imread('D:/EE569_Assignment/3/C++/Image_Processing_HW3_P2_b/x64/Debug/Boat.jpg');
tic, E=edgesDetect(I,model); toc
tic, Ea=edgesDetect(Ia,model); toc
figure(1); im(I); figure(2); im(1-E);
figure(3); im(Ia); figure(4); im(1-Ea);%output the edge image
namepart1 = 'D:/EE569_Assignment/3/P3/Castle_gt';namepart10 = 'Castle_gt';
namepart2 = 'D:/EE569_Assignment/3/P3/Boat_gt';namepart20 = 'Boat_gt';
num = ['1' '2' '3' '4' '5' '6'];

E1 = zeros(size(E,1), size(E,2));
Ea1 = zeros(size(Ea,1), size(Ea,2));

prob = 0:0.01:0.49;
Fm = [];
for n = 1: size(prob,2)
	for i = 1:size(E,1)
        for j = 1:size(E,2)
            if(E(i,j) < prob(n))
                E1(i,j) = 0;
            else
                E1(i,j) = 1;
            end
        end
    end
    R = []; P = [];
    for k = 1:size(num,2)
        Parameter = struct('out','','thrs',1,'maxDist',.0075,'thin',1);
        Name2 = strcat(namepart10, num(k), '.mat');
        [thrs,cntR,sumR,cntP,sumP,V] = edgesEvalImg( E1, Name2, Parameter );
        %for the ground truth, we will use the Create ground truth function
        %to build the file we want.
        R = [R cntR / sumR];
        P = [P cntP / sumP];
    end
    re = mean(R);
    pre = mean(P);
    F = 2 * (re * pre) / (re + pre);
    Fm = [Fm F];
end
[Fmm, Probm] = max(Fm); % get the max f
Probm = (Probm - 1) * 0.01;
for i = 1:size(E,1)
	for j = 1:size(E,2)
        if(E(i,j) < Probm)
            E1(i,j) = 0;
        else
            E1(i,j) = 1;
        end
    end
end
figure
imshow(E1);


proba = 0:0.01:0.49;
Fma = [];
for n = 1: size(proba,2)
	for i = 1:size(Ea,1)
        for j = 1:size(Ea,2)
            if(Ea(i,j) < proba(n))
                Ea1(i,j) = 0;
            else
                Ea1(i,j) = 1;
            end
        end
    end
    Ra = []; Pa = [];
    for k = 1:size(num,2)
        Parametera = struct('out','','thrs',1,'maxDist',.0075,'thin',1);
        Name2a = strcat(namepart20, num(k), '.mat');
        [thrs,cntR,sumR,cntP,sumP,V] = edgesEvalImg( Ea1, Name2a, Parametera );
        Ra = [Ra cntR / sumR];
        Pa = [Pa cntP / sumP];
    end
    rea = mean(Ra);
    prea = mean(Pa);
    Fa = 2 * (rea * prea) / (rea + prea);
    Fma = [Fma Fa];
end
[Fmma, Probma] = max(Fma);
Probma = (Probma - 1) * 0.01;
for i = 1:size(Ea,1)
	for j = 1:size(Ea,2)
        if(Ea(i,j) < Probma)
            Ea1(i,j) = 0;
        else
            Ea1(i,j) = 1;
        end
    end
end
figure
imshow(Ea1);
R = []; P = [];
for k = 1:size(num,2)
	Parameter = struct('out','','thrs',1,'maxDist',.0075,'thin',1);
	Name2 = strcat(namepart10, num(k), '.mat');
	[thrs,cntR,sumR,cntP,sumP,V] = edgesEvalImg( E1, Name2, Parameter );
	R = [R cntR / sumR];
	P = [P cntP / sumP];
end

