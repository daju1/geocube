function V2=Laplase_filter1(V,cvf,nstr,ncikl)
% cvf - ����������� �������� �������
%   nstr -  ����� ���� ������� 
% ncikl - ���������� ������ ����������
for nc=1:ncikl
   lnx=length(V);
   qw=0;
   hw=waitbar(0,['�������� ����������  c ����������� ��������� ������� = ' num2str(cvf) '.���� ' num2str(nc) ' �� ' num2str(ncikl)]);
   for nx=1:lnx
      x1=nx-nstr;if x1<1,x1=1;end;ncx=1+nx-x1;
      xend=nx+nstr;if xend>lnx;xend=lnx;end;
      % ���������� ������� �� ���������� �������� ���������, ������ NaN ����� ������ ��������
      v=V(x1:xend);
      vt=v(ncx);
      v(find(~isfinite(v)))=0;
      v(ncx)=vt;
   
      filtr1=ones(size(v));
      filtr1(ncx)=cvf;
      filtr1(find(~isfinite(v)))=0;
      k=sum(filtr1);
      V2(nx)=sum(v.*filtr1)/k;
      
      qw=qw+1;waitbar(qw/lnx,hw);
   end
   
   close(hw);

end

   