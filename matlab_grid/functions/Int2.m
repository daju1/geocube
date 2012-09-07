function output = Int2(M,dx,dy)

if nargin ~= 3
  error('Wrong number of input arguments.');
end

[Mx My] = size(M);

output = dx*dy*0.25*( 4 * sum(sum(M)) - ...
2*( sum(M(1,:)) + sum(M(Mx,:)) + sum(M(:,My)) + sum(M(:,1)) ) +...
 ( M(1,1) + M(1,My) +  M(Mx,1) + M(Mx,My)) );
