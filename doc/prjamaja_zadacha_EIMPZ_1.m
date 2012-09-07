clear;clc;%close all;

ax = 0; ay = 0; az = 1;
k_oslablenie = 0.0005; pw_dnp = 4;







k1 = 1.0;
% k = 0.75;% отношение глубины источника к полной (два плеча) длине аномалии
% k_phi_max = (pi/2.0)/atan(1.0/2.0*k);
% smoof_power = 4096;
% smoof_power = 12;
% 
% smoof_power = 24;
% smoof_power = 8;
% smoof_power = 4;
d = 10;
% координаты геологического источника сигнала
xi = 0.0;
yi = 0.0;
zi = -d:-d:-3000;

% координаты антенн Ц приЄмника сигнала
X = (-3000 : d : 3000)';
Y = 0;
Z = 0;


% рассто€ние от геологического источника
% до приЄмника на профиле
len = sqrt(	((X-xi).*(X-xi)) * ones(size(zi)) + (Y-yi)*(Y-yi) + ones(size(X)) * ((Z-zi).*(Z-zi)));
% угол направлени€ на источник
% phi = acos ((ones(size(X)) * (Z-zi)) ./ len);

% угол между направлением на источник и нормалью к антене
scalar_product = ax*((X-xi) * ones(size(zi))) + ay*(Y-yi) + az*((ones(size(X)) * (Z-zi)));
scalar_product_len = scalar_product ./ len;
phi = acos(scalar_product_len);
% phi(find(abs(phi) > pi)) = 0.0;
% коэффициент выхода диаграммы направленности
phi_k = sin(phi) .^ pw_dnp;


% 
Value = k1 * exp ( - k_oslablenie * len) .* phi_k;
% добавление элемента в разреженную строку

% k_phi = k_phi_max * phi;
% k_phi(find(abs(k_phi) > pi)) = 0.0;
% 
% м€гкое включение углового коэффициента
% phi_k = sin(phi2) .^ smoof_power;

% добавление элемента в разреженную строку
% Value = k1 * exp ( - k_oslablenie * len) .* phi_k;

figure (1)
[c,h] = contour (X, zi, Value'); clabel(c,h), colorbar
xlabel('X, m');
ylabel('zi, m');

% figure (2)
% surfl (X, zi, Value'); colormap pink;
% xlabel('X, m');
% ylabel('zi, m');

figure (3)
surfl (X, zi, phi'); 
title('phi');
xlabel('X, m');
ylabel('zi, m');

figure (4)
[c,h] = contour (X, zi, scalar_product');  clabel(c,h), colorbar
title('scalar_product');
xlabel('X, m');
ylabel('zi, m');

figure (5)
[c,h] = contour (X, zi, scalar_product_len');  clabel(c,h), colorbar
title('scalar_product / len');
xlabel('X, m');
ylabel('zi, m');

figure (6)
[c,h] = contour (X, zi, len');  clabel(c,h), colorbar
title('len');
xlabel('X, m');
ylabel('zi, m');


