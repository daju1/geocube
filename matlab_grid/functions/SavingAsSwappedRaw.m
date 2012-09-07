function SavingAsSwappedRaw(prec, stream, nPag, nRow, nCol, xLL, yLL, zLL, xSize, ySize, zSize, vMin, vMax, v);
switch (prec)
    case 1, SaveAsSwappedRaw_unsigned_char(stream, nPag, nRow, nCol, xLL, yLL, zLL, xSize, ySize, zSize, vMin, vMax, v);
    case 2, SaveAsSwappedRaw_double(stream, nPag, nRow, nCol, xLL, yLL, zLL, xSize, ySize, zSize, vMin, vMax, v);
end;

% function SaveAsSwappedRaw_unsigned_char(stream, nPag, nRow, nCol, xLL, yLL, zLL, xSize, ySize, zSize, vMin, vMax, v);
% for p = 1:nPag
%     for r = 1:nRow
%         for c = 1:nCol
%             if isnan(v(r,c,p))
%                 wrote = fwrite(stream, Swap8Bytes(0), 'uchar');
%             else
%                 value = (v(r,c,p) - vMin) / (vMax - vMin) * 255;
%                 wrote = fwrite(stream, Swap8Bytes(value), 'uchar');
%             end
%         end
%     end
% end

function SaveAsSwappedRaw_double(stream, nPag, nRow, nCol, xLL, yLL, zLL, xSize, ySize, zSize, vMin, vMax, v);
hw=waitbar(0,'Save As Swapped Raw double');
for p = 1:nPag
    for r = 1:nRow
        for c = 1:nCol
            if isnan(v(r,c,p))
                wrote = fwrite(stream, Swap8Bytes(vMin), 'double');
            else
                value = v(r,c,p);
                wrote = fwrite(stream, Swap8Bytes(value), 'double');
            end
        end
    end
    waitbar(p/nPag,hw);
end  
close(hw);