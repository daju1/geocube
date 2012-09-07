%test_griddata.m
clear, close all
[FILENAME, PATHNAME]=uigetfile('*.dat','open data file.dat');


filename=[PATHNAME, FILENAME];

data = dlmread(filename, ',');
xx = data(:,1); 
yy = data(:,2); 
zz = data(:,3);
        
zflag = 0;

Dx = max(xx) - min(xx);
Dy = max(yy) - min(yy);
Dz = max(zz) - min(zz);

% 	if (Dz < Dx && Dz < Dy)
% 		zflag = 0;
% 	else
		if (Dx < Dy)
			zflag = 2;
		else
			zflag = 1;
        end
%     end
    
    

switch(zflag)
    case 0
        x = data(:,1); 
        y = data(:,2); 
        z = data(:,3);

    case 1
        z = data(:,1); 
        y = data(:,2); 
        x = data(:,3);

    case 2
        x = data(:,1); 
        z = data(:,2); 
        y = data(:,3);
end

zflag


nx = 50;
ny = 60;

min_x = min(x);
min_y = min(y);

max_x = max(x);
max_y = max(y);

step_x = (max_x-min_x)/nx;
step_y = (max_y-min_y)/ny;

xi = min_x:step_x:max_x;
yi = (min_y:step_y:max_y)';

%zi = griddata(x,y,z, xi,yi,'v4');
zi = griddata(x,y,z, xi,yi,'cubic');
% zi = griddata(x,y,z, xi,yi,'linear');

surf(xi,yi,zi);

default_filename = FILENAME(1:end-4)

default_filename = [default_filename '_zflag_' num2str(zflag) '.grd'];

% FILENAME(end-2) = 'g';
% FILENAME(end-1) = 'r';
% FILENAME(end  ) = 'd';

[FILENAME, PATHNAME] = uiputfile('*.grd','save grid', default_filename);
filename=[PATHNAME, FILENAME];

% nRow    = size(xi,2)
% nCol    = size(yi,1)

nCol    = size(xi,2);
nRow    = size(yi,1);


xLL     = xi(1);
yLL     = yi(1);
xSize   = xi(2) - xi(1);
ySize   = yi(2) - yi(1);
zMin    = min(min(zi));
zMax    = max(max(zi));


SaveAsSurferGrid7(filename, nRow, nCol, xLL, yLL, xSize, ySize, zMin, zMax, zi);
