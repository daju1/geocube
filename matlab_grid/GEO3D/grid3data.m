function VI=grid3data(Xanaliz,Yanaliz,Zanaliz,Canaliz,x,y,z,method);

if (size(y,1)==1), y=y'; end;
if (size(x,1)==1), x=x'; end;
if (size(z,1)==1), z=z'; end;
if (size(Xanaliz,1)==1), Xanaliz=Xanaliz'; end;
if (size(Yanaliz,1)==1), Yanaliz=Yanaliz'; end;
if (size(Zanaliz,1)==1), Zanaliz=Zanaliz'; end;
if (size(Canaliz,1)==1), Canaliz=Canaliz'; end;

if strcmp(method,'cubic')
   A=pinv(f_koord_cubic(Xanaliz,Yanaliz,Zanaliz))*Canaliz;
   for iy=1:length(y)
      for ix=1:length(x)
         VI(iy,ix,:)=f_koord_cubic(x(ix)*ones(size(z)),y(iy)*ones(size(z)),z)*A;
      end
   end
end

function K=f_koord_cubic(vx,vy,vz);
K(:,1)=ones(size(vx));

K(:,2)=vx;
K(:,3)=vy;
K(:,4)=vz;

K(:,5)=vx.^2;
K(:,6)=vy.^2;
K(:,7)=vz.^2;

K(:,8) =vx.*vy;
K(:,9) =vy.*vz;
K(:,10)=vx.*vz;

K(:,11)=vx.^3;
K(:,12)=vy.^3;
K(:,13)=vz.^3;

K(:,14)=(vx.^2).*vy;
K(:,15)=(vy.^2).*vz;
K(:,16)=(vx.^2).*vz;

K(:,17)=vx.*(vy.^2);
K(:,18)=vy.*(vz.^2);
K(:,19)=vx.*(vz.^2);

K(:,20) =vx.*vy.*vz;

