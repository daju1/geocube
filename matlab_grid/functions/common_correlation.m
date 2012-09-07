function [Tau,Rfg]=common_correlation(t_f,f,mean_f,t_g,g,mean_g);

% autocorrelation
if nargin ==3,
   g=f;
   t_g=t_f;
   mean_g=mean_f;
end
if isempty(mean_f), mean_f=mean(f);end
if isempty(mean_g), mean_g=mean(g);end

% input arguments must be the vectors
if ~isvector(f),      error('f must be a vector'); end
if ~isvector(t_f),    error('t_f must be a vector'); end
if ~isvector(mean_f), error('mean_f must be a vector'); end
if ~isvector(g),      error('g must be a vector'); end
if ~isvector(t_g),    error('t_g must be a vector'); end
if ~isvector(mean_g), error('mean_g must be a vector'); end

% lengthes of time and signal skale must be equial
n=length(f);
if n ~=length(t_f),error('f and t_f must have the same lengthes');end
m=length(g);
if m ~=length(t_g),error('g and t_g must have the same lengthes');end

if length(mean_f)~=n & length(mean_f)~=1, 
   error('mean_f must have the same length as f or must be a number');
end
if length(mean_g)~=m & length(mean_g)~=1, 
   error('mean_g must have the same length as g or must be a number');
end

% converting to vertical form
if size(f,2)~=1, f=f'; end
if size(g,2)~=1, g=g'; end

if size(t_f,2)~=1, t_f=t_f'; end
if size(t_g,2)~=1, t_g=t_g'; end

if size(mean_f,2)~=1, mean_f=mean_f'; end
if size(mean_g,2)~=1, mean_g=mean_g'; end

% centralized signals
f0=f-mean_f;
g0=g-mean_g;

% minimal of m and n
min_mn = min(m,n);
% Length of interim solution
L = (m + n - 1 - 2*min_mn)*min_mn + 2*sum(1:min_mn)

vRfg=zeros(L,1);
vTau=zeros(L,1);

Ind=1;
for q=1:n+m-1,
   i1 = max(1,1+q-m); i2 = min(n,q);
   j1 = max(1,1+m-q); j2 = min(m,n+m-q);
   
   FillLen=i2-i1;
   
   VectTau(Ind:Ind + FillLen) = t_f(i1:i2) - t_g(j1:j2);
   VectRfg(Ind:Ind + FillLen) = f0(i1:i2).*g0(j1:j2);
   
   Ind=Ind+FillLen+1;
end

%Sorting along tau
[SortVectTau,I]=sort(VectTau);
SortVectRfg=VectRfg(I);

DiffVectTau=diff(SortVectTau);

epsilon=10^(-6);

BoundInd=find(DiffVectTau > epsilon);
BoundInd(end+1)=length(SortVectRfg);
BoundInd(end+1)=length(SortVectRfg)+1;

LenBoundInd = length(BoundInd);

for q=1:LenBoundInd-1,
   Rfg(q)=sum(SortVectRfg(BoundInd(q):BoundInd(q+1)-1))/(BoundInd(q+1)-BoundInd(q));
   Tau(q)=SortVectTau(BoundInd(q));
end
