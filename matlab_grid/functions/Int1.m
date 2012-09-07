function output = Int1(M,dx,dim)

if nargin == 2
   
output = dx*0.5*(2*sum(M) - M(1) - M(end));

elseif nargin == 3
   Mx  = size(M,dim);
   if dim == 1
      MMx=M(Mx,:,:,:);
      M1=M(1,:,:,:);
   elseif dim == 2
      MMx=M(:,Mx,:,:);
      M1=M(:,1,:,:);
   elseif dim == 3
      MMx=M(:,:,Mx,:);
      M1=M(:,:,1,:);
   elseif dim == 4
      MMx=M(:,:,:,Mx);
      M1=M(:,:,:,1);
   elseif (dim ~=1)|(dim ~=2)|(dim ~=3)|(dim ~=4)
      error('Wrong Value of `dim`.');
   end
   
output = dx*0.5*(2*sum(M,dim) - M1 - MMx);

elseif (nargin ~= 2)|(nargin ~= 3)
   error('Wrong number of input arguments.');
end


