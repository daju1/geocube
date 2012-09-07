function [dfdx,dfdy,dfdz] = gradient3D_1(f,dx,dy,dz)
% Наиболее скоростная функция для трехмерного градиента
[nx1,ny1,nz1]=size(f);
perm = [2 3 1]; % Cyclic permutation
% @@@@@@@@@@
%k = 1;
[n,p] = size(f);
h=dy*((1:nx1)');
g  = zeros(size(f)); % case of singleton dimension
   % Take forward differences on left and right edges
g(1,:) = (f(2,:) - f(1,:))/(h(2)-h(1));
g(n,:) = (f(n,:) - f(n-1,:))/(h(end)-h(end-1));
   % Take centered differences on interior points
h = h(3:n) - h(1:n-2);
g(2:n-1,:) = (f(3:n,:)-f(1:n-2,:))./h(:,ones(p,1));
dfdy = ipermute(g,[1 2 3]);
f = permute(f,perm);
% @@@@@@@@@@
%k = 2;
[n,p] = size(f);
h=dx*((1:ny1)');
g  = zeros(size(f)); % case of singleton dimension
   % Take forward differences on left and right edges
g(1,:) = (f(2,:) - f(1,:))/(h(2)-h(1));
g(n,:) = (f(n,:) - f(n-1,:))/(h(end)-h(end-1));
   % Take centered differences on interior points
h = h(3:n) - h(1:n-2);
g(2:n-1,:) = (f(3:n,:)-f(1:n-2,:))./h(:,ones(p,1));
dfdx = ipermute(g,[2 3 1]);
f = permute(f,perm);
% @@@@@@@@@@
%k = 3;
[n,p] = size(f);
h=dz*((1:nz1)');
g  = zeros(size(f)); % case of singleton dimension
   % Take forward differences on left and right edges
g(1,:) = (f(2,:) - f(1,:))/(h(2)-h(1));
g(n,:) = (f(n,:) - f(n-1,:))/(h(end)-h(end-1));
   % Take centered differences on interior points
h = h(3:n) - h(1:n-2);
g(2:n-1,:) = (f(3:n,:)-f(1:n-2,:))./h(:,ones(p,1));
dfdz = ipermute(g,[3 1 2]);
f = permute(f,perm);
%-------------------------------------------------------
