function [rotx,roty,rotz,div]=rotor_div(Vx,Vy,Vz,dx,dy,dz)
[dVxdx,dVxdy,dVxdz]=gradient3D(Vx,dx,dy,dz);
[dVydx,dVydy,dVydz]=gradient3D(Vy,dx,dy,dz);
[dVzdx,dVzdy,dVzdz]=gradient3D(Vz,dx,dy,dz);
rotx=dVzdy-dVydz;
roty=dVxdz-dVzdx;
rotz=dVydx-dVxdy;
div =dVxdx+dVydy+dVzdz;