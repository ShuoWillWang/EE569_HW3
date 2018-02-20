% EE 569 Homework #3
% date:		Mar. 24th, 2017
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
type = 2;
if(type == 1)%origin PCA
    Textureout = importdata('D:/EE569_Assignment/3/P1/Textureout.txt');%import the origin 25-D vectors data
    aS9 = reshape(Textureout,[25,12]);
    [coeff1,score1,latent1] = pca(aS9);
    B = 1000 * coeff1(:,:)';

    fid = fopen('data1.txt', 'wt');% save it in a txt file
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
else%the PCA delete the first dimension element
    aS9 = reshape(Textureout,[25,12]);
    [coeff1,score1,latent1] = pca((aS9(2:25,:)));
    a = zeros(12,1);
    coeff = [a coeff1']';
    B = 1000 * coeff(:,:)';
    fid = fopen('data1a.txt', 'wt');
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
