function h=slideplot(varargin)
% Функция построения двумерного графика с возможностью мануального 
% управления масштабом графика и с прокруткой. 
% Можно менять направление осей X,Y : set(ax,'YDir','reverse');
% Можно применять после функции SUBPLOT
% Аргументы - как у функции PLOT
%
%           Дроздов А.Ю. 7.04.2001.
% Дроздов Алексей Юрьевич. E-mail: alexey_drozdov@mail.ru
% "Научно-Технологический Институт Транскрипции Трансляции и Репликации".
% г. Харьков. 8-0572-19-55-77


if nargin==1 & ischar(varargin{1})
   action=varargin{1};
else action='start';
end

if ~strcmp(action,'start') 
   if strcmp(action,'Hide'),
      ax=gca;
   else
      ax = get(gcbo,'Userdata');
      if isempty(ax), ax=gca;end
   end
   ud=get(ax,'Userdata');
   if isempty(ud) & strcmp(action,'motion')
      return
   end
   if ~strcmp(ud.xdir,get(ud.ax,'XDir')),
      ud.posx=fliplr(ud.posx);
      ud.xdir=get(ud.ax,'XDir');
      ud=reset_buttonX_positions(ud);
   end
   if ~strcmp(ud.ydir,get(ud.ax,'YDir')),
      ud.posy=fliplr(ud.posy);
      ud.ydir=get(ud.ax,'YDir');
      ud=reset_buttonY_positions(ud);
   end
   switch action,
   case 'EditX1',  ud=f_Edit_X1(ud);
   case 'EditY1',  ud=f_Edit_Y1(ud);
   case 'EditX2',  ud=f_Edit_X2(ud);
   case 'EditY2',  ud=f_Edit_Y2(ud);
   case 'TextX1',  ud=f_Text_X1(ud);
   case 'TextY1',  ud=f_Text_Y1(ud);
   case 'TextX2',  ud=f_Text_X2(ud);
   case 'TextY2',  ud=f_Text_Y2(ud);
   case 'SlideX', ud=f_SlideX(ud);
   case 'SlideY', ud=f_SlideY(ud);
   case 'Hide', ud=f_Hide_buttons(ud);
   case 'Show', ud=f_Show_buttons(ud);
   end
end % if ~strcmp(action,'start') 


if strcmp(action,'start'),
   % @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   % @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   childList = allchild(0);
   if ~isempty(childList),
      ud.fig1=gcf;figcolor=get(ud.fig1,'Color');
      ud.ax=gca;
      old_ud=get(ud.ax,'Userdata');
      if ~isempty(old_ud)
         if ishandle(old_ud.textX1),delete(old_ud.textX1);end;
         if ishandle(old_ud.editX1),delete(old_ud.editX1);end;
         if ishandle(old_ud.slideX),delete(old_ud.slideX);end;
         if ishandle(old_ud.editX2),delete(old_ud.editX2);end;
         if ishandle(old_ud.textX2),delete(old_ud.textX2);end;
         if ishandle(old_ud.textY1),delete(old_ud.textY1);end;
         if ishandle(old_ud.editY1),delete(old_ud.editY1);end;
         if ishandle(old_ud.slideY),delete(old_ud.slideY);end;
         if ishandle(old_ud.editY2),delete(old_ud.editY2);end;
         if ishandle(old_ud.textY2),delete(old_ud.textY2);end;
         if ishandle(old_ud.hide),delete(old_ud.hide);end;
         if ishandle(old_ud.show),delete(old_ud.show);end;
      end
   else
      ud.fig1=figure;figcolor=[0.8 0.8 0.8];ud.ax=axes;
   end
   
   
   ud.varargin=varargin;
   ud.plot=plot(ud.varargin{:});
   h=ud.plot;
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   ud.xdir=get(ud.ax,'XDir');
   ud.ydir=get(ud.ax,'YDir');

% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   ud.xlim=get(ud.ax,'XLim');
   ud.ylim=get(ud.ax,'YLim');
   ud.xrange=ud.xlim;
   ud.yrange=ud.ylim;
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   ud.slideXval=0;
   ud.slideXmax=0;
   ud.slideXmin=0;
   
   ud.slideYval=0;
   ud.slideYmax=0;
   ud.slideYmin=0;
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   ud.X1=ud.xlim(1);
   ud.X2=ud.xlim(2);
   ud.Y1=ud.ylim(1);
   ud.Y2=ud.ylim(2);
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   axPosition=get(ud.ax,'Position');
   x1=axPosition(1);
   y1=axPosition(2);
   dx=axPosition(3);
   dy=axPosition(4);
   ddx=0.06;
   ddy=0.04;
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

ndxy=1.7;
ud.posx={[x1         y1-ndxy*ddy   ddx    ddy]   [x1+dx-ddx    y1-ndxy*ddy    ddx    ddy]
       [x1+ddx     y1-ndxy*ddy   ddx    ddy]   [x1+dx-2*ddx  y1-ndxy*ddy    ddx    ddy]};
ud.posy={[x1+dx+.005    y1             ddx    ddy]  [x1+dx+.005    y1+dy-ddy        ddx   ddy]
       [x1+dx+.005    y1+1.25*ddy    ddx    ddy]  [x1+dx+.005    y1+dy-2.25*ddy   ddx   ddy]};
    
if  strcmp(ud.xdir,'reverse'), ud.posx=fliplr(ud.posx);end
if  strcmp(ud.ydir,'reverse'), ud.posy=fliplr(ud.posy);end

% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   ud.textX1=uicontrol('Style','Pushbutton','Units','normalized',...
      'Position',ud.posx{1,1},...
   'ForegroundColor','k','BackgroundColor',figcolor,...
   'String',num2str(ud.xrange(1)),'Callback',['slideplot(''TextX1'');'],'Userdata',ud.ax); 
   
   ud.editX1=uicontrol('Style','edit','Units','normalized',...
      'Position',ud.posx{2,1},...
      'String', num2str(ud.xlim(1)),'BackgroundColor','white','Callback',['slideplot(''EditX1'');'],'Userdata',ud.ax);
   ud.slideX=uicontrol('Style','slider','Units','normalized','Visible','off',...
      'Position',[x1+2*ddx     y1-ndxy*ddy      dx-4*ddx    ddy],...
      'Value',0,'Max',0,'Min',0,'Callback',['slideplot(''SlideX'');'],'Userdata',ud.ax);
   ud.editX2=uicontrol('Style','edit','Units','normalized',...
      'Position',ud.posx{2,2},...
      'String', num2str(ud.xlim(2)),'BackgroundColor','white','Callback',['slideplot(''EditX2'');'],'Userdata',ud.ax);
   ud.textX2=uicontrol('Style','Pushbutton','Units','normalized',...
      'Position',ud.posx{1,2},...
   'ForegroundColor','k','BackgroundColor',figcolor,...
   'String',num2str(ud.xrange(2)),'Callback',['slideplot(''TextX2'');'],'Userdata',ud.ax); 
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   ud.textY1=uicontrol('Style','Pushbutton','Units','normalized',...
      'Position',ud.posy{1,1},...
   'ForegroundColor','k','BackgroundColor',figcolor,...
   'String',num2str(ud.yrange(1)),'Callback',['slideplot(''TextY1'');'],'Userdata',ud.ax); 
   ud.editY1=uicontrol('Style','edit','Units','normalized',...
      'Position',ud.posy{2,1},...
      'String', num2str(ud.ylim(1)),'BackgroundColor','white','Callback',['slideplot(''EditY1'');'],'Userdata',ud.ax);
   ud.slideY=uicontrol('Style','slider','Units','normalized','Visible','off',...
      'Position',[x1+dx+.01    y1+2.5*ddy        .03        dy-5*ddy],'Value',0,'Max',0,'Min',0,'Callback',['slideplot(''SlideY'');'],'Userdata',ud.ax);
   ud.editY2=uicontrol('Style','edit','Units','normalized',...
      'Position',ud.posy{2,2},...
      'String', num2str(ud.ylim(2)),'BackgroundColor','white','Callback',['slideplot(''EditY2'');'],'Userdata',ud.ax);
   ud.textY2=uicontrol('Style','Pushbutton','Units','normalized',...
      'Position',ud.posy{1,2},...
   'ForegroundColor','k','BackgroundColor',figcolor,...
   'String',num2str(ud.yrange(2)),'Callback',['slideplot(''TextY2'');'],'Userdata',ud.ax); 
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   ud.hide=uicontrol('Style','Pushbutton','Units','normalized',...
      'Position',[x1+dx+.005  y1-ndxy*ddy      ddx    ddy],...
   'ForegroundColor','k','BackgroundColor',figcolor,...
   'String','Hide','Callback',['slideplot(''Hide'');'],'Userdata',ud.ax); 
   ud.show=uicontrol('Style','Pushbutton','Units','normalized',...
      'Position',[x1+dx+.005  y1-ndxy*ddy      ddx    ddy],...
   'ForegroundColor','k','BackgroundColor',figcolor,...
   'String','Show','Callback',['slideplot(''Show'');'],'Visible','off','Userdata',ud.ax); 


end % if strcmp(action,'start')


% End of initialization.
set(ud.ax,'UserData',ud);


% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

function ud=f_Edit_X1(ud)

ud.X1=str2double(get(ud.editX1,'String'));
if ud.X1<ud.xrange(1),ud.X1=ud.xrange(1);set(ud.editX1,'String',num2str(ud.X1));end
if ud.X1>ud.xrange(2),ud.X1=ud.xrange(1);set(ud.editX1,'String',num2str(ud.X1));end
if ud.X1>=ud.X2,ud.X1=ud.xrange(1);set(ud.editX1,'String',num2str(ud.X1));end
ud.xlim(1)=ud.X1;
set(ud.ax,'XLim',ud.xlim);
set(ud.ax,'YLim',ud.ylim);

ud.slideXval=0;
ud.slideXmax=ud.xrange(2)-ud.X2;
ud.slideXmin=ud.xrange(1)-ud.X1;

if ~(ud.slideXmax>ud.slideXmin), set(ud.slideX,'Visible','off');
elseif (ud.slideXmax>ud.slideXmin) & strcmp(ud.xdir,'normal')
   set(ud.slideX,'Max',ud.slideXmax,'Min',ud.slideXmin,'Value',ud.slideXval,'Visible','on');
elseif (ud.slideXmax>ud.slideXmin) & strcmp(ud.xdir,'reverse')
   set(ud.slideX,'Max',-ud.slideXmin,'Min',-ud.slideXmax,'Value',ud.slideXval,'Visible','on');
end

% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

function ud=f_Edit_X2(ud)

ud.X2=str2double(get(ud.editX2,'String'));
if ud.X2<ud.xrange(1),ud.X2=ud.xrange(2);set(ud.editX2,'String',num2str(ud.X2));end
if ud.X2>ud.xrange(2),ud.X2=ud.xrange(2);set(ud.editX2,'String',num2str(ud.X2));end
if ud.X1>=ud.X2,ud.X2=ud.xrange(2);set(ud.editX2,'String',num2str(ud.X2));end
ud.xlim(2)=ud.X2;
set(ud.ax,'XLim',ud.xlim);
set(ud.ax,'YLim',ud.ylim);

ud.slideXval=0;
ud.slideXmax=ud.xrange(2)-ud.X2;
ud.slideXmin=ud.xrange(1)-ud.X1;

if ~(ud.slideXmax>ud.slideXmin), set(ud.slideX,'Visible','off');
elseif (ud.slideXmax>ud.slideXmin) & strcmp(ud.xdir,'normal')
   set(ud.slideX,'Max',ud.slideXmax,'Min',ud.slideXmin,'Value',ud.slideXval,'Visible','on');
elseif (ud.slideXmax>ud.slideXmin) & strcmp(ud.xdir,'reverse')
   set(ud.slideX,'Max',-ud.slideXmin,'Min',-ud.slideXmax,'Value',ud.slideXval,'Visible','on');
end


% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

function ud=f_Edit_Y1(ud)

ud.Y1=str2double(get(ud.editY1,'String'));
if ud.Y1<ud.yrange(1),ud.Y1=ud.yrange(1);set(ud.editY1,'String',num2str(ud.Y1));end
if ud.Y1>ud.yrange(2),ud.Y1=ud.yrange(1);set(ud.editY1,'String',num2str(ud.Y1));end
if ud.Y1>=ud.Y2,ud.Y1=ud.yrange(1);set(ud.editY1,'String',num2str(ud.Y1));end
ud.ylim(1)=ud.Y1;
set(ud.ax,'XLim',ud.xlim);
set(ud.ax,'YLim',ud.ylim);

ud.slideYval=0;
ud.slideYmax=ud.yrange(2)-ud.Y2;
ud.slideYmin=ud.yrange(1)-ud.Y1;


if ~(ud.slideYmax>ud.slideYmin), set(ud.slideY,'Visible','off');
elseif (ud.slideYmax>ud.slideYmin) & strcmp(ud.ydir,'normal')
   set(ud.slideY,'Max',ud.slideYmax,'Min',ud.slideYmin,'Value',ud.slideYval,'Visible','on');
elseif (ud.slideYmax>ud.slideYmin) & strcmp(ud.ydir,'reverse')
   set(ud.slideY,'Max',-ud.slideYmin,'Min',-ud.slideYmax,'Value',ud.slideYval,'Visible','on');
end


% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

function ud=f_Edit_Y2(ud)

ud.Y2=str2double(get(ud.editY2,'String'));
if ud.Y2<ud.yrange(1),ud.Y2=ud.yrange(2);set(ud.editY2,'String',num2str(ud.Y2));end
if ud.Y2>ud.yrange(2),ud.Y2=ud.yrange(2);set(ud.editY2,'String',num2str(ud.Y2));end
if ud.Y1>=ud.Y2,ud.Y2=ud.yrange(2);set(ud.editY2,'String',num2str(ud.Y2));end
ud.ylim(2)=ud.Y2;
set(ud.ax,'XLim',ud.xlim);
set(ud.ax,'YLim',ud.ylim);

ud.slideYval=0;
ud.slideYmax=ud.yrange(2)-ud.Y2;
ud.slideYmin=ud.yrange(1)-ud.Y1;

if ~(ud.slideYmax>ud.slideYmin), set(ud.slideY,'Visible','off');
elseif (ud.slideYmax>ud.slideYmin) & strcmp(ud.ydir,'normal')
   set(ud.slideY,'Max',ud.slideYmax,'Min',ud.slideYmin,'Value',ud.slideYval,'Visible','on');
elseif (ud.slideYmax>ud.slideYmin) & strcmp(ud.ydir,'reverse')
   set(ud.slideY,'Max',-ud.slideYmin,'Min',-ud.slideYmax,'Value',ud.slideYval,'Visible','on');
end


% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

function ud=f_SlideX(ud)

if strcmp(ud.xdir,'normal'),
   ud.slideXval=get(ud.slideX,'Value');
elseif strcmp(ud.xdir,'reverse')
   ud.slideXval=-get(ud.slideX,'Value');
end


ud.slideXmax=ud.slideXmax-ud.slideXval;
ud.slideXmin=ud.slideXmin-ud.slideXval;
ud.slideXval=0;

if strcmp(ud.xdir,'normal')
   set(ud.slideX,'Max',ud.slideXmax,'Min',ud.slideXmin,'Value',ud.slideXval,'Visible','on');
elseif strcmp(ud.xdir,'reverse')
   set(ud.slideX,'Max',-ud.slideXmin,'Min',-ud.slideXmax,'Value',ud.slideXval,'Visible','on');
end


ud.X2=ud.xrange(2)-ud.slideXmax;
ud.X1=ud.xrange(1)-ud.slideXmin;
set(ud.editX2,'String',num2str(ud.X2));
set(ud.editX1,'String',num2str(ud.X1));
ud.xlim=[ud.X1 ud.X2];
set(ud.ax,'XLim',ud.xlim);
set(ud.ax,'YLim',ud.ylim);

% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

function ud=f_SlideY(ud)

if strcmp(ud.ydir,'normal')
   ud.slideYval=get(ud.slideY,'Value');
elseif strcmp(ud.ydir,'reverse')
   ud.slideYval=-get(ud.slideY,'Value');
end



ud.slideYmax=ud.slideYmax-ud.slideYval;
ud.slideYmin=ud.slideYmin-ud.slideYval;
ud.slideYval=0;

if  strcmp(ud.ydir,'normal'),
   set(ud.slideY,'Max',ud.slideYmax,'Min',ud.slideYmin,'Value',ud.slideYval,'Visible','on');
elseif strcmp(ud.ydir,'reverse'),
  set(ud.slideY,'Max',-ud.slideYmin,'Min',-ud.slideYmax,'Value',ud.slideYval,'Visible','on');
end


ud.Y2=ud.yrange(2)-ud.slideYmax;
ud.Y1=ud.yrange(1)-ud.slideYmin;
set(ud.editY2,'String',num2str(ud.Y2));
set(ud.editY1,'String',num2str(ud.Y1));
ud.ylim=[ud.Y1 ud.Y2];
set(ud.ax,'XLim',ud.xlim);
set(ud.ax,'YLim',ud.ylim);

% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function ud=f_Text_X1(ud)
ud.X1=ud.xrange(1);
set(ud.editX1,'String',num2str(ud.X1));
ud.xlim(1)=ud.X1;
set(ud.ax,'XLim',ud.xlim);
set(ud.ax,'YLim',ud.ylim);

ud.slideXval=0;
ud.slideXmax=ud.xrange(2)-ud.X2;
ud.slideXmin=ud.xrange(1)-ud.X1;

if ~(ud.slideXmax>ud.slideXmin), set(ud.slideX,'Visible','off');
elseif (ud.slideXmax>ud.slideXmin) & strcmp(ud.xdir,'normal')
   set(ud.slideX,'Max',ud.slideXmax,'Min',ud.slideXmin,'Value',ud.slideXval,'Visible','on');
elseif (ud.slideXmax>ud.slideXmin) & strcmp(ud.xdir,'reverse')
   set(ud.slideX,'Max',-ud.slideXmin,'Min',-ud.slideXmax,'Value',ud.slideXval,'Visible','on');
end

% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function ud=f_Text_X2(ud)
ud.X2=ud.xrange(2);
set(ud.editX2,'String',num2str(ud.X2));
ud.xlim(2)=ud.X2;
set(ud.ax,'XLim',ud.xlim);
set(ud.ax,'YLim',ud.ylim);

ud.slideXval=0;
ud.slideXmax=ud.xrange(2)-ud.X2;
ud.slideXmin=ud.xrange(1)-ud.X1;

if ~(ud.slideXmax>ud.slideXmin), set(ud.slideX,'Visible','off');
elseif (ud.slideXmax>ud.slideXmin) & strcmp(ud.xdir,'normal')
   set(ud.slideX,'Max',ud.slideXmax,'Min',ud.slideXmin,'Value',ud.slideXval,'Visible','on');
elseif (ud.slideXmax>ud.slideXmin) & strcmp(ud.xdir,'reverse')
   set(ud.slideX,'Max',-ud.slideXmin,'Min',-ud.slideXmax,'Value',ud.slideXval,'Visible','on');
end

% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function ud=f_Text_Y1(ud)
ud.Y1=ud.yrange(1);
set(ud.editY1,'String',num2str(ud.Y1));
ud.ylim(1)=ud.Y1;
set(ud.ax,'XLim',ud.xlim);
set(ud.ax,'YLim',ud.ylim);

ud.slideYval=0;
ud.slideYmax=ud.yrange(2)-ud.Y2;
ud.slideYmin=ud.yrange(1)-ud.Y1;

if ~(ud.slideYmax>ud.slideYmin), set(ud.slideY,'Visible','off');
elseif (ud.slideYmax>ud.slideYmin) & strcmp(ud.ydir,'normal')
   set(ud.slideY,'Max',ud.slideYmax,'Min',ud.slideYmin,'Value',ud.slideYval,'Visible','on');
elseif (ud.slideYmax>ud.slideYmin) & strcmp(ud.ydir,'reverse')
   set(ud.slideY,'Max',-ud.slideYmin,'Min',-ud.slideYmax,'Value',ud.slideYval,'Visible','on');
end

% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function ud=f_Text_Y2(ud)
ud.Y2=ud.yrange(2);
set(ud.editY2,'String',num2str(ud.Y2));
ud.ylim(2)=ud.Y2;
set(ud.ax,'XLim',ud.xlim);
set(ud.ax,'YLim',ud.ylim);

ud.slideYval=0;
ud.slideYmax=ud.yrange(2)-ud.Y2;
ud.slideYmin=ud.yrange(1)-ud.Y1;

if ~(ud.slideYmax>ud.slideYmin), set(ud.slideY,'Visible','off');
elseif (ud.slideYmax>ud.slideYmin) & strcmp(ud.ydir,'normal')
   set(ud.slideY,'Max',ud.slideYmax,'Min',ud.slideYmin,'Value',ud.slideYval,'Visible','on');
elseif (ud.slideYmax>ud.slideYmin) & strcmp(ud.ydir,'reverse')
   set(ud.slideY,'Max',-ud.slideYmin,'Min',-ud.slideYmax,'Value',ud.slideYval,'Visible','on');
end
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function ud=f_Hide_buttons(ud);
set(ud.textX1,'Visible','off');
set(ud.textX2,'Visible','off');
set(ud.textY1,'Visible','off');
set(ud.textY2,'Visible','off');
set(ud.editX1,'Visible','off');
set(ud.editX2,'Visible','off');
set(ud.editY1,'Visible','off');
set(ud.editY2,'Visible','off');
set(ud.slideX,'Visible','off');
set(ud.slideY,'Visible','off');
set(ud.hide,'Visible','off');
set(ud.show,'Visible','on');


% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function ud=f_Show_buttons(ud);
set(ud.textX1,'Visible','on');
set(ud.textX2,'Visible','on');
set(ud.textY1,'Visible','on');
set(ud.textY2,'Visible','on');
set(ud.editX1,'Visible','on');
set(ud.editX2,'Visible','on');
set(ud.editY1,'Visible','on');
set(ud.editY2,'Visible','on');
if (ud.slideXmax>ud.slideXmin),set(ud.slideX,'Visible','on');end
if (ud.slideYmax>ud.slideYmin),set(ud.slideY,'Visible','on');end
set(ud.show,'Visible','off');
set(ud.hide,'Visible','on');
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

function ud=reset_buttonX_positions(ud)

set(ud.textX1,'Position',ud.posx{1,1});
set(ud.textX2,'Position',ud.posx{1,2});
set(ud.editX1,'Position',ud.posx{2,1});
set(ud.editX2,'Position',ud.posx{2,2});

function ud=reset_buttonY_positions(ud)

set(ud.textY1,'Position',ud.posy{1,1});
set(ud.textY2,'Position',ud.posy{1,2});
set(ud.editY1,'Position',ud.posy{2,1});
set(ud.editY2,'Position',ud.posy{2,2});
