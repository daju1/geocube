% egg2
% Cоздание трЄхмерной геометрии (€йцо)
close all;clear;
dx=.5;
dy=.5;
dz=1;

x=-10:dx:10;
y=-12:dy:12;
z=-15:dz:15;
[X,Y,Z] = meshgrid(x,y,z);
sigmax=5;
sigmay=3;
sigmaz=5;
mux=5;
muy=1;
muz=0;
vx=exp(-(0.5*(X-mux)./sigmax).^2)./(sqrt(2*pi).* sigmax);
vy=exp(-(0.5*(Y-muy)./sigmay).^2)./(sqrt(2*pi).* sigmay);
vz=exp(-(0.5*(Z-muz)./sigmaz).^2)./(sqrt(2*pi).* sigmaz);
V=-10000*vx.*vy.*vz;
%clear X Y Z;
% ‘ормирование переменных, запрашиваемых функцией viz3d
ud.V=V;
ud.Altday=z(1)*ones(size(V(:,:,1)));
ud.X=X;
ud.Y=Y;
ud.Z=Z;
ud.x=x;
ud.y=y;
ud.z=z;
ude=[];
ud.dx=dx;
ud.dy=dy;
ud.dz=dz;
ud.FILENAME='egg2.m';
viz3Dgeo([],[],ud,ude,13);

%viz3d([],[],ud);