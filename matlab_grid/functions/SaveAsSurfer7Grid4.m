function SaveAsSurfer7Grid4(filename, nPag, nRow, nCol, xLL, yLL, zLL, xSize, ySize, zSize, vMin, vMax, v);
% int SaveAsSurfer7Grid4(char *file, Grid4* pgrid)
% {
% 	printf("SaveAsSurferGrid7 %s\n", file);
% 
% 	FILE * stream;
% 	if ((stream = fopen(file,"wb")) == NULL)
% 	{
% 		char errstr[1024];
% 		sprintf(errstr, "Cannot open output file.\n%s", szPath);
% 		MessageBox(0, errstr, "SaveAsSurferGrid7", 
% 			MB_OK | MB_ICONINFORMATION);
% 		return -1;
% 	}
% 
% 	size_t wrote;
% 
% 	// Записываем
% 	long headerID = 0x42525377;
% 	wrote = fwrite(&headerID, sizeof(long), 1, stream);
% 
% 	long headerSize = 4;
% 	wrote = fwrite(&headerSize, sizeof(long), 1, stream);
% 
% 	long Version = 4;
% 	wrote = fwrite(&Version, sizeof(long), 1, stream);
% 		
% 	long gridID = 0x47524433;
% 	wrote = fwrite(&gridID, sizeof(long), 1, stream);
% 	
% 	long gridSize = 3*sizeof(long) + 10*sizeof(double);//92;
% 	wrote = fwrite(&gridSize, sizeof(long), 1, stream);
% 
% 	wrote = fwrite(&pgrid->grid4Section.nPag, sizeof(long), 1, stream);
% 	wrote = fwrite(&pgrid->grid4Section.nRow, sizeof(long), 1, stream);
% 	wrote = fwrite(&pgrid->grid4Section.nCol, sizeof(long), 1, stream);
% 	wrote = fwrite(&pgrid->grid4Section.xLL, sizeof(double), 1, stream);
% 	wrote = fwrite(&pgrid->grid4Section.yLL, sizeof(double), 1, stream);
% 	wrote = fwrite(&pgrid->grid4Section.zLL, sizeof(double), 1, stream);
% 	wrote = fwrite(&pgrid->grid4Section.xSize, sizeof(double), 1, stream);
% 	wrote = fwrite(&pgrid->grid4Section.ySize, sizeof(double), 1, stream);
% 	wrote = fwrite(&pgrid->grid4Section.zSize, sizeof(double), 1, stream);
% 	wrote = fwrite(&pgrid->grid4Section.vMin, sizeof(double), 1, stream);
% 	wrote = fwrite(&pgrid->grid4Section.vMax, sizeof(double), 1, stream);
% 
% 	double Rotation = 0.0;// not currently used
% 	wrote = fwrite(&Rotation, sizeof(double), 1, stream);
% 
% 	double BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value
% 	wrote = fwrite(&BlankValue, sizeof(double), 1, stream);
% 
% 	long dataID = 0x44415441;
% 	wrote = fwrite(&dataID, sizeof(long), 1, stream);
% 
% 	long dataSize = pgrid->grid4Section.nPag * pgrid->grid4Section.nRow * pgrid->grid4Section.nCol * sizeof(double);
% 	wrote = fwrite(&dataSize, sizeof(long), 1, stream);
% 
% 	long r, c, p;
% 	for (p = 0; p < pgrid->grid4Section.nPag; p++)
% 	{
% 		for (r = 0; r < pgrid->grid4Section.nRow; r++)
% 		{
% 			wrote = fwrite(pgrid->grid4Section.v[p][r], sizeof(double), pgrid->grid4Section.nCol, stream);
% 		}
% 	}
% 
% 	fclose(stream);
% 
% 	return 0;
% }


stream = fopen(filename,'w');
% 	// Записываем
% long headerID = 0x42525377;
headerID = 1112691575;
wrote = fwrite(stream, headerID, 'int32');

headerSize = 4;
wrote = fwrite(stream, headerSize, 'int32');

Version = 4;
wrote = fwrite(stream, Version, 'int32');
		
% 	long gridID = 0x47524433;
gridID = 1196573747;
wrote = fwrite(stream, gridID, 'int32');
	
% 	long gridSize = 3*sizeof(long) + 10*sizeof(double);//92;
gridSize = 92;

wrote = fwrite(stream, gridSize, 'int32');

% 	wrote = fwrite(&pgrid->grid4Section.nPag, sizeof(long), 1, stream);
% 	wrote = fwrite(&pgrid->grid4Section.nRow, sizeof(long), 1, stream);
% 	wrote = fwrite(&pgrid->grid4Section.nCol, sizeof(long), 1, stream);
% 	wrote = fwrite(&pgrid->grid4Section.xLL, sizeof(double), 1, stream);
% 	wrote = fwrite(&pgrid->grid4Section.yLL, sizeof(double), 1, stream);
% 	wrote = fwrite(&pgrid->grid4Section.zLL, sizeof(double), 1, stream);
% 	wrote = fwrite(&pgrid->grid4Section.xSize, sizeof(double), 1, stream);
% 	wrote = fwrite(&pgrid->grid4Section.ySize, sizeof(double), 1, stream);
% 	wrote = fwrite(&pgrid->grid4Section.zSize, sizeof(double), 1, stream);
% 	wrote = fwrite(&pgrid->grid4Section.vMin, sizeof(double), 1, stream);
% 	wrote = fwrite(&pgrid->grid4Section.vMax, sizeof(double), 1, stream);
% 

wrote = fwrite(stream, nPag, 'int32');
wrote = fwrite(stream, nRow, 'int32');
wrote = fwrite(stream, nCol, 'int32');
wrote = fwrite(stream, xLL, 'double');
wrote = fwrite(stream, yLL, 'double');
wrote = fwrite(stream, zLL, 'double');
wrote = fwrite(stream, xSize, 'double');
wrote = fwrite(stream, ySize, 'double');
wrote = fwrite(stream, zSize, 'double');
wrote = fwrite(stream, vMin, 'double');
wrote = fwrite(stream, vMax, 'double');

Rotation = 0.0;%// not currently used
wrote = fwrite(stream, Rotation, 'double');

BlankValue = 170141000918782800000000000000000000000.000000;%//1.70141e38;// nodes are blanked if greater or equal to this value
wrote = fwrite(stream, BlankValue, 'double');

% 	long dataID = 0x44415441;
dataID = 1145132097;
wrote = fwrite(stream, dataID, 'int32');

% dataSize = nRow * nCol * sizeof(double);
dataSize = nPag * nRow * nCol * 8;
wrote = fwrite(stream, dataSize, 'int32');

% 	for (p = 0; p < pgrid->grid4Section.nPag; p++)
% 	{
% 		for (r = 0; r < pgrid->grid4Section.nRow; r++)
% 		{
% 			wrote = fwrite(pgrid->grid4Section.v[p][r], sizeof(double), pgrid->grid4Section.nCol, stream);
% 		}
% 	}
% 

for p = 1:nPag
    for r = 1:nRow
        for c = 1:nCol
            if isnan(v(r,c,p))
                wrote = fwrite(stream, BlankValue, 'double');
            else
                wrote = fwrite(stream, v(r,c,p), 'double');
            end
        end
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