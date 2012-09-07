[x,y,z,V]=flow(5);V(1,1,1)=NaN
v2=interp3(x,y,z,V,x,y,z,'nearest')
v2-V
