function varargout=Mercury1;

% Mercury1  c*10^-4 = % ����.
%
% ������� ������� �������. E-mail: alexey_drozdov@mail.ru
% "������-��������������� �������� ������������ ���������� � ����������".
% �. �������. 8-0572-19-55-77
%
close all;clear;%pack;
ud=[];ude=[];FILENAME='';
mwork=0;
while mwork<3
   mwork=menu('Programm of data prepare for 3D visualization - ��������� ���������� ������ ��� 3D-Geo ������������',...
      'Start - ���������','Save - C��������','Visualissate - ������������','Exit - �����');
if mwork==1
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@   ���� �������� �����   @@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

f00=0;way=[];
while f00<3
   f00=menu('Open file? - ������� ����?','wk1','mat','No - ���');
   if f00==1
      [FILENAME, PATHNAME]=uigetfile('*.wk1','open data file.wk1');  
      cd(PATHNAME);
      if all(FILENAME==0) 
         f00=0;
      else
         tp=FILENAME(end-3:end);
         if  strcmp(tp,'.wk1')
            M=wk1read([PATHNAME FILENAME]);f00=2;
         else
            errordlg(['���������� ����� ������ ���� .wk1'],'ERROR','CREATEMODE');
            f00=0;
         end
      end;
      if f00==2
         [d1,d2]=size(M);
         if d2<8
            errordlg(['����� �������� ������� ������ ���� �� ������ 8. ' ...
               '������ ������� ������������� X ����������. ' ...
               '������ ������� ������������� Y ����������.'],'ERROR','CREATEMODE');
            f00=0;
         else f00=3;way=1;
         end 
      end
   end
   if f00==2
      [FILENAME, PATHNAME]=uigetfile('*.mat','open data file.mat');  
      cd(PATHNAME);
      if all(FILENAME==0) 
         f00=0;
      else
         tp=FILENAME(end-3:end);
         if  strcmp(tp,'.mat')
            %PA=FILENAME(1:end-4);ud=[]; eval([PA '=[];']);
            load([PATHNAME FILENAME]);
            if ~isempty(ud) | ~isempty(ude); 
            %elseif ~isempty(eval(PA)) ud=eval(PA);
            else f00=0; errordlg('sorry incorrect data or variable name','ERROR','CREATEMODE');
            end;   
            f00=3;way=2;
            if ~isempty(ud) mgeoelektr = 1; 
            elseif ~isempty(ude) mgeoelektr = 4; 
            end
         else
            errordlg(['���������� ����� ������ ���� .mat'],'ERROR','CREATEMODE');
            f00=0;
         end
      end;
   end
end
clear PATHNAME d1 d2 f00 tp;
ud.FILENAME=FILENAME;

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@  ����� ����� �������� �����   @@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

if way==1
   mgeoelektr=menu('wk1 file data contents: ������ � ����� � ����������� .wk1 ��������:',...
      'concentration data on drills - ���������� �� ������������� ������������ �������� �� ��������� �� ������ ��������',...
      'h of water gorizont - ������� ����������� ���������',...
      'Stratigrafical information C���������������� ����������',...
      'EIMPZ field ���������� �� ���������������� ������ �������');
if mgeoelektr ==1
    
    ud.input_M = M;
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@ ��������� ���������� �� �������������  @@@@@@@@@@@@
%@@@@@@@@@@@@  ������������ �������� �� ���������  @@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@  �� ������ ��������  @@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@ ��������� ����������   @@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@  �� ���������������� ������ �������  @@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@  ���� ���������� ������ � ������������  @@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   
% ���   % macc
PDC=2.1*10^-4; % macc
%log10PDC=log10(PDC);
% ����������� ������������, ������������ �����������
mindetc=3*10^-6/2;
log10mindetc=log10(mindetc);
logmindetc=log(mindetc);
% ��������� ������
rho=1.9*10^3;%rho=1.8:0.1:2.0*10^3;
% x,y -���������� �������
Xdril=M(:,2);Xdril(1:2)=[];
Ydril=M(:,3);Ydril(1:2)=[];
%����������� �������� �� ������ ������ � �����
% k=1.729828;
% Xdril=Xdril/k;Ydril=Ydril/k;

% �������� ��������� ������� �� ������������
dupl=[]; ndupl=[]; ons1=ones(size(Xdril));
for ndril=1:length(Xdril)
   ons2=ons1;ons2(ndril)=0;
   fdupl = find( Xdril(ndril)==Xdril & Ydril(ndril)==Ydril & ons2 );
   if ~isempty(fdupl)
      ndupl=[ndupl ndril];
   end
end
if ~isempty(ndupl)
   errordlg(['���������� ������� �� ' num2str(ndupl) ' �����������'],'ERROR','CREATEMODE');
end
%���������� ����� �������
plot(Xdril,Ydril,'.');title('����� �������');

xmax=floor(max(Xdril));   % xmax=ceil(max(Xdril));
xmin=ceil(min(Xdril));   % xmin=floor(min(Xdril));

ymax=floor(max(Ydril));   % ymax=ceil(max(Ydril));
ymin=ceil(min(Ydril));   % ymin=floor(min(Ydril));
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
malt=menu('Use plane surface? - ��������� ����������� ������� ������� �����������','Yes - ��','No - ���');
if malt==1
   Altulok=zeros(size(Xdril));zmax=0;zmin=0;lokzer=0;
elseif malt==2
   
% z (��������� ��� ���-���� ����) ����� �������
Altu=M(:,4);Altu(1:2)=[];
% ������������ ��������� �����������
almax=max(Altu);almin=min(Altu);
% ������� ���� ������
mzer=menu('Local zero evaluation - ������� ���� ������',...
   ['On max altitude - �� ������������ ��������� ����������� = ' num2str(round(almax)) ' �'],...
   ['On min altitude - �� ����������� ��������� ����������� = ' num2str(round(almin)) ' �'],...
   'Enter with keyboard - ������ � ����������');
if mzer==1
   lokzer=round(almax);
elseif mzer==2
   lokzer=round(almin);
elseif mzer==3
   lokzer=inputdlg('Enter local zero altitude - ������� ��������� �������� ���� ������,� =');lokzer=(str2num(lokzer{:}));
end

Altulok=Altu-lokzer;
% ������������ ��������� �����������, ���������� �� ������ �����
zmax= ceil(almax);
zmin=floor(almin);
end %if malt==1
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% ������� ������������
C=M(:,6:end);C(1,:)=[];%clear M;
% �������� ������ �������
h=C(1,:);C(1,:)=[];
   mprived=menu(' Privesti consetration to mass % ? - ���������� ������������ � % ����',...
      'Yes','No');
if mprived==1
% ���������� ������������ � % ����
C=C*10^-4;
end
% ����������� ��������� ������������:
MinZ=floor(zmin-h(end));%clear zmin;
%������ ������� �������� �� NaN ��������� ������ ������ ������ ��������� ��� ����
[dril,hz]=find(C);
NC=NaN*ones(size(C));
for q=1:length(dril)
   NC(dril(q),hz(q))=C(dril(q),hz(q));
end
maxNC=max(max(NC));
disp(['������������ �������� � �������� ������ ' num2str(maxNC)]);
minNC=min(min(NC));
disp(['����������� �������� � �������� ������ ' num2str(minNC)]);

% ������� ���������� ������� ��������
MAltulok=(Altulok*ones(1,size(NC,2))-ones(size(NC,1),1)*h);
%����� �������� � ����� ������� ������� ���������
[ndfin,nhfin]=find(isfinite(NC));
% ����� ��������
Nanaliz=length(ndfin);
% C���������� �������� ��������� �������� � ������������ � �������� ������������
for ii=1:Nanaliz
   Xanaliz(ii)=Xdril(ndfin(ii));
   Yanaliz(ii)=Ydril(ndfin(ii));
   Zanaliz(ii)=MAltulok(ndfin(ii),nhfin(ii));
   Canaliz(ii)=NC(ndfin(ii),nhfin(ii));
end
figure;plot(Xanaliz,Yanaliz,'r.');title('���������� �������� ��������');
ff=figure;plot3(Xanaliz,Yanaliz,Zanaliz,'r.');view([-30 45]);title('���������� �������� ��������');
set(ff,'Color',[1 1 1]);
% ����������� ���������� ����� ����������
minr=[];
for jj=1:length(Xdril)
   Xd=Xdril;Xd(jj)=[];
   Yd=Ydril;Yd(jj)=[];
   r=sqrt((Xdril(jj)-Xd).^2+(Ydril(jj)-Yd).^2);
   minr=min([r; minr]);
end
disp(['����������� ���������� ����� ���������� = ' num2str(minr)]);
dx=minr/2;dy=minr/2;


% ��� ������������
dz=.1;
mstep=menu('Interpolation step - ��� ������������',...
   ['Use ������������ �� ��������� dz=0.1� dx=dy=�������� ���������� ����� ���������� = ' num2str(dx) ' �'],...
   'dx=dy=10 �, dz=0.2 � ',...
   'Enter with keyboard - ������ � ����������');
if mstep==2,dx=10; dy=10; dz=0.2;
elseif mstep==3
dxdydz=inputdlg('Enter - ������� [dx dy dz],� =');dxdydz=(str2num(dxdydz{:}));
dx=dxdydz(1);dy=dxdydz(2);dz=dxdydz(3);
end

x=xmin:dx:xmax; %clear xmin xmax;
y=ymin:dy:ymax; %clear ymin ymax;
z=(MinZ:dz:zmax)-lokzer;% clear MinZ zmax;%lokzer;
lnz=length(z);lny=length(y);lnx=length(x);

% ����������� ���������������� ����� ��� ������ ��������
%zs=-fliplr(h(1):dz:h(end));



mmet=menu('Select interpolation metod for relief (v4 recommended)�������� ����� ������������ ������� �����������.������������� v4',...
   'linear','cubic','nearest','v4');
switch mmet
case 1, method3='linear';
case 2, method3='cubic';
case 3, method3='nearest';
case 4, method3='v4';
end

% ���������� ������������, ����������� ������ ������ �����������
Altday = griddata(Xdril,Ydril,Altulok,x,y',method3);
figure(2);surf(x,y,Altday);title('����� ������� �����������');
xlabel('X');ylabel('Y');

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

mlog1=menu('Use log of input data? - ��������� ���������������� �������� ������?',...
   'log10 ���������� ��������',...
   'log ����������� ��������','Do not use - �� ���������');
if mlog1==1
   ll=log10(NC);ll(find(~isfinite(ll)))=NaN;NC=ll;
   Canaliz=log10(Canaliz);
   disp('��������� ���������������� �������� ������ ���������� ����������');
elseif mlog1==2
   ll=log(NC);ll(find(~isfinite(ll)))=NaN;NC=ll;
   Canaliz=log(Canaliz);
   disp('��������� ���������������� �������� ������ ����������� ����������');
elseif mlog1==3
   disp('���������������� �������� ������ �� ���������');
end

maxNC=max(max(NC));
disp(['������������ �������� � �������� ������ ' num2str(maxNC)]);
minNC=min(min(NC));
disp(['����������� �������� � �������� ������ ' num2str(minNC)]);
disp(' ');
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

madd=menu('Use over contour drills with zero concentration? �������� �� �������� ����������� ���������� ������ �������� � �������� ���������� ������������ ��� ������ ������������ ?',...
   'Yes - ��','No - ���');
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
if madd==1
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

mcon=menu('Number of zero concentration drills profils ����� �������� �������� ������ �������',...
   'Use ������������ 1',...
   'Use ������������ 2',...
   'Use ������������ 3',...
   'Enter with keyboard - ������ � ����������');
switch mcon
case 1,nmp=1;
case 2,nmp=2;
case 3,nmp=3;
case 4
nmp=inputdlg('Enter Number of zero concentration drills profils ������� ����� �������� ������ �������');nmp=round(str2num(nmp{:}));
end
st=5;
mst=menu('distance between zero conc. drills profils - ���������� ����� ��������� ������ �������',...
   'use 5 * step of interpolation - ������������ ������ 5 * ��� ������������',...
   'enter x * step of interpolation ������ � ���������� �����, ������� ���� �������� �� ��� ������������');
if mst==2
st=inputdlg('enter x * step of interpolation - ������ � ���������� �����, ������� ���� �������� �� ��� ������������');st=round(str2num(st{:}));
end
xp=x;yp=y;
Xadd=[ ];Yadd=[ ];Altadd=[];
for mp=1:nmp
   lx=length(xp);ly=length(yp);
   Xadd=[Xadd [xp xp(end)+st*dx]  (xp(end)+st*dx)*ones(1,ly+1) [fliplr(xp) xp(1)-st*dx] (xp(1)-st*dx)*ones(1,ly+1)];
   Yadd=[Yadd (yp(1)-st*dy)*ones(1,lx+1) [yp yp(end)+st*dy] (yp(end)+st*dy)*ones(1,lx+1) [fliplr(yp) yp(1)-st*dy]];
   
   Altadd=[Altadd ...
         repmat(Altday(1,1),1,mp-1)     Altday(1,:)           repmat(Altday(1,end),1,mp)...
         repmat(Altday(1,end),1,mp-1)   Altday(:,end)'        repmat(Altday(end,end),1,mp)...
         repmat(Altday(end,end),1,mp-1) fliplr(Altday(end,:)) repmat(Altday(end,1),1,mp)...
         repmat(Altday(end,1),1,mp-1)   fliplr(Altday(:,1)')  repmat(Altday(1,1),1,mp)];
   
   xp=[xp(1)-st*dx xp xp(end)+st*dx];yp=[yp(1)-st*dy yp yp(end)+st*dy];
end

if mlog1==1
   minC=10.^(minNC);
elseif mlog1==2
   minC=exp(minNC);
end

mim=menu('As zero concentration use - � �������� �������� ������������ � ������ ��������� ������������:',...
   ['C which is min may be detected by detector ���������� ������������ �������� ������������ = ' num2str(mindetc) ' % ���� mass'],...
   ['PDC ��� = ' num2str(PDC) ' % ���� mass'],...
   ['C which is min detected from all the analises - ����������� �� ����������� �������� ������������ = ' num2str(minC) ' % ����'],...
   'Enter with keyboard - ������ � ����������');
switch mim
case 1, imc=mindetc;
case 2, imc=PDC;
case 3, imc=minC;
case 4
   imc=inputdlg('As zero concentration use - ������� �������� ������������ � ������ ���������');
   imc=(str2num(imc{:}));
end

% ���������������� �������� ������������ � ������ ��������� � ������, 
% ���� ��������� ���������������� �������� ������
if mlog1==1
   imc=log10(imc);
elseif mlog1==2
   imc=log(imc);
end

for q=1:length(Xadd)
   CIad=imc*ones(1,lnz);
   CIad(find(z>Altadd(q)))=NaN;
   CIad(find(CIad<imc & isfinite(CIad)))=imc;
   Czad(q,:)=CIad;
end

figure(3);plot([Xdril],[Ydril],'r.');
hold on;plot([Xadd'],[ Yadd'],'b.');title('����� ������� �������� � ������');
xa=xp(1):dx:xp(end);
ya=yp(1):dy:yp(end);
Altdayadd = griddata([Xdril;Xadd'],[Ydril;Yadd'],[Altulok;Altadd'],xa,ya',method3);
figure(4);surf(xa,ya,Altdayadd);title('��������������� ����� ������� ����������� � ������� ���������');
xlabel('X');ylabel('Y');
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
end %if madd==1
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@  ����� ����� ���������� ������ � ������������ @@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@  ���� ������������  @@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

mm=menu('Select C interpolation method �������� ����� ������������  ������������ ',...
   'First by drills after by gorizontal planes - �������� �� ��������� - ����� �� ������� �������������� ����������',...
   'by all volume without relief ����� �� ����� ������ ��� ����� �������',...
   'by all volume with relief ����� �� ����� ������ c ����o� �������',...
   'by all volume with relief use nnet ����� �� ����� ������ c ����o� ������� c �������������� ������������� �������������');

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

if mm==4
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@  ������� ������������  @@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@ c �������������� ������������� ������������� @@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   
   %x,y,z
   
   
   P=[Xanaliz;Yanaliz;Zanaliz];
   
   
   T=Canaliz;
   size(P)
   size(T)
   Nanaliz
   
   MinNeurons=[5,5,3];
   MaxNeurons=200;
   Sigma0=[10,10,1];;
   Goal=10;
   W0=1;
   A0=0.00;
   B0=.0;
   
   minmaxSigma=[1,50; 1,50; .0001,5; ];
   
minmaxAlpha=[-1,1;     -1,1;    -1,1;];
minmaxC    =minmax(P);
minmaxA    =[-10,10;     -10,10;    -10,10;];
minmaxB    =[-10,10;     -10,10;    -10,10;];
minmaxW    =[-1000,1000;];

net=myrbnet_6(P,T,Goal,Sigma0,W0,A0,B0,MinNeurons,MaxNeurons,minmaxSigma,minmaxAlpha,minmaxC,minmaxA,minmaxB,minmaxW);

net.Sigma
net.Alpha
net.A
net.B
net.C
net.W

hw=waitbar(0,'digitizing on volume - ��������� �� ������');
Lz=length(z)
for k=1:Lz,
[Y,X,Z]=ndgrid(y,x,z(k));XX=[X(:)';Y(:)';Z(:)'];
% �������� ������ ����������� ���� �����:
Nu=output_radial_6(XX,net.C,net.Sigma,net.Alpha);
% �������� ������ ���� �����:
YXZ=net.W*Nu+net.A*XX+sum(net.B);
V(:,:,k)=reshape(YXZ,size(X));
waitbar(k/Lz,hw);
end
close(hw)


%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

elseif mm==2

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@  ������� ������������  @@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@  �����  �� ����� ��ڨ��  @@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


if madd==2
   
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
V=grid3data(Xanaliz,Yanaliz,Zanaliz,Canaliz,x,y,z,'cubic');
if mlog1==1
   V(find(V<log10mindetc & isfinite(V)))=log10mindetc;
elseif mlog1==2
   V(find(V<logmindetc & isfinite(V)))=logmindetc;
elseif mlog1==3
   V(find(V<mindetc & isfinite(V)))=mindetc;
end
[X,Y,Z]=meshgrid(x,y,z);clear X Y;
for jj=1:lnz
   ALTDAY(:,:,jj)=Altday;
end
V(find(Z>ALTDAY(q)))=NaN;clear ALTDAY;
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
elseif madd==1
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

% ����������� �������� ������� �������������
qw=0;hw=waitbar(0,['Interpolation of concentration on slice gorizontal planes by method - ������������ ������������ �� ������� �������������� ��������� ������� ' method2]);
lnya=length(ya);lnxa=length(xa);
%[XIa,YIa]=meshgrid(xa,ya);
Ydra=[Xanaliz;Yadd'];
Xdra=[Xanaliz;Xadd'];
Cza=[Cz; Czad];

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
end % if madd==2

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@  ����� �������� ������������  @@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@  ����� �� ����� ��ڨ��  @@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

   
elseif mm==1
   
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@  ������� ������������ ��������  @@@@@@@@@@@@@@@@@
%@@@@@@@@@@  �� ��������� �������� �� �����������  @@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   

mmet=menu('Select interpolation method on every drill - �������� ����� ������������  ������������ �� ������ ��������.������������� nearest or linear recommended',...
   'nearest','linear','spline','cubic','*nearest','*linear','*cubic');
switch mmet
case 1, method='nearest';
case 2, method='linear';
case 3, method='spline';
case 4, method='cubic';
case 5, method='*nearest';
case 6, method='*linear';
case 7, method='*cubic';
end
mextr=menu('While interpolation along well if absent day surface data to extrapolate them with data on nearest glubina ? ��� ������������ �� ��������� ��� ���������� ������ �� ����������� ���������������� �� �� ������� �������� �� ��������� �������','Yes - ��','No - ���')   
% ������������ ������ �� ������ �������� �� ����� ���������� ��������
hw=waitbar(0,['Interpolation of concetration on every well by method - ������������  ������������ �� ������ �������� ������� ' method]);
for q=1:size(NC,1)
   hhh=NC(q,:);nfinit=find(isfinite(hhh));
   if ~isempty(nfinit) & length(nfinit)>2
      switch mmet
      case {2,3, 4, 7}
      CI=interp1(Altulok(q)-h(nfinit),hhh(nfinit),z,method);
      case {1,  5,  6}
      CI=interp1(Altulok(q)-h,hhh,z,method);
      end
   elseif isempty(nfinit)
      CI=NaN*ones(size(z)); 
   elseif ~isempty(nfinit) & (length(nfinit)==1)
      CI=NaN*ones(size(z)); 
      for jj=1:length(nfinit)
      CI(find(abs((z - Altulok(q)+h(nfinit(jj)) )/dz)<1))=hhh(nfinit(jj));
      end
   elseif ~isempty(nfinit) & (length(nfinit)==2)
      CI=interp1(Altulok(q)-h,hhh,z,'linear');
   end
   if ~isempty(nfinit)
      nfci=find(isfinite(CI));
      if nfci(1)>2, CI(nfci(1)-1)=hhh(nfinit(end));CI(nfci(1)-2)=hhh(nfinit(end))/2;end
      if nfci(end)<length(z)-1, CI(nfci(end)+1)=hhh(nfinit(1));CI(nfci(end)+2)=hhh(nfinit(1))/2;end
   end
   CI(find(z>Altulok(q)))=NaN;
   if mextr==1,
      nfc=find(isfinite(CI));
      if ~isempty(nfc),CI(find(isnan(CI) &  z<=Altulok(q) &  z>z(nfc(end))))=CI(nfc(end));end;
   end 
   
   if mlog1==1
   CI(find(CI<log10mindetc & isfinite(CI)))=log10mindetc;
   elseif mlog1==2
   CI(find(CI<logmindetc & isfinite(CI)))=logmindetc;
   elseif mlog1==3
   CI(find(CI<mindetc & isfinite(CI)))=mindetc;
   end
   Cz(q,:)=CI;
   waitbar(q/size(NC,1),hw);
end 
close(hw);
   
surf(z,1:size(NC,1),Cz);
maxCz=max(max(max(Cz)));
disp(['������������  ������������ �� ������ �������� ������� ' method]);
disp(['����.�������� � ������.������ �� �����. ' num2str(maxCz)]);
minCz=min(min(min(Cz)));
disp(['����������� �������� � ������.������ �� �����. ' num2str(minCz)]);
disp(' ');


% ������������ �� ����� �� ������� �������������� ��������� c ������� ���������:
mmet=menu('Select interpolation method for gorisontal planes nearest recommended - �������� ����� ������������  ������������ �� ������� �������������� ���������. ������������� nearest ',...
   'linear','cubic','nearest','v4');
switch mmet
case 1, method2='linear';
case 2, method2='cubic';
case 3, method2='nearest';
case 4, method2='v4';
end
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
if madd==1
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

% ����������� �������� ������� �������������
% ������������ ������������ �� ������� �������������� ���������
% � ������ ���������� ������ ������� ��������
qw=0;hw=waitbar(0,['Interpolation of concentration on slice gorizontal planes with image(nonreal) wells by method - ������������ ������������ �� ������� �������������� ��������� � ������ ������ ������� ������� ' method2]);
lnya=length(ya);lnxa=length(xa);
[XIa,YIa]=meshgrid(xa,ya);
Ydra=[Ydril;Yadd'];
Xdra=[Xdril;Xadd'];
Cza=[Cz; Czad];
for qq=1:length(z)
   ndra=[Cz(:,qq); Czad(:,qq)];nfinit=find(isfinite(ndra));%length(nfinit)
   if ~isempty(nfinit) & length(nfinit)>3
      VI = griddata([Xdra(nfinit)],[Ydra(nfinit)],[ndra(nfinit) ],xa,ya',method2);
   elseif isempty(nfinit)
      VI = NaN*ones(lnya,lnxa);
   elseif ~isempty(nfinit) & (length(nfinit)==1)% | length(nfinit)==2 | length(nfinit)==3)
      VI = NaN*ones(lnya,lnxa);
      for jj=1:length(nfinit)
         VI(find(abs((Xdra(nfinit(jj))-XIa)/dx)<1 & abs((Ydra(nfinit(jj))-YIa)/dy)<1))=ndra(nfinit(jj));
      end
   elseif ~isempty(nfinit) & (length(nfinit)==2 | length(nfinit)==3)
      VI = NaN*ones(lny,lnx);
      for jj=1:length(nfinit)
         VI(find(abs((Xdra(nfinit(jj))-XIa)/dx)<1 & abs((Ydra(nfinit(jj))-YIa)/dy)<1))=ndra(nfinit(jj));
      end
   end
   VI(find(z(qq)>Altdayadd))=NaN;
   if mlog1==1
      VI(find(VI<log10mindetc & isfinite(VI)))=log10mindetc;
   elseif mlog1==2
      VI(find(VI<logmindetc & isfinite(VI)))=logmindetc;
   elseif mlog1==3
      VI(find(VI<mindetc & isfinite(VI)))=mindetc;
   end
   Va(:,:,qq)=VI;
   qw=qw+1;waitbar(qw/length(z),hw);
end
close(hw);clear ndra nfinit VI
% ��������� ������������ ����������� ������ �������
dln=(lnya-lny)/2;
V=Va(1+dln:end-dln,1+dln:end-dln,:);
clear Va;

maxV=max(max(max(V)));
disp(['������������ ������������ �� ������� �������������� ��������� � ������ ������ ������� ������� ' method2]);
disp(['����.�������� � ������.������ �� ������ ' num2str(maxV)]);
minV=min(min(min(V)));
disp(['���.�������� � ������.������ �� ������ ' num2str(minV)]);
disp(' ');

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

elseif madd==2
   
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   
   % ����������� �������� ������� �������������
   % ������������ ������������ �� ������� �������������� ���������
   % ��� ���������� ������ �������
qw=0;hw=waitbar(0,['Interpolation of concentration on slice gorizontal planes by method - ������������ ������������ �� ������� �������������� ��������� ������� ' method2]);
lny=length(y);lnx=length(x);
[XI,YI]=meshgrid(x,y);
for qq=1:length(z)
   ndr=Cz(:,qq);nfinit=find(isfinite(ndr));%length(nfinit)
   if ~isempty(nfinit) & length(nfinit)>3
      VI = griddata(Xdril(nfinit),Ydril(nfinit),ndr(nfinit),x,y',method2);
   elseif isempty(nfinit)
      VI = NaN*ones(lny,lnx);
   elseif ~isempty(nfinit) & (length(nfinit)==1)% | length(nfinit)==2 | length(nfinit)==3)
      VI = NaN*ones(lny,lnx);
      for jj=1:length(nfinit)
         VI(find(abs((Xdril(nfinit(jj))-XI)/dx)<1 & abs((Ydril(nfinit(jj))-YI)/dy)<1))=ndr(nfinit(jj));
      end
   elseif ~isempty(nfinit) & (length(nfinit)==2 | length(nfinit)==3)
      VI = NaN*ones(lny,lnx);
      for jj=1:length(nfinit)
         VI(find(abs((Xdril(nfinit(jj))-XI)/dx)<1 & abs((Ydril(nfinit(jj))-YI)/dy)<1))=ndr(nfinit(jj));
      end
   end
   VI(find(z(qq)>Altday))=NaN;
   if mlog1==1
      VI(find(VI<log10mindetc & isfinite(VI)))=log10mindetc;
   elseif mlog1==2
      VI(find(VI<logmindetc & isfinite(VI)))=logmindetc;
   elseif mlog1==3
      VI(find(VI<mindetc & isfinite(VI)))=mindetc;
   end
   V(:,:,qq)=VI;
   qw=qw+1;waitbar(qw/length(z),hw);
end
close(hw);clear ndr nfinit VI
maxV=max(max(max(V)));
disp(['������������ ������������ �� ������� �������������� ��������� ������� ' method2]);
disp(['����.�������� � ������.������ �� ������ ' num2str(maxV)]);
minV=min(min(min(V)));
disp(['���.�������� � ������.������ �� ������ ' num2str(minV)]);
disp(' ');
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

end %if madd==1

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@  ����� �������� ������������ ��������  @@@@@@@@@@@@@
%@@@@@@@@@@  �� ��������� �������� �� �����������  @@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

end % if mm==2

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


mm2=menu('Use again interpolation with interp2 method nearest? ��������� ��������� ������������  ������������ �������� ''interp2'' ������� ''nearest''',...
   'Yes with the same step �� � ��� �� ����� ������������',...
   'Yes with other step �� � ������ ����� ������������',...
   'No ���');
if mm2==1
   % ����������� �������� ������� �������������
   % ��������� ������������ ������������ �� ������� �������������� 
   % ��������� ������� ''nearest'' '
qw=0;hw=waitbar(0,['Again Interpolation of concentration on slice gorizontal planes by method ��������� ������������ ������������ �� ������� �������������� ��������� ������� ''nearest'' ']);
[XI,YI]=meshgrid(x,y);
for qq=1:length(z)
   M=V(:,:,qq);[nfy,nfx]=find(isfinite(M));
   if ~isempty(nfx) & length(nfx)>3
   VI=interp2(XI,YI,M,XI,YI,'nearest');
   elseif isempty(nfx)
      VI = NaN*ones(lny,lnx);
   elseif ~isempty(nfx) & (length(nfx)==1)
      VI = NaN*ones(lny,lnx);
      for jj=1:length(nfx)
         VI(find(abs((M(nfx(jj))-XI)/dx)<1 & abs((M(nfy(jj))-YI)/dy)<1))=M(nfy(jj),nfx(jj));
      end
   elseif ~isempty(nfx) & (length(nfx)==2 | length(nfx)==3)
      VI = NaN*ones(lny,lnx);
      for jj=1:length(nfx)
         VI(find(abs((M(nfx(jj))-XI)/dx)<1 & abs((M(nfy(jj))-YI)/dy)<1))=M(nfy(jj),nfx(jj));
      end
   end
   VI(find(z(qq)>Altday))=NaN;
   if mlog1==1
      VI(find(VI<log10mindetc & isfinite(VI)))=log10mindetc;
   elseif mlog1==2
      VI(find(VI<logmindetc & isfinite(VI)))=logmindetc;
   elseif mlog1==3
      VI(find(VI<mindetc & isfinite(VI)))=mindetc;
   end
   V(:,:,qq)=VI;
   qw=qw+1;waitbar(qw/length(z),hw);
end
close(hw);clear ndr nfinit VI
maxV=max(max(max(V)));
disp(['��������� ������������ ������������ �� ������� �������������� ��������� ������� ''nearest'' ']);
disp(['����.�������� � ������.������ �� ������ ' num2str(maxV)]);
minV=min(min(min(V)));
disp(['���.�������� � ������.������ �� ������ ' num2str(minV)]);
disp(' ');
end

mm3=menu('Use again interpolation with interp3 method nearest? ��������� ��������� ������������  ������������ �������� ''interp3'' ������� ''nearest''',...
   'Yes with the same step �� � ��� �� ����� ������������',...
   'Yes with other step �� � ������ ����� ������������',...
   'No ���');
if mm3==1
   % ��������� ������������ �� ����� �������� ''interp3'' ������� ''nearest'''
   [XI,YI,ZI]=meshgrid(x,y,z);
   V=interp3(XI,YI,ZI,V,XI,YI,ZI,'nearest');
   clear XI YI ZI;
maxV=max(max(max(V)));
disp(['��������� ������������ �� ����� �������� ''interp3'' ������� ''nearest''']);
disp(['����.�������� � ������.������ �� ������ ' num2str(maxV)]);
minV=min(min(min(V)));
disp(['���.�������� � ������.������ �� ������ ' num2str(minV)]);
disp('  ');
end
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@  ����� ����� ������������  @@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@  ���� ���������� � ����������� @@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% �������� �������� � ����������������� ��������� ������� �� ������������ �������� � ���������:
% Checkout(mlog1,V,x,y,z,dx,dy,dz,Xanaliz,Yanaliz,Zanaliz,Canaliz,Nanaliz);
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

% ����������
V=filtracion(mlog1,V,x,y,z,dx,dy,dz,Xanaliz,Yanaliz,Zanaliz,Canaliz,Nanaliz);

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

% ������� ��������� ����� �����
M=calculi_M(mlog1,V,dx,dy,dz,rho);

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% �������� �������� � ����������������� ��������� ������� �� ������������ �������� � ���������:
%  Checkout(mlog1,V,x,y,z,dx,dy,dz,Xanaliz,Yanaliz,Zanaliz,Canaliz,Nanaliz);
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

if mlog1==3
mlog2=menu('Use log for the interpolated data? ��������� ���������������� ����������������� ������ ?',...
   'log10 ���������� ��������',...
   'log ����������� ��������','Do not use �� ���������');
if mlog2==1
   ll=log10(V);ll(find(~isfinite(ll)))=NaN;V=ll;
   Canaliz=log10(Canaliz);
   disp('��������� ���������������� ����������������� ������ ���������� ����������');
elseif mlog2==2
   ll=log(V);ll(find(~isfinite(ll)))=NaN;V=ll;
   Canaliz=log(Canaliz);
   disp('��������� ���������������� ����������������� ������ ����������� ����������');
elseif mlog2==3
   V=V;%clear V;
   disp('���������������� ����������������� ������ �� ���������');
end
clear ll;
maxV=max(max(max(V)));
disp(['����.�������� � �����.��������.������ �� ������ ' num2str(maxV)]);
minV=min(min(min(V)));
disp(['���.�������� � �����.��������.������ �� ������ ' num2str(minV)]);
disp(' ');
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% ������� ��������� ����� �����
M=calculi_M(mlog2,V,dx,dy,dz,rho);
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% �������� �������� � ����������������� ��������� ������� �� ������������ �������� � ���������:
%    Checkout(mlog2,V,x,y,z,dx,dy,dz,Xanaliz,Yanaliz,Zanaliz,Canaliz,Nanaliz);
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

% ����������
V=filtracion(mlog2,V,x,y,z,dx,dy,dz,Xanaliz,Yanaliz,Zanaliz,Canaliz,Nanaliz);

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

% ������� ��������� ����� �����
M=calculi_M(mlog2,V,dx,dy,dz,rho);

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% �������� �������� � ����������������� ��������� ������� �� ������������ �������� � ���������:
%   Checkout(mlog2,V,x,y,z,dx,dy,dz,Xanaliz,Yanaliz,Zanaliz,Canaliz,Nanaliz);
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
end %if mlog1==3

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@  ����� ����� ���������� � ����������� @@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@  ���� ������������ ����������  @@@@@@@@@@@@@@@@
%@@@@@@@@@@@  ��� ������� �Ш������� ������������  @@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% ������������ ����������, ������������� �������� viz3Dgeo
ud.dx=dx;%clear dx;
ud.dy=dy;%clear dy;
ud.dz=dz;%clear dz;
ud.x=x;  %clear x;
ud.y=y;  %clear y;
ud.z=z;  %clear z;
%ud.zs=zs;%clear z;
ud.Altday=Altday;
ud.V=V;  %clear V;
size(V)
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@  ����� ����� ������������ ����������  @@@@@@@@@@@@@
%@@@@@@@@@@@  ��� ������� �Ш������� ������������  @@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
elseif mgeoelektr==4
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@ ��������� ����������   @@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@  �� ���������������� ������ �������  @@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
M(1,:)=[];% ��������� ������ ������,���������� ����� �������
% x,y -���������� ��������� ������ �������
Xizm=M(:,1)*20;
Yizm=M(:,2)*20;
%����������� �������� �� ������ ������ � �����
k=1.729828;
Xizm=Xizm/k;Yizm=Yizm/k;

% �������� ��������� ��������� ������ ������� �� ������������
dupl=[]; ndupl=[]; ons1=ones(size(Xizm));
for nizm=1:length(Xizm)
   ons2=ons1;ons2(nizm)=0;
   fdupl = find( Xizm(nizm)==Xizm & Yizm(nizm)==Yizm & ons2 );
   if ~isempty(fdupl)
      ndupl=[ndupl nizm];
   end
end
if ~isempty(ndupl)
   errordlg(['����������  ��������� ������ ������� �� ' num2str(ndupl) ' �����������'],'ERROR','CREATEMODE');
end
%���������� ����� ��������� ������ �������
plot(Xizm,Yizm,'.');title('�����  ��������� ������ �������');

xmax=floor(max(Xizm));   % xmax=ceil(max(Xizm));
xmin=ceil(min(Xizm));   % xmin=floor(min(Xizm));

ymax=floor(max(Yizm));   % ymax=ceil(max(Yizm));
ymin=ceil(min(Yizm));   % ymin=floor(min(Yizm));

Azim=M(:,3);
Maxv=M(:,4);
Minv=M(:,5);
Gorv=M(:,6);

% ����������� ���������� ����� �������� ��������� ������ �������
minr=[];
for jj=1:length(Xizm)
   Xd=Xizm;Xd(jj)=[];
   Yd=Yizm;Yd(jj)=[];
   r=sqrt((Xizm(jj)-Xd).^2+(Yizm(jj)-Yd).^2);
   minr=min([r; minr]);
end
disp(['����������� ���������� ����� �������� ��������� ������ �������  = ' num2str(minr)]);
dx=minr/2;dy=minr/2;
% ��� ������������
mstep=menu('Step of interpolation ��� ������������',...
   ['������������ �� ��������� dx=dy=�������� ���������� ����� �������� ��������� ������ ������� = ' num2str(dx) ' �'],...
   'dx=dy=10 �',...
   'dx=dy=25 �',...
   'dx=dy=50 �',...
   '������ � ����������');
if mstep==2,dx=10;dy=10;
elseif mstep==3,dx=25;dy=25;
elseif mstep==4,dx=50;dy=50;
elseif mstep==5
dxdy=inputdlg('������� [dx dy],� =');dxdy=(str2num(dxdy{:}));
dx=dxdy(1);dy=dxdy(2);
end
x=xmin:dx:xmax; %clear xmin xmax;
y=ymin:dy:ymax; %clear ymin ymax;

% lny=length(y);lnx=length(x);
 

mmet=menu('�������� ����� ������������ ����������� ��������� ������ �������.������������� v4',...
   'linear','cubic','nearest','v4');
switch mmet
case 1, method3='linear';
case 2, method3='cubic';
case 3, method3='nearest';
case 4, method3='v4';
end

% ���������� ������������ ������������ ����������� ��������� ������ �������.
gridMax = griddata(Xizm,Yizm,Maxv,x,y',method3);
figure;surf(x,y,gridMax);title('����� ����������� gridMax');xlabel('X');ylabel('Y');
gridMin = griddata(Xizm,Yizm,Minv,x,y',method3);
figure;surf(x,y,gridMin);title('����� ����������� gridMin');xlabel('X');ylabel('Y');
gridGor = griddata(Xizm,Yizm,Gorv,x,y',method3);
figure;surf(x,y,gridGor);title('����� ����������� gridGor');xlabel('X');ylabel('Y');
gridAzim = griddata(Xizm,Yizm,Azim,x,y',method3);
figure;surf(x,y,gridAzim);title('����� ����������� gridAzim ');xlabel('X');ylabel('Y');
[X,Y]=meshgrid(x,y);
% ���������� ������������ ������������ ����������� ��������� ������ �������.
gridMax = exp(-0.00001*sqrt(X.^2+Y.^2));
figure;surf(x,y,gridMax);title('����� ����������� gridMax');xlabel('X');ylabel('Y');
gridMin = exp(-0.00001*sqrt(X.^2+Y.^2)).*cos(X.^2+Y.^2);
figure;surf(x,y,gridMin);title('����� ����������� gridMin');xlabel('X');ylabel('Y');
gridAzim = 90*sin(sqrt(X.^2+Y.^2));
figure;surf(x,y,gridAzim);title('����� ����������� gridAzim ');xlabel('X');ylabel('Y');

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@  ���� ������������ ����������  @@@@@@@@@@@@@@@@
%@@@@@@@@@@@  ��� ������� �Ш������� ������������  @@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% ������������ ����������, ������������� �������� viz3Dgeo
ude.dx=dx;%clear dx;
ude.dy=dy;%clear dy;
ude.x=x;%clear x;
ude.y=y;%clear y;
ude.Max=gridMax;
ude.Min=gridMin;
ude.Gor=gridGor;
ude.Azim=gridAzim;
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@  ����� ����� ������������ ����������  @@@@@@@@@@@@@
%@@@@@@@@@@@  ��� ������� �Ш������� ������������  @@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

end % if mgeoelektr
end %if way==1

elseif mwork==2 %& way==1
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@  ���� ���������� ����������  @@@@@@@@@@@@@@@@@
%@@@@@@@@@@@  ��� ������� �Ш������� ������������  @@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
if mgeoelektr==1, nam=' ud';elseif mgeoelektr==4, nam=' ude';end
sav=menu('save in format:','wk1','mat','txt', 'grid4', 'raw', 'vtk');
if sav==1 
   pa1='*.wk1';
elseif sav==2 
   pa1='*.mat'; 
elseif sav==3 
   pa1='*.txt';
elseif sav==4 
   pa1='*.cub';
elseif sav==5 
   pa1='*.raw';
elseif sav==6 
   pa1='*.vtk';
end;
[FILENAME, PATHNAME] = uiputfile(pa1, ['save variable' nam ' in format: ' pa1]);
cd(PATHNAME);
if all(FILENAME~=0)
if sav==1 
 wk1write([PATHNAME FILENAME],ud);
elseif sav==2
   eval(['save ' [PATHNAME FILENAME] nam]);
elseif sav==3  
   dlmwrite([PATHNAME FILENAME],ud,' ');
elseif sav==4  
   SaveAs3DGrid([PATHNAME FILENAME],ud);
elseif sav==5  
   SaveAsRaw([PATHNAME FILENAME],ud);
elseif sav==6  
   SaveAsVtk([PATHNAME FILENAME],ud);
end; 
end;
ud.FILENAME=FILENAME;
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@  ����� ����� ���������� ����������  @@@@@@@@@@@@@@
%@@@@@@@@@@@  ��� ������� �Ш������� ������������  @@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

elseif mwork==3
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
ud
ude
close all;
viz3Dgeo([],[],ud,ude,18);
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
end % if mwork==1
end % while mwork<4




%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@   ��������������� �������   @@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@   ������� ����������   @@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

function V=filtracion(mlog,V,x,y,z,dx,dy,dz,Xanaliz,Yanaliz,Zanaliz,Canaliz,Nanaliz);

mf=menu('Use filtration of 3D matrix? ������������ ���������� ��������� �������?',...
   '������� vertical � ��������������� ������������ ����� ���������� � ��������',...
   '������� volume � ��������������� ������������ ����� ���������� � ��������',...
   '���� ��������.�������.����� �� ����� ��������� ���������� �� ����� �� �����.���� �������� ������� volume.������ ������.���������.',...
   '���� �����.�������.������.�������� �� ����� ����� ������.�����.�����.�� ����� �� �����.���� ������.������� volume.������ ������.���������.',...
   '���� ��������.�������.����� ��������� ���������� �� ����� �� �����.���� �������� ������� volume.������ ������.���������.',...
   '���� �����.�������.������.�������� �� ����� ������.�����.�����.�� ����� �� �����.���� ������.������� volume.������ ������.���������.',...
   '���� ��������.�������.����� �� ����� ��������� ���������� �� ����� �� �����.���� ��������=[1-(��� ����.�������� ��� ����������)]',...
   '���� �����.�������.������.�������� �� ����� ����� ������.�����.�����.�� ����� �� �����.���� ������.=[1-(��� ����.�������� ��� ����������)]',...
   '������������ ������� smooth3 - ����������� ���������� � ������ ��������',...
   'No ���');
if mf==1|mf==2
   mcvf=menu('����������� ��������� ������� =',...
   '������������ 0',...
   '������������ 1',...
   '������������ 2',...
   '������ � ����������');
   switch mcvf
   case 1, cvf=0;
   case 2, cvf=1;
   case 3, cvf=2;
   case 4
      cvf=inputdlg('������� ����������� �������� �������');cvf=(str2num(cvf{:}));
   end
   switch mf
   case 1, type='vertical';
   case 2, type='volume';
   end
end
if mf==1 |mf==2 |mf==3 | mf==4 | mf==5 | mf==6 | mf==7 | mf==8 
   mstr=menu('����� ���� ������� =',...
   '������������ 1',...
   '������������ 2',...
   '������������ 3',...
   '������ � ����������');
   switch mstr
   case 1, nstr=1;
   case 2, nstr=2;
   case 3, nstr=3;
   case 4
      nstr=inputdlg('������� ����������� �������� �������');
      nstr=round(str2num(nstr{:}));
   end
   mcikl=menu('����� ������ ���������� =',...
   '������������ 1',...
   '������������ 2',...
   '������������ 3',...
   '������ � ����������');
   switch mcikl
   case 1, ncikl=1;
   case 2, ncikl=2;
   case 3, ncikl=3;
   case 4
      nstr=inputdlg('������� ����������� �������� �������');
      nstr=round(str2num(nstr{:}));
   end
end
%������������ ������� ALFA - ���������������� ����������� ���� ����������
if mf==3 | mf==5
   [X,Y,Z]=meshgrid(x,y,z);
   ALFA=zeros(size(V));
   hw=waitbar(0,'������� ����� �� ����� ��������� ����������');
   for ii=1:Nanaliz
      ALFA=ALFA+(X-Xanaliz(ii)).^2+(Y-Yanaliz(ii)).^2+(Z-Zanaliz(ii)).^2;
      waitbar(ii/Nanaliz,hw);
   end
   clear X Y Z;
   close(hw);
   maxALFA=max(max(max(ALFA)));
   ALFA=sqrt(ALFA/maxALFA);
end
%������������ ������� ALFA - ���������������� ����������� ���� ����������
if mf==4 | mf==8
   [X,Y,Z]=meshgrid(x,y,z);
   ALFA=zeros(size(V));
   hw=waitbar(0,'������� �������� �������� �� ����� ����� �������� ��������� ����������');
   for ii=1:Nanaliz
      ALFA=ALFA+1./((X-Xanaliz(ii)).^2+(Y-Yanaliz(ii)).^2+(Z-Zanaliz(ii)).^2);
      waitbar(ii/Nanaliz,hw);
   end
   clear X Y Z;
   close(hw);
   ALFA=1./ALFA;
   maxALFA=max(max(max(ALFA)));
   ALFA=sqrt(ALFA/maxALFA);
   minALFA=min(min(min(ALFA)));
end
%������������ ������� ALFA - ���������������� ����������� ���� ����������
if mf==5
   [X,Y,Z]=meshgrid(x,y,z);
   ALFA=zeros(size(V));
   hw=waitbar(0,'������� ����� ��������� ����������');
   for ii=1:Nanaliz
      ALFA=ALFA+(X-Xanaliz(ii)).^2+(Y-Yanaliz(ii)).^2+(Z-Zanaliz(ii)).^2;
      waitbar(ii/Nanaliz,hw);
   end
   clear X Y Z;
   close(hw);
   maxALFA=max(max(max(ALFA)));
   ALFA=(ALFA/maxALFA);
end
%������������ ������� ALFA - ���������������� ����������� ���� ����������
if mf==6
   [X,Y,Z]=meshgrid(x,y,z);
   ALFA=zeros(size(V));
   hw=waitbar(0,'������� �������� �������� �� ����� �������� ��������� ����������');
   for ii=1:Nanaliz
      ALFA=ALFA+1./((X-Xanaliz(ii)).^2+(Y-Yanaliz(ii)).^2+(Z-Zanaliz(ii)).^2);
      waitbar(ii/Nanaliz,hw);
   end
   clear X Y Z;
   close(hw);
   ALFA=1./ALFA;
   maxALFA=max(max(max(ALFA)));
   ALFA=(ALFA/maxALFA);
   minALFA=min(min(min(ALFA)));
end
%fff=figure;plot(sort(ALFA(:)));title('plot ALFA');
if mf==3 | mf==4 | mf==5 | mf==6 
   %���������� ����� ������� V,����.� �����������.������,������.���������� � ���� ������
   % � ���������� ����������� ����� ������� ALFA ������ 
   %��� ������ ���� �������� �� ��������� ��� ����������
   mreplaceV=menu('��������� ������ ������� V, ��������� � ����������������� ������,������.���������� � ���� ������','��','���');
   mreplaceALFA=menu('��������� ������ ������� ALFA, ��������� � ����������������� ������,������.���������� � ���� ������','��','���');
   
   hw=waitbar(0,'���������� ����� ������� ALFA, ����.� �����������.������ ������ ��� ������ �� ��������� ������.�������� � ���� ������');
   for ii=1:Nanaliz
      nxanaliz=find(abs(x-Xanaliz(ii))<=.5*dx);
      nyanaliz=find(abs(y-Yanaliz(ii))<=.5*dy);
      nzanaliz=find(abs(z-Zanaliz(ii))<=.5*dz);
      for yj=1:length(nyanaliz)
         for xj=1:length(nxanaliz)
            for zj=1:length(nzanaliz)
               if mreplaceV==1,V(nyanaliz(yj),nxanaliz(xj),nzanaliz(zj))=Canaliz(ii);end;
               if mreplaceALFA==1,ALFA(nyanaliz(yj),nxanaliz(xj),nzanaliz(zj))=0;end;
            end
         end
      end
      waitbar(ii/Nanaliz,hw);
   end
   close(hw);
   disp(['����� ���������� ��������� � ������� ALFA = ' num2str(length(find(~isfinite(ALFA))))]);
   fff=figure;plot(sort(ALFA(:)));title('plot ALFA')
end

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% �������� �������� � ������� V �� ������������ �������� � ���������:
%  Checkout(mlog,V,x,y,z,dx,dy,dz,Xanaliz,Yanaliz,Zanaliz,Canaliz,Nanaliz);
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
if mf==1|mf==2
   V=Laplase_filter3(V,cvf,nstr,ncikl,type);
   disp(['�������.��������.������� ' type ' c �����.����.������� = ' num2str(cvf)]);
   maxV=max(max(max(V)));
   disp(['����.�������� � ������.������ �� ������ ' num2str(maxV)]);
   minV=min(min(min(V)));
   disp(['���.�������� � ������.������ �� ������ ' num2str(minV)]);
   disp(' ');
end


if mf==3 | mf==4 | mf==5 | mf==6
   % ��������.������� ''volume'' � �������� �������� (ALFA) ����� ����������
   V=Lapl_part_filter3(V,ALFA,nstr,ncikl,'volume');
   clear ALFA;
   disp(['�������.��������.������� ''volume'' � �������� �������� ����� ����������']);
   maxV=max(max(max(V)));
   disp(['����.�������� � ������.������ �� ������ ' num2str(maxV)]);
   minV=min(min(min(V)));
   disp(['���.�������� � ������.������ �� ������ ' num2str(minV)]);
   disp(' ');
end

if mf==7 | mf==8
   %  ���������� ������� V ������� �������� � �������������� ������� ������� ALFA
   %   nstr -  ����� ���� ������� 
   %   q    -  ���������� �������, �������������� ���� �������� ��������� ��� ���������� 
   % ���� q ������ 1 �� ������� �� ������ �����, �������� �� �����������������, �����������
   % ncikl - ���������� ������ ����������
   q=1;
   V=Weight_filter3(V,ALFA,nstr,q,ncikl);
   disp(['�������.��������.�������: ���� �����.-������.�����. �� ����� ����� ������.��������� ���������� = 1 - (��� ������� �������� ��� ����������)']);
   maxV=max(max(max(V)));
   disp(['����.�������� � ������.������ �� ������ ' num2str(maxV)]);
   minV=min(min(min(V)));
   disp(['���.�������� � ������.������ �� ������ ' num2str(minV)]);
   disp(' ');
end
if mf==9
   mtypefiltr=menu('��� �������:','''gaussian''','''box''' );
   switch mtypefiltr
   case 1, filt='gaussian';
   case 2, filt='box';
   end
   msz=menu('������ �������:','3*3*3','4*4*1','5*5*5','6*6*6','7*7*7','8*8*8');
   switch msz
   case 1, sz=3;
   case 2, sz=4;
   case 3, sz=5;
   case 4, sz=6;
   case 5, sz=7;
   case 6, sz=8;
   end
   % ����������� ���������� � ������ ��������
   V = smooth3(V, filt, sz);
end

if mf==10
   disp(['���������� �� ������������']);disp(' ');
end

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@  ����� ������� ����������   @@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@   ������� �������� ��������� �����   @@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

function M=calculi_M(mlog,V,dx,dy,dz,rho)
% ������� ��������� ����� �����
if  mlog==1
   M=Int3(10.^V,dx,dy,dz,'withoutNaN')*rho*0.01;
elseif  mlog==2
   M=Int3(exp(V),dx,dy,dz,'withoutNaN')*rho*0.01;
elseif  mlog==3
   M=Int3(V,dx,dy,dz,'withoutNaN')*rho*0.01;
end
disp(['��������� ����� ����� ' num2str(M) ' ��']);
disp(' ');

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@  ����� ������� �������� ��������� �����   @@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@   ������� �������� ��������   @@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


function Checkout(mlog,V,x,y,z,dx,dy,dz,Xanaliz,Yanaliz,Zanaliz,Canaliz,Nanaliz)
% �������� �������� � ����������������� ��������� ������� �� ������������ �������� � ���������:
dd=.5;
for ii=1:Nanaliz
   nxanaliz=find(abs(x-Xanaliz(ii))<=dd*dx);
   nyanaliz=find(abs(y-Yanaliz(ii))<=dd*dy);
   nzanaliz=find(abs(z-Zanaliz(ii))<=dd*dz);
   CV=[];
   for yj=1:length(nyanaliz)
      for xj=1:length(nxanaliz)
         for zj=1:length(nzanaliz)
            CV=[CV V(nyanaliz(yj),nxanaliz(xj),nzanaliz(zj))];
         end
      end
   end
   if mlog==1
      DeltaC(ii)=min((10.^CV)-(10.^Canaliz(ii)));
   elseif mlog==2
      DeltaC(ii)=min(exp(CV)-exp(Canaliz(ii)));
   elseif mlog==3
      DeltaC(ii)=min(CV-Canaliz(ii));
   end
end
sqe=DeltaC(find(isfinite(DeltaC)));
nnan=length(find(~isfinite(DeltaC)));
disp(['����� ��������� ���������� = ' num2str(sqe*sqe') ]);
disp(['����� ������� ������ ������ �������� �� NaN = ' num2str(nnan) ]);
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@  ����� ������� �������� ��������   @@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
