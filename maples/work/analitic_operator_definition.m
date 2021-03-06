% ???????????? ????????? ???????? ??? ??????-????????? ?????? 
clear;
close all;

sIn1 = '-int(Pi/(a^2*b*sqw), a);';
sIn2 = '-int(Pi*hi^2/(a^4*b*sqw), a);';
sIn3 = '-int(Pi*exp(-2*a*b*sqw)/(a^2*b*sqw), a);';
sIn4 = '-int(Pi*hi^2*exp(-2*a*b*sqw)/(a^4*b*sqw), a);';

sIn1_ = maple(sIn1)
sIn2_ = maple(sIn2)
sIn3_ = maple(sIn3)
sIn4_ = maple(sIn4)

syms a hi

I1 = subs(sym(sIn1_), a, hi)
I2 = subs(sym(sIn2_), a, hi)
I3 = subs(sym(sIn3_), a, hi)
I4 = subs(sym(sIn4_), a, hi)

IsZ = expand(I1-I2-I3+I4)
IsXY = expand(0.5 * (I1+I2-I3-I4))

nju = 100000;
val_sqw = sqrt(2*pi*nju)

syms sqw
IsZw = subs(IsZ, sqw, val_sqw)
IsXYw = subs(IsXY, sqw, val_sqw)

ro = 100;%:100:1000;
sigma = 1./ro;
c = 3e8;
e0 = 8.85e-12;
mju = 1.0;
vector_b = (1.0 / c) * sqrt(mju*sigma/(2.*e0));


syms b

h = zeros(1,100)
z = zeros(1,100)
xy = zeros(1,100)

for i = 1 : 100
    val_hi = 100 * i;
    h(i) = val_hi;
    i_z = subs(IsZw, {hi, b}, {val_hi, vector_b});
    i_xy = subs(IsXYw, {hi, b}, {val_hi, vector_b});
    
    s_z = ['evalf(' char(i_z) ');'];
    s_xy = ['evalf(' char(i_xy) ');'];
    
    v_z = maple(s_z)
    v_xy = maple(s_xy)
    
    z(i) = str2num(v_z);
    xy(i) = str2num(v_xy);
    
end

subplot (1,2,1)
plot(h,z, 'green');title ('z');xlabel('h');
subplot (1,2,2)
plot (h,xy, 'red');title ('xy');xlabel('h');

% maple(is_z)
% eval(is_z)
% eval(is_xy)
% 
% syms w0 w1 w2
% 
% IsZw = expand(IsZ*(w0+hi*w1+hi*hi*w2));
% IsXYw = expand(IsXY*(w0+hi*w1+hi*hi*w2));
% 
% I_Z = int (IsZw,hi,0,inf)
% I_XY = int (IsZw,hi,0,inf)
% 
