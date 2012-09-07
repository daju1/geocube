function g=gradient1D(f,dx)

%f=(sin((1:180)*pi/180))'; dx=pi/180;
%f=f(:);

[n,p] = size(f);   
h = dx*(1:length(f));
g  = zeros(size(f)); % case of singleton dimension
% Take forward differences on left and right edges
if n > 1
   g(1,:) = (f(2,:) - f(1,:))/(h(2)-h(1));
   g(n,:) = (f(n,:) - f(n-1,:))/(h(end)-h(end-1));
end

% Take centered differences on interior points
if n > 2
   h = h(3:n) - h(1:n-2);
   g(2:n-1,:) = (f(3:n,:)-f(1:n-2,:))./h(:,ones(p,1));
end
