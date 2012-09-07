function SaveAsVtk(filename, ud);
vMin = min(min(min(ud.V)));
vMax = max(max(max(ud.V)));
SaveAsVtk3D(filename, size(ud.z,2), size(ud.y,2), size(ud.x,2), ud.x(1), ud.y(1), ud.z(1), ud.dx, ud.dy, ud.dz, vMin, vMax, ud.V);


function SaveAsVtk3D(filename, nPag, nRow, nCol, xLL, yLL, zLL, xSize, ySize, zSize, vMin, vMax, v);
% prec = menu('What Precision of Vtk File?', 'unsigned char', 'double');
prec = 2;
stream = fopen(filename,'w');

% # vtk DataFile Version 1.0
% Created by Golden Software ioVtk.dll
% 
% BINARY
% 
% DATASET STRUCTURED_POINTS
% DIMENSIONS 128 128 128
% ASPECT_RATIO 1.0 1.0 1.0
% ORIGIN 2.0 5.0 1.0
% 
% POINT_DATA 2097152
% SCALARS scalar1of1 unsigned_char
% LOOKUP_TABLE default
fprintf(stream, '# vtk DataFile Version 2.0\r\n');
fprintf(stream, 'Created by matlab\r\n');
fprintf(stream, '\r\n');
fprintf(stream, 'BINARY\r\n');
fprintf(stream, '\r\n');
fprintf(stream, 'DATASET STRUCTURED_POINTS\r\n');
fprintf(stream, 'DIMENSIONS %d %d %d\r\n', nCol, nRow, nPag);
fprintf(stream, 'ORIGIN %f %f %f\r\n', xLL, yLL, zLL);
fprintf(stream, 'SPACING %f %f %f\r\n', xSize, ySize, zSize);
% fprintf(stream, 'ASPECT_RATIO 1.0 1.0 1.0\r\n');
fprintf(stream, '\r\n');
fprintf(stream, 'POINT_DATA %d\r\n', nPag * nRow * nCol);
switch(prec)
    case 1, fprintf(stream, 'SCALARS scalar1of1 unsigned_char\r\n');
    case 2, fprintf(stream, 'SCALARS scalar1of1 double\r\n');
end

fprintf(stream, 'LOOKUP_TABLE default\r\n');

SavingAsSwappedRaw(prec, stream, nPag, nRow, nCol, xLL, yLL, zLL, xSize, ySize, zSize, vMin, vMax, v);
fclose(stream);

