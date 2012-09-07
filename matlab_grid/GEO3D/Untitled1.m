V=flow(6);%V(1,1,1)=NaN;
V2=Laplase_filter3(V,1,1,1,'volume');
f=ones(3,3,3);%f(3,3,3)=1;
V3=convn(V,f,'valid');