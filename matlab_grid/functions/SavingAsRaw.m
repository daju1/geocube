function SavingAsRaw(prec, stream, nPag, nRow, nCol, xLL, yLL, zLL, xSize, ySize, zSize, vMin, vMax, v);
switch (prec)
    case 1, SaveAsRaw_unsigned_char(stream, nPag, nRow, nCol, xLL, yLL, zLL, xSize, ySize, zSize, vMin, vMax, v);
    case 2, SaveAsRaw_double(stream, nPag, nRow, nCol, xLL, yLL, zLL, xSize, ySize, zSize, vMin, vMax, v);
end;

function SaveAsRaw_unsigned_char(stream, nPag, nRow, nCol, xLL, yLL, zLL, xSize, ySize, zSize, vMin, vMax, v);
for p = 1:nPag
    for r = 1:nRow
        for c = 1:nCol
            if isnan(v(r,c,p))
                wrote = fwrite(stream, 0, 'uchar');
            else
                value = (v(r,c,p) - vMin) / (vMax - vMin) * 255;
                wrote = fwrite(stream, value, 'uchar');
            end
        end
    end
end

function SaveAsRaw_double(stream, nPag, nRow, nCol, xLL, yLL, zLL, xSize, ySize, zSize, vMin, vMax, v);
for p = 1:nPag
    for r = 1:nRow
        for c = 1:nCol
            if isnan(v(r,c,p))
                wrote = fwrite(stream, vMin, 'double');
            else
                value = v(r,c,p);
                wrote = fwrite(stream, value, 'double');
            end
        end
    end
end