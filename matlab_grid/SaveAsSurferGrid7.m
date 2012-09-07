function SaveAsSurferGrid7(filename, nRow, nCol, xLL, yLL, xSize, ySize, zMin, zMax, z);
%stream = fopen(filename,"wb");
stream = fopen(filename,'w');
% 	// Записываем
% headerID = 0x42525344;
headerID = 1112691524;
wrote = fwrite(stream, headerID, 'int32');

headerSize = 4;
wrote = fwrite(stream, headerSize, 'int32');

Version = 4;
wrote = fwrite(stream, Version, 'int32');
		
% gridID = 0x44495247;
gridID = 1145655879;
wrote = fwrite(stream, gridID, 'int32');
	
gridSize = 72;
wrote = fwrite(stream, gridSize, 'int32');

wrote = fwrite(stream, nRow, 'int32');
wrote = fwrite(stream, nCol, 'int32');
wrote = fwrite(stream, xLL, 'double');
wrote = fwrite(stream, yLL, 'double');
wrote = fwrite(stream, xSize, 'double');
wrote = fwrite(stream, ySize, 'double');
wrote = fwrite(stream, zMin, 'double');
wrote = fwrite(stream, zMax, 'double');

Rotation = 0%.0;// not currently used
wrote = fwrite(stream, Rotation, 'double');

BlankValue = 170141000918782800000000000000000000000.000000;%//1.70141e38;// nodes are blanked if greater or equal to this value
wrote = fwrite(stream, BlankValue, 'double');

% dataID = 0x41544144;
dataID = 1096040772
wrote = fwrite(stream, dataID, 'int32');

% dataSize = nRow * nCol * sizeof(double);
dataSize = nRow * nCol * 8;
wrote = fwrite(stream, dataSize, 'int32');

% for r = 1:nRow
% %     wrote = fwrite(stream, z(r,:), 'double');
%     wrote = fwrite(stream, z(:,r), 'double');
% end

for r = 1:nRow
    for c = 1:nCol
        wrote = fwrite(stream, z(r,c), 'double');
    end
end

% wrote = fwrite(stream, z, 'double');
    
% 	if (pgrid->faultSection.nTraces && 
% 		pgrid->faultSection.nVertices &&
% 		pgrid->faultSection.traces && 
% 		pgrid->faultSection.vertexes)
% 	{
% 		long faultID = 0x49544c46;
% 		wrote = fwrite(&faultID, sizeof(long), 1, stream);
% 		long faultSize = 8;
% 		wrote = fwrite(&faultSize, sizeof(long), 1, stream);
% 		wrote = fwrite(&pgrid->faultSection.nTraces, sizeof(long), 1, stream);
% 		wrote = fwrite(&pgrid->faultSection.nVertices, sizeof(long), 1, stream);
% 
% 		long faultDataID = 1096040772;
% 		wrote = fwrite(&faultDataID, sizeof(long), 1, stream);
% 		long faultDataSize = 
% 			pgrid->faultSection.nTraces   * sizeof(Trace) + 
% 			pgrid->faultSection.nVertices * sizeof(Vertex);
% 		wrote = fwrite(&faultDataSize, sizeof(long), 1, stream);
% 		wrote = fwrite(pgrid->faultSection.traces, sizeof(Trace), pgrid->faultSection.nTraces, stream);
% 		wrote = fwrite(pgrid->faultSection.vertexes, sizeof(Vertex), pgrid->faultSection.nVertices, stream);
% 	}

fclose(stream);