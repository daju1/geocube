function VF=Weight_filter3(V,ALFA,nstr,q,ncikl)
% ALFA Доля фильтрации и вес каждого соседнего элемента при фильтрации (1-ALFA)
% зависят от координат - задаются матрично: 
%   nstr -  число слоёв фильтра 
%   q    -  показатель степени, корректирующий веса соседних элементов при фильтрации 
% если показатель степени больше 1 то влияние на фильтр точек, удалённых от экспериментальных, уменьшается
% ncikl - количество циклов фильтрации
if size(V) ~= size(ALFA), errordlg(['Разммеры матриц V и ALFA должны быть одинаковы'],'ERROR','CREATEMODE');end;
for nc=1:ncikl
lny=size(V,1);lnx=size(V,2);lnz=size(V,3);
qw=0;hw=waitbar(0,['Фильтрация V матрицы весовым м-дом с матрично заданными:долей фильтрации,весом фильтра.Цикл ' num2str(nc) ' из ' num2str(ncikl)]);
for ny=1:lny
   for nx=1:lnx
      for nz=1:lnz
         y1=ny-nstr;if y1<1,y1=1;end;
         yend=ny+nstr;if yend>lny;yend=lny;end;
         x1=nx-nstr;if x1<1,x1=1;end;
         xend=nx+nstr;if xend>lnx;xend=lnx;end;
         z1=nz-nstr;if z1<1,z1=1;end;
         zend=nz+nstr;if zend>lnz;zend=lnz;end;
         filterw3=(1-ALFA(y1:yend,x1:xend,z1:zend)).^q;
         % Исключение влияния на фильтрацию соседних элементов, равных NaN кроме самого элемента
         v=V(y1:yend,x1:xend,z1:zend);
         vt=v(ncy,ncx,ncz);
         v(find(~isfinite(v)))=0;
         v(ncy,ncx,ncz)=vt;
         filterw3(find(~isfinite(v)))=0;
         k=sum(sum(sum(filterw3)));
         VF(ny,nx,nz)=ALFA(ny,nx,nz)*sum(sum(sum(v.*filterw3)))/k+...
            V(ny,nx,nz)*(1-ALFA(ny,nx,nz));
      end
   end
   qw=qw+1;waitbar(qw/lny,hw);
end
close(hw);
end
         
