% ����� ��������� ��� �������������� ������� ��������� (����� ���, ����������� �����, p=2)
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

        



% ���� ������ ����� �������� �� a �� hi �� �������������
Is = ['-int(' s_pogloschenie ' * (1/a) * (2 - ax^2*(a^2-hi^2)/(a^2)- 2*(az*hi/a)^2), a);']

mIs = maple(Is)

%����������� ������ ����������� ������ 
mIs_X = subs(mIs, {ax,az}, {1,0})
mIs_Z = subs(mIs, {ax,az}, {0,1})

% ��������� �� �����, ��� mIs = 0 ��� ��� ���������� a �
%�������������, �����, ����� ����� �������� �� ������� ��������� ��
%�������������, ����� ��������� ����� ���������� �����, � ������ a
%���������� ������� ���������

mIs_X_hi = subs(mIs_X, a, hi)
mIs_Z_hi = subs(mIs_Z, a, hi)

%������ ������������, ��� �������� ����������:
% 1) ��������� �� ���� ������� - �� ������� �� �������
% 2) ��������������� �������
% 3) ��������������� �������� �������

% ������ �������� �� ������� � ��������������� �������
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

        

% ����������� mIs_Xw_hi_w �� ������� hi �� ���� �� �������������
maple ('assume(b > 0); assume(sqw > 0);');
sIs_X_hi_w_Ihi_ = ['expand(int(' sIs_X_hi_w ', hi));']
sIs_Z_hi_w_Ihi_ = ['expand(int(' sIs_Z_hi_w ', hi));']

sIs_X_hi_w_Ihi = ['expand(int(' sIs_X_hi_w ', hi=0..infinity));']
sIs_Z_hi_w_Ihi = ['expand(int(' sIs_Z_hi_w ', hi=0..infinity));']

mIs_X_hi_w_Ihi_ = maple(sIs_X_hi_w_Ihi_)
mIs_Z_hi_w_Ihi_ = maple(sIs_Z_hi_w_Ihi_)

mIs_X_hi_w_Ihi = maple(sIs_X_hi_w_Ihi)
mIs_Z_hi_w_Ihi = maple(sIs_Z_hi_w_Ihi)
