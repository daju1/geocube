function VF=Lapl_part_filter3(V,ALFA,nstr,ncikl,type)
% ALFA ���� ���������� ������� �� ��������� - ������� ��������
%   nstr -  ����� ���� ������� 
% ncikl - ���������� ������ ����������
if size(V) ~= size(ALFA), errordlg(['�������� ������ V � ALFA ������ ���� ���������'],'ERROR','CREATEMODE');end;

switch type
case 'vertical'
filtr1(:,:,1)=1;
filtr1(:,:,2)=0;
filtr1(:,:,3)=1;
k=sum(sum(sum(filtr1)));
VF=V;
qw=0;hw=waitbar(0,['���������� �������� ������� ������� ' type ' � �������� �������� ����� ����������' ]);
Q=size(V,1);
for ny=1:size(V,1)
   for nx=1:size(V,2)
      for nz=2:size(V,3)-1
         VF(ny,nx,nz)=ALFA(ny,nx,nz)*sum(V(ny,nx,nz-1:nz+1).*filtr1)/k+...
            V(ny,nx,nz)*(1-ALFA(ny,nx,nz));
      end
   end
   qw=qw+1;waitbar(qw/Q,hw);
end
close(hw);
case 'volume'
for nc=1:ncikl
lny=size(V,1);lnx=size(V,2);lnz=size(V,3);
qw=0;hw=waitbar(0,['���������� �������� ������� ������� ' type ' � �������� �������� ����� ����������.���� ' num2str(nc) ' �� ' num2str(ncikl)]);
for ny=1:lny
   for nx=1:lnx
      for nz=1:lnz
         y1=ny-nstr;if y1<1,y1=1;end;ncy=1+ny-y1;
         yend=ny+nstr;if yend>lny;yend=lny;end;
         x1=nx-nstr;if x1<1,x1=1;end;ncx=1+nx-x1;
         xend=nx+nstr;if xend>lnx;xend=lnx;end;
         z1=nz-nstr;if z1<1,z1=1;end;ncz=1+nz-z1;
         zend=nz+nstr;if zend>lnz;zend=lnz;end;
         % ���������� ������� �� ���������� �������� ���������, ������ NaN ����� ������ ��������
         v=V(y1:yend,x1:xend,z1:zend);
         vt=v(ncy,ncx,ncz);
         v(find(~isfinite(v)))=0;
         v(ncy,ncx,ncz)=vt;
         filter3p=ones(size(v));
         filter3p(ncy,ncx,ncz)=0;
         filter3p(find(~isfinite(v)))=0;
         k=sum(sum(sum(filter3p)));
         VF(ny,nx,nz)=ALFA(ny,nx,nz)*sum(sum(sum(v.*filter3p)))/k+V(ny,nx,nz)*(1-ALFA(ny,nx,nz));
      end
   end
   qw=qw+1;waitbar(qw/lny,hw);
end
close(hw);
end
end %switch