% EE 569 Homework #3
% date:		Mar. 24th, 2017
% Name:		Shuo Wang
% ID:		8749390300
% email:	wang133@usc.edu
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
type = 3;
if(type == 3)%the PCA Matrix for Law filter result of use the AC value of the image and do the RMS
    KittyAC1 = importdata('D:/EE569_Assignment/3/P1/KittyAC1.txt');%import the origin 25-D vectors data
    aS7 = (reshape(KittyAC1,[25,590*350]));
    [coeff,score,latent] = pca((aS7(:,:)));
    B = 1000 * coeff(:,:)';
    fid = fopen('dataAC1.txt', 'wt');% save it in a txt file
    [row, col] = size(B);
    for i = 1:row
        for j = 1:col
            if(j == col)
                fprintf(fid, '%g\n', B(i,j));
            else
                fprintf(fid, '%g\t', B(i,j));
            end
        end
    end
elseif(type == 2)%the PCA Matrix for Law filter result of use the AC value of the image and do average
    KittyAC = importdata('D:/EE569_Assignment/3/P1/KittyAC.txt');%import the origin 25-D vectors data
    aS7 = (reshape(KittyAC,[25,590*350]));
    [coeff,score,latent] = pca((aS7(:,:)));
    B = 1000 * coeff(:,:)';
    fid = fopen('dataAC1.txt', 'wt');% save it in a txt file
    [row, col] = size(B);
    for i = 1:row
        for j = 1:col
            if(j == col)
                fprintf(fid, '%g\n', B(i,j));
            else
                fprintf(fid, '%g\t', B(i,j));
            end
        end
    end
else%the PCA Matrix for Law filter result of use the Origin value of the image and do the RMS
    KittyDC = importdata('D:/EE569_Assignment/3/P1/KittyDC.txt');%import the origin 25-D vectors data
    aS7 = (reshape(KittyDC,[25,590*350]));
    [coeff,score,latent] = pca((aS7(:,:)));
    B = 1000 * coeff(:,:)';
    fid = fopen('dataAC1.txt', 'wt');% save it in a txt file
    [row, col] = size(B);
    for i = 1:row
        for j = 1:col
            if(j == col)
                fprintf(fid, '%g\n', B(i,j));
            else
                fprintf(fid, '%g\t', B(i,j));
            end
        end
    end
end

    

