function P = Leg(m,x)

if nargin ~= 2
  error('Wrong number of input arguments.');
end

if m == 0
	P = ones(size(x));
elseif m == 1
	P = x;
elseif m == 2
	P = 0.5*(3*(x.^2)-1);
elseif m == 3
	P = 0.5*(5*(x.^3)-3*x);
elseif m == 4
	P = 0.125*(35*(x.^4)-30*(x.^2)+3);
elseif m == 5
	P = 0.125*(63*(x.^5)-70*(x.^3)+15*x);
elseif m == 6
   P = (231*(x.^6)-315*(x.^4)+105*(x.^2)-5)./16;
end

