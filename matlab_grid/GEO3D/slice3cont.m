function hout = slice3cont(varargin)
%SLICE3CONT  Volumetric slice contour plot.
%   SLICE3CONT(X,Y,Z,V,Sx,Sy,Sz) draws contour slices along the x,y,z directions at
%   the points in the vectors Sx,Sy,Sz. The arrays X,Y,Z define the
%   coordinates for V and must be monotonic and 3-D plaid (as if
%   produced by MESHGRID).  The color at each point will be determined
%   by 3-D interpolation into the volume V.  V must be an M-by-N-by-P
%   volume array. 
%
%   SLICE3CONT(X,Y,Z,V,XI,YI,ZI) draws contour slices through the volume V along the
%   surface defined by the arrays XI,YI,ZI.
%
%   SLICE3CONT(V,Sx,Sy,Sz) or SLICE(V,XI,YI,ZI) assumes X=1:N, Y=1:M, Z=1:P. 
%
%   SLICE3CONT(...,'method') specifies the interpolation method to use.
%   'method' can be 'linear', 'cubic', or 'nearest'.  'linear' is the
%   default (see INTERP3).
%
%   H = SLICE3CONT(...) returns a vector of handles to SURFACE objects.
%
%   See also MESHGRID, INTERP3.

%   J.N. Little 1-23-92
%   Revised 4-27-93, 2-10-94
%   Revised 6-17-94 by Clay M. Thompson
%   Copyright (c) 1984-98 by The MathWorks, Inc.
%   $Revision: 5.16 $  $Date: 1997/11/21 23:46:47 $
%   Revised 27-12-01 Дроздов Алексей Юрьевич. E-mail: alexey_drozdov@mail.ru
%  "Научно-Технологический Институт Транскрипции Трансляции и Репликации".
%  г. Харьков. 8-0572-19-55-77
error(nargchk(4,9,nargin));

cax = newplot;
next = lower(get(cax,'NextPlot'));
hold_state = ishold;
axis_slice = 0; % Slice only along axes?
method = 'linear';
var_clabel='without_clabel';
nin = nargin;
for iii=1:2
   if isstr(varargin{nin}), % slice(...,'method')
      if ~strcmp(varargin{nin},'clabel') & ~strcmp(varargin{nin},'without_clabel')
         method = varargin{nin};
      else 
         var_clabel=varargin{nin};
         nin = nin - 1;
      end
   end
end


nv=[];
if nin==8
   nv= varargin{8};
   nin = nin - 1;
end

if nin == 4 | nin == 5 % slice(v,xi,yi,zi,<nx>)
    v = varargin{1}; varargin{1} = [];

    if nin == 5,
      warning(sprintf([ ...
        'Specifying the number of columns is no longer necessary.\n',...
        '         Use slice(v,xi,yi,zi) instead.']))
      if ndims(v)==2, % Reshape the volume.
        v = reshape(v,size(v,1)/varargin{5},varargin{5},size(v,2));
      end
    end

    if ndims(v)~=3, error('V must be a 3-D array.'); end
    [ny,nx,nz] = size(v);
    if min(size(varargin{2}))<=1 & min(size(varargin{3}))<=1 & ...
       min(size(varargin{4}))<=1,
        axis_slice = 1;
    end
    sx = varargin{2};
    sy = varargin{3};
    sz = varargin{4};
    [x,y,z] = meshgrid(1:nx,1:ny,1:nz);
elseif nin == 6,
    error('Wrong number of input arguments.');
elseif nin == 7 | nin == 8, % slice(x,y,z,v,xi,yi,zi,<nx>)
    v = varargin{4}; varargin{4} = [];

    if nin == 8,
      warning(sprintf([ ...
        'Specifying the number of columns is no longer necessary.\n',...
        '         Use slice(x,y,z,v,xi,yi,zi) instead.']))
      if ndims(v)==2, % Reshape the volume
        v = reshape(v,size(v,1)/varargin{8},varargin{8},size(v,2));
      end
    end

    if ndims(v)~=3, error('V must be a 3-D array.'); end
    if min(size(varargin{1}))==1 | min(size(varargin{2}))==1 | ...
       min(size(varargin{3}))==1,
        [x,y,z] = meshgrid(varargin{1:3});
    else
        x = varargin{1};
        y = varargin{2};
        z = varargin{3};
    end
    [ny,nx,nz] = size(v);

    if min(size(varargin{5}))<=1 & min(size(varargin{6}))<=1 & ...
       min(size(varargin{7}))<=1,
        axis_slice = 1;
    end
    sx = varargin{5};
    sy = varargin{6};
    sz = varargin{7};
 end
hout=[];
if axis_slice,
    h = [];
    [xi,yi,zi] = meshgrid(sx,y(:,1,1),z(1,1,:));
    vi = interp3(x,y,z,v,xi,yi,zi,method);
    for i = 1:length(sx)
        [cout,h,CS] =   contourf3slice_( ...
            reshape(xi(:,i,:),[ny nz]),reshape(yi(:,i,:),[ny nz]), ...
            reshape(zi(:,i,:),[ny nz]),reshape(vi(:,i,:),[ny nz]),nv);
         hout=[hout; h];
    end

    [xi,yi,zi] = meshgrid(x(1,:,1),sy,z(1,1,:));
    vi = interp3(x,y,z,v,xi,yi,zi,method);
    for i = 1:length(sy)
        [cout,h,CS] =  contourf3slice_( ...
            reshape(xi(i,:,:),[nx nz]),reshape(yi(i,:,:),[nx nz]),...
            reshape(zi(i,:,:),[nx nz]),reshape(vi(i,:,:),[nx nz]),nv);
         hout=[hout; h];
    end

    [xi,yi,zi] = meshgrid(x(1,:,1),y(:,1,1),sz);
    vi = interp3(x,y,z,v,xi,yi,zi,method);
    for i = 1:length(sz)
       [cout,h,CS] =  contourf3slice_(xi(:,:,i),yi(:,:,i),zi(:,:,i),vi(:,:,i),nv);
       hout=[hout; h];
    end
   
 else
    vi = interp3(x,y,z,v,sx,sy,sz,method);
    [cout,h,CS] = contourf3slice_(sx,sy,sz,vi,nv);
    hout=[hout; h];
 end
 
if ~isempty(h)  & strcmp(var_clabel,'clabel') & isequal(sz(1,1)*ones(size(sz)),sz)
   % Цифры уровней только, если сечение горизонтальное
   clabel(cout,h,nv);
end



% Use ISFINITE to make sure no NaNs or Infs get passed to CAXIS
u=v(isfinite(v)); u = u(:);
caxis([min(u) max(u)])


function [cout,H,CS] = contourf3slice_(varargin)
%contourf3slice_ Filled contour plot for volumetric slice contour plot.
%   contourf3slice_(...) is the same as CONTOUR(...) except that the contours
%   are filled.  Areas of the data at or above a given level are filled.
%   Areas below a level are either left blank or are filled by a lower
%   level.  NaN's in the data leave holes in the filled contour plot.
%
%   C = contourf3slice_(...) returns contour matrix C as described in CONTOURC
%   and used by CLABEL.
%
%   [C,H,CF] = contourf3slice_(...) also returns a column vector H of handles
%   to PATCH objects and the contour matrix CF for the filled areas.
%   The UserData property of each object contains the height value for each
%   contour.
%
%   Author: R. Pawlowicz (IOS)  rich@ios.bc.ca   12/14/94
%   Copyright (c) 1984-98 by The MathWorks, Inc.
%   $Revision: 1.23 $  $Date: 1998/04/09 13:17:29 $
%   Revised 27-12-01 Дроздов Алексей Юрьевич. E-mail: alexey_drozdov@mail.ru
%   "Научно-Технологический Институт Транскрипции Трансляции и Репликации".
%   г. Харьков. 8-0572-19-55-77

error(nargchk(1,6,nargin));

% Check for empty arguments.
for i = 1:nargin-2
  if isempty(varargin{i})
    error ('Invalid Argument - Input matrix is empty');
  end
end

% Trim off the last arg if it's a string (line_spec).
nin = nargin;
if isstr(varargin{end})
  [lin,col,mark,msg] = colstyle(varargin{end});
  if ~isempty(msg), error(msg); end
  nin = nin - 1;
else
  lin = '';
  col = '';
end

if (nin == 5),
   [xk,yk,zk,z,nv] = deal(varargin{1:5});
elseif (nin == 4),
   [xk,yk,zk,z] = deal(varargin{1:4});
   nv = [];
end

if isequal(zk(1,1)*ones(size(zk)),zk)
   x=xk;y=yk;xyk=zk(1,1);xydir='z';
else
   if isequal(xk(1,1)*ones(size(xk)),xk)
         x=zk;y=yk;z=z;xyk=xk(1,1);xydir='x';
   else
      if isequal(yk(1,1)*ones(size(yk)),yk)
            x=xk;y=zk;xyk=yk(1,1);xydir='y';
      else
         
         x=xk;y=yk;
         xydir='zz';
      end
   end
end

if (size(y,1)==1), y=y'; end;
if (size(x,2)==1), x=x'; end;
[mz,nz] = size(z);
  
lims = [min(x),max(x),min(y),max(y)];

i = find(isfinite(z));
if isempty(i),cout=[]; H=[];CS=[];disp('Ошибка: секущая плоскость содержит только неконечные значения');return; end;
minz = min(z(i));
maxz = max(z(i));

% Generate default contour levels if they aren't specified 
if length(nv) <= 1
  if isempty(nv)
    CS=contourc([minz maxz ; minz maxz]);
  else
    CS=contourc([minz maxz ; minz maxz],nv);
  end

  % Find the levels
  ii = 1;
  nv = minz; % Include minz so that the contours are totally filled 
  while (ii < size(CS,2)),
    nv=[nv CS(1,ii)];
    ii = ii + CS(2,ii) + 1;
  end
end

% Don't fill contours below the lowest level specified in nv.
% To fill all contours, specify a value of nv lower than the
% minimum of the surface. 
draw_min=0;
if any(nv <= minz),
  draw_min=1;
end

% Get the unique levels
nv = sort([minz nv(:)']);
zi = [1, find(diff(nv))+1];
nv = nv(zi);
if length(nv)==1,cout=[];H=[];CS=[];disp('ошибка нет вариации в данных ');return;end

% Surround the matrix by a very low region to get closed contours, and
% replace any NaN with low numbers as well.

zz=[ repmat(NaN,1,nz+2) ; repmat(NaN,mz,1) z repmat(NaN,mz,1) ; repmat(NaN,1,nz+2)];
kk=find(isnan(zz(:)));
zz(kk)=minz-1e4*(maxz-minz)+zeros(size(kk));

xx = [2*x(:,1)-x(:,2), x, 2*x(:,nz)-x(:,nz-1)];
yy = [2*y(1,:)-y(2,:); y; 2*y(mz,:)-y(mz-1,:)];

if (min(size(yy))==1),
  [CS,msg]=contours(xx,yy,zz,nv);
else
  [CS,msg]=contours(xx([ 1 1:mz mz],:),yy(:,[1 1:nz nz]),zz,nv);
end;
if ~isempty(msg), error(msg); end

% Find the indices of the curves in the c matrix, and get the
% area of closed curves in order to draw patches correctly. 
ii = 1;
ncurves = 0;
I = [];
Area=[];
while (ii < size(CS,2)),
  nl=CS(2,ii);
  ncurves = ncurves + 1;
  I(ncurves) = ii;
  xp=CS(1,ii+(1:nl));  % First patch
  yp=CS(2,ii+(1:nl));
  Area(ncurves)=sum( diff(xp).*(yp(1:nl-1)+yp(2:nl))/2 );
  ii = ii + nl + 1;
end


% Plot patches in order of decreasing size. This makes sure that
% all the levels get drawn, not matter if we are going up a hill or
% down into a hole. When going down we shift levels though, you can
% tell whether we are going up or down by checking the sign of the
% area (since curves are oriented so that the high side is always
% the same side). Lowest curve is largest and encloses higher data
% always.

H=[];
[FA,IA]=sort(-abs(Area));
if ~isstr(get(gca,'color')),
  bg = get(gca,'color');
else
  bg = get(gcf,'color');
end
if isempty(col)
  edgec = get(gcf,'defaultsurfaceedgecolor');
else
  edgec = col;
end
if isempty(lin)
  edgestyle = get(gcf,'defaultpatchlinestyle');
else
  edgestyle = lin;
end

% Tolerance for edge comparison
xtol = 0.1*(lims(2)-lims(1))/size(z,2);
ytol = 0.1*(lims(4)-lims(3))/size(z,1);
zzk=[zk(:,1) zk zk(:,end)];
zzkk=[zzk(1,:); zzk; zzk(end,:)];

%func='patchm';
%func='fill3m';
%func='patch';
func='fill3';

if nargout>0
  cout = [];
end
for jj=IA,
  nl=CS(2,I(jj));
  lev=CS(1,I(jj));
  if (lev ~= minz | draw_min ),
    xp=CS(1,I(jj)+(1:nl));  
    yp=CS(2,I(jj)+(1:nl)); 
    if (sign(Area(jj)) ~=sign(Area(IA(1))) ),
      kk=find(nv==lev);
      if (kk>1+sum(nv<=minz)*(~draw_min)), 
        lev=nv(kk-1);
      else 
        lev=NaN;         % missing data section
      end
   end
   switch xydir
   case 'z'
      xyp=xyk*ones(size(xp));
      if (isfinite(lev)),
         H=[H;feval(func,xp,yp,xyp,lev,'facecolor','flat','edgecolor',edgec, ...
              'linestyle',edgestyle,'userdata',lev)];
      else
         H=[H;feval(func,xp,yp,xyp,lev,'facecolor',bg,'edgecolor',edgec, ...
              'linestyle',edgestyle,'userdata',CS(1,I(jj)))];
      end
   case 'x'
      xyp=xyk*ones(size(xp));
      if (isfinite(lev)),
         H=[H;feval(func,xyp,yp,xp,lev,'facecolor','flat','edgecolor',edgec, ...
               'linestyle',edgestyle,'userdata',lev)];
      else
         H=[H;feval(func,xyp,yp,xp,lev,'facecolor',bg,'edgecolor',edgec, ...
              'linestyle',edgestyle,'userdata',CS(1,I(jj)))];
      end
   case 'y'
      xyp=xyk*ones(size(xp));
      if (isfinite(lev)),
         H=[H;feval(func,xp,xyp,yp,lev,'facecolor','flat','edgecolor',edgec, ...
               'linestyle',edgestyle,'userdata',lev)];
     
      else
         H=[H;feval(func,xp,xyp,yp,lev,'facecolor',bg,'edgecolor',edgec, ...
              'linestyle',edgestyle,'userdata',CS(1,I(jj)))];
      end
   case 'zz'
      clear zp;
      for q=1:length(xp)
         zp(q)=interp2(xx([ 1 1:mz mz],:),yy(:,[1 1:nz nz]),zzkk,xp(q),yp(q));
      end
      
      if (isfinite(lev)),
         H=[H;feval(func,xp,yp,zp,lev,'facecolor','flat','edgecolor',edgec, ...
              'linestyle',edgestyle,'userdata',lev)];
      else
         H=[H;feval(func,xp,yp,zp,lev,'facecolor',bg,'edgecolor',edgec, ...
              'linestyle',edgestyle,'userdata',CS(1,I(jj)))];
      end
  end
    if nargout>0
      xp(abs(xp - lims(1)) < xtol | abs(xp - lims(2)) < xtol) = NaN;
      yp(abs(yp - lims(3)) < ytol | abs(yp - lims(4)) < ytol) = NaN;
      cout = [cout,[lev xp;nl yp]];
    end
  end
end

numPatches = length(H);
if numPatches>1
   for i=1:numPatches
      if ishandle(H(i)),
         set(H(i), 'faceoffsetfactor', 0, 'faceoffsetbias', (1e-3)+(numPatches-i)/(numPatches-1)/30); 
      end
      
  end
end
%hout=H;