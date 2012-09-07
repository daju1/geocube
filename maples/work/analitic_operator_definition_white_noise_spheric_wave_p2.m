% Вывод уравнения для аналитического подбора оператора (белый шум, сферическая волна, p=2)
clear;
close all;

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

        



% наша задача взять интеграл по a от hi до бесконечности
Is = ['-int(' s_pogloschenie ' * (1/a) * (2 - ax^2*(a^2-hi^2)/(a^2)- 2*(az*hi/a)^2), a);']

mIs = maple(Is)

%подставляем вектор направления антенн 
mIs_X = subs(mIs, {ax,az}, {1,0})
mIs_Z = subs(mIs, {ax,az}, {0,1})


%подставляем верхний предел частоты
nju = 100000;
val_sqw = sqrt(2*pi*nju)

syms sqw
mIs_Xw = subs(mIs_X, sqw, val_sqw)
mIs_Zw = subs(mIs_Z, sqw, val_sqw)

% mIs_Xw = mIs_X;
% mIs_Zw = mIs_Z;


%чтобы понять к чему стремится выражение mIs при стремлении a к
%бесконечности, построим график его зависимости от a 

%для этого подставляем какое-то значение глубины источника
val_hi = 200;
mIs_Xwhi = subs(mIs_Xw, hi, val_hi)
mIs_Zwhi = subs(mIs_Zw, hi, val_hi)

%а также какое-то значение интегрального коэффициента затухания, зависящего от проводимости
val_ro = 1000;
val_sigma = 1./val_ro;
c = 3e8;
e0 = 8.85e-12;
mju = 1.0;
val_b = (1.0 / c) * sqrt(mju*val_sigma/(2.*e0));


syms b
mIs_Xwhib = subs(mIs_Xwhi, b, val_b)
mIs_Zwhib = subs(mIs_Zwhi, b, val_b)

%теперь готовим вектор значений a
Na = 50
va = zeros(1,Na);
vz = zeros(1,Na);
vx = zeros(1,Na);

for ia = 1 : Na
    val_a = val_hi * ia;
    va(ia) = val_a;
    mIs_Xwhib_a = subs(mIs_Xwhib, a, val_a);
    mIs_Zwhib_a = subs(mIs_Zwhib, a, val_a);
    
    class_mIs_Xwhib_a = class(mIs_Xwhib_a);
    if (strcmp(class_mIs_Xwhib_a, 'double'))          
        vx(ia) = mIs_Xwhib_a;            
        vz(ia) = mIs_Zwhib_a;  
    else
        s_mIs_Xwhib_a = ['evalf(' char(mIs_Xwhib_a) ');'];
        s_mIs_Zwhib_a = ['evalf(' char(mIs_Zwhib_a) ');'];
        
        v_mIs_Xwhib_a = maple(s_mIs_Xwhib_a)
        v_mIs_Zwhib_a = maple(s_mIs_Zwhib_a)
        
        vx(ia) = str2num(v_mIs_Xwhib_a);
        vz(ia) = str2num(v_mIs_Zwhib_a); 
    end
end

figure(1)
subplot (1,2,1)
plot(va,vz, 'green');title ('vz');xlabel('a');
subplot (1,2,2)
plot (va,vx, 'red');title ('vx');xlabel('a');

figure(2)
plot(va,vz, 'green', va,vx, 'red');title ('vz-green vx-red');xlabel('a');

% поскольку мы видим, что mIs = 0 при при стремлении a к
%бесконечности, тогда, чтобы взять интеграл от глубины источника до
%бесконечности, нужно поставить перед интегралом минус, а вместо a
%подставить глубину источника

mIs_Xw_hi = subs(mIs_Xw, a, hi)
mIs_Zw_hi = subs(mIs_Zw, a, hi)

%теперь предполагаем, что мощность источников:
% 1) постоянна по всей глубине - не зависит от глубины
% 2) пропорциональна глубине
% 3) пропорциональна квадрату глубины

% теперь умножаем на глубину в соответствующей степени
w_pw = 0;
switch (w_pw)
    case 0
        sIs_Xw_hi_w = char(mIs_Xw_hi);
        sIs_Zw_hi_w = char(mIs_Zw_hi);
    case 1
        sIs_Xw_hi_w = ['sqrt(hi) * (' char(mIs_Xw_hi) ')'];
        sIs_Zw_hi_w = ['sqrt(hi) * (' char(mIs_Zw_hi) ')'];
    case 2
        sIs_Xw_hi_w = ['hi * (' char(mIs_Xw_hi) ')'];
        sIs_Zw_hi_w = ['hi * (' char(mIs_Zw_hi) ')'];
end
        



%теперь интересно построить график зависимости этого интеграла от глубины
%источника

%для этого подставляем какое-то значение интегрального коэффициента затухания, зависящего от проводимости
mIs_Xw_hib = subs(sym(sIs_Xw_hi_w), b, val_b)
mIs_Zw_hib = subs(sym(sIs_Zw_hi_w), b, val_b)

Nh = 50
h = zeros(1,Nh);
z_h = zeros(1,Nh);
x_h = zeros(1,Nh);

for ih = 1 : Nh
    v_hi = val_hi * ih;
    h(ih) = v_hi;
    mIs_Xw_hib_hi = subs(mIs_Xw_hib, hi, v_hi);
    mIs_Zw_hib_hi = subs(mIs_Zw_hib, hi, v_hi);
    
    
    class_mIs_Xw_hib_hi = class(mIs_Xw_hib_hi);
    if (strcmp(class_mIs_Xw_hib_hi, 'double'))
        x_h(ih) = mIs_Xw_hib_hi;
        z_h(ih) = mIs_Zw_hib_hi;
    else
        s_mIs_Xw_hib_hi = ['evalf(' char(mIs_Xw_hib_hi) ');'];
        s_mIs_Zw_hib_hi = ['evalf(' char(mIs_Zw_hib_hi) ');'];
        
        v_mIs_Xw_hib_hi = maple(s_mIs_Xw_hib_hi)
        v_mIs_Zw_hib_hi = maple(s_mIs_Zw_hib_hi)
        
        x_h(ih) = str2num(v_mIs_Xw_hib_hi);
        z_h(ih) = str2num(v_mIs_Zw_hib_hi);
    end    
end

figure(3)
subplot (1,2,1)
plot(h,z_h, 'green');title ('z');xlabel('h');
subplot (1,2,2)
plot (h,x_h, 'red');title ('x');xlabel('h');

figure(4)
plot(h,z_h, 'green', h,x_h, 'red');title ('z_h-green x_h-red');xlabel('h');


% интегрируем mIs_Xw_hi_w по глубине hi от нуля до бесконечности

sIs_Xw_hi_w_Ihi = ['int(' sIs_Xw_hi_w ', hi=0..1.0e9);']
sIs_Zw_hi_w_Ihi = ['int(' sIs_Zw_hi_w ', hi=0..1.0e9);']

mIs_Xw_hi_w_Ihi = maple(sIs_Xw_hi_w_Ihi)
mIs_Zw_hi_w_Ihi = maple(sIs_Zw_hi_w_Ihi)

%теперь интересно построить график зависимости этого интеграла от глубины
%источника

%для этого подставляем какое-то значение интегрального коэффициента затухания, зависящего от проводимости
mIs_Xw_hi_w_Ihib = subs(mIs_Xw_hi_w_Ihi, b, val_b)
mIs_Zw_hi_w_Ihib = subs(mIs_Zw_hi_w_Ihi, b, val_b)

        s_mIs_Xw_hi_w_Ihib = ['evalf(' char(mIs_Xw_hi_w_Ihib) ');']
        s_mIs_Zw_hi_w_Ihib = ['evalf(' char(mIs_Zw_hi_w_Ihib) ');']
        
        m_mIs_Xw_hi_w_Ihib = maple(s_mIs_Xw_hi_w_Ihib)
        m_mIs_Zw_hi_w_Ihib = maple(s_mIs_Zw_hi_w_Ihib)
        
        

for ih = 1 : Nh
    v_hi = val_hi * ih;
    h(ih) = v_hi;
    mIs_Xw_hi_w_Ihib_hi = subs(mIs_Xw_hi_w_Ihib, hi, v_hi);
    mIs_Zw_hi_w_Ihib_hi = subs(mIs_Zw_hi_w_Ihib, hi, v_hi);
    
    
    class_mIs_Xw_hi_w_Ihib_hi = class(mIs_Xw_hi_w_Ihib_hi);
    if (strcmp(class_mIs_Xw_hi_w_Ihib_hi, 'double'))
        x_h(ih) = mIs_Xw_hi_w_Ihib_hi;
        z_h(ih) = mIs_Zw_hi_w_Ihib_hi;
    else
        s_mIs_Xw_hi_w_Ihib_hi = ['evalf(' char(mIs_Xw_hi_w_Ihib_hi) ');'];
        s_mIs_Zw_hi_w_Ihib_hi = ['evalf(' char(mIs_Zw_hi_w_Ihib_hi) ');'];
        
        v_mIs_Xw_hi_w_Ihib_hi = maple(s_mIs_Xw_hi_w_Ihib_hi)
        v_mIs_Zw_hi_w_Ihib_hi = maple(s_mIs_Zw_hi_w_Ihib_hi)
        
        x_h(ih) = str2num(v_mIs_Xw_hi_w_Ihib_hi);
        z_h(ih) = str2num(v_mIs_Zw_hi_w_Ihib_hi);
    end    
end

figure(5)
subplot (1,2,1)
plot(h,z_h, 'green');title ('z');xlabel('h');
subplot (1,2,2)
plot (h,x_h, 'red');title ('x');xlabel('h');

figure(6)
plot(h,z_h, 'green', h,x_h, 'red');title ('z_h-green x_h-red');xlabel('h');


% поскольку мы видим, что для случаев w_pw = 0..1 mIs_Xw_hi_w 
% стремится к 0 при при стремлении hi к
% бесконечности, тогда, чтобы взять интеграл по глубине от 0 до
% бесконечности, нужно поставить перед интегралом минус, а вместо 
%подставить глубину источника

% mIs_Xw_hi = subs(mIs_Xw, a, hi)
% mIs_Zw_hi = subs(mIs_Zw, a, hi)
