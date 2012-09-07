function V2=Laplase_filter3(V,vcf,type)

switch type
case 'vertical'
case 'volume'
   
end

%V исходная трехмерная матрица
%V=flow(5);
filtr3(:,:,1)=ones(3);
filtr3(:,:,2)=ones(3);
filtr3(:,:,3)=ones(3);
filtr3(2,2,2)=vcf;
k=1/sum(sum(sum(filtr3)));
V2=zeros(size(V));
for ny=2:size(V,1)-1
   for nx=2:size(V,2)-1
      for nz=2:size(V,3)-1
         V2(ny,nx,nz)=k.*sum(sum(sum(V(ny-1:ny+1,...
            nx-1:nx+1,nz-1:nz+1).*filtr3)));
      end
   end
end
x=1:size(V,2);
y=1:size(V,1);
z=1:size(V,3);
dx=1;
dy=1;
dz=1;
ud.x=x;
ud.y=y;
ud.z=z;

ud.dx=dx;
ud.dy=dy;
ud.dz=dz;
ud.Altday=meshgrid(x,y)
ud.V=V;
ud.V=V2;

viz3Dgeo([],[],ud);
