function viz3d(action,flag,ud)
%
% Демонстрационная программа визуализации объёма, заданного 
% в виде трёхмерной матрицы чисел (в данной версии числа задают 
% яйцеобразное распределение некоторого параметра в пространстве),
% посредством построения передвигаемых ортогональных 
% разрезов и изоповерхности с возможностью увеличения
% масштаба, и скрытия ненужных элементов. Цвет соответствует значению
% распределённого параметра в данной точка пространства

%
%           Дроздов А.Ю. 18.12.2001.
% Дроздов Алексей Юрьевич. E-mail: alexey_drozdov@mail.ru
% "Научно-Технологический Институт Транскрипции Трансляции и Репликации".
% г. Харьков. 8-0572-19-55-77
%

if nargin < 1 | isempty(action)
    action = 'start';
end
%On recursive calls get all necessary handles and data.
if ~strcmp(action,'start')   
   childList = allchild(0);
   distfig = childList(find(childList == gcbf));
   ud = get(distfig,'Userdata');
   if isempty(ud) & strcmp(action,'motion')
      return
   end

   switch action,
      case 'setpfield',
         switch flag
             case 1, ud = setpfield(1,ud);
             case 2, ud = setpfield(2,ud);
             case 3, ud = setpfield(3,ud);
             case 4, ud = setpfield(4,ud);
         end
      case 'setpslider',
         switch flag
             case 1, ud = setpslider(1,ud);
             case 2, ud = setpslider(2,ud);
             case 3, ud = setpslider(3,ud);
             case 4, ud = setpslider(4,ud);
         end
      case 'setphi',
         switch flag
            case 1, ud = setphi(1,ud);
            case 2, ud = setphi(2,ud);
            case 3, ud = setphi(3,ud);
            case 4, ud = setphi(4,ud);
         end
      case 'setplo',
         switch flag
            case 1, ud = setplo(1,ud);
            case 2, ud = setplo(2,ud);
            case 3, ud = setplo(3,ud);
            case 4, ud = setplo(4,ud);
         end
      case 'viz',
         switch flag
            case 1, ud=viz(1,ud);
            case 2, ud=viz(2,ud);
            case 3, ud=viz(3,ud);
            case 4, ud=viz(4,ud);
         end
      case 'unviz',
         switch flag
            case 1, ud=unviz(1,ud);
            case 2, ud=unviz(2,ud);
            case 3, ud=unviz(3,ud);
            case 4, ud=unviz(4,ud);
         end
      case 'changemode',
            ud=changemode(ud);
      case 'rangeaxes'
         switch flag
            case 1, ud.ra=1;
            case 2, ud.ra=2;
            end
            ud=newrange(ud);
      case 'perspective'
         switch flag
         case 'on', 
            set(ud.axes1,'Projection','perspective');
            set(ud.menperspon,'Visible','off');
            set(ud.menperspoff,'Visible','on');
         case 'off',
            set(ud.axes1,'Projection','orthographic');
            set(ud.menperspoff,'Visible','off');
            set(ud.menperspon,'Visible','on');
         end
      case 'changecolorfon', 
         ud=changecolorfon(ud);
      case 'changecolormap', 
         ud=changecolormap(ud);
      end
end % if ~strcmp(action,'start') 

% Initialize all GUI objects. Plot slise with sliders for parameters.
if strcmp(action,'start'),
   % Set positions of graphic objects
   axisp   = [.23 .30 .75 .45];%[.23 .35 .75 .55];
   % Create cell array of positions for parameter controls.
   pos{1,1} = [.18 .08 .095 .05];
   pos{2,1} = pos{1,1} + [.15 .06 0 0];
   pos{3,1} = pos{2,1} + [0 -0.13 0 0];
   pos{4,1} = pos{1,1} + [.11 -0.07 -0.07 0.13];
   pos{5,1} = pos{1,1} + [0 0.05 0 0];   
   pos{6,1} = pos{2,1} + [0 -0.075 0 0];
   pos{7,1} = pos{1,1} + [0 -0.068 0 0];

   pos{1,2} = [.46 .08 .095 .05];
   pos{2,2} = pos{1,2} + [.15 .06 0 0];
   pos{3,2} = pos{2,2} + [0 -0.13 0 0];
   pos{4,2} = pos{1,2} + [.11 -0.07 -0.07 0.13];
   pos{5,2} = pos{1,2} + [0 0.05 0 0];
   pos{6,2} = pos{2,2} + [0 -0.075 0 0];
   pos{7,2} = pos{1,2} + [0 -0.068 0 0];
   
   pos{1,3} = [.74 .08 .095 .05];
   pos{2,3} = pos{1,3} + [.15 .06 0 0];
   pos{3,3} = pos{2,3} + [0 -0.13 0 0];
   pos{4,3} = pos{1,3} + [.11 -0.07 -0.07 0.13];
   pos{5,3} = pos{1,3} + [0 0.05 0 0];
   pos{6,3} = pos{2,3} + [0 -0.075 0 0];
   pos{7,3} = pos{1,3} + [0 -0.068 0 0];
   
   pos{1,4} = [.01 .28 .095 .05];
   pos{2,4} = pos{1,4} + [.15 .06 0 0];
   pos{3,4} = pos{2,4} + [0 -0.13 0 0];
   pos{4,4} = pos{1,4} + [.11 -0.07 -0.07 0.13];
   pos{5,4} = pos{1,4} + [0 0.05 0 0];
   pos{6,4} = pos{2,4} + [0 -0.075 0 0];
   pos{7,4} = pos{1,4} + [0 -0.068 0 0];
   
   posui1=pos{5,4}+[0 0.62 0.25 -0.01];
   posui2=pos{5,4}+[0 0.62 0.46 -0.01];
   posui3=pos{5,4}+[0.23 0.57 0.135 -0.01];

ud.maxv=max(max(max(ud.V)));
ud.minv=min(min(min(ud.V)));
% Определение пределов изменения координат
xmax=max(ud.x);xmin=min(ud.x);
ymax=max(ud.y);ymin=min(ud.y);
zmax=max(ud.z);zmin=min(ud.z);
ud.minmax.xyz={[xmin xmax] [ymin ymax] [zmin zmax] [ud.minv ud.maxv]};

% Граничные номера элементов трёхмерных матриц data
ud.yborder=[1 length(ud.y)];
ud.xborder=[1 length(ud.x)];
ud.zborder=[1 length(ud.z)];


% Параметры для ранжировки осей графика
ud.ra=2;
% Установление текущей ранжировки осех графика:
switch ud.ra
%      Вариант 1: масштаб по всем осям одинаков:
case 1
ud.kmax=max([ud.x(ud.xborder(2)) ud.y(ud.yborder(2)) ud.z(ud.zborder(2))]);
ud.kmin=min([ud.x(ud.xborder(1)) ud.y(ud.yborder(1)) ud.z(ud.zborder(1))]);

ud.xrange = [ud.kmin ud.kmax];
ud.yrange = [ud.kmin ud.kmax];
ud.zrange = [ud.kmin ud.kmax];
%      Вариант 2: масштаб по всем осям неодинаков:
case 2
ud.xrange = [ud.x(ud.xborder(1)) ud.x(ud.xborder(2))];
ud.yrange = [ud.y(ud.yborder(1)) ud.y(ud.yborder(2))];
ud.zrange = [ud.z(ud.zborder(1)) ud.z(ud.zborder(2))];
end

paramtext  = str2mat('X-разрез','Y-разрез','Z-разрез','Изоповерх.');
paramtext2  = str2mat('Xграницы','Yграницы','Zграницы','Vграницы');
% Переменная, определяющая - показать или скрыть график
ud.flunviz(1)=1;
ud.flunviz(2)=1;
ud.flunviz(3)=1;
ud.flunviz(4)=1;

% Координаты изображаемых разрезов:
ud.newxyzv={[0.5*(ud.x(1)+ud.x(end))]....
      [0.5*(ud.y(1)+ud.y(end))]....
      [0.5*(ud.z(1)+ud.z(end))]....
      [(ud.maxv+ud.minv)/2]};
%   Create slise Plot
ud.slise_fig = figure('Tag','slisefig');

set(ud.slise_fig,'Units','Normalized','Backingstore','off','InvertHardcopy','on',...
    'PaperPositionMode','auto');

figcolor=[0.55 0.5 .8];
set(ud.slise_fig,'Color',figcolor,'Colormap',hsv);
ud.axiscolor = 1-figcolor;  
ud.cl='hsv';ud.c=colormap;
ud.axes1 = axes;
set(ud.axes1,'Color',ud.axiscolor,'NextPlot','add','DrawMode','fast',...
   'Position',axisp,'XLim',ud.xrange,'YLim',ud.yrange,'ZLim',ud.zrange,...
   'Box','off','View',[60 20],'XDir','reverse'); %,'Scale',);
xlabel('X');ylabel('Y');zlabel('Z');%camproj perspective;orthographic
ud.per=0;set(ud.axes1,'Projection','orthographic');



   for idx = 1:4
      nstr = int2str(idx);
      ud.pfhndl(idx)=uicontrol('Style','edit','Units','normalized','Position',pos{1,idx},...
          'String',num2str(ud.newxyzv{idx}),'BackgroundColor','white',...
          'CallBack',['viz3d(''setpfield'',',nstr,')']);
         
       ud.hihndl(idx)=uicontrol('Style','edit','Units','normalized','Position',pos{2,idx},...
         'String',num2str(ud.minmax.xyz{idx}(2)),'BackgroundColor','white',...
         'CallBack',['viz3d(''setphi'',',nstr,')']);
         
       ud.lohndl(idx)=uicontrol('Style','edit','Units','normalized','Position',pos{3,idx},...
         'String',num2str(ud.minmax.xyz{idx}(1)),'BackgroundColor','white',... 
         'CallBack',['viz3d(''setplo'',',nstr,')']);

       ud.pslider(idx)=uicontrol('Style','slider','Units','normalized','Position',pos{4,idx},...
         'Value',ud.newxyzv{idx},'Max',ud.minmax.xyz{idx}(2),...
         'Min',ud.minmax.xyz{idx}(1),'Callback',['viz3d(''setpslider'',',nstr,')']);
            
       ud.ptext(idx) =uicontrol('Style','text','Units','normalized','Position',pos{5,idx},...
         'ForegroundColor','k','BackgroundColor',figcolor,'String',paramtext(idx,:)); 
       
       ud.ptext2(idx) =uicontrol('Style','text','Units','normalized','Position',pos{6,idx},...
         'ForegroundColor','k','BackgroundColor',figcolor,'String',paramtext2(idx,:)); 
      
       ud.viz(idx)=uicontrol('Style','Pushbutton','Units','normalized','Position',pos{7,idx},...
       'String','Показать','Visible','off','Callback',['viz3d(''viz'',',nstr,')']);
    
       ud.unviz(idx)=uicontrol('Style','Pushbutton','Units','normalized','Position',pos{7,idx},...
       'String','Скрыть','Callback',['viz3d(''unviz'',',nstr,')']);
   end   %for idx = 1:3   
   
   ud.menrange1=uicontrol('Style','Pushbutton','Units','normalized','Position',posui1,...
      'String','Сделать масштаб осей одинаковым','Callback',['viz3d(''rangeaxes'',','1',')']);
   ud.menrange2=uicontrol('Style','Pushbutton','Units','normalized','Position',posui2,...
      'String','Сделать масштаб осей в соответствии с границами объёма','Visible','off','Callback',['viz3d(''rangeaxes'',','2',')']);
   
   ud.menperspon=uicontrol('Style','Pushbutton','Units','normalized','Position',posui3,...
      'String','Включить перспективу','Callback',['viz3d(''perspective'',''on'')']);
   ud.menperspoff=uicontrol('Style','Pushbutton','Units','normalized','Position',posui3,...
      'String','Выключить перспективу','Visible','off','Callback',['viz3d(''perspective'',''off'')']);
   
   ud.colorfon=uicontrol('Style','Popup','String',...
      'Защитный|Красный|Оранжевый|Жёлтый|Зелёный|Аквамариновый|Голубой|Синий|Фиолетовый|Коричневый|Белый|Серый|Чёрный',...
      'Value',1,'Units','normalized',....
      'Position',[.84 .93 .155 .06],'CallBack','viz3d(''changecolorfon'')');
   ud.ptextfon =uicontrol('Style','text','Units','normalized',...
      'Position',[.78 .935 .06 .06],...
      'ForegroundColor','k','BackgroundColor',figcolor,'String','Цвет фона:'); 
   
   ud.colormap=uicontrol('Style','Popup','String',...
      'hsv|hot|gray|bone|copper|pink|white|flag|lines|colorcube|vga|jet|prism|cool|autumn|spring|winter|summer|"default"',....
      'Value',1,'Units','normalized',....
      'Position',[.665 .93 .115 .06],'CallBack','viz3d(''changecolormap'')');
   ud.ptextmap =uicontrol('Style','text','Units','normalized',...
      'Position',[.605 .935 .055 .06],...
      'ForegroundColor','k','BackgroundColor',figcolor,'String','Пали- тра:'); 
   
   ud.mode=uicontrol('Style','Popup','String','slice|fill3|surfl|fill3+surfl|drill slits',....
      'Value',1,'Units','normalized','Position',[0.095 .9 .125 .035],'CallBack','viz3d(''changemode'')');
   ud.textmode =uicontrol('Style','text','Units','normalized',...
      'Position',[0.01 .89 .08 .04],...
      'ForegroundColor','k','BackgroundColor',figcolor,'String','РЕЖИМ:'); 
   
   ud.square=uicontrol('Style','Popup','String','0|1|2|3|4|1+2|1+3|1+4|2+3|2+4|3+4|1+2+3|1+2+4|1+3+4|2+3+4|1+2+3+4',....
      'Value',1,'Units','normalized','Position',[0.095    0.835    0.12    0.035],'CallBack','viz3d(''changemode'')');
   ud.textsquare =uicontrol('Style','text','Units','normalized',...
      'Position',[0.01    0.82    0.08    0.04],...
      'ForegroundColor','k','BackgroundColor',figcolor,'String','Квадрат:'); 

   close_button = uicontrol('Style','Pushbutton','Units','normalized',...
      'Position',[0.01 0.01 0.13 0.05],'Callback','close','String','Закрыть');
   
   
ud = updateslise(ud)
end % if strcmp(action,'start')


% End of initialization.
set(ud.slise_fig,'UserData',ud);
% END OF disttool MAIN FUNCTION.

% BEGIN HELPER  FUNCTIONS.
function ud = newborder(ud);
% Номера граничных координат
ud.xborder(1)=min(find(abs((ud.x-str2num(get(ud.lohndl(1),'String')) )/ud.dx)<1));
ud.xborder(2)=max(find(abs((ud.x-str2num(get(ud.hihndl(1),'String')) )/ud.dx)<1));

ud.yborder(1)=min(find(abs((ud.y-str2num(get(ud.lohndl(2),'String')) )/ud.dy)<1));
ud.yborder(2)=max(find(abs((ud.y-str2num(get(ud.hihndl(2),'String')) )/ud.dy)<1));

ud.zborder(1)=min(find(abs((ud.z-str2num(get(ud.lohndl(3),'String')) )/ud.dz)<1));
ud.zborder(2)=max(find(abs((ud.z-str2num(get(ud.hihndl(3),'String')) )/ud.dz)<1));
%-------------------------------------------
function ud = newrange(ud);
% Установление текущей ранжировки осех графика:
switch ud.ra
%      Вариант 1: масштаб по всем осям одинаков:
case 1
ud.kmax=max([ud.x(ud.xborder(2)) ud.y(ud.yborder(2)) ud.z(ud.zborder(2))]);
ud.kmin=min([ud.x(ud.xborder(1)) ud.y(ud.yborder(1)) ud.z(ud.zborder(1))]);

ud.xrange = [ud.kmin ud.kmax];
ud.yrange = [ud.kmin ud.kmax];
ud.zrange = [ud.kmin ud.kmax];

set(ud.menrange1,'Visible','off');
set(ud.menrange2,'Visible','on');
case 2
%      Вариант 2: масштаб по всем осям неодинаков: 
ud.xrange = [ud.x(ud.xborder(1)) ud.x(ud.xborder(2))];
ud.yrange = [ud.y(ud.yborder(1)) ud.y(ud.yborder(2))];
ud.zrange = [ud.z(ud.zborder(1)) ud.z(ud.zborder(2))];

set(ud.menrange2,'Visible','off');
set(ud.menrange1,'Visible','on');
end;
set(ud.axes1,'XLim',ud.xrange,'YLim',ud.yrange,'ZLim',ud.zrange);

% -----------------------------------------
function ud = updateslise(ud);
% Установление текущих параметров разреза и изоповерхности
if ud.flunviz(1)==1; ud.newxyzv{1}=str2num(get(ud.pfhndl(1),'String'));elseif ud.flunviz(1)==0; ud.newxyzv{1}=[];end;
if ud.flunviz(2)==1; ud.newxyzv{2}=str2double(get(ud.pfhndl(2),'String'));elseif ud.flunviz(2)==0; ud.newxyzv{2}=[];end;
if ud.flunviz(3)==1; ud.newxyzv{3}=str2double(get(ud.pfhndl(3),'String'));elseif ud.flunviz(3)==0; ud.newxyzv{3}=[];end;
if ud.flunviz(4)==1; ud.newxyzv{4}=str2num(get(ud.pfhndl(4),'String'));elseif ud.flunviz(4)==0; ud.newxyzv{4}=[];end;

ud.dslise = slice(ud.X(ud.yborder(1):ud.yborder(2),ud.xborder(1):ud.xborder(2),ud.zborder(1):ud.zborder(2)),...
   ud.Y(ud.yborder(1):ud.yborder(2),ud.xborder(1):ud.xborder(2),ud.zborder(1):ud.zborder(2)),...
   ud.Z(ud.yborder(1):ud.yborder(2),ud.xborder(1):ud.xborder(2),ud.zborder(1):ud.zborder(2)),...
   ud.V(ud.yborder(1):ud.yborder(2),ud.xborder(1):ud.xborder(2),ud.zborder(1):ud.zborder(2)),...
   [ud.newxyzv{1}],[ud.newxyzv{2}],[ud.newxyzv{3}]);
shading interp;
%set(gcf, 'Colormap', ud.c); if isstr(ud.c), ud.c=colormap; end;

if ud.flunviz(2)==1 & ud.flunviz(3)==1
ud.linex=line(ud.xrange,[ud.newxyzv{2} ud.newxyzv{2}],...
   [ud.newxyzv{3} ud.newxyzv{3}]);
end
if ud.flunviz(1)==1 & ud.flunviz(3)==1
ud.liney=line([ud.newxyzv{1} ud.newxyzv{1}],ud.yrange,...
   [ud.newxyzv{3} ud.newxyzv{3}]);
end
if ud.flunviz(1)==1 & ud.flunviz(2)==1
ud.linez=line([ud.newxyzv{1} ud.newxyzv{1}],...
   [ud.newxyzv{2} ud.newxyzv{2}],ud.zrange);
end

if ud.flunviz(4)==1;
% Вставка изоповерхности
ud.p = patch(isosurface(ud.X(ud.yborder(1):ud.yborder(2),ud.xborder(1):ud.xborder(2),ud.zborder(1):ud.zborder(2)),...
   ud.Y(ud.yborder(1):ud.yborder(2),ud.xborder(1):ud.xborder(2),ud.zborder(1):ud.zborder(2)),...
   ud.Z(ud.yborder(1):ud.yborder(2),ud.xborder(1):ud.xborder(2),ud.zborder(1):ud.zborder(2)),...
   ud.V(ud.yborder(1):ud.yborder(2),ud.xborder(1):ud.xborder(2),ud.zborder(1):ud.zborder(2)),...
   ud.newxyzv{4}));
 
isonormals(ud.X(ud.yborder(1):ud.yborder(2),ud.xborder(1):ud.xborder(2),ud.zborder(1):ud.zborder(2)),...
   ud.Y(ud.yborder(1):ud.yborder(2),ud.xborder(1):ud.xborder(2),ud.zborder(1):ud.zborder(2)),...
   ud.Z(ud.yborder(1):ud.yborder(2),ud.xborder(1):ud.xborder(2),ud.zborder(1):ud.zborder(2)),...
   ud.V(ud.yborder(1):ud.yborder(2),ud.xborder(1):ud.xborder(2),ud.zborder(1):ud.zborder(2)),...
   ud.p)
colorizosurf=ud.c(fix(1+63*(ud.newxyzv{4}-ud.minv)/(ud.maxv-ud.minv)),:);
set(ud.p, 'FaceColor', colorizosurf, 'EdgeColor', 'none');
end;
% Create or set position of a light
%   CAMLIGHT HEADLIGHT creates a light in the current axes at the
%                         camera position of the current axes. 
%   CAMLIGHT RIGHT     creates a light right and up from camera.
%   CAMLIGHT LEFT      creates a light left and up from camera.
%   CAMLIGHT           same as CAMLIGHT RIGHT.
%   CAMLIGHT(AZ, EL)   creates a light at AZ, EL from camera.
%
%   CAMLIGHT(..., style) set the style of the light.
%                 Style can be 'local' (default) or 'infinite'.
%                
%   CAMLIGHT(H, ...)   places specified light at specified position.
%   H = CAMLIGHT(...)  returns light handle.
%   See also LIGHT, LIGHTANGLE, LIGHTING, MATERIAL, CAMORBIT.

camlight(0,1);

% LIGHTING Lighting mode.
%    LIGHTING controls the lighting of SURFACE and PATCH objects.
%    SURFACE and PATCH objects are created by the functions SURF, MESH,
%    PCOLOR, FILL, and FILL3. 
% 
%    LIGHTING FLAT sets the lighting of the current graph to flat.
%    LIGHTING GOURAUD sets the lighting to gouraud.
%    LIGHTING PHONG sets the lighting to phong.
%    LIGHTING NONE turns off lighting.
 
lighting phong;

% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-----------------------------
function ud = updatesurfl(square,ud);

if square ~=0

if ud.flunviz(1)==1; 
   bx=max(find(abs((ud.x-str2num(get(ud.pfhndl(1),'String')) )/ud.dx)<1));
elseif ud.flunviz(1)==0;
   bx=ud.xborder(2);
end;

if ud.flunviz(2)==1;
by=min(find(abs((ud.y-str2num(get(ud.pfhndl(2),'String')) )/ud.dy)<1));
elseif ud.flunviz(2)==0; by1=ud.xborder(2);
end;

switch square
case 1
      for jj=1:ud.nstratum
   H=surfl(ud.x(ud.xborder(1):bx),ud.y(ud.yborder(1):by),...
      ud.Zs{jj}(ud.yborder(1):by,ud.xborder(1):bx));HH{jj}=H;end
case 2
      for jj=1:ud.nstratum
   H=surfl(ud.x(ud.xborder(1):bx),ud.y(by:ud.yborder(2)),...
      ud.Zs{jj}(by:ud.yborder(2),ud.xborder(1):bx));HH{jj}=H;end
case 3
         for jj=1:ud.nstratum
   H=surfl(ud.x(bx:ud.xborder(2)),ud.y(ud.yborder(1):by),...
      ud.Zs{jj}(ud.yborder(1):by,bx:ud.xborder(2)));HH{jj}=H;end
case 4
         for jj=1:ud.nstratum
   H=surfl(ud.x(bx:ud.xborder(2)),ud.y(by:ud.yborder(2)),...
      ud.Zs{jj}(by:ud.yborder(2),bx:ud.xborder(2)));HH{jj}=H;end
end   

c=get(H,'CData');
ud.light=.3;
for jj=1:ud.nstratum
   set(HH{jj},'CData',c*jj*ud.light);set(HH{jj},'FaceColor','interp','EdgeColor','none');
end
end
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-----------------------------
function ud = updatefill3(ud);

for zi=1:ud.nstratum,  
   [yi,xi] = find(isfinite(ud.Zs{zi}));Yi{zi}=yi;
   Xi{zi}=xi;
end
clear yi xi;
xn=max(find(abs((ud.x-str2num(get(ud.pfhndl(1),'String')) )/ud.dx)<1));
yn=min(find(abs((ud.y-str2num(get(ud.pfhndl(2),'String')) )/ud.dy)<1));

for zi=1:ud.nstratum
   fy=find((Yi{zi}==yn));
for q=1:length(fy)
   zz{zi}(q)=ud.Zs{zi}(Yi{zi}(fy(q)),Xi{zi}(fy(q)));
   xx{zi}(q)=ud.x(Xi{zi}(fy(q)));
   yy{zi}(q)=ud.y(Yi{zi}(fy(q)));
end
end

for zi=1:ud.nstratum-1
colorfill=ud.c(fix(1+63*(zi-0)/(ud.nstratum-0)),:);
fily=fill3([xx{zi} fliplr(xx{zi+1})],[yy{zi} fliplr(yy{zi+1})],[zz{zi} fliplr(zz{zi+1})],colorfill,'EdgeColor','none');
end
clear xx yy zz;
for zi=1:ud.nstratum
   fx=find((Xi{zi}==xn));
   for q=1:length(fx)
   zz{zi}(q)=ud.Zs{zi}(Yi{zi}(fx(q)),Xi{zi}(fx(q)));
   xx{zi}(q)=ud.x(Xi{zi}(fx(q)));
   yy{zi}(q)=ud.y(Yi{zi}(fx(q)));
end
end

for zi=1:ud.nstratum-1
colorfill=ud.c(fix(1+63*(zi-0)/(ud.nstratum-0)),:);
filx=fill3([xx{zi} fliplr(xx{zi+1})],[yy{zi} fliplr(yy{zi+1})],[zz{zi} fliplr(zz{zi+1})],colorfill,'EdgeColor','none');
end
camlight;lighting phong;


% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-----------------------------
function ud = updatefill3_(ud);

for zi=1:ud.nstratum,  
   [yi,xi] = find(isfinite(ud.Zs{zi}));Yi{zi}=yi;
   Xi{zi}=xi;
end
clear yi xi;
xn=max(find(abs((ud.x-str2num(get(ud.pfhndl(1),'String')) )/ud.dx)<1));
yn=min(find(abs((ud.y-str2num(get(ud.pfhndl(2),'String')) )/ud.dy)<1));
% -----------------------
ud.line=line([ud.x(xn) ud.x(xn)],...
   [ud.y(yn) ud.y(yn)],[ud.Zs{1}(yn,xn) ud.Zs{ud.nstratum}(yn,xn)],'Color',[0 0 0]);
% -----------------------
for zi=1:ud.nstratum
   fy=find((Yi{zi}==yn)&(Xi{zi}>=xn));
for q=1:length(fy)
   zz{zi}(q)=ud.Zs{zi}(Yi{zi}(fy(q)),Xi{zi}(fy(q)));
   xx{zi}(q)=ud.x(Xi{zi}(fy(q)));
   yy{zi}(q)=ud.y(Yi{zi}(fy(q)));
end
end
for zi=1:ud.nstratum-1
colorfill=ud.c(fix(1+63*(zi-0)/(ud.nstratum-0)),:);
fily=fill3([xx{zi} fliplr(xx{zi+1})],[yy{zi} fliplr(yy{zi+1})],[zz{zi} fliplr(zz{zi+1})],colorfill,'EdgeColor','none');
end
clear xx yy zz ;
% -----------------------
clear xx yy zz;
for zi=1:ud.nstratum
   fx=find((Xi{zi}==xn)&(Yi{zi}>=yn));
   for q=1:length(fx)
   zz{zi}(q)=ud.Zs{zi}(Yi{zi}(fx(q)),Xi{zi}(fx(q)));
   xx{zi}(q)=ud.x(Xi{zi}(fx(q)));
   yy{zi}(q)=ud.y(Yi{zi}(fx(q)));
end
end

for zi=1:ud.nstratum-1
colorfill=ud.c(fix(1+63*(zi-0)/(ud.nstratum-0)),:);
filx=fill3([xx{zi} fliplr(xx{zi+1})],[yy{zi} fliplr(yy{zi+1})],[zz{zi} fliplr(zz{zi+1})],colorfill,'EdgeColor','none');
end
clear xx yy zz fi;
% -----------------------
for zi=1:ud.nstratum
   fy=find((Yi{zi}==yn)&(Xi{zi}<=xn));
for q=1:length(fy)
   zz{zi}(q)=ud.Zs{zi}(Yi{zi}(fy(q)),Xi{zi}(fy(q)));
   xx{zi}(q)=ud.x(Xi{zi}(fy(q)));
   yy{zi}(q)=ud.y(Yi{zi}(fy(q)));
end
end
for zi=1:ud.nstratum-1
colorfill=ud.c(fix(1+63*(zi-0)/(ud.nstratum-0)),:);
fily=fill3([xx{zi} fliplr(xx{zi+1})],[yy{zi} fliplr(yy{zi+1})],[zz{zi} fliplr(zz{zi+1})],colorfill);
end
clear xx yy zz fi;
% -----------------------
clear xx yy zz;
for zi=1:ud.nstratum
   fx=find((Xi{zi}==xn)&(Yi{zi}<=yn));
   for q=1:length(fx)
   zz{zi}(q)=ud.Zs{zi}(Yi{zi}(fx(q)),Xi{zi}(fx(q)));
   xx{zi}(q)=ud.x(Xi{zi}(fx(q)));
   yy{zi}(q)=ud.y(Yi{zi}(fx(q)));
end
end

for zi=1:ud.nstratum-1
colorfill=ud.c(fix(1+63*(zi-0)/(ud.nstratum-0)),:);
filx=fill3([xx{zi} fliplr(xx{zi+1})],[yy{zi} fliplr(yy{zi+1})],[zz{zi} fliplr(zz{zi+1})],colorfill);
end

clear xx yy zz fi;
% #######################################################
function   ud = updatefill3surfl(ud);
ud = updatefill3(ud);
squarevalue = get(ud.square,'Value');
   switch squarevalue
   case 1,  square=0;ud=updatesurfl(square,ud);
   case 2,  square=1;ud=updatesurfl(square,ud);
   case 3,  square=2;ud=updatesurfl(square,ud);
   case 4,  square=3;ud=updatesurfl(square,ud);
   case 5,  square=4;ud=updatesurfl(square,ud);
   case 6, square=1;ud=updatesurfl(square,ud);square=2;ud=updatesurfl(square,ud);
   case 7, square=1;ud=updatesurfl(square,ud);square=3;ud=updatesurfl(square,ud);
   case 8, square=1;ud=updatesurfl(square,ud);square=4;ud=updatesurfl(square,ud);
   case 9, square=2;ud=updatesurfl(square,ud);square=3;ud=updatesurfl(square,ud);
   case 10,square=2;ud=updatesurfl(square,ud);square=4;ud=updatesurfl(square,ud);
   case 11,square=3;ud=updatesurfl(square,ud);square=4;ud=updatesurfl(square,ud);
   case 12, square=1;ud=updatesurfl(square,ud);square=2;ud=updatesurfl(square,ud);square=3;ud=updatesurfl(square,ud);
   case 13, square=1;ud=updatesurfl(square,ud);square=2;ud=updatesurfl(square,ud);square=4;ud=updatesurfl(square,ud);
   case 14, square=1;ud=updatesurfl(square,ud);square=3;ud=updatesurfl(square,ud);square=4;ud=updatesurfl(square,ud);
   case 15, square=2;ud=updatesurfl(square,ud);square=3;ud=updatesurfl(square,ud);square=4;ud=updatesurfl(square,ud);
   case 16,square=1;ud=updatesurfl(square,ud);square=2;ud=updatesurfl(square,ud);square=3;ud=updatesurfl(square,ud);square=4;ud=updatesurfl(square,ud);
   end

% #######################################################
% END HELPER  FUNCTIONS.

% BEGIN CALLBACK FUNCTIONS.
% Callback for controlling lower bound of the parameters using editable text boxes.
function ud = setplo(fieldno,ud,newx)
cv  = str2double(get(ud.lohndl(fieldno),'String'));
pv   = str2double(get(ud.pfhndl(fieldno),'String'));
vmin = ud.minmax.xyz{fieldno}(1);
vmax = ud.minmax.xyz{fieldno}(2);
cmax = str2double(get(ud.hihndl(fieldno),'String'));

if cv > vmin & cv < vmax,
	if cv >= cmax
	   cv = get(ud.pslider(fieldno),'Min');
       set(ud.lohndl(fieldno),'String',num2str(cv));
    elseif cv > pv
        set(ud.pfhndl(fieldno),'String',num2str(cv));
        set(ud.lohndl(fieldno),'String',num2str(cv));
        ud = setpfield(fieldno,ud);
    end

    set(ud.pslider(fieldno),'Min',cv);
    ud = changemode(ud); 
elseif cv >= vmax
   set(ud.lohndl(fieldno),'String',get(ud.pslider(fieldno),'Min'));
else
   set(ud.lohndl(fieldno),'String',num2str(ud.minmax.xyz{fieldno}(1)));
end
ud = newborder(ud);
ud=newrange(ud);
ud = changemode(ud);

% Callback for controlling upper bound of the parameters using editable text boxes.
function ud = setphi(fieldno,ud,newx)
cv = str2double(get(ud.hihndl(fieldno),'String'));
pv = str2double(get(ud.pfhndl(fieldno),'String'));

vmin = ud.minmax.xyz{fieldno}(1);
vmax = ud.minmax.xyz{fieldno}(2);

cmin = str2double(get(ud.lohndl(fieldno),'String'));
if cv > vmin & cv < vmax,
	if cv <= cmin
	   cv = get(ud.pslider(fieldno),'Max');
       set(ud.hihndl(fieldno),'String',num2str(cv));
    elseif cv < pv
       set(ud.hihndl(fieldno),'String',num2str(cv));
       set(ud.pfhndl(fieldno),'String',num2str(cv));
       ud = setpfield(fieldno,ud);
	end

    set(ud.pslider(fieldno),'Max',cv);
    ud = changemode(ud); 
elseif cv <= vmax
   set(ud.hihndl(fieldno),'String',get(ud.pslider(fieldno),'Max'));
else
    set(ud.hihndl(fieldno),'String',num2str(ud.minmax.xyz{fieldno}(2)));
end
ud = newborder(ud);
ud=newrange(ud);
ud = changemode(ud);

% Callback for controlling the parameter values using sliders.
function ud = setpslider(sliderno,ud)

cv = get(ud.pslider(sliderno),'Value');
set(ud.pfhndl(sliderno),'String',num2str(cv));
ud = changemode(ud); 

% Callback for controlling the parameter values using editable text boxes.
function ud = setpfield(fieldno,ud)
cv = str2double(get(ud.pfhndl(fieldno),'String'));
vmin = ud.minmax.xyz{fieldno}(1);
vmax = ud.minmax.xyz{fieldno}(2);
phivalue = str2double(get(ud.hihndl(fieldno),'String'));
plovalue = str2double(get(ud.lohndl(fieldno),'String'));
if (cv > vmax), 
   cv=vmax;
end
if (cv < vmin), 
   cv=vmin;
end
set(ud.pfhndl(fieldno),'String',cv)
    if (cv > phivalue), 
        set(ud.hihndl(fieldno),'String',num2str(cv));
        set(ud.pslider(fieldno),'Max',cv);
        ud = setphi(fieldno,ud);
    end
    if (cv < plovalue), 
        set(ud.lohndl(fieldno),'String',num2str(cv));
        set(ud.pslider(fieldno),'Min',cv);
        ud = setplo(fieldno,ud);
    end

set(ud.pslider(fieldno),'Value',cv);
       
ud = changemode(ud); 
% --------------------------------
function ud=changecolorfon(ud)
colorfonvalue = get(ud.colorfon,'Value');
switch colorfonvalue
case 1
   ud.axiscolor =[0.45 0.5 0.2];  % Защитный
case 2
   ud.axiscolor ='red';           % Красный
case 3
   ud.axiscolor =[1 0.5 0];       % Оранжевый
case 4
   ud.axiscolor ='yellow';        % Жёлтый
case 5
   ud.axiscolor ='green';         % Зелёный
case 6
   ud.axiscolor =[127/255 1 212/255]; % Аквамариновый
case 7
   ud.axiscolor = [0 1 1];        % Голубой
case 8
   ud.axiscolor ='blue';          % Синий
case 9
   ud.axiscolor =[0.75  0   0.75]; % Фиолетовый
case 10
   ud.axiscolor =[ 0.4365 0.2728 0.1737];     % Коричневый
case 11
   ud.axiscolor =[1 1 1];         % Белый
case 12
   ud.axiscolor =[0.8 0.8 0.8];   % Серый
case 13
   ud.axiscolor =[0.01 0.01 0.01];   % Чёрный
end
set(ud.axes1,'Color',ud.axiscolor);
% --------------------------------
function ud=changecolormap(ud)
colormapvalue = get(ud.colormap,'Value');
switch colormapvalue
case 1
   ud.c =hsv;%        - Hue-saturation-value color map.
case 2
   ud.c =hot;%        - Black-red-yellow-white color map.
case 3
   ud.c =gray;%       - Linear gray-scale color map.
case 4
   ud.c =bone;%       - Gray-scale with tinge of blue color map.
case 5
   ud.c =copper;%     - Linear copper-tone color map.
case 6
   ud.c =pink;%       - Pastel shades of pink color map.
case 7
   ud.c =white;%      - All white color map.
case 8
   ud.c =flag;%       - Alternating red, white, blue, and black color map.
case 9
   ud.c =lines;%      - Color map with the line colors.
case 10
   ud.c =colorcube;%  - Enhanced color-cube color map.
case 11
   ud.c =vga;%        - Windows colormap for 16 colors.
case 12
   ud.c =jet;%        - Variant of HSV.
case 13
   ud.c =prism;%      - Prism color map. 
case 14
   ud.c =cool;%       - Shades of cyan and magenta color map.
case 15
   ud.c =autumn;%     - Shades of red and yellow color map.
case 16
   ud.c =spring;%     - Shades of magenta and yellow color map.
case 17
   ud.c =winter;%     - Shades of blue and green color map.
case 18
   ud.c =summer;%     - Shades of green and yellow color map.
case 19
   ud.c ='default';% .
end

set(gcf, 'Colormap', ud.c); if isstr(ud.c), ud.c=colormap; end;
% --------------------------------
function  ud=changemode(ud);
modevalue = get(ud.mode,'Value');
squarevalue = get(ud.square,'Value');
switch modevalue
case 1
   switch squarevalue
   case 1,
   case 2,
   case 3,
   case 4,
   case 5,
   case 6,
   case 7,
   case 8,
   case 9,
   case 10,
   case 11,
   case 12,
   case 13,
   case 14,
   case 15,
   case 16,
   case 17,
   end
   cla(ud.axes1);hold on;ud = updateslise(ud);
case 2
      switch squarevalue
   case 1,
   case 2,
   case 3,
   case 4,
   case 5,
   case 6,
   case 7,
   case 8,
   case 9,
   case 10,
   case 11,
   case 12,
   case 13,
   case 14,
   case 15,
   case 16,
   case 17,
   end
   cla(ud.axes1);hold on;ud = updatefill3(ud);
case 3
      switch squarevalue
   case 1,
   case 2,
   case 3,
   case 4,
   case 5,
   case 6,
   case 7,
   case 8,
   case 9,
   case 10,
   case 11,
   case 12,
   case 13,
   case 14,
   case 15,
   case 16,
   case 17,
   end
   cla(ud.axes1);hold on;ud = updatesurfl(ud);
case 4
      switch squarevalue
   case 1,
   case 2,
   case 3,
   case 4,
   case 5,
   case 6,
   case 7,
   case 8,
   case 9,
   case 10,
   case 11,
   case 12,
   case 13,
   case 14,
   case 15,
   case 16,
   case 17,
   end
   cla(ud.axes1);hold on;ud = updatefill3surfl(ud);
end


% --------------------------------
function h = gcba

h = get(gcbf,'CurrentAxes');
% --------------------------------
function  ud=viz(idx,ud);

ud.flunviz(idx)=1;
set(ud.viz(idx),'Visible','off');set(ud.unviz(idx),'Visible','on');
set(ud.pfhndl(idx),'Visible','on');
set(ud.hihndl(idx),'Visible','on');
set(ud.lohndl(idx),'Visible','on');
set(ud.pslider(idx),'Visible','on');
ud = changemode(ud);
% --------------------------------
function  ud=unviz(idx,ud);

ud.flunviz(idx)=0;
set(ud.unviz(idx),'Visible','off');set(ud.viz(idx),'Visible','on');
set(ud.pfhndl(idx),'Visible','off');
set(ud.hihndl(idx),'Visible','off');
set(ud.lohndl(idx),'Visible','off');
set(ud.pslider(idx),'Visible','off');
ud = changemode(ud);

