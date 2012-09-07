clear;clc;

k_oslablenie = 0.0005;
smoof_power = 2;

k1 = 1.0;
k = 0.75;% ��������� ������� ��������� � ������ (��� �����) ����� ��������
k_phi_max = (pi/2.0)/atan(1.0/2.0*k);


% ���������� �������������� ��������� �������
xi = 0.0;
yi = 0.0;
zi = -5:-5:-3000;

% ���������� ������ � �������� �������
X = (-3000 : 5 : 3000)';
Y = 0;
Z = 0;


% ���������� �� �������������� ���������
% �� �������� �� �������
len = sqrt(	((X-xi).*(X-xi)) * ones(size(zi)) + (Y-yi)*(Y-yi) + ones(size(X)) * ((Z-zi).*(Z-zi)));
% ���� ����������� �� ��������
phi = acos ((ones(size(X)) * (Z-zi)) ./ len);

k_phi = k_phi_max * phi;
k_phi(find(abs(k_phi) > pi)) = 0.0;

% ������ ��������� �������� ������������
phi_k = sin(k_phi) .^ smoof_power;

% ���������� �������� � ����������� ������
Value = k1 * exp ( - k_oslablenie * len) .* phi_k;

figure (1)
%surfl (zi, X, Value); colormap pink;
[c,h] = contour (X, zi, Value');  clabel(c,h), colorbar
xlabel('X, m');
ylabel('zi, m');



