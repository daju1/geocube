% Sample3 - data from surfer
clear;

f00=0;

while f00<2
f00=menu('Открыть файл?','Да','Нет');
if f00<2
[FILENAME, PATHNAME]=uigetfile('*.wk1','open data file.wk1');   
if all(FILENAME==0) 
   f00=0;
else
   tp=FILENAME(end-3:end);
   if  strcmp(tp,'.wk1')
   M=wk1read([PATHNAME FILENAME]);f00=1;
else
   errordlg(['Расширение файла должно быть .wk1'],'ERROR','CREATEMODE');
   f00=0;
end

end;
if f00==1
[d1,d2]=size(M);
if d2<4
   errordlg(['Число столбцов матрицы должно быть не меньше 4. ' ...
         'Первый столбец соответствует X координате. ' ...
      'Второй столбец соответствует Y координате.'],'ERROR','CREATEMODE');
else f00=2;
end 
end
end
end
   %M=sort(M,1);
X=M(:,1);
Y=M(:,2);
ud.nstratum=d2-2;
for ii=1:ud.nstratum
   Z{ii}=M(:,ii+2)/1000+ii*1;
end


xmax=ceil(max(X));
xmin=floor(min(X));

ymax=ceil(max(Y));
ymin=floor(min(Y));

zmax= ceil(max([Z{1};Z{2};Z{3};Z{4};Z{5};Z{6}]));
zmin=floor(min([Z{1};Z{2};Z{3};Z{4};Z{5};Z{6}]));
deltaz=zmax-zmin;

dx=1;
dy=1;
dz=deltaz/50;

x=xmin:dx:xmax;
y=ymin:dy:ymax;
z=zmin:dz:zmax;

q=0;hw=waitbar(0,'Интерполяция...');
for ii=1:ud.nstratum
   [XI,YI,ZI] = griddata(X,Y,Z{ii},x,y','v4');
Zs{ii}=ZI;
q=q+1;waitbar(q/ud.nstratum,hw);
end;
close(hw);

clear M N   XI YI ZI X Y Z;
clear xmax xmin ymax ymin zmax zmin;
clear  ii ix iy iz deltaz hw q;

% Формирование переменных, запрашиваемых функцией viz3d
ud.Zs=Zs;

ud.x=x;
ud.y=y;
ud.z=z;

ud.dx=dx;
ud.dy=dy;
ud.dz=dz;


% Изменение альтитуд вышележащих слоёв, если таковые меньше, чем для нижележащих слоёв
for zi=(2:ud.nstratum)
   [yj,xj] = find(ud.Zs{zi}<ud.Zs{zi-1});
   Yj{zi}=yj;
   Xj{zi}=xj;
for q=1:length(Yj{zi})
ud.Zs{zi}(Yj{zi}(q),Xj{zi}(q))=ud.Zs{zi-1}(Yj{zi}(q),Xj{zi}(q));
end
end

% @@@@@@@@@@@@@@@@@@@@@@@@@2





[XX,YY,ZZ] = meshgrid(x,y,z);
V=ones(size(XX))*NaN;
N=length(x)*length(y);

q=0;hw=waitbar(0,'Формирование объёмной матрицы...');
for ix=1:length(x)
for iy=1:length(y)
iz=find(z<=Zs{1}(iy,ix));     % if Zs{1}(iy,ix)==NaN
   V(iy,ix,iz)=0;
iz=find( z>Zs{1}(iy,ix) & z<=Zs{2}(iy,ix));
   V(iy,ix,iz)=20;
iz=find( z>Zs{2}(iy,ix) & z<=Zs{3}(iy,ix));
   V(iy,ix,iz)=25;
iz=find( z>Zs{3}(iy,ix) & z<=Zs{4}(iy,ix));
   V(iy,ix,iz)=30;
iz=find( z>Zs{4}(iy,ix) & z<=Zs{5}(iy,ix));
   V(iy,ix,iz)=35;
iz=find( z>Zs{5}(iy,ix) & z<=Zs{6}(iy,ix));
   V(iy,ix,iz)=40;
iz=find( z>Zs{6}(iy,ix));
   V(iy,ix,iz)=NaN;
   
   q=q+1;waitbar(q/N,hw);
end
end
close(hw);

ud.V=V;
clear x y z V XX YY ZZ dx dy dz Zs;


viz3Dgeo([],[],ud)


return
ii=20;fill3([ud.x(ii)*(1:52)*0.001 fliplr(ud.x(ii)*(1:52)*0.001)],[ud.y fliplr(ud.y)],[ud.Zs{1}(:,ii)' fliplr(ud.Zs{3}(:,ii)')],'b')
