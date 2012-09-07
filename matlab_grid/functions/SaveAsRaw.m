function SaveAsRaw(filename, ud);
vMin = min(min(min(ud.V)));
vMax = max(max(max(ud.V)));
SaveAsRaw3D(filename, size(ud.z,2), size(ud.y,2), size(ud.x,2), ud.x(1), ud.y(1), ud.z(1), ud.dx, ud.dy, ud.dz, vMin, vMax, ud.V);



function SaveAsRaw3D(filename, nPag, nRow, nCol, xLL, yLL, zLL, xSize, ySize, zSize, vMin, vMax, v);

prec = menu('What Precision of Raw File?', 'unsigned char', 'double');

filename2 = [filename '.hdr.txt'];
stream2 = fopen(filename2,'w');
fprintf(stream2, 'HEADER of RAW FILE %s\r\n', filename);
fprintf(stream2, 'DIMENSIONS %d %d %d\r\n', nCol, nRow, nPag);
fprintf(stream2, 'ORIGIN %f %f %f\r\n', xLL, yLL, zLL);
fprintf(stream2, 'SPACING %f %f %f\r\n', xSize, ySize, zSize);
switch(prec)
    case 1, fprintf(stream2, 'PRECISION unsigned_char\r\n');
    case 2, fprintf(stream2, 'PRECISION double\r\n');
end
fclose(stream2);

stream = fopen(filename,'w');
SavingAsRaw(prec, stream, nPag, nRow, nCol, xLL, yLL, zLL, xSize, ySize, zSize, vMin, vMax, v);
fclose(stream);

