function SaveAs3DGrid(filename, ud);
% SaveAsSurfer7Grid4(filename, nPage, nRow, nCol, xLL, yLL, zLL, xSize, ySize, zSize, vMin, vMax, z);
vMin = min(min(min(ud.V)));
vMax = max(max(max(ud.V)));

SaveAsSurfer7Grid4(filename, size(ud.z,2), size(ud.y,2), size(ud.x,2), ud.x(1), ud.y(1), ud.z(1), ud.dx, ud.dy, ud.dz, vMin, vMax, ud.V);


filename(end-2) = 'g';
filename(end-1) = 'r';
filename(end) = 'd';
zMin = min(min(ud.Altday));
zMax = max(max(ud.Altday));
SaveAsSurferGrid7(filename, size(ud.y,2), size(ud.x,2), ud.x(1), ud.y(1), ud.dx, ud.dy, zMin, zMax, ud.Altday);

