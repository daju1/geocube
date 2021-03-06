function output = Int3(M,dx,dy,dh,withoutNaN)

if nargin ~= 4 & nargin ~= 5
  error('Wrong number of input arguments.');
end
if nargin == 5 & withoutNaN == 'withoutNaN'
   % ?????? ?????????? ????????? ??????, ????? ?? ???????? ?? ? ??????????????
   M(find(~isfinite(M)))=0;
end

[Mx My Mh] = size(M);

output = dx*dy*dh*0.125*( 8 * sum(sum(sum(M))) - ...
4*( sum(sum(M(1,:,:))) + sum(sum(M(Mx,:,:))) + sum(sum(M(:,1,:))) + ...
    sum(sum(M(:,My,:))) + sum(sum(M(:,:,1))) + sum(sum(M(:,:,Mh))) ) + ...
2*( sum(M(1,1,:)) + sum(M(Mx,1,:)) + sum(M(Mx,My,:)) + sum(M(1,My,:)) + ...
    sum(M(1,:,1)) + sum(M(1,:,Mh)) + sum(M(Mx,:,Mh)) + sum(M(Mx,:,1)) + ...
    sum(M(:,1,1)) + sum(M(:,1,Mh)) + sum(M(:,My,Mh)) + sum(M(:,My,1)) ) - ...
( M(1,1,1) + M(1,1,Mh) + M(1,My,1) + M(1,My,Mh) +...
  M(Mx,1,1) + M(Mx,1,Mh) + M(Mx,My,1) + M(Mx,My,Mh) ));
