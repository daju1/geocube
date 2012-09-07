%function fff
load topo

load worldmtx


% filename = 'C:\\topo.txt';
% writer_txt(filename,flipud(topo))
% 
% filename = 'C:\\topof.txt';
% writer_txtf(filename,flipud(topo))

% filename = 'topomap1.txt';
% writer_txtf(filename,topomap1)
% 
% filename = 'topomap2.txt';
% writer_txtf(filename,topomap2)
% 
% filename = 'clrmap.txt';
% writer_txtf(filename,clrmap)

filename = 'topomap1.txt';
writer_txt(filename,floor(255*topomap1))

filename = 'topomap2.txt';
writer_txt(filename,floor(255*topomap2))

filename = 'clrmap.txt';
writer_txt(filename,floor(255*clrmap))

filename = 'colormap_hsv.txt';
colormap hsv
writer_txt(filename,floor(255*colormap))

filename = 'colormap_hot.txt';
colormap hot
writer_txt(filename,floor(255*colormap))

filename = 'colormap_gray.txt';
colormap gray
writer_txt(filename,floor(255*colormap))

filename = 'colormap_bone.txt';
colormap bone
writer_txt(filename,floor(255*colormap))

filename = 'colormap_copper.txt';
colormap copper
writer_txt(filename,floor(255*colormap))

filename = 'colormap_pink.txt';
colormap pink
writer_txt(filename,floor(255*colormap))

filename = 'colormap_white.txt';
colormap white
writer_txt(filename,floor(255*colormap))

filename = 'colormap_flag.txt';
colormap flag
writer_txt(filename,floor(255*colormap))

filename = 'colormap_lines.txt';
colormap lines
writer_txt(filename,floor(255*colormap))

filename = 'colormap_colorcube.txt';
colormap colorcube
writer_txt(filename,floor(255*colormap))

filename = 'colormap_vga.txt';
colormap vga
writer_txt(filename,floor(255*colormap))

filename = 'colormap_jet.txt';
colormap jet
writer_txt(filename,floor(255*colormap))

filename = 'colormap_prism.txt';
colormap prism
writer_txt(filename,floor(255*colormap))

filename = 'colormap_cool.txt';
colormap cool
writer_txt(filename,floor(255*colormap))

filename = 'colormap_autumn.txt';
colormap autumn
writer_txt(filename,floor(255*colormap))

filename = 'colormap_spring.txt';
colormap spring
writer_txt(filename,floor(255*colormap))


filename = 'colormap_winter.txt';
colormap winter
writer_txt(filename,floor(255*colormap))


filename = 'colormap_summer.txt';
colormap summer
writer_txt(filename,floor(255*colormap))

% filename = 'C:\\map.txt';
% writer_txt(filename,map)

% filename = 'C:\\nations.txt';
% FID = fopen(filename,'wt')
% fprintf(FID,'%d %d\n', size(nations,1), size(nations,2));
% 
% for i1=1:size(nations,1)
% for i2=1:size(nations,2)
%     
% fprintf(FID,'%s \n', nations(i1,i2).name);
% end
% fprintf(FID,'\n');
% end
% 
% fclose(FID);

