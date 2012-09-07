function writer_txt(filename,m)

FID = fopen(filename,'wt')
fprintf(FID,'%d %d\n', size(m,1), size(m,2));

for i1=1:size(m,1)
for i2=1:size(m,2)
    
fprintf(FID,'%d ', m(i1,i2));
end
fprintf(FID,'\n');
end

fclose(FID);

