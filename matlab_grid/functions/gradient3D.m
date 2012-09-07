function varargout = gradient3D(f,dx,dy,dz)
%GRADIENT Approximate gradient.
%   [FX,FY] = GRADIENT(F) returns the numerical gradient of the
%   matrix F. FX corresponds to dF/dx, the differences in the
%   x (column) direction. FY corresponds to dF/dy, the differences
%   in the y (row) direction. The spacing between points in each
%   direction is assumed to be one. When F is a vector, DF = GRADIENT(F)
%   is the 1-D gradient.
%
%   [FX,FY] = GRADIENT(F,H), where H is a scalar, uses H as the
%   spacing between points in each direction.
%
%   [FX,FY] = GRADIENT(F,HX,HY), when F is 2-D, uses the spacing
%   specified by HX and HY. HX and HY can either be scalars to specify
%   the spacing between coordinates or vectors to specify the
%   coordinates of the points.  If HX and HY are vectors, their length
%   must match the cooresponding dimension of F.
%
%   [FX,FY,FZ] = GRADIENT(F), when F is a 3-D array, returns the
%   numerical gradient of F. FZ corresponds to dF/dz, the differences
%   in the z direction. GRADIENT(F,H), where H is a scalar, 
%   uses H as the spacing between points in each direction.
%
%   [FX,FY,FZ] = GRADIENT(F,HX,HY,HZ) uses the spacing given by
%   HX, HY, HZ. 
%
%   [FX,FY,FZ,...] = GRADIENT(F,...) extends similarly when F is N-D
%   and must be invoked with N outputs and either 2 or N+1 inputs.
%
%   Examples:
%       [x,y] = meshgrid(-2:.2:2, -2:.2:2);
%       z = x .* exp(-x.^2 - y.^2);
%       [px,py] = gradient(z,.2,.2);
%       contour(z),hold on, quiver(px,py), hold off
%
%   See also DIFF, DEL2.

%   D. Chen, 16 March 95
%   Copyright (c) 1984-98 by The MathWorks, Inc.
%   $Revision: 5.12 $  $Date: 1997/11/21 23:23:47 $
%nx=5;ny=6;nz=8;f=1:(nx*ny*nz);f=sin(f);f=reshape(f,nx,ny,nz);dx=1;dy=0.5;dz=0.25;
% [dfdx,dfdy,dfdz]=gradient3D(f,dx,dy,dz);
%[msg,f,ndim,loc,cflag] = parse_inputs(f,varargin);
%if ~isempty(msg), error(msg); end

% Loop over each dimension. Permute so that the gradient is always taken along
% the columns.
[nx1,ny1,nz1]=size(f);
perm = [2:3 1]; % Cyclic permutation
loc{1}=dy*(1:nx1);loc{2}=dx*(1:ny1);loc{3}=dz*(1:nz1);
for k = 1:3
   [n,p] = size(f);
   h = loc{k}(:);   
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

   varargout{k} = ipermute(g,[k:3 1:k-1]);

   % Set up for next pass through the loop
   f = permute(f,perm);
end 

% Swap 1 and 2 since x is the second dimension and y is the first.
  tmp = varargout{1};
  varargout{1} = varargout{2};
  varargout{2} = tmp;

%if cflag, varargout{1} = varargout{1}.'; end


%-------------------------------------------------------
