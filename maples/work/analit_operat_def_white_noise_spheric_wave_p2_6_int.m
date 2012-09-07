% Вывод уравнения для аналитического подбора оператора (белый шум, сферическая волна, p=2)
clear;
close all;
clc;

syms a hi ax az

noise_color = 3;
s_pogloschenie = '1';
switch (noise_color)
    case 0
        s_pogloschenie = '( exp(-2*a*b) )'
    case 3 %white
        s_pogloschenie = '( 1/(2*a^2*b^2*sqw^2) - exp(-2*a*b*sqw)/(a*b*sqw) - exp(-2*a*b*sqw)/(2*a^2*b^2*sqw^2) )'
    case 4 %pink-white
        s_pogloschenie = '( (1 - exp(-2*a*b*sqw))/(2*a*b*sqw) )'
end

        

sI1 = 'int(1/(2*(a*b*sqw)^2)/a,a=hi..infinity);'
sI2 = 'int(exp(-2*a*b*sqw)/(a*b*sqw)/a,a=hi..infinity);'
sI3 = 'int(exp(-2*a*b*sqw)/(2*(a*b*sqw)^2)/a,a=hi..infinity);'

sI4 = 'int(1/(2*(a*b*sqw)^2)/a^3*hi^2,a=hi..infinity);'
sI5 = 'int(exp(-2*a*b*sqw)/(a*b*sqw)/a^3*hi^2,a=hi..infinity);'
sI6 = 'int(exp(-2*a*b*sqw)/(2*(a*b*sqw)^2)/a^3*hi^2,a=hi..infinity);'


maple ('assume(hi > 0);assume(b > 0); assume(sqw > 0);');

I1 = sym(maple(sI1))
I2 = sym(maple(sI2))
I3 = sym(maple(sI3))
I4 = sym(maple(sI4))
I5 = sym(maple(sI5))
I6 = sym(maple(sI6))

syms a b sqw hi


IX = expand(pi * (I1 - I2 - I3 + I4 - I5 - I6))
IZ = expand(2*pi * (I1 - I2 - I3 - I4 + I5 + I6))
% 
% IX = 3/8*pi/b^2/sqw^2/hi^2 -3/4*pi/b/sqw/hi/exp(b*sqw*hi)^2   +pi*Ei(1,2*b*sqw*hi) -3/8*pi/b^2/sqw^2/hi^2/exp(b*sqw*hi)^2 +1/4*pi/exp(b*sqw*hi)^2 -1/2*pi*b*sqw*hi/exp(b*sqw*hi)^2   +pi*b^2*sqw^2*hi^2*Ei(1,2*b*sqw*hi)
% IZ = 1/4*pi/b^2/sqw^2/hi^2 -1/2*pi/b/sqw/hi/exp(b*sqw*hi)^2 +2*pi*Ei(1,2*b*sqw*hi) -1/4*pi/b^2/sqw^2/hi^2/exp(b*sqw*hi)^2 -1/2*pi/exp(b*sqw*hi)^2     +pi*b*sqw*hi/exp(b*sqw*hi)^2 -2*pi*b^2*sqw^2*hi^2*Ei(1,2*b*sqw*hi)
% 
return;

% наша задача взять интеграл по a от hi до бесконечности
Is = ['-int(' s_pogloschenie ' * (1/a) * (2 - ax^2*(a^2-hi^2)/(a^2)- 2*(az*hi/a)^2), a);']

mIs = maple(Is)

%подставляем вектор направления антенн 
mIs_X = subs(mIs, {ax,az}, {1,0})
mIs_Z = subs(mIs, {ax,az}, {0,1})

% поскольку мы видим, что mIs = 0 при при стремлении a к
%бесконечности, тогда, чтобы взять интеграл от глубины источника до
%бесконечности, нужно поставить перед интегралом минус, а вместо a
%подставить глубину источника

mIs_X_hi = subs(mIs_X, a, hi)
mIs_Z_hi = subs(mIs_Z, a, hi)

%теперь предполагаем, что мощность источников:
% 1) постоянна по всей глубине - не зависит от глубины
% 2) пропорциональна глубине
% 3) пропорциональна квадрату глубины

% теперь умножаем на глубину в соответствующей степени
w_pw = 5;
switch (w_pw)
    case 0
        sIs_X_hi_w = char(mIs_X_hi);
        sIs_Z_hi_w = char(mIs_Z_hi);
    case 1
        sIs_X_hi_w = ['sqrt(hi) * (' char(mIs_X_hi) ')'];
        sIs_Z_hi_w = ['sqrt(hi) * (' char(mIs_Z_hi) ')'];
    case 2
        sIs_X_hi_w = ['hi^(2/3) * (' char(mIs_X_hi) ')'];
        sIs_Z_hi_w = ['hi^(2/3) * (' char(mIs_Z_hi) ')'];
    case 3
        sIs_X_hi_w = ['hi^(1/3) * (' char(mIs_X_hi) ')'];
        sIs_Z_hi_w = ['hi^(1/3) * (' char(mIs_Z_hi) ')'];
    case 4
        sIs_X_hi_w = ['hi^(1/4) * (' char(mIs_X_hi) ')'];
        sIs_Z_hi_w = ['hi^(1/4) * (' char(mIs_Z_hi) ')'];
    case 5
        sIs_X_hi_w = ['hi^(n) * (' char(mIs_X_hi) ')'];
        sIs_Z_hi_w = ['hi^(n) * (' char(mIs_Z_hi) ')'];
end

maple ('assume(0<n,n<1)');

        

% интегрируем mIs_Xw_hi_w по глубине hi от нуля до бесконечности
maple ('assume(b > 0); assume(sqw > 0);');
sIs_X_hi_w_Ihi_ = ['expand(int(' sIs_X_hi_w ', hi));']
sIs_Z_hi_w_Ihi_ = ['expand(int(' sIs_Z_hi_w ', hi));']

sIs_X_hi_w_Ihi = ['expand(int(' sIs_X_hi_w ', hi=0..infinity));']
sIs_Z_hi_w_Ihi = ['expand(int(' sIs_Z_hi_w ', hi=0..infinity));']

mIs_X_hi_w_Ihi_ = maple(sIs_X_hi_w_Ihi_)
mIs_Z_hi_w_Ihi_ = maple(sIs_Z_hi_w_Ihi_)

mIs_X_hi_w_Ihi = maple(sIs_X_hi_w_Ihi)
mIs_Z_hi_w_Ihi = maple(sIs_Z_hi_w_Ihi)
