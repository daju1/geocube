function ud=viz3Dgeo(action,flag,ud,ude,modeval);
%
% ???????????????? ????????? ???????????? ??????, ????????? 
% ? ???? ?????????? ??????? ????? (? ?????? ?????? ????? ?????? 
% ???????????? ????????????? ?????????? ????????? ? ????????????),
% ??????????? ?????????? ????????????? ????????????? 
% ???????? ? ?????????????? ? ???????????? ??????????
% ????????, ? ??????? ???????? ?????????. ???? ????????????? ????????
% ??????????????? ????????? ? ?????? ????? ????????????
%
%           ??????? ?.?. 18.12.2001.
% ??????? ??????? ???????. E-mail: alexey_drozdov@mail.ru
% "??????-??????????????? ???????? ???????????? ?????????? ? ??????????".
% ?. ???????. 8-0572-19-55-77

if nargin < 4 
   modeval=1;
end

if nargin < 1 | isempty(action)
    action = 'start';
end
%On recursive calls get all necessary handles and data.
if ~strcmp(action,'start')   
   childList = allchild(0);
   fig1 = childList(find(childList == gcbf));
   ud = get(fig1,'Userdata');
   %if ~isstruct(ud), ud=get(ud,'Userdata');end
   if isempty(ud) & strcmp(action,'motion')
      return
   end
   
   % @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   %  ?????? ?? ?????????? ???????? ?????-???? ??????? ??????
   % @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   if ~isstruct(ud) & ishandle(ud), ud=get(ud,'Userdata');end
   
   if ~isstruct(ud),
      close all;
      errordlg(['??????? ?? ??? ??????? ??????. ? ????? ? ???? ????????? ?????????? ??????'],'ERROR','CREATEMODE');
      return
   end
   
   if ~all(ishandle(ud.fig1:ud.fig4)),
      errordlg(['??????? ?? ??? ??????? ??????. ? ????? ? ???? ????????? ?????????? ??????'],'ERROR','CREATEMODE');
      if ishandle(ud.fig1),close(ud.fig1);end
      if ishandle(ud.fig2),close(ud.fig2);end
      if ishandle(ud.fig3),close(ud.fig3);end
      if ishandle(ud.fig4),close(ud.fig4);end
      return
   end
   % @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   % @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
   
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
      case 'close',
         if ishandle(ud.fig1),close(ud.fig1);end
         if ishandle(ud.fig2),close(ud.fig2);end
         if ishandle(ud.fig3),close(ud.fig3);end
         if ishandle(ud.fig4),close(ud.fig4);end
      case 'izosurface'
         %set(ud.izo(flag) ,'Visible','off');
         delete(ud.izo(flag));
         figure(ud.fig4);hold on;
         izov(flag)=get(ud.slidizo(flag),'Value')*(ud.maxv-ud.minv)+ud.minv;
         newizo=makeizosurface(izov(flag),ud);
         ud.izo(flag)=newizo;
         figure(ud.fig1);
      case 'rangeaxes'
         switch flag
         case 1, ud.ra=1;
         case 2, ud.ra=2;
         case 3, ud.ra=3;
         end
         ud=newrange(ud);
         
      case 'box'
         boxv=get(ud.box,'Value');
         axes(ud.axes1);
         switch boxv
         case 1, box off;
         case 2, box on;
         end
         figure(ud.fig2);
         
      case 'title'
         ud.nlabel=1;
         set(ud.edit3,'String',ud.title_label1{1})
      case 'xlabel'
         ud.nlabel=2;
         set(ud.edit3,'String',ud.title_label1{2})
      case 'ylabel'
         ud.nlabel=3;
         set(ud.edit3,'String',ud.title_label1{3})
      case 'zlabel'
         ud.nlabel=4;
         set(ud.edit3,'String',ud.title_label1{4})
      case 'edit_title_label'
         switch ud.nlabel
         case 1, figure(ud.fig4);ud.title_label1{1}=get(ud.edit3,'String'); title(ud.title_label1(1));figure(ud.fig3);
         case 2, figure(ud.fig4);ud.title_label1{2}=get(ud.edit3,'String');xlabel(ud.title_label1(2));figure(ud.fig3);
         case 3, figure(ud.fig4);ud.title_label1{3}=get(ud.edit3,'String');ylabel(ud.title_label1(3));figure(ud.fig3);
         case 4, figure(ud.fig4);ud.title_label1{4}=get(ud.edit3,'String');zlabel(ud.title_label1(4));figure(ud.fig3);
         end
         
      case 'grid'
         switch flag
         case 'on', ud.grid=1;
            set(ud.h,'EdgeColor',ud.gridcolor);
            set(ud.gridon,'Visible','off');
            set(ud.gridoff,'Visible','on');
            set(ud.slidcolgrid,'Visible','on');
         case 'off', ud.grid=0;
            set(ud.h,'EdgeColor','none');
            set(ud.gridoff,'Visible','off');
            set(ud.gridon,'Visible','on');
            set(ud.slidcolgrid,'Visible','off');
         case 'color', 
            cm=[ud.c;conv2([1 1 1],(0:63)'/63)];
            ud.gridcolor=cm(1+round(get(ud.slidcolgrid,'Value')*63.5),:);
            set(ud.h,'EdgeColor',ud.gridcolor);
            if ud.flunviz(2)==1 & ud.flunviz(3)==1
               set(ud.linex,'Color',ud.gridcolor);  
            end
            if ud.flunviz(1)==1 & ud.flunviz(3)==1
               set(ud.liney,'Color',ud.gridcolor);
            end
            if ud.flunviz(1)==1 & ud.flunviz(2)==1
               set(ud.linez,'Color',ud.gridcolor);
            end
         end
         
      case 'line'
         switch flag
         case 'on', %ud.lineon=1;
            set(ud.lineon,'Visible','off');
            set(ud.lineoff,'Visible','on');
            %set(ud.slidcolline,'Visible','on');
            if ud.flunviz(2)==1 & ud.flunviz(3)==1
               set(ud.linex,'Visible','on');  
            end
            if ud.flunviz(1)==1 & ud.flunviz(3)==1
               set(ud.liney,'Visible','on');
            end
            if ud.flunviz(1)==1 & ud.flunviz(2)==1
               set(ud.linez,'Visible','on');
            end
         case 'off', %ud.lineon=0;
            set(ud.lineoff,'Visible','off');
            set(ud.lineon,'Visible','on');
            %set(ud.slidcolline,'Visible','off');
            if ud.flunviz(2)==1 & ud.flunviz(3)==1
               set(ud.linex,'Visible','off');  
            end
            if ud.flunviz(1)==1 & ud.flunviz(3)==1
               set(ud.liney,'Visible','off');
            end
            if ud.flunviz(1)==1 & ud.flunviz(2)==1
               set(ud.linez,'Visible','off');
            end
         end
         
      case 'light'
         switch flag
         case 'on',% ud.light=1;
            set(ud.lighton,'Visible','off');
            set(ud.lightoff,'Visible','on');
            set(ud.slidlight1,'Visible','on');
            set(ud.slidlight2,'Visible','on');
            set(ud.lightmode,'Visible','on');
            figure(ud.fig4);axes(ud.axes1);
            %lighting none;camlight;lighting phong;
            ud.hl = light('position',[1 0 1],'Color',[1 1 1],'Style','infinite');
            figure(ud.fig1);
         case 'off', %ud.light=0;
            set(ud.lightoff,'Visible','off');
            set(ud.lighton,'Visible','on');
            set(ud.slidlight1,'Visible','off');
            set(ud.slidlight2,'Visible','off');
            set(ud.lightmode,'Visible','off');
            %figure(ud.fig4);axes(ud.axes1);
            delete(ud.hl);%lighting none;
            %figure(ud.fig1);
         case 'source', 
            p1=get(ud.slidlight1,'Value');
            p2=get(ud.slidlight2,'Value');
            p3=get(ud.slidlight3,'Value');
            
            %figure(ud.fig4);axes(ud.axes1);
            set(ud.hl,'position',[p1 p2 p3]);
            %camlight;lighting none;camlight(az,el);lighting phong;
            %figure(ud.fig1);
         case 'mode',
            figure(ud.fig4);axes(ud.axes1);
            lmodevalue=get(ud.lightmode,'Value');
            switch lmodevalue
            case 1, delete(ud.hl);camlight headlight;
            case 2, delete(ud.hl);camlight right;
            case 3, delete(ud.hl);camlight left;
            case 4, set(ud.hl,'Style','local');
            case 5, set(ud.hl,'Style','infinite');
            case 6, lighting flat;
            case 7, lighting gouraud;
            case 8, lighting phong;
            case 9, lighting none;
            end
            figure(ud.fig1);
         end
         
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
      case 'colorbar', 
         pcv=get(ud.popupcolorbar,'Value');axes(ud.axes1);
         switch pcv
         case 1, if isfield(ud,'colorbar') if ishandle(ud.colorbar), delete(ud.colorbar); end;end;
            ud.colorbar=colorbar('vert');
            fontsize=str2num(get(ud.axes1fontsize,'String'));
            set(ud.colorbar,'FontSize',fontsize);
         case 2, if isfield(ud,'colorbar') if ishandle(ud.colorbar), delete(ud.colorbar); end;end;
            ud.colorbar=colorbar('horiz');
            fontsize=str2num(get(ud.axes1fontsize,'String'));
            set(ud.colorbar,'FontSize',fontsize);
         case 3, if isfield(ud,'colorbar') if ishandle(ud.colorbar), delete(ud.colorbar); end;end;
         end
         figure(ud.fig1);
      case 'axes1fontsize'
         fontsize=str2num(get(ud.axes1fontsize,'String'));
         set(ud.axes1,'FontSize',fontsize);
         if isfield(ud,'colorbar') if ishandle(ud.colorbar), set(ud.colorbar,'FontSize',fontsize);; end;end;
         figure(ud.fig4);
          title(ud.title_label1(1));
         xlabel(ud.title_label1(2));
         ylabel(ud.title_label1(3));
         zlabel(ud.title_label1(4));
   end
end % if ~strcmp(action,'start') 

% Initialize all GUI objects. Plot slice with sliders for parameters.
if strcmp(action,'start'),
   % Create cell array of positions for parameter controls.
   pos{1,1} = [0.1800    0.3500    0.2950    0.0500];
   pos{2,1} = pos{1,1} + [0.4500    0.0450         0         0];
   pos{3,1} = pos{2,1} + [0   -0.0950         0         0];
   pos{4,1} = pos{1,1} + [0.3250   -0.0500   -0.2000    0.0950];
   pos{5,1} = pos{1,1} + [0    0.0550         0   -0.0100];   
   pos{6,1} = pos{1,1} + [0.4500         0         0   -0.0100];
   pos{7,1} = pos{1,1} + [0   -0.0480         0   -0.0060];

   pos{1,2} = [0.1800    0.5100    0.2950    0.0500];
   pos{2,2} = pos{1,2} + [0.4500    0.0450         0         0];
   pos{3,2} = pos{2,2} + [0   -0.0950         0         0];
   pos{4,2} = pos{1,2} + [0.3250   -0.0500   -0.2000    0.0950];
   pos{5,2} = pos{1,2} + [0    0.0550         0   -0.0100];
   pos{6,2} = pos{1,2} + [0.4500         0         0   -0.0100];
   pos{7,2} = pos{1,2} + [0 -0.03-.018 0 -.006];
   
   pos{1,3} = [0.1800    0.6700    0.2950    0.0500];
   pos{2,3} = pos{1,3} + [0.4500    0.0450         0         0];
   pos{3,3} = pos{2,3} + [0   -0.0950         0         0];
   pos{4,3} = pos{1,3} + [0.3250   -0.0500   -0.2000    0.0950];
   pos{5,3} = pos{1,3} + [0    0.0550         0   -0.0100];
   pos{6,3} = pos{1,3} + [0.4500         0         0   -0.0100];
   pos{7,3} = pos{1,3} + [0 -0.03-.018 0 -.006];
   
   pos{1,4} = [0.1800    0.1200    0.2950    0.0500];%;
   pos{2,4} = pos{1,4} + [0.4500    0.0450         0         0];
   pos{3,4} = pos{2,4} + [0   -0.0950         0         0];
   pos{4,4} = pos{1,4} + [0.3250   -0.0500   -0.2000    0.0950];
   pos{5,4} = pos{1,4} + [0    0.0550         0   -0.0100];
   pos{6,4} = pos{1,4} + [0.4500         0         0   -0.0100];
   pos{7,4} = pos{1,4} + [0 -0.03-.018 0 -.006];
   
   posui1=[0.0100    0.7300    0.4350    0.0330];
   posui5=[0.0100    0.6900    0.4350    0.0330];
   posui2=[0.0100    0.9500    0.4350    0.0330];
   posui3=[0.0100    0.9100    0.4350    0.0330];
   posui4=[.64 .73 .355 .033];
ud.maxv=max(max(max(ud.V)));
ud.minv=min(min(min(ud.V)));
disp(['???????????? ???????? ? ?????? ?? ??????, ']);
disp(['???????????? ?????????????? ' num2str(ud.maxv)]);
disp(['??????????? ???????? ? ?????? ?? ??????, ']);
disp(['???????????? ?????????????? ' num2str(ud.minv)]);

% ??????????? ???????? ????????? ?????????
xmax=max(ud.x);xmin=min(ud.x);
ymax=max(ud.y);ymin=min(ud.y);
zmax=max(ud.z);zmin=min(ud.z);
ud.minmax={[xmin xmax] [ymin ymax] [zmin zmax] [ud.minv ud.maxv]};

% ????????? ?????? ????????? ?????????? ?????? data
ud.ybord=[1 length(ud.y)];
ud.xbord=[1 length(ud.x)];
ud.zbord=[1 length(ud.z)];


% ????????? ??? ?????????? ???? ???????
ud.ra=3;
% ???????????? ??????? ?????????? ???? ???????:
switch ud.ra
%      ??????? 1: ??????? ?? ???? ???? ????????:
case 1
kmax=max([ud.x(ud.xbord(2)) ud.y(ud.ybord(2)) ud.z(ud.zbord(2))]);
kmin=min([ud.x(ud.xbord(1)) ud.y(ud.ybord(1)) ud.z(ud.zbord(1))]);

ud.xrange = [kmin kmax];
ud.yrange = [kmin kmax];
ud.zrange = [kmin kmax];
%      ??????? 2: ??????? ?? ???? ???? ??????????:
case 2
ud.xrange = [ud.x(ud.xbord(1)) ud.x(ud.xbord(2))];
ud.yrange = [ud.y(ud.ybord(1)) ud.y(ud.ybord(2))];
ud.zrange = [ud.z(ud.zbord(1)) ud.z(ud.zbord(2))];
case 3
dmax=max([ud.x(ud.xbord(2))-ud.x(ud.xbord(1)) ud.y(ud.ybord(2))-ud.y(ud.ybord(1))]);
ud.xrange = [ud.x(ud.xbord(1)) ud.x(ud.xbord(1))+dmax];
ud.yrange = [ud.y(ud.ybord(1)) ud.y(ud.ybord(1))+dmax];
ud.zrange = [ud.z(ud.zbord(1)) ud.z(ud.zbord(2))];
end

paramtext  = str2mat('X-??????','Y-??????','Z-??????','  ');
paramtext2  = str2mat('X???????','Y???????','Z???????','V???????');
% ??????????, ???????????? - ???????? ??? ?????? ??????
ud.flunviz(1)=1;
ud.flunviz(2)=1;
ud.flunviz(3)=1;
ud.flunviz(4)=1;

% ?????????? ???????????? ????????:
ud.newxyzv={[0.5*(ud.x(1)+ud.x(end))]....
      [0.5*(ud.y(1)+ud.y(end))]....
      [0.5*(ud.z(1)+ud.z(end))]....
     [(ud.maxv+ud.minv)/2]};
%   ???????? ?????? ??? ??????
figcolor=[0.55 0.5 .8];

ud.fig1 = figure('Visible','off','Tag','slicefig');
set(ud.fig1,'Units','Normalized','Backingstore','off','InvertHardcopy','on','PaperPositionMode','auto',...
    'Color',figcolor,'Position',[0.7562    0.0517    0.2388    0.6300]);
%   ???????? ??????
ud.textbutton1 =uicontrol('Style','text','Units','normalized',...
   'Position',pos{1,3}+[-0.2200    0.0950    0.8000         0],...
   'ForegroundColor','k','BackgroundColor',figcolor,'String','?????? ?????????? ?????????:'); 
ud.textbutton2 =uicontrol('Style','text','Units','normalized',...
   'Position',pos{1,4}+[-0.2000    0.1050    0.8000    0.0200],...
   'ForegroundColor','k','BackgroundColor',figcolor,'String','?????? ?????????? ???????????????:'); 

   for idx = 1:4
      nstr = int2str(idx);
      ud.pfhndl(idx)=uicontrol('Style','edit','Units','normalized','Position',pos{1,idx},...
          'String',num2str(ud.newxyzv{idx}),'BackgroundColor','white',...
          'CallBack',['viz3Dgeo(''setpfield'',',nstr,');']);
         
       ud.hihndl(idx)=uicontrol('Style','edit','Units','normalized','Position',pos{2,idx},...
         'String',num2str(ud.minmax{idx}(2)),'BackgroundColor','white',...
         'CallBack',['viz3Dgeo(''setphi'',',nstr,');']);
         
       ud.lohndl(idx)=uicontrol('Style','edit','Units','normalized','Position',pos{3,idx},...
         'String',num2str(ud.minmax{idx}(1)),'BackgroundColor','white',... 
         'CallBack',['viz3Dgeo(''setplo'',',nstr,');']);

       ud.pslider(idx)=uicontrol('Style','slider','Units','normalized','Position',pos{4,idx},...
         'Value',ud.newxyzv{idx},'Max',ud.minmax{idx}(2),...
         'Min',ud.minmax{idx}(1),'Callback',['viz3Dgeo(''setpslider'',',nstr,');']);
            
       ud.ptext(idx) =uicontrol('Style','text','Units','normalized','Position',pos{5,idx},...
         'ForegroundColor','k','BackgroundColor',figcolor,'String',paramtext(idx,:)); 
       
       ud.ptext2(idx) =uicontrol('Style','text','Units','normalized','Position',pos{6,idx},...
         'ForegroundColor','k','BackgroundColor',figcolor,'String',paramtext2(idx,:)); 
      
       ud.viz(idx)=uicontrol('Style','Pushbutton','Units','normalized','Position',pos{7,idx},...
       'String','????????','Visible','off','Callback',['viz3Dgeo(''viz'',',nstr,');']);
    
       ud.unviz(idx)=uicontrol('Style','Pushbutton','Units','normalized','Position',pos{7,idx},...
       'String','??????','Callback',['viz3Dgeo(''unviz'',',nstr,');']);
 end   %for idx = 1:3  
 
 
   
   close_button = uicontrol('Style','Pushbutton','Units','normalized',...
      'Position',[0.0900    0.0100    0.4000    0.0500],'Callback','viz3Dgeo(''close'');','String','???????');
   apply_button = uicontrol('Style','Pushbutton','Units','normalized',...
      'Position',[0.5300    0.0100    0.4000    0.0500],'Callback','viz3Dgeo(''changemode'');','String','?????????');
 
 
   ud.mode=uicontrol('Style','Popup','String',...
      'slice|fill3|surfl|fill3+surfl|slice3contour|surfl+slice3contour|surf+slice|one surf|slice(surface)|cub_slice|cub_slice3cont|cut_slice|cut_slice3cont|izosurface|slices|slises3cont|new slice|new slice3cont|?????? cone plot|?????? quver3 plot',....
      'Value',modeval,'Units','normalized','Position',[0.295 .965 .705 .033]);%,'CallBack','viz3Dgeo(''changemode'');');
   ud.textmode =uicontrol('Style','text','Units','normalized',...
      'Position',[0.01 .955 .28 .033],...
      'ForegroundColor','k','BackgroundColor',figcolor,'String','?????:'); 
   
   ud.textsqu =uicontrol('Style','text','Units','normalized',...
      'Position',[0.01    0.9    0.18    0.032],...
      'ForegroundColor','k','BackgroundColor',figcolor,'String','????'); 
   ud.squ=uicontrol('Style','Popup','String',...
      '0|1|2|3|4|1+2|1+3|1+4|2+3|2+4|3+4|1+2+3|1+2+4|1+3+4|2+3+4|1+2+3+4',....
      'Value',15,'Units','normalized','Position',[0.195    0.91    0.4    0.032]);%,'CallBack','viz3Dgeo(''changemode'');');
   ud.cut=uicontrol('Style','Popup','String','????.?????.|??? ?????.',....
      'Value',1,'Units','normalized','Position',[0.595    0.91    0.405    0.032]);%,'CallBack','viz3Dgeo(''changemode'');');
   ud.textcolorbar =uicontrol('Style','text','Units','normalized',...
      'Position',[0.01    0.840    0.44    0.03],...
      'ForegroundColor','k','BackgroundColor',figcolor,'String','????. ?????:'); 
   ud.popupcolorbar=uicontrol('Style','Popup','String','????????????|??????????????|???????',....
      'Value',1,'Units','normalized','Position',[0.45    0.850    0.55    0.032],....
      'CallBack', 'viz3Dgeo(''colorbar'');' );
 
 
ud.fig2 = figure('Visible','off','Tag','slicefig');
set(ud.fig2,'Units','Normalized','Backingstore','off','InvertHardcopy','on','PaperPositionMode','auto',...
    'Color',figcolor,'Position',[0.7562    0.3317    0.2388    0.6000]);

   ud.menrange1=uicontrol('Style','Pushbutton','Units','normalized','Position',posui2,...
      'String','?????.??.????.','Callback',['viz3Dgeo(''rangeaxes'',','1',');']);
   ud.menrange2=uicontrol('Style','Pushbutton','Units','normalized','Position',posui2,...
      'String','?????.??.????.?????','Visible','off','Callback',['viz3Dgeo(''rangeaxes'',','2',');']);
   ud.menrange3=uicontrol('Style','Pushbutton','Units','normalized','Position',posui2,...
      'String','?????.???.??.????.','Visible','off','Callback',['viz3Dgeo(''rangeaxes'',','3',');']);
   
   ud.menperspon=uicontrol('Style','Pushbutton','Units','normalized','Position',posui3,...
      'String','???????? ???????????','Callback',['viz3Dgeo(''perspective'',''on'');']);
   ud.menperspoff=uicontrol('Style','Pushbutton','Units','normalized','Position',posui3,...
      'String','????????? ???????????','Visible','off','Callback',['viz3Dgeo(''perspective'',''off'');']);
   
   ud.gridon=uicontrol('Style','Pushbutton','Units','normalized','Position',posui1,...
      'String','???. ?????','Callback',['viz3Dgeo(''grid'',''on'');']);
   ud.gridoff=uicontrol('Style','Pushbutton','Units','normalized','Position',posui1,...
      'String','????.?????','Visible','off','Callback',['viz3Dgeo(''grid'',''off'');']);
   
   ud.lineon=uicontrol('Style','Pushbutton','Units','normalized','Position',posui5,...
      'String','???. line','Visible','off','Callback',['viz3Dgeo(''line'',''on'');']);
   ud.lineoff=uicontrol('Style','Pushbutton','Units','normalized','Position',posui5,...
      'String','????.line','Callback',['viz3Dgeo(''line'',''off'');']);
   
   ud.lighton=uicontrol('Style','Pushbutton','Units','normalized','Position',posui4,...
      'String','???.????','Visible','off','Callback',['viz3Dgeo(''light'',''on'');']);
   ud.lightoff=uicontrol('Style','Pushbutton','Units','normalized','Position',posui4,...
      'String','????.????','Callback',['viz3Dgeo(''light'',''off'');']);
   
   ud.ptextfon =uicontrol('Style','text','Units','normalized',...
      'Position',[.46 .915 .16 .033],...
      'ForegroundColor','k','BackgroundColor',figcolor,'String','???:'); 
   ud.colorfon=uicontrol('Style','Popup','String',...
      '????????|???????|?????????|Ƹ????|???????|?????????????|???????|?????|??????????|??????????|?????|?????|׸????',...
      'Value',11,'Units','normalized',....
      'Position',[.64 .910 .355 .033],'CallBack','viz3Dgeo(''changecolorfon'');');
   ud.begcolorm=uicontrol('Style','Popup','String',...
      '????????|???????|?????????|Ƹ????|???????|?????????????|???????|?????|??????????|??????????|?????|?????|׸????',...
      'Value',8,'Units','normalized',....
      'Position',[.64 .815 .355 .033],'CallBack','viz3Dgeo(''changecolormap'');');
   ud.endcolorm=uicontrol('Style','Popup','String',...
      '????????|???????|?????????|Ƹ????|???????|?????????????|???????|?????|??????????|??????????|?????|?????|׸????',...
      'Value',11,'Units','normalized',....
      'Position',[.64 .775 .355 .033],'CallBack','viz3Dgeo(''changecolormap'');');
   ud.box=uicontrol('Style','Popup','String','BOX OFF|BOX ON',...
      'Value',1,'Units','normalized',....
      'Position',[.0 .02 .4 .033],'CallBack','viz3Dgeo(''box'');');
   ud.axes1fontsize=uicontrol('Style','edit','Units','normalized','Position',[0 0.05 0.3 0.05],...
          'String',num2str(10),'BackgroundColor','white',...
          'CallBack',['viz3Dgeo(''axes1fontsize'');']);
   ud.clabel=uicontrol('Style','Popup','String','without clabel|with clabel',...
      'Value',1,'Units','normalized',....
      'Position',[.0 .32 .52 .033],'CallBack','viz3Dgeo(''box'');');

   ud.slidcolmap1=uicontrol('Style','slider','Units','normalized',...
      'Position',[0.17 .1 .08 .19],'Value',1,'Max',3,'Min',.1,'Callback',['viz3Dgeo(''changecolormap'');']);
   ud.slidcolmap2=uicontrol('Style','slider','Units','normalized',...
      'Position',[0.25 .1 .08 .19],'Value',1,'Max',3,'Min',.1,'Callback',['viz3Dgeo(''changecolormap'');']);
   ud.slidcolmap3=uicontrol('Style','slider','Units','normalized',...
      'Position',[0.09 .1 .08 .19],'Value',1,'Max',1,'Min',0,'Callback',['viz3Dgeo(''changecolormap'');']);
   ud.slidcolmap4=uicontrol('Style','slider','Units','normalized',...
      'Position',[0.01 .1 .08 .19],'Value',1,'Max',1,'Min',.0,'Callback',['viz3Dgeo(''changecolormap'');']);
   ud.slidcolgrid=uicontrol('Style','slider','Units','normalized',...
      'Position',[0.33 .1 .08 .19],'Value',1,'Max',2,'Min',0,'Callback',['viz3Dgeo(''grid'',''color'');']);
   
   ud.slidlight1=uicontrol('Style','slider','Units','normalized',...
      'Position',[0.41 .495 .08 .095],'Value',0,'Max',10,'Min',-10,'Callback',['viz3Dgeo(''light'',''source'');']);
   ud.slidlight2=uicontrol('Style','slider','Units','normalized',...
      'Position',[0.41 .590 .08 .095],'Value',0,'Max',10,'Min',-10,'Callback',['viz3Dgeo(''light'',''source'');']);
   ud.slidlight3=uicontrol('Style','slider','Units','normalized',...
      'Position',[0.41 .685 .08 .095],'Value',0,'Max',10,'Min',-10,'Callback',['viz3Dgeo(''light'',''source'');']);
   
   ud.slidz1=uicontrol('Style','slider','Units','normalized',...
      'Position',[0.51 .01 .08 .23],'Value',0,'Max',1,'Min',0);%,'Callback','viz3Dgeo(''changemode'');');
   ud.slidday=uicontrol('Style','slider','Units','normalized',...
      'Position',[0.59 .01 .08 .23],'Value',1,'Max',1,'Min',0);%,'Callback','viz3Dgeo(''changemode'');');
   ud.slidx1=uicontrol('Style','slider','Units','normalized',...
      'Position',[0.67 .01 .08 .23],'Value',0,'Max',1,'Min',0);%,'Callback','viz3Dgeo(''changemode'');');
   ud.slidx2=uicontrol('Style','slider','Units','normalized',...
      'Position',[0.75 .01 .08 .23],'Value',1,'Max',1,'Min',0);%,'Callback','viz3Dgeo(''changemode'');');
   ud.slidy1=uicontrol('Style','slider','Units','normalized',...
      'Position',[0.83 .01 .08 .23],'Value',0,'Max',1,'Min',0);%,'Callback','viz3Dgeo(''changemode'');');
   ud.slidy2=uicontrol('Style','slider','Units','normalized',...
      'Position',[0.91 .01 .08 .23],'Value',1,'Max',1,'Min',0);%,'Callback','viz3Dgeo(''changemode'');');
   
   
   ud.slidizo(1)=uicontrol('Style','slider','Units','normalized','Visible','off',...
      'Position',[0.51 .01 .08 .23],'Value',0.2,'Max',1,'Min',0,'Callback',['viz3Dgeo(''izosurface'',' '1' ');']);
   ud.slidizo(2)=uicontrol('Style','slider','Units','normalized','Visible','off',...
      'Position',[0.59 .01 .08 .23],'Value',0.3,'Max',1,'Min',0,'Callback',['viz3Dgeo(''izosurface'',' '2' ');']);
   ud.slidizo(3)=uicontrol('Style','slider','Units','normalized','Visible','off',...
      'Position',[0.67 .01 .08 .23],'Value',0.4,'Max',1,'Min',0,'Callback',['viz3Dgeo(''izosurface'',' '3' ');']);
   ud.slidizo(4)=uicontrol('Style','slider','Units','normalized','Visible','off',...
      'Position',[0.75 .01 .08 .23],'Value',0.5,'Max',1,'Min',0,'Callback',['viz3Dgeo(''izosurface'',' '4' ');']);
   ud.slidizo(5)=uicontrol('Style','slider','Units','normalized','Visible','off',...
      'Position',[0.83 .01 .08 .23],'Value',0.6,'Max',1,'Min',0,'Callback',['viz3Dgeo(''izosurface'',' '5' ');']);
   ud.slidizo(6)=uicontrol('Style','slider','Units','normalized','Visible','off',...
      'Position',[0.91 .01 .08 .23],'Value',0.7,'Max',1,'Min',0,'Callback',['viz3Dgeo(''izosurface'',' '6' ');']);
 
 
   ud.ptextmap =uicontrol('Style','text','Units','normalized',...
      'Position',[.465 .965 .205 .033],...
      'ForegroundColor','k','BackgroundColor',figcolor,'String','???.'); 
   ud.colormap=uicontrol('Style','Popup','String',...
      'hsv|hot|gray|bone|copper|pink|white|flag|lines|colorcube|vga|jet|prism|cool|autumn|spring|winter|summer|"default"|???.???.??',....
      'Value',2,'Units','normalized',....
      'Position',[.665 .96 .315 .033],'CallBack','viz3Dgeo(''changecolormap'');');
   
   ud.invcolormap=uicontrol('Style','Popup','String',...
      'inverse colormap|matlab colormap',....
      'Value',1,'Units','normalized',....
      'Position',[.665 .86 .515 .033],'CallBack','viz3Dgeo(''changecolormap'');');
   
   ud.lightmode=uicontrol('Style','Popup','String',...
      'HEADLIGHT|RIGHT|LEFT|local|infinite|FLAT|GOURAUD|PHONG|NONE',....
      'Value',1,'Units','normalized','Position',[.64 .698 .355 .030],'CallBack',['viz3Dgeo(''light'',''mode'');']);
   
   
%   ???????? ?????? ??? ??????

ud.fig3 = figure('Visible','off','Tag','slicefig3');
set(ud.fig3,'Units','Normalized','Backingstore','off','InvertHardcopy','on','PaperPositionMode','auto',...
   'Color',figcolor,'Position',[0.0438    0.0500    0.8463    0.2050]);

ud.textizolines=uicontrol('Style','text','Units','normalized',...
      'Position',[.05 .82 .4 .15],...
   'ForegroundColor','k','BackgroundColor',figcolor,...
   'String','????????? ????????'); 
  
ud.editizolines=uicontrol('Style','edit','Units','normalized',...
      'Position',[.05 .7 .4 .15],...
      'String', ' -6  -5  -4  -3  -2  -1  0 ','BackgroundColor','white');
ud.textizosurf=uicontrol('Style','text','Units','normalized',...
      'Position',[.5 .82 .4 .15],...
   'ForegroundColor','k','BackgroundColor',figcolor,...
   'String','?????????????? ?????????? ????????????'); 
   
ud.editizosurf=uicontrol('Style','edit','Units','normalized',...
      'Position',[.5 .7 .4 .15],...
      'String', num2str([-6 -5 -4 -3 -2 -1  0]),'BackgroundColor','white');
   
   
   
ud.textXslices=uicontrol('Style','text','Units','normalized',...
      'Position',[.03 .52 .29 .15],...
   'ForegroundColor','k','BackgroundColor',figcolor,...
   'String','??????? ???????????????? ??? X'); 
ud.editXslices=uicontrol('Style','edit','Units','normalized',...
      'Position',[.03 .4 .29 .15],...
      'String', num2str([  ]),'BackgroundColor','white');
   
ud.textYslices=uicontrol('Style','text','Units','normalized',...
      'Position',[.33 .52 .29 .15],...
   'ForegroundColor','k','BackgroundColor',figcolor,...
   'String','??????? ???????????????? ??? Y'); 
   
ud.editYslices=uicontrol('Style','edit','Units','normalized',...
      'Position',[.33 .4 .29 .15],...
      'String', num2str([  ]),'BackgroundColor','white');
ud.textZslices=uicontrol('Style','text','Units','normalized',...
      'Position',[.63 .52 .29 .15],...
   'ForegroundColor','k','BackgroundColor',figcolor,...
   'String','??????? ???????????????? ??? Z'); 
   
ud.editZslices=uicontrol('Style','edit','Units','normalized',...
      'Position',[.63 .4 .29 .15],...
      'String', num2str([-8 -7 -6 -5 -4 -3 -2 -1  0]),'BackgroundColor','white');
ud.text1=uicontrol('Style','text','Units','normalized',...
      'Position',[0 .22 .26 .15],...
   'ForegroundColor','k','BackgroundColor',figcolor,...
   'String','??? ?????,??????.V-???????'); 
   
ud.edit1=uicontrol('Style','edit','Units','normalized',...
      'Position',[.02 .1 .22 .15],...
      'String', ud.FILENAME,'BackgroundColor','white');
   
ud.text2=uicontrol('Style','text','Units','normalized',...
      'Position',[.265 .22 .16 .15],...
   'ForegroundColor','k','BackgroundColor',figcolor,...
   'String','?????? V-???????'); 
   
ud.edit2=uicontrol('Style','edit','Units','normalized',...
      'Position',[.27 .1 .15 .15],...
      'String', num2str([size(ud.V)]),'BackgroundColor','white');
   
ud.nlabel=1; % ??????????, ????????????, ??? ?????????????:title xlabel ylabel ??? zlabel
title_button = uicontrol('Style','Pushbutton','Units','normalized',...
   'Position',[.465 .22 .2 .15],'Callback','viz3Dgeo(''title'');',...
   'String','????????? ???????');
xlabel_button = uicontrol('Style','Pushbutton','Units','normalized',...
   'Position',[.665 .22 .1 .15],'Callback','viz3Dgeo(''xlabel'');',...
   'String','X ???????');
ylabel_button = uicontrol('Style','Pushbutton','Units','normalized',...
   'Position',[.765 .22 .1 .15],'Callback','viz3Dgeo(''ylabel'');',...
   'String','Y ???????');
zlabel_button = uicontrol('Style','Pushbutton','Units','normalized',...
   'Position',[.865 .22 .1 .15],'Callback','viz3Dgeo(''zlabel'');',...
   'String','Z ???????');
ud.edit3=uicontrol('Style','edit','Units','normalized',...
      'Position',[.435 .1 .55 .15],...
      'String', num2str([  ]),'BackgroundColor','white','Callback','viz3Dgeo(''edit_title_label'');');
   
   % ???????? ?????? ??? ????????   
ud.fig4 = figure('Visible','off','Tag','slicefig2');
set(ud.fig4,'Units','Normalized','Backingstore','off','InvertHardcopy','on','PaperPositionMode','auto',...
   'Color',[1 1 1],'Colormap',hot,'Position',[0.0438    0.1750    0.7050    0.7050]);
%set(ud.fig4,'Position',[0.105  0.15    0.89  0.75])
% ???????? ????
ud.axiscolor = [1 1 1];  
ud.c=colormap;
ud.axes1 = axes;
ud.per=0;
set(ud.axes1,'Color',ud.axiscolor,'NextPlot','add','DrawMode','fast',...
   'XLim',ud.xrange,'YLim',ud.yrange,'ZLim',ud.zrange,...
   'Box','off','View',[-30 45],....%'XDir','reverse',...
   'Projection','orthographic');% perspective;orthographic
ud.gridcolor=[0 0 1];
ud.title_label1{1}='?????????? ??????';
ud.title_label1{2}='X-??????????';
ud.title_label1{3}='Y-??????????';
ud.title_label1{4}='Z-??????????';
title(ud.title_label1(1));
xlabel(ud.title_label1(2));
ylabel(ud.title_label1(3));
zlabel(ud.title_label1(4));
set(ud.edit3,'String',ud.title_label1(1));
%???????? ???????
cla(ud.axes1);
ud.grid=0;
ud.h=[];
%ud = changemode(ud);%colorbar;
%ud=changecolormap(ud);

%ud = makefill3surfl(ud);

ud.e=ude;

set([ud.fig2:ud.fig4 ud.fig1],'Visible','on');

end % if strcmp(action,'start')


if ~isempty(gcbf) | strcmp(action,'start'),
set(ud.fig1,'UserData',ud);
set(ud.fig2,'UserData',ud.fig1);
set(ud.fig3,'UserData',ud.fig1);
set(ud.fig4,'UserData',ud.fig1);
end
% End of initialization.

% END OF viz3Geo MAIN FUNCTION.







% BEGIN HELPER  FUNCTIONS.
function ud = newbord(ud);
% ?????? ????????? ?????????
ud.xbord(1)=min(find(abs((ud.x-str2num(get(ud.lohndl(1),'String')) )/ud.dx)<1));
ud.xbord(2)=max(find(abs((ud.x-str2num(get(ud.hihndl(1),'String')) )/ud.dx)<1));

ud.ybord(1)=min(find(abs((ud.y-str2num(get(ud.lohndl(2),'String')) )/ud.dy)<1));
ud.ybord(2)=max(find(abs((ud.y-str2num(get(ud.hihndl(2),'String')) )/ud.dy)<1));

ud.zbord(1)=min(find(abs((ud.z-str2num(get(ud.lohndl(3),'String')) )/ud.dz)<1));
ud.zbord(2)=max(find(abs((ud.z-str2num(get(ud.hihndl(3),'String')) )/ud.dz)<1));
%-------------------------------------------
function ud = newrange(ud);
% ???????????? ??????? ?????????? ???? ???????:
switch ud.ra
%      ??????? 1: ??????? ?? ???? ???? ????????:
case 1
kmax=max([ud.x(ud.xbord(2)) ud.y(ud.ybord(2)) ud.z(ud.zbord(2))]);
kmin=min([ud.x(ud.xbord(1)) ud.y(ud.ybord(1)) ud.z(ud.zbord(1))]);
ud.xrange = [kmin kmax]+ud.x(ud.xbord(1))-kmin;
ud.yrange = [kmin kmax]+ud.y(ud.ybord(1))-kmin;
ud.zrange = [kmin kmax]+ud.z(ud.zbord(1))-kmin;

set(ud.menrange1,'Visible','off');
set(ud.menrange2,'Visible','on');
case 2
%      ??????? 2: ??????? ?? ???? ???? ??????????: 
ud.xrange = [ud.x(ud.xbord(1)) ud.x(ud.xbord(2))];
ud.yrange = [ud.y(ud.ybord(1)) ud.y(ud.ybord(2))];
ud.zrange = [ud.z(ud.zbord(1)) ud.z(ud.zbord(2))];

set(ud.menrange2,'Visible','off');
set(ud.menrange3,'Visible','on');
case 3
%      ??????? 3: ??????? ?? ?????????????? ???? ????????: 
%kmax=max([ud.x(ud.xbord(2)) ud.y(ud.ybord(2))]);
%kmin=min([ud.x(ud.xbord(1)) ud.y(ud.ybord(1))]);
dmax=max([ud.x(ud.xbord(2))-ud.x(ud.xbord(1)) ud.y(ud.ybord(2))-ud.y(ud.ybord(1))]);
ud.xrange = [ud.x(ud.xbord(1)) ud.x(ud.xbord(1))+dmax];
ud.yrange = [ud.y(ud.ybord(1)) ud.y(ud.ybord(1))+dmax];
ud.zrange = [ud.z(ud.zbord(1)) ud.z(ud.zbord(2))];
set(ud.menrange3,'Visible','off');
set(ud.menrange1,'Visible','on');
end;
set(ud.axes1,'XLim',ud.xrange,'YLim',ud.yrange,'ZLim',ud.zrange);

% -----------------------------------------
function ud = newdata(ud)
% ???????????? ??????? ?????????? ??????? ? ??????????????
if ud.flunviz(1)==1; ud.newxyzv{1}=str2double(get(ud.pfhndl(1),'String'));elseif ud.flunviz(1)==0; ud.newxyzv{1}=[];end;
if ud.flunviz(2)==1; ud.newxyzv{2}=str2double(get(ud.pfhndl(2),'String'));elseif ud.flunviz(2)==0; ud.newxyzv{2}=[];end;
if ud.flunviz(3)==1; ud.newxyzv{3}=str2double(get(ud.pfhndl(3),'String'));elseif ud.flunviz(3)==0; ud.newxyzv{3}=[];end;
if ud.flunviz(4)==1; ud.newxyzv{4}=str2double(get(ud.pfhndl(4),'String'));elseif ud.flunviz(4)==0; ud.newxyzv{4}=[];end;
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function ud = makeslice3cont(ud)
ud = newdata(ud);

if ud.flunviz(4)==1;
ud.p = patch(isosurface(ud.x(ud.xbord(1):ud.xbord(2)),...
   ud.y(ud.ybord(1):ud.ybord(2)),...
   ud.z(ud.zbord(1):ud.zbord(2)),...
   ud.V(ud.ybord(1):ud.ybord(2),ud.xbord(1):ud.xbord(2),ud.zbord(1):ud.zbord(2)),...
   ud.newxyzv{4}));
ud.p2 = patch(isocaps(ud.x(ud.xbord(1):ud.xbord(2)),...
   ud.y(ud.ybord(1):ud.ybord(2)),...
   ud.z(ud.zbord(1):ud.zbord(2)),...
   ud.V(ud.ybord(1):ud.ybord(2),ud.xbord(1):ud.xbord(2),ud.zbord(1):ud.zbord(2)),...
   ud.newxyzv{4}));
set(ud.p2, 'FaceColor', 'interp', 'EdgeColor', 'none');
disp(['?????????????? ?????? ????????????1 = ' num2str(ud.newxyzv{4}) '% ????']);
isonormals(ud.x(ud.xbord(1):ud.xbord(2)),...
   ud.y(ud.ybord(1):ud.ybord(2)),...
   ud.z(ud.zbord(1):ud.zbord(2)),...
   ud.V(ud.ybord(1):ud.ybord(2),ud.xbord(1):ud.xbord(2),ud.zbord(1):ud.zbord(2)),...
   ud.p);
colorizosurf=ud.c(fix(1+63*(ud.newxyzv{4}-ud.minv)/(ud.maxv-ud.minv)),:);
set(ud.p, 'FaceColor', colorizosurf, 'EdgeColor', 'none');
%ud.h=[ud.h; ud.p];
camlight; lighting phong;

end;


[ud.newxyzv{1}],[ud.newxyzv{2}],[ud.newxyzv{3}]

ud.dslice = slice3cont(ud.x(ud.xbord(1):ud.xbord(2)),...
   ud.y(ud.ybord(1):ud.ybord(2)),...
   ud.z(ud.zbord(1):ud.zbord(2)),...
   ud.V(ud.ybord(1):ud.ybord(2),ud.xbord(1):ud.xbord(2),ud.zbord(1):ud.zbord(2)),...
   [ud.newxyzv{1}],[ud.newxyzv{2}],[ud.newxyzv{3}]);
%shading interp;
ud.h=[ud.h; ud.dslice];
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

%camlight;

% LIGHTING Lighting mode.
%    LIGHTING controls the lighting of SURFACE and PATCH objects.
%    SURFACE and PATCH objects are created by the functions SURF, MESH,
%    PCOLOR, FILL, and FILL3. 
% 
%    LIGHTING FLAT sets the lighting of the current graph to flat.
%    LIGHTING GOURAUD sets the lighting to gouraud.
%    LIGHTING PHONG sets the lighting to phong.
%    LIGHTING NONE turns off lighting.
 
%lighting phong;

% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-----------------------------

% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-----------------------------

% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function ud = makeline(ud)
ud = newdata(ud);
if ud.flunviz(2)==1 & ud.flunviz(3)==1
ud.linex=line([ud.x(ud.xbord(1)),ud.x(ud.xbord(2))],[ud.newxyzv{2} ud.newxyzv{2}],...
   [ud.newxyzv{3} ud.newxyzv{3}]);
end
if ud.flunviz(1)==1 & ud.flunviz(3)==1
ud.liney=line([ud.newxyzv{1} ud.newxyzv{1}],[ud.y(ud.ybord(1)),ud.y(ud.ybord(2))],...
   [ud.newxyzv{3} ud.newxyzv{3}]);
end
if ud.flunviz(1)==1 & ud.flunviz(2)==1
ud.linez=line([ud.newxyzv{1} ud.newxyzv{1}],...
   [ud.newxyzv{2} ud.newxyzv{2}],[ud.z(ud.zbord(1)),ud.z(ud.zbord(2))]);
end


function ud = makeslice(ud)
ud = newdata(ud);
% ud.dslice = slice(ud.x(ud.xbord(1):ud.xbord(2)),...
%    ud.y(ud.ybord(1):ud.ybord(2)),...
%    ud.z(ud.zbord(1):ud.zbord(2)),...
%    ud.V(ud.ybord(1):ud.ybord(2),ud.xbord(1):ud.xbord(2),ud.zbord(1):ud.zbord(2)),...
%    [ud.newxyzv{1}],[ud.newxyzv{2}],[ud.newxyzv{3}]);
% shading interp;
% ud.h=[ud.h; ud.dslice];
% ud = makeline(ud)
if ud.flunviz(4)==1;
ud.p = patch(isosurface(ud.x(ud.xbord(1):ud.xbord(2)),...
   ud.y(ud.ybord(1):ud.ybord(2)),...
   ud.z(ud.zbord(1):ud.zbord(2)),...
   ud.V(ud.ybord(1):ud.ybord(2),ud.xbord(1):ud.xbord(2),ud.zbord(1):ud.zbord(2)),...
   ud.newxyzv{4}));
ud.p2 = patch(isocaps(ud.x(ud.xbord(1):ud.xbord(2)),...
   ud.y(ud.ybord(1):ud.ybord(2)),...
   ud.z(ud.zbord(1):ud.zbord(2)),...
   ud.V(ud.ybord(1):ud.ybord(2),ud.xbord(1):ud.xbord(2),ud.zbord(1):ud.zbord(2)),...
   ud.newxyzv{4}));
set(ud.p2, 'FaceColor', 'interp', 'EdgeColor', 'none');
disp(['?????????????? ?????? ????????????2 = ' num2str(ud.newxyzv{4}) '% ????']);

colorizosurf=ud.c(fix(1+63*(ud.newxyzv{4}-ud.minv)/(ud.maxv-ud.minv)),:);
set(ud.p, 'FaceColor', colorizosurf, 'EdgeColor', 'none');
% colormap(ud.colormap);
% camlight; lighting gouraud
isonormals(ud.x(ud.xbord(1):ud.xbord(2)),...
   ud.y(ud.ybord(1):ud.ybord(2)),...
   ud.z(ud.zbord(1):ud.zbord(2)),...
   ud.V(ud.ybord(1):ud.ybord(2),ud.xbord(1):ud.xbord(2),ud.zbord(1):ud.zbord(2)),...
   ud.p);ud.h=[ud.h; ud.p];
end;

camlight; lighting phong;

% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-----------------------------
function ud = makesurfl(squ,f1,f2,src,ud);%src=0,1
if squ ~=0

if ud.flunviz(1)==1; 
   bx=max(find(abs((ud.x-str2num(get(ud.pfhndl(1),'String')) )/ud.dx)<1));
elseif ud.flunviz(1)==0;
   bx=ud.xbord(2);
end;

if ud.flunviz(2)==1;
   by=min(find(abs((ud.y-str2num(get(ud.pfhndl(2),'String')) )/ud.dy)<1));
elseif ud.flunviz(2)==0
   by=ud.ybord(2);
end;

axes(ud.axes1);
switch squ
case 1
   for jj=f1:f2 %:ud.nstratum
   H=surfl(ud.x(ud.xbord(1):bx),ud.y(ud.ybord(1):by),...
      ud.Zs{jj}(ud.ybord(1):by,ud.xbord(1):bx));
   ud.h=[ud.h; H];
   if src==0 
   CDt=ud.Vs{jj}(ud.ybord(1):by,ud.xbord(1):bx);
   CDt(find(~isfinite(ud.Zs{jj}(ud.ybord(1):by,ud.xbord(1):bx))))=NaN;
   set(H,'CData',CDt);
   end
   HH{jj}=H;
end
case 2
   for jj=f1:f2 %:ud.nstratum
   H=surfl(ud.x(ud.xbord(1):bx),ud.y(by:ud.ybord(2)),...
      ud.Zs{jj}(by:ud.ybord(2),ud.xbord(1):bx));
   ud.h=[ud.h; H];
   if src==0 
   CDt=ud.Vs{jj}(by:ud.ybord(2),ud.xbord(1):bx);
   CDt(find(~isfinite(ud.Zs{jj}(by:ud.ybord(2),ud.xbord(1):bx))))=NaN;
   set(H,'CData',CDt);
   end
HH{jj}=H;
end
case 3
   for jj=f1:f2 %:ud.nstratum
   H=surfl(ud.x(bx:ud.xbord(2)),ud.y(ud.ybord(1):by),...
      ud.Zs{jj}(ud.ybord(1):by,bx:ud.xbord(2)));
   ud.h=[ud.h; H];
   if src==0 
   CDt=ud.Vs{jj}(ud.ybord(1):by,bx:ud.xbord(2));
   CDt(find(~isfinite(ud.Zs{jj}(ud.ybord(1):by,bx:ud.xbord(2)))))=NaN;
   set(H,'CData',CDt);
   end
   HH{jj}=H;
end
case 4
   for jj=f1:f2 %:ud.nstratum
   H=surfl(ud.x(bx:ud.xbord(2)),ud.y(by:ud.ybord(2)),...
      ud.Zs{jj}(by:ud.ybord(2),bx:ud.xbord(2)));
   ud.h=[ud.h; H];
   if src==0 
   CDt=ud.Vs{jj}(by:ud.ybord(2),bx:ud.xbord(2));
   CDt(find(~isfinite(ud.Zs{jj}(by:ud.ybord(2),bx:ud.xbord(2)))))=NaN;
   set(H,'CData',CDt);
   end
   HH{jj}=H;
end
end

if ud.grid==1;
for jj=f1:f2 % :ud.nstratum
   set(HH{jj},'EdgeColor','none','FaceColor','interp');
end
end
end
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-----------------------------

function ud=makefill3(p,f1,f2,ud);
for zi=f1:f2 %ud.nstratum
   [yi,xi] = find(isfinite(ud.Zs{zi}));
   Yi{zi}=yi;
   Xi{zi}=xi;
end

clear yi xi;
xn=max(find(abs((ud.x-str2num(get(ud.pfhndl(1),'String')) )/ud.dx)<1));
yn=min(find(abs((ud.y-str2num(get(ud.pfhndl(2),'String')) )/ud.dy)<1));
% -----------------------
%ud.line=line([ud.x(xn) ud.x(xn)],...
%   [ud.y(yn) ud.y(yn)],[ud.Zs{1}(yn,xn) ud.Zs{ud.nstratum}(yn,xn)],'Color',[0 0 0]);
if p(1)==1
% -----------------------
for zi=f1:f2% ud.nstratum
   fy=find((Yi{zi}==yn)&(Xi{zi}>=xn));
for q=1:length(fy)
   zz{zi}(q)=ud.Zs{zi}(Yi{zi}(fy(q)),Xi{zi}(fy(q)));
   xx{zi}(q)=ud.x(Xi{zi}(fy(q)));
   yy{zi}(q)=ud.y(Yi{zi}(fy(q)));
end
end

for zi=fliplr(f1:f2-1)%ud.nstratum-1)
colorfill=ud.c(fix(1+63*(zi-0)/(ud.nstratum-0)),:);
fily=fill3([xx{zi} fliplr(xx{zi+1})],[yy{zi} fliplr(yy{zi+1})],[zz{zi} fliplr(zz{zi+1})],colorfill,'EdgeColor','none','Parent',ud.axes1);
ud.h=[ud.h; fily];
end
clear xx yy zz fi;
% -----------------------
end

if p(2)==1
% -----------------------
clear xx yy zz;
for zi=f1:f2 %ud.nstratum
   fx=find((Xi{zi}==xn)&(Yi{zi}>=yn));
   for q=1:length(fx)
   zz{zi}(q)=ud.Zs{zi}(Yi{zi}(fx(q)),Xi{zi}(fx(q)));
   xx{zi}(q)=ud.x(Xi{zi}(fx(q)));
   yy{zi}(q)=ud.y(Yi{zi}(fx(q)));
end
end

for zi=fliplr(f1:f2-1)%ud.nstratum-1)
colorfill=ud.c(fix(1+63*(zi-0)/(ud.nstratum-0)),:);
filx=fill3([xx{zi} fliplr(xx{zi+1})],[yy{zi} fliplr(yy{zi+1})],[zz{zi} fliplr(zz{zi+1})],colorfill,'EdgeColor','none','Parent',ud.axes1);
ud.h=[ud.h; filx];
end
clear xx yy zz fi;
% -----------------------
end

if p(3)==1
% -----------------------
for zi=f1:f2 %ud.nstratum
   fy=find((Yi{zi}==yn)&(Xi{zi}<=xn));
for q=1:length(fy)
   zz{zi}(q)=ud.Zs{zi}(Yi{zi}(fy(q)),Xi{zi}(fy(q)));
   xx{zi}(q)=ud.x(Xi{zi}(fy(q)));
   yy{zi}(q)=ud.y(Yi{zi}(fy(q)));
end
end
for zi=fliplr(f1:f2-1)%ud.nstratum-1)
colorfill=ud.c(fix(1+63*(zi-0)/(ud.nstratum-0)),:);
fily=fill3([xx{zi} fliplr(xx{zi+1})],[yy{zi} fliplr(yy{zi+1})],[zz{zi} fliplr(zz{zi+1})],colorfill,'Parent',ud.axes1);
ud.h=[ud.h; fily];
end
clear xx yy zz fi;
% -----------------------
end

if p(4)==1
% -----------------------
clear xx yy zz;
for zi=f1:f2%ud.nstratum
   fx=find((Xi{zi}==xn)&(Yi{zi}<=yn));
   for q=1:length(fx)
   zz{zi}(q)=ud.Zs{zi}(Yi{zi}(fx(q)),Xi{zi}(fx(q)));
   xx{zi}(q)=ud.x(Xi{zi}(fx(q)));
   yy{zi}(q)=ud.y(Yi{zi}(fx(q)));
end
end

for zi=fliplr(f1:f2-1)%ud.nstratum-1)
colorfill=ud.c(fix(1+63*(zi-0)/(ud.nstratum-0)),:);
filx=fill3([xx{zi} fliplr(xx{zi+1})],[yy{zi} fliplr(yy{zi+1})],[zz{zi} fliplr(zz{zi+1})],colorfill,'Parent',ud.axes1);
ud.h=[ud.h; filx];
end
% -----------------------
end

clear xx yy zz fi;
% #######################################################
% END HELPER  FUNCTIONS.

% BEGIN CALLBACK FUNCTIONS.
% Callback for controlling lower bound of the parameters using editable text boxes.
function ud = setplo(fieldno,ud,newx)
cv  = str2double(get(ud.lohndl(fieldno),'String'));
pv   = str2double(get(ud.pfhndl(fieldno),'String'));
vmin = ud.minmax{fieldno}(1);
vmax = ud.minmax{fieldno}(2);
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
    %ud = changemode(ud); 
elseif cv >= vmax
   set(ud.lohndl(fieldno),'String',get(ud.pslider(fieldno),'Min'));
else
   set(ud.lohndl(fieldno),'String',num2str(ud.minmax{fieldno}(1)));
end
ud=newbord(ud);
ud=newrange(ud);
%ud=changemode(ud);

% Callback for controlling upper bound of the parameters using editable text boxes.
function ud = setphi(fieldno,ud,newx)
cv = str2double(get(ud.hihndl(fieldno),'String'));
pv = str2double(get(ud.pfhndl(fieldno),'String'));

vmin = ud.minmax{fieldno}(1);
vmax = ud.minmax{fieldno}(2);

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
    %ud = changemode(ud); 
elseif cv <= vmax
   set(ud.hihndl(fieldno),'String',get(ud.pslider(fieldno),'Max'));
else
    set(ud.hihndl(fieldno),'String',num2str(ud.minmax{fieldno}(2)));
end
ud = newbord(ud);
ud=newrange(ud);
%ud = changemode(ud);

% Callback for controlling the parameter values using sliders.
function ud = setpslider(sliderno,ud)

cv = get(ud.pslider(sliderno),'Value');
set(ud.pfhndl(sliderno),'String',num2str(cv));
ud = newbord(ud);
ud = newrange(ud);
%ud = changemode(ud); 

% Callback for controlling the parameter values using editable text boxes.
function ud = setpfield(fieldno,ud)
cv = str2double(get(ud.pfhndl(fieldno),'String'));
vmin = ud.minmax{fieldno}(1);
vmax = ud.minmax{fieldno}(2);
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
ud = newbord(ud);
ud = newrange(ud);
%ud = changemode(ud); 
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
%ud = changemode(ud);
% --------------------------------
function  ud=unviz(idx,ud);

ud.flunviz(idx)=0;
set(ud.unviz(idx),'Visible','off');set(ud.viz(idx),'Visible','on');
set(ud.pfhndl(idx),'Visible','off');
set(ud.hihndl(idx),'Visible','off');
set(ud.lohndl(idx),'Visible','off');
set(ud.pslider(idx),'Visible','off');
%ud = changemode(ud);
% --------------------------------
function ud=changecolorfon(ud)
colorfonvalue = get(ud.colorfon,'Value');
switch colorfonvalue
case 1,   ud.axiscolor =[0.45 0.5 0.2];  % ????????
case 2,   ud.axiscolor ='red';           % ???????
case 3,   ud.axiscolor =[1 0.5 0];       % ?????????
case 4,   ud.axiscolor ='yellow';        % Ƹ????
case 5,   ud.axiscolor ='green';         % ???????
case 6,   ud.axiscolor =[127/255 1 212/255]; % ?????????????
case 7,   ud.axiscolor = [0 1 1];        % ???????
case 8,   ud.axiscolor ='blue';          % ?????
case 9,   ud.axiscolor =[0.75  0   0.75]; % ??????????
case 10,   ud.axiscolor =[ 0.4365 0.2728 0.1737];     % ??????????
case 11,   ud.axiscolor =[1 1 1];         % ?????
case 12,   ud.axiscolor =[0.8 0.8 0.8];   % ?????
case 13,   ud.axiscolor =[0.01 0.01 0.01];   % ׸????
end
set(ud.axes1,'Color',ud.axiscolor);

% --------------------------------
function ud=changecolormap(ud)

colormapvalue = get(ud.colormap,'Value');
invcolormapvalue = get(ud.invcolormap,'Value');
begcolormvalue=get(ud.begcolorm,'Value');
endcolormvalue=get(ud.endcolorm,'Value');
gamma1=get(ud.slidcolmap1,'Value');gamma2=get(ud.slidcolmap2,'Value');
k1=get(ud.slidcolmap3,'Value');k2=get(ud.slidcolmap4,'Value');

switch begcolormvalue
case 1,  bc =[0.45 0.5 0.2];  % ????????
case 2,  bc =[1 0 0];           % ???????
case 3,  bc =[1 0.5 0];       % ?????????
case 4,  bc =[1 1 0];        % Ƹ????
case 5,  bc =[0 1 0];         % ???????
case 6,  bc =[127/255 1 212/255]; % ?????????????
case 7,  bc =[0 1 1];        % ???????
case 8,  bc =[0 0 1];          % ?????
case 9,  bc =[0.75  0   0.75]; % ??????????
case 10, bc =[ 0.4365 0.2728 0.1737];     % ??????????
case 11, bc =[1 1 1];         % ?????
case 12, bc =[0.8 0.8 0.8];   % ?????
case 13, bc =[0.01 0.01 0.01];   % ׸????
end

switch endcolormvalue
case 1,  ec =[0.45 0.5 0.2];  % ????????
case 2,  ec =[1 0 0];           % ???????
case 3,  ec =[1 0.5 0];       % ?????????
case 4,  ec =[1 1 0];        % Ƹ????
case 5,  ec =[0 1 0];         % ???????
case 6,  ec =[127/255 1 212/255]; % ?????????????
case 7,  ec =[0 1 1];        % ???????
case 8,  ec =[0 0 1];          % ?????
case 9,  ec =[0.75  0   0.75]; % ??????????
case 10, ec =[ 0.4365 0.2728 0.1737];     % ??????????
case 11, ec =[1 1 1];         % ?????
case 12, ec =[0.8 0.8 0.8];   % ?????
case 13, ec =[0.01 0.01 0.01];   % ׸????
end

switch colormapvalue
case 1,   c0 =hsv;%        - Hue-saturation-value color map.
case 2,   c0 =hot;%        - Black-red-yellow-white color map.
case 3,   c0 =gray;%       - Linear gray-scale color map.
case 4,   c0 =bone;%       - Gray-scale with tinge of blue color map.
case 5,   c0 =copper;%     - Linear copper-tone color map.
case 6,   c0 =pink;%       - Pastel shades of pink color map.
case 7,   c0 =white;%      - All white color map.
case 8,   c0 =flag;%       - Alternating red, white, blue, and black color map.
case 9,   c0 =lines;%      - Color map with the line colors.
case 10,   c0 =colorcube;%  - Enhanced color-cube color map.
case 11,   c0 =vga;%        - Windows colormap for 16 colors.
case 12,   c0 =jet;%        - Variant of HSV.
case 13,   c0 =prism;%      - Prism color map. 
case 14,   c0 =cool;%       - Shades of cyan and magenta color map.
case 15,   c0 =autumn;%     - Shades of red and yellow color map.
case 16,   c0 =spring;%     - Shades of magenta and yellow color map.
case 17,   c0 =winter;%     - Shades of blue and green color map.
case 18,   c0 =summer;%     - Shades of green and yellow color map.
case 19,   c0 =jet;% .
case 20,v1=k1*(((0:63)'/63).^gamma1);v2=k2*(((0:63)'/63).^gamma2);
   c0=(v1*ec+flipud(v2)*bc);c0(find(c0<0))=0;c0(find(c0>1))=1;
end
if invcolormapvalue==1
   ud.c=flipud(c0);
else
   ud.c=c0;
end
set(ud.fig4, 'Colormap', ud.c);
if ((get(ud.mode,'Value')==1)|(get(ud.mode,'Value')==5)) & ud.flunviz(4)==1
   colorizosurf=ud.c(fix(1+63*(ud.newxyzv{4}-ud.minv)/(ud.maxv-ud.minv)),:);
   set(ud.p, 'FaceColor', colorizosurf);
end

if get(ud.mode,'Value')==14
   for niz=1:length(ud.izov)
      ncm=fix(1+63*(ud.izov(niz)-ud.minv)/(ud.maxv-ud.minv));
      if ncm<1,ncm=1;elseif ncm>64,ncm=64;end
      colorizosurf=ud.c(ncm,:);
      set(ud.izo(niz),'FaceColor',colorizosurf);
   end
end
% --------------------------------
function  ud=changemode(ud);
%'slice|fill3|surfl|fill3+surfl|slice3cont|surfl+slice3cont|surf+slice|one surf|slice(surface)|cub_slice3cont|cut_slice|cut_slice3|izosurface'
modevalue = get(ud.mode,'Value');
squvalue = get(ud.squ,'Value');

pfx=str2double(get(ud.pfhndl(1),'String'));
hix=str2double(get(ud.hihndl(1),'String'));
lox=str2double(get(ud.lohndl(1),'String'));
pfy=str2double(get(ud.pfhndl(2),'String'));
hiy=str2double(get(ud.hihndl(2),'String'));
loy=str2double(get(ud.lohndl(2),'String'));
pfz=str2double(get(ud.pfhndl(3),'String'));
hiz=str2double(get(ud.hihndl(3),'String'));
loz=str2double(get(ud.lohndl(3),'String'));
switch modevalue
case 1 %slice
   figure(ud.fig4);cla(ud.axes1);ud.h=[];hold on;ud = makeslice(ud);
case 2 %fill3
   figure(ud.fig4);cla(ud.axes1);ud.h=[];hold on;p=[1 1 1 1];ud = makefill3(p,f1,f2,ud);
case 3 %surfl
   figure(ud.fig4);cla(ud.axes1);ud.h=[];hold on;
   f1=1;
   f2=1+round((ud.nstratum-1)*((pfz-loz)/(hiz-loz)));
   src=0;
   switch squvalue
   case 1,  squ=0;ud=makesurfl(squ,f1,f2,src,ud);
   case 2,  squ=1;ud=makesurfl(squ,f1,f2,src,ud);
   case 3,  squ=2;ud=makesurfl(squ,f1,f2,src,ud);
   case 4,  squ=3;ud=makesurfl(squ,f1,f2,src,ud);
   case 5,  squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   case 6, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=2;ud=makesurfl(squ,f1,f2,src,ud);
   case 7, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);
   case 8, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   case 9, squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);
   case 10,squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   case 11,squ=3;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   case 12, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);
   case 13, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   case 14, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   case 15, squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   case 16,squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   end
case 4 % fill3+surfl
   figure(ud.fig4);cla(ud.axes1);ud.h=[];hold on;
   f1=1;
   f2=1+round((ud.nstratum-1)*((pfz-loz)/(hiz-loz)));
   src=1;
   switch squvalue
   case 1,  squ=0;ud=makesurfl(squ,f1,f2,src,ud);p=[1 1 1 1];
   case 2,  squ=1;ud=makesurfl(squ,f1,f2,src,ud);p=[0 0 1 1];
   case 3,  squ=2;ud=makesurfl(squ,f1,f2,src,ud);p=[0 1 1 0];
   case 4,  squ=3;ud=makesurfl(squ,f1,f2,src,ud);p=[1 0 0 1];
   case 5,  squ=4;ud=makesurfl(squ,f1,f2,src,ud);p=[1 1 0 0];
   case 6, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=2;ud=makesurfl(squ,f1,f2,src,ud);p=[0 1 0 1];
   case 7, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);p=[1 0 1 0];
   case 8, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);p=[1 1 1 1];
   case 9, squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);p=[1 1 1 1];
   case 10,squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);p=[1 0 1 0];
   case 11,squ=3;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);p=[0 1 0 1];
   case 12, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);p=[1 1 0 0];
   case 13, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);p=[1 0 0 1];
   case 14, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);p=[0 1 1 0];
   case 15, squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);p=[0 0 1 1];
   case 16,squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);p=[0 0 0 0];
   end
   ud = makefill3(p,f1,f2,ud);
case 5 %slice3contour
   figure(ud.fig4);cla(ud.axes1);ud.h=[];hold on;ud = makeslice3cont(ud);
case 6 %surfl+slice3contour
   figure(ud.fig4);cla(ud.axes1);ud.h=[];hold on;ud = makeslice3cont(ud);
   f1=ud.nstratum;f2=f1;src=0;
   switch squvalue
   case 1,  squ=0;ud=makesurfl(squ,f1,f2,src,ud);
   case 2,  squ=1;ud=makesurfl(squ,f1,f2,src,ud);
   case 3,  squ=2;ud=makesurfl(squ,f1,f2,src,ud);
   case 4,  squ=3;ud=makesurfl(squ,f1,f2,src,ud);
   case 5,  squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   case 6, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=2;ud=makesurfl(squ,f1,f2,src,ud);
   case 7, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);
   case 8, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   case 9, squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);
   case 10,squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   case 11,squ=3;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   case 12, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);
   case 13, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   case 14, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   case 15, squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   case 16,squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   end
case 7 %surfl+slice
   figure(ud.fig4);cla(ud.axes1);ud.h=[];hold on;ud = makeslice(ud);
%    f1=ud.nstratum;f2=f1;src=0;
%    f1=1;f2=f1;src=0;
%    switch squvalue
%    case 1,  squ=0;ud=makesurfl(squ,f1,f2,src,ud);
%    case 2,  squ=1;ud=makesurfl(squ,f1,f2,src,ud);
%    case 3,  squ=2;ud=makesurfl(squ,f1,f2,src,ud);
%    case 4,  squ=3;ud=makesurfl(squ,f1,f2,src,ud);
%    case 5,  squ=4;ud=makesurfl(squ,f1,f2,src,ud);
%    case 6, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=2;ud=makesurfl(squ,f1,f2,src,ud);
%    case 7, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);
%    case 8, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
%    case 9, squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);
%    case 10,squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
%    case 11,squ=3;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
%    case 12, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);
%    case 13, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
%    case 14, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
%    case 15, squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
%    case 16,squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
%    end
case 8 %one surf
   figure(ud.fig4);cla(ud.axes1);ud.h=[];hold on;
   f1=1+round((ud.nstratum-1)*((pfz-loz)/(hiz-loz)));f2=f1;src=0;
   switch squvalue
   case 1,  squ=0;ud=makesurfl(squ,f1,f2,src,ud);
   case 2,  squ=1;ud=makesurfl(squ,f1,f2,src,ud);
   case 3,  squ=2;ud=makesurfl(squ,f1,f2,src,ud);
   case 4,  squ=3;ud=makesurfl(squ,f1,f2,src,ud);
   case 5,  squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   case 6, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=2;ud=makesurfl(squ,f1,f2,src,ud);
   case 7, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);
   case 8, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   case 9, squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);
   case 10,squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   case 11,squ=3;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   case 12, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);
   case 13, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   case 14, squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   case 15, squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   case 16,squ=1;ud=makesurfl(squ,f1,f2,src,ud);squ=2;ud=makesurfl(squ,f1,f2,src,ud);squ=3;ud=makesurfl(squ,f1,f2,src,ud);squ=4;ud=makesurfl(squ,f1,f2,src,ud);
   end
case 9 %slice(surface)
   % ????????? ??????????, ??????????? ??????????? ???? ?? ????????? ???????
   var_clabel='without_clabel';
   valclabel=get(ud.clabel,'Value');
   if valclabel==2 var_clabel='clabel';end
   figure(ud.fig4);cla(ud.axes1);ud.h=[];hold on;
   ud = newdata(ud);
   dZ=ud.z(end)-ud.z(1);
   if  isfield(ud,'Altday')
      S=ud.Altday(ud.ybord(1):ud.ybord(2),ud.xbord(1):ud.xbord(2))-dZ*((hiz-pfz)/(hiz-loz));
   elseif  ~isfield(ud,'Altday'),
      S=pfz*ones(ud.ybord(2)-ud.ybord(1)+1,ud.xbord(2)-ud.xbord(1)+1);
   end


   [X,Y] = meshgrid(ud.x(ud.xbord(1):ud.xbord(2)),ud.y(ud.ybord(1):ud.ybord(2)));
   %
   ud.slice = slice3cont(ud.x(ud.xbord(1):ud.xbord(2)),...
     ud.y(ud.ybord(1):ud.ybord(2)),...
     ud.z(ud.zbord(1):ud.zbord(2)),...
     ud.V(ud.ybord(1):ud.ybord(2),ud.xbord(1):ud.xbord(2),ud.zbord(1):ud.zbord(2)),...
     [X],[Y],[S],var_clabel);%shading interp;
  ud.h=[ud.h; ud.slice];
case {10,11,12,13,17,18}% cub_slice3cont
   if modevalue==10,fun='slice';            method='surface';
   elseif modevalue==11,fun='slice3cont';method='surface';
   elseif modevalue==12,fun='slice';        method='cutsurf';
   elseif modevalue==13,fun='slice3cont';method='cutsurf';
   end
   % ????????? ??????????, ??????????? ??????????? ???? ?? ????????? ???????
   var_clabel='without_clabel';
   valclabel=get(ud.clabel,'Value');
   if valclabel==2 var_clabel='clabel';end
   
   for niz=1:6
      set(ud.slidizo(niz),'Visible','off');
   end
   set(ud.slidz1,'Visible','on');
   set(ud.slidday,'Visible','on');
   set(ud.slidx1,'Visible','on');
   set(ud.slidx2,'Visible','on');
   set(ud.slidy1,'Visible','on');
   set(ud.slidy2,'Visible','on');
   
   cutvalue = get(ud.cut,'Value');
   figure(ud.fig4);cla(ud.axes1);ud.h=[];hold on;
   x1=ud.x(ud.xbord(1));   x2=ud.x(ud.xbord(2));
   y1=ud.y(ud.ybord(1));   y2=ud.y(ud.ybord(2));
   z1=ud.z(ud.zbord(1));   z2=ud.z(ud.zbord(2));
   dx=ud.dx*(x2-x1)/(ud.minmax{1}(2)-ud.minmax{1}(1));
   dy=ud.dy*(y2-y1)/(ud.minmax{2}(2)-ud.minmax{2}(1));
   dz=ud.dz*(z2-z1)/(ud.minmax{3}(2)-ud.minmax{3}(1));
   x=x1:dx:x2;
   y=y1:dy:y2;
   z=z1:dz:z2;
   nx=ceil(((pfx-lox)*(x2-x1))/(dx*(hix-lox)))+1;
   ny=ceil(((pfy-loy)*(y2-y1))/(dy*(hiy-loy)))+1;
   nz=floor(((pfz-loz)*(z2-z1))/(dz*(hiz-loz)))+1;% FLOOR ?
   xt=x(nx);yt=y(ny);zt=z(nz);
   gx1=get(ud.slidx1,'Value');
   gx2=get(ud.slidx2,'Value');
   gy1=get(ud.slidy1,'Value');
   gy2=get(ud.slidy2,'Value');
   gz1=get(ud.slidz1,'Value');
   gz2=get(ud.slidday,'Value');
   
   nx1=1+round((length(x)-1)*gx1);
   nx2=1+round((length(x)-1)*gx2);
   ny1=1+round((length(y)-1)*gy1);
   ny2=1+round((length(y)-1)*gy2);
   nz1=1+round((length(z)-1)*gz1);
   nz2=1+round((length(z)-1)*gz2);
   
   delZ=ud.z(end)-ud.z(1);
   if (modevalue==10 | modevalue==11 | modevalue==17 | modevalue==18) & isfield(ud,'Altday')
      Sday=ud.Altday(ud.ybord(1):ud.ybord(2),ud.xbord(1):ud.xbord(2))-delZ*(1-gz2);
   elseif (modevalue==12 | modevalue==13) | ~isfield(ud,'Altday')
      Sday=ud.V(ud.ybord(1):ud.ybord(2),ud.xbord(1):ud.xbord(2),ud.zbord(2))-delZ*(1-gz2);
   end
   [xs,ys]=meshgrid(x1:ud.dx:x2,y1:ud.dy:y2);
   Zday=interp2(xs,ys,Sday,x,y','linear');
   clear xs ys Sday;
   % sl-????????? str-???? squ-???????
   switch cutvalue
   case 1, % ??????? ????
      switch squvalue
      case 1,p=[1:6 12:16 21:25 30:33];
      case 2,
      case 3,
      case 4,
      case 5,p=[1:16 21:25 30:33];
      case 6,
      case 7,
      case 8,
      case 9,
      case 10,
      case 11,
      case 12,
      case 13,
      case 14,
      case 15,p=[6:11 15:20 24:29 31:33];%p=[1:33];
      case 16,p=[1:36];
      end
   case 2, % ?????? ????
      switch squvalue
      case 1,p=[];
      case 2,
      case 3,
      case 4,
      case 5,p=[1:6];
      case 6,
      case 7,
      case 8,
      case 9,
      case 10,
      case 11,
      case 12,p=[4:5 12:16 21:25 30:33];
      case 13,p=[1:6 12:16 23 30:33];
      case 14,p=[1:6 14 21:25 30:33];
      case 15,p=[1:6 12:16 21:25];
      case 16,p=[1:6 12:16 21:25 30:33];
      end
   end
   
   nv=str2num(get(ud.editizolines,'String'));
   figure(ud.fig4);cla(ud.axes1);ud.h=[];hold on;
   if modevalue==10 | modevalue==11 | modevalue==12 | modevalue==13
      ud=makecubslice(fun,p,ud.V,x,nx1,nx,nx2,y,ny1,ny,ny2,z,nz1,nz,nz2,Zday,nv,ud,method,var_clabel);
   elseif modevalue==17 | modevalue==18
      if ud.flunviz(1)==1; 
         bx=min(find(abs((ud.x-str2num(get(ud.pfhndl(1),'String')) )/ud.dx)<=1));
      elseif ud.flunviz(1)==0;
         bx=ud.xbord(1)-1;
      end;
   
      if ud.flunviz(2)==1,
         by=min(find(abs((ud.y-str2num(get(ud.pfhndl(2),'String')) )/ud.dy)<=1));
      elseif ud.flunviz(2)==0
         by=ud.ybord(1)-1;
      end;

      if ud.flunviz(3)==1,
         bz=max(find(abs((ud.z-str2num(get(ud.pfhndl(3),'String')) )/ud.dz)<=1));
      elseif ud.flunviz(3)==0
         bz=ud.zbord(2)+1;
      end;
      V=ud.V;
      %V(ud.ybord(1):(by),ud.xbord(1):(bx),(bz):ud.zbord(2))=NaN;
      %V(ud.ybord(1):(ny-1),ud.xbord(1):(nx-1),(nz+1):ud.zbord(2))=NaN;
      if modevalue==17,fun='slice';          method='surface';
      elseif modevalue==18,fun='slice3cont'; method='surface';
      end
      p=[37 33 28 19 38 39];
      %ud=makecubslice(fun,p,V,x,nx1,nx,nx2,y,ny1,ny,ny2,z,nz1,nz,nz2,Zday,nv,ud,method,var_clabel);
      ud=makecubslice2(fun,p,V,x,nx1,nx,nx2,y,ny1,ny,ny2,z,nz1,nz,nz2,Zday,nv,ud,method,var_clabel);
      clear V;
   end
   
case 14, 
   set(ud.slidz1,'Visible','off');
   set(ud.slidday,'Visible','off');
   set(ud.slidx1,'Visible','off');
   set(ud.slidx2,'Visible','off');
   set(ud.slidy1,'Visible','off');
   set(ud.slidy2,'Visible','off');
   figure(ud.fig4);cla(ud.axes1);ud.h=[];hold on;
   %surfl(ud.x,ud.y,ud.Altday);
   %vizs=inputdlg('??????? ?????? ???????????????');
   vizs=(get(ud.editizosurf,'String'));

   if strcmp(vizs,''), %vizs=[];maxniz=6; 
      for niz=1:6
         set(ud.slidizo(niz),'Visible','on');
         ud.izov(niz)=get(ud.slidizo(niz),'Value')*(ud.maxv-ud.minv)+ud.minv;
         newizo=makeizosurface(ud.izov(niz),ud);
         ud.izo(niz)=newizo;
      end
    title(['?????????????? ???????????? ?????: ' num2str(10^ud.izov(1)) ', '  num2str(10^ud.izov(2)) ', ' num2str(10^ud.izov(3)) ', ' num2str(10^ud.izov(4)) ', ' num2str(10^ud.izov(5)) ', ' num2str(10^ud.izov(6)) '   macc. % ']);
   else   ud.izov=(str2num(vizs));
     tit=[];
     for niz=1:length(ud.izov);
         %if ud.izov(niz)>=ud.minv & ud.izov(niz)<=ud.maxv
         newizo=makeizosurface(ud.izov(niz),ud);
         ud.izo(niz)=newizo;
         tit=[tit num2str(10^vizs(niz)) ', ' ];
         %end
      title(['?????????????? ???????????? ?????: ' tit '   macc. % ']);
      end
   end
case {15,16} % ?????????????? ?????????   
   
   % ????????? ??????????, ??????????? ???????????? ???? ?? ????????? ???????
   var_clabel='without_clabel';
   valclabel=get(ud.clabel,'Value');
   if valclabel==2 var_clabel='clabel';end
   
   Zslices=str2num(get(ud.editZslices,'String'));
   Yslices=fliplr(sort(str2num(get(ud.editYslices,'String'))));
   Xslices=fliplr(sort(str2num(get(ud.editXslices,'String'))));
   nv=str2num(get(ud.editizolines,'String'));
   figure(ud.fig4);cla(ud.axes1);ud.h=[];hold on;
   if ud.flunviz(1)==1; 
      bx=max(find(abs((ud.x-str2num(get(ud.pfhndl(1),'String')) )/ud.dx)<1));
   elseif ud.flunviz(1)==0;
      bx=ud.xbord(1)-1;
   end;

   if ud.flunviz(2)==1;
      by=min(find(abs((ud.y-str2num(get(ud.pfhndl(2),'String')) )/ud.dy)<1));
   elseif ud.flunviz(2)==0
      by=ud.ybord(1)-1;
   end;

   if ud.flunviz(3)==1;
      bz=min(find(abs((ud.z-str2num(get(ud.pfhndl(3),'String')) )/ud.dz)<1));
   elseif ud.flunviz(3)==0
      bz=ud.zbord(2)+1;
   end;
   V=ud.V;
   V(ud.ybord(1):by,ud.xbord(1):bx,bz:ud.zbord(2))=NaN;
if modevalue==15,%fun='slice';

   ud.slice3cont = slice(ud.x(ud.xbord(1):ud.xbord(2)),...
     ud.y(ud.ybord(1):ud.ybord(2)),...
     ud.z(ud.zbord(1):ud.zbord(2)),...
     V(ud.ybord(1):ud.ybord(2),ud.xbord(1):ud.xbord(2),ud.zbord(1):ud.zbord(2)),...
     [Xslices],[Yslices],[Zslices]);
  shading interp;
  
  camlight; lighting phong;

elseif modevalue==16,%fun='slice3cont';
   
   
    ud.slice3cont = slice3cont(ud.x(ud.xbord(1):ud.xbord(2)),...
     ud.y(ud.ybord(1):ud.ybord(2)),...
     ud.z(ud.zbord(1):ud.zbord(2)),...
     V(ud.ybord(1):ud.ybord(2),ud.xbord(1):ud.xbord(2),ud.zbord(1):ud.zbord(2)),...
     [Xslices],[Yslices],[Zslices],nv,var_clabel);
  
  
  end
  clear V;
  ud.h=[ud.h; ud.slice3cont];
case 21,
   DZGor=ud.e.Gor;
   DYMax=ud.e.Max.*cos(ud.e.Azim*pi/180);
   DXMax=ud.e.Max.*sin(ud.e.Azim*pi/180);
   DYMin=-ud.e.Min.*sin(ud.e.Azim*pi/180);
   DXMin=ud.e.Min.*cos(ud.e.Azim*pi/180);
   
   [X,Y,Z]=meshgrid(ud.e.x,ud.e.y,1);
   
   figure(ud.fig4);hold on;
   %hgor=quiver3(X,Y,Z,0*ud.Gor,0*ud.Gor,ud.Gor);
   %set(hgor,'Color',[1 0 0]);
   
   hmax=quiver3(X,Y,Z,DXMax,DYMax,0*DYMax);
   set(hmax,'Color',[0 1 0]);
   
   hmin=quiver3(X,Y,Z,DXMin,DYMin,0*DYMin);
   set(hmin,'Color',[0 0 1]);

case 22,
   DZGor=ud.e.Gor;
   DY=sqrt(ud.e.Max.^2+ud.e.Min.^2).*cos(ud.e.Azim*pi/180);
   DX=sqrt(ud.e.Max.^2+ud.e.Min.^2).*sin(ud.e.Azim*pi/180);
   
   [X,Y,Z]=meshgrid(ud.e.x,ud.e.y,1);
   
   figure(ud.fig4);hold on;
   %hgor=quiver3(X,Y,Z,0*ud.Gor,0*ud.Gor,ud.Gor);
   %set(hgor,'Color',[1 0 0]);
   
   henergy=quiver3(X,Y,Z,DX,DY,0*DY);
   set(hmax,'Color',[0 1 0]);
   
end

figure(ud.fig4);ud=changecolormap(ud);ud.colorbar=colorbar;%camlight; lighting phong;
figure(ud.fig1);
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function ud=makecubslice(fun,p,V,x,nx1,nx,nx2,y,ny1,ny,ny2,z,nz1,nz,nz2,Zday,nv,ud,method,var_clabel);
% sl-????????? squ-??????? str-???? 
   fun
tab={'xy'   [4]    [1]
    'yz'    [2]    [3]
    'xz'    [2]    [3]
    'xz'    [2]    [2]
    'yz'    [2]    [2]
    'xy'    [4]    [2]%1-? ?????; ?????? ?6
    'yz'    [4]    [3]
    'xz'    [4]    [3]
    'xy'    [4]    [3]
    'yz'    [4]    [2]
    'xz'    [4]    [2]%2-? ?????; ?????? ?11
    'xy'    [3]    [1]
    'xz'    [1]    [3]
    'xz'    [1]    [2]
    'yz'    [2]    [1]
    'xy'    [3]    [2]%3-? ?????; ?????? ?16
    'xz'    [3]    [3]
    'xy'    [3]    [3]
    'xz'    [3]    [2]
    'yz'    [4]    [1]%4-? ?????; ?????? ?20
    'xy'    [2]    [1]
    'yz'    [1]    [3]
    'yz'    [1]    [2]
    'xz'    [2]    [1]
    'xy'    [2]    [2]%5-? ?????; ?????? ?25
    'yz'    [3]    [3]
    'xy'    [2]    [3]
    'yz'    [3]    [2]
    'xz'    [4]    [1]%6-? ?????; ?????? ?29
    'xy'    [1]    [1]
    'xz'    [1]    [1]
    'yz'    [1]    [1]
    'xy'    [1]    [2]%7-? ?????; ?????? ?33
    'xy'    [1]    [3]
    'xz'    [3]    [1]
    'yz'    [3]    [1]%8-? ?????; ?????? ?36
    'xy'    [5]    [3]
    'yz'    [5]    [1]
    'xz'    [5]    [1]};%????? ???????
 
for ii=p
sl=tab{ii,1};squ=tab{ii,2};str=tab{ii,3};
switch sl
case 'xy'
   switch squ
   case 1, [X,Y]=meshgrid(x(nx1:nx),  y(ny1:ny));  Zd=Zday(ny1:ny,nx1:nx);
   case 2, [X,Y]=meshgrid(x(nx:nx2),y(ny1:ny));  Zd=Zday(ny1:ny,nx:nx2);
   case 3, [X,Y]=meshgrid(x(nx1:nx),  y(ny:ny2));Zd=Zday(ny:ny2,nx1:nx);
   case 4, [X,Y]=meshgrid(x(nx:nx2),y(ny:ny2));Zd=Zday(ny:ny2,nx:nx2);
   case 5, [X,Y]=meshgrid(x(nx1:nx2),y(ny1:ny2));Zd=Zday(ny1:ny2,nx1:nx2);
   end
   
   switch str
   case 1, Z=z(nz1)*ones(size(X));
   case 2, Z=z(nz)*ones(size(X));
   case 3, 
      if strcmp(method,'surface')% & strcmp(fun,'slice')
         Z=Zd;
      elseif strcmp(method,'cutsurf')
         Z=z(nz2)*ones(size(X));
      end;
   end
case 'xz'
   switch squ
   case 1, [X,Z]=meshgrid(x(nx1:nx),  z(nz1:nz));
   case 2, [X,Z]=meshgrid(x(nx:nx2),z(nz1:nz));
   case 3, [X,Z]=meshgrid(x(nx1:nx),  z(nz:nz2));
   case 4, [X,Z]=meshgrid(x(nx:nx2),z(nz:nz2));
   case 5, [X,Z]=meshgrid(x(nx1:nx2),z(nz1:nz2));
      
   end
   switch str
   case 1, Y=y(ny1)*ones(size(X));
   case 2, Y=y(ny)*ones(size(X));
   case 3, Y=y(ny2)*ones(size(X));
   end
case 'yz'
   switch squ
   case 1, [Y,Z]=meshgrid(y(ny1:ny),  z(nz1:nz));
   case 2, [Y,Z]=meshgrid(y(ny:ny2),z(nz1:nz));
   case 3, [Y,Z]=meshgrid(y(ny1:ny),  z(nz:nz2));
   case 4, [Y,Z]=meshgrid(y(ny:ny2),z(nz:nz2));
   case 5, [Y,Z]=meshgrid(y(ny1:ny2),z(nz1:nz2));
   end
   switch str
   case 1, X=x(nx1)*ones(size(Y));
   case 2, X=x(nx)*ones(size(Y));
   case 3, X=x(nx2)*ones(size(Y));
   end
end

%if  ~(str==3 & strcmp(sl,'xy') & strcmp(method,'surface'))
   switch fun
   case 'slice'
      ud.slice = slice(ud.x(ud.xbord(1):ud.xbord(2)),...
     ud.y(ud.ybord(1):ud.ybord(2)),...
     ud.z(ud.zbord(1):ud.zbord(2)),...
     V(ud.ybord(1):ud.ybord(2),ud.xbord(1):ud.xbord(2),ud.zbord(1):ud.zbord(2)),...
     [X],[Y],[Z]);
  
  set(ud.slice,'FaceColor','interp');
  set(ud.slice,'EdgeColor','none');
  ud = makeline(ud);
  ud.h=[ud.h; ud.slice];
  case 'slice3cont'
     
     
     ud.slice3cont = slice3cont(...
        ud.x(ud.xbord(1):ud.xbord(2)),...
        ud.y(ud.ybord(1):ud.ybord(2)),...
        ud.z(ud.zbord(1):ud.zbord(2)),...
        V(ud.ybord(1):ud.ybord(2),ud.xbord(1):ud.xbord(2),ud.zbord(1):ud.zbord(2)),...
        [X],[Y],[Z],nv,var_clabel);
  ud.h=[ud.h; ud.slice3cont];
   end

%end 
%pause
end % for i=p
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function newizo=makeizosurface(izov,ud)
%ud=makecubslice('slice',[11 20 29 36],ud.x,1,10,ud.xbord(2),ud.y,1,10,ud.ybord(2),ud.z,1,10,ud.zbord(2),ud.Altday,ud,'surface');
if ud.flunviz(1)==1; 
   bx=max(find(abs((ud.x-str2num(get(ud.pfhndl(1),'String')) )/ud.dx)<1));
elseif ud.flunviz(1)==0;
   bx=ud.xbord(1)-1;
end;

if ud.flunviz(2)==1;
   by=min(find(abs((ud.y-str2num(get(ud.pfhndl(2),'String')) )/ud.dy)<1));
elseif ud.flunviz(2)==0
   by=ud.ybord(1)-1;
end;

if ud.flunviz(3)==1;
   bz=min(find(abs((ud.z-str2num(get(ud.pfhndl(3),'String')) )/ud.dz)<1));
elseif ud.flunviz(3)==0
   bz=ud.zbord(2)+1;
end;
V=ud.V;
V(ud.ybord(1):by,ud.xbord(1):bx,bz:ud.zbord(2))=NaN;

hold on;
newizo=patch(isosurface(ud.x(ud.xbord(1):ud.xbord(2)),...
   ud.y(ud.ybord(1):ud.ybord(2)),...
   ud.z(ud.zbord(1):ud.zbord(2)),...
   V(ud.ybord(1):ud.ybord(2),ud.xbord(1):ud.xbord(2),ud.zbord(1):ud.zbord(2)),...
   izov));
newizo2=patch(isocaps(ud.x(ud.xbord(1):ud.xbord(2)),...
   ud.y(ud.ybord(1):ud.ybord(2)),...
   ud.z(ud.zbord(1):ud.zbord(2)),...
   V(ud.ybord(1):ud.ybord(2),ud.xbord(1):ud.xbord(2),ud.zbord(1):ud.zbord(2)),...
   izov));
set(newizo2, 'FaceColor', 'interp', 'EdgeColor', 'none');
disp(['?????????????? ?????? ????????????3 = ' num2str(izov) ' % ????']);
isonormals(ud.x(ud.xbord(1):ud.xbord(2)),...
   ud.y(ud.ybord(1):ud.ybord(2)),...
   ud.z(ud.zbord(1):ud.zbord(2)),...
   V(ud.ybord(1):ud.ybord(2),ud.xbord(1):ud.xbord(2),ud.zbord(1):ud.zbord(2)),...
   newizo);
clear V;
ncm=fix(1+63*(izov-ud.minv)/(ud.maxv-ud.minv));
if ncm<1,ncm=1;elseif ncm>64,ncm=64;end
colorizosurf=ud.c(ncm,:);
set(newizo, 'FaceColor', colorizosurf, 'EdgeColor', 'none');
camlight; lighting gouraud
%ud.h=[ud.h; ud.izo(niz)];
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function ud=makecubslice2(fun,p,V,x,nx1,nx,nx2,y,ny1,ny,ny2,z,nz1,nz,nz2,Zday,nv,ud,method,var_clabel);
% sl-????????? squ-??????? str-???? 
   fun
tab={'xy'   [4]    [1]
    'yz'    [2]    [3]
    'xz'    [2]    [3]
    'xz'    [2]    [2]
    'yz'    [2]    [2]
    'xy'    [4]    [2]%1-? ?????; ?????? ?6
    'yz'    [4]    [3]
    'xz'    [4]    [3]
    'xy'    [4]    [3]
    'yz'    [4]    [2]
    'xz'    [4]    [2]%2-? ?????; ?????? ?11
    'xy'    [3]    [1]
    'xz'    [1]    [3]
    'xz'    [1]    [2]
    'yz'    [2]    [1]
    'xy'    [3]    [2]%3-? ?????; ?????? ?16
    'xz'    [3]    [3]
    'xy'    [3]    [3]
    'xz'    [3]    [2]
    'yz'    [4]    [1]%4-? ?????; ?????? ?20
    'xy'    [2]    [1]
    'yz'    [1]    [3]
    'yz'    [1]    [2]
    'xz'    [2]    [1]
    'xy'    [2]    [2]%5-? ?????; ?????? ?25
    'yz'    [3]    [3]
    'xy'    [2]    [3]
    'yz'    [3]    [2]
    'xz'    [4]    [1]%6-? ?????; ?????? ?29
    'xy'    [1]    [1]
    'xz'    [1]    [1]
    'yz'    [1]    [1]
    'xy'    [1]    [2]%7-? ?????; ?????? ?33
    'xy'    [1]    [3]
    'xz'    [3]    [1]
    'yz'    [3]    [1]%8-? ?????; ?????? ?36
    'xy'    [5]    [3]
    'yz'    [5]    [1]
    'xz'    [5]    [1]};%????? ???????
 
for ii=p
sl=tab{ii,1};squ=tab{ii,2};str=tab{ii,3};
switch sl
case 'xy'
   switch squ
   case 1, [X,Y]=meshgrid(x(nx1:nx),  y(ny1:ny));  Zd=Zday(ny1:ny,nx1:nx);
   case 2, [X,Y]=meshgrid(x(nx:nx2),y(ny1:ny));  Zd=Zday(ny1:ny,nx:nx2);
   case 3, [X,Y]=meshgrid(x(nx1:nx),  y(ny:ny2));Zd=Zday(ny:ny2,nx1:nx);
   case 4, [X,Y]=meshgrid(x(nx:nx2),y(ny:ny2));Zd=Zday(ny:ny2,nx:nx2);
   case 5, [X,Y]=meshgrid(x(nx1:nx2),y(ny1:ny2));Zd=Zday(ny1:ny2,nx1:nx2);
   end
   
   switch str
   case 1, Z=z(nz1)*ones(size(X));
   case 2, Z=z(nz)*ones(size(X));
   case 3, 
      if strcmp(method,'surface')% & strcmp(fun,'slice')
         Z=Zd;
      elseif strcmp(method,'cutsurf')
         Z=z(nz2)*ones(size(X));
      end;
   end
case 'xz'
   switch squ
   case 1, [X,Z]=meshgrid(x(nx1:nx),  z(nz1:nz));
   case 2, [X,Z]=meshgrid(x(nx:nx2),z(nz1:nz));
   case 3, [X,Z]=meshgrid(x(nx1:nx),  z(nz:nz2));
   case 4, [X,Z]=meshgrid(x(nx:nx2),z(nz:nz2));
   case 5, [X,Z]=meshgrid(x(nx1:nx2),z(nz1:nz2));
      
   end
   switch str
   case 1, Y=y(ny1)*ones(size(X));
   case 2, Y=y(ny)*ones(size(X));
   case 3, Y=y(ny2)*ones(size(X));
   end
case 'yz'
   switch squ
   case 1, [Y,Z]=meshgrid(y(ny1:ny),  z(nz1:nz));
   case 2, [Y,Z]=meshgrid(y(ny:ny2),z(nz1:nz));
   case 3, [Y,Z]=meshgrid(y(ny1:ny),  z(nz:nz2));
   case 4, [Y,Z]=meshgrid(y(ny:ny2),z(nz:nz2));
   case 5, [Y,Z]=meshgrid(y(ny1:ny2),z(nz1:nz2));
   end
   switch str
   case 1, X=x(nx1)*ones(size(Y));
   case 2, X=x(nx)*ones(size(Y));
   case 3, X=x(nx2)*ones(size(Y));
   end
end

%if  ~(str==3 & strcmp(sl,'xy') & strcmp(method,'surface'))
   switch fun
   case 'slice'
      ud.slice = slice(ud.x(ud.xbord(1):ud.xbord(2)),...
     ud.y(ud.ybord(1):ud.ybord(2)),...
     ud.z(ud.zbord(1):ud.zbord(2)),...
     V(ud.ybord(1):ud.ybord(2),ud.xbord(1):ud.xbord(2),ud.zbord(1):ud.zbord(2)),...
     [X],[Y],[Z]);
  
  set(ud.slice,'FaceColor','interp');
  set(ud.slice,'EdgeColor','none');
  ud = makeline(ud);
  ud.h=[ud.h; ud.slice];
  case 'slice3cont'
     
     
     ud.slice3cont = slice3cont(...
        ud.x(ud.xbord(1):ud.xbord(2)),...
        ud.y(ud.ybord(1):ud.ybord(2)),...
        ud.z(ud.zbord(1):ud.zbord(2)),...
        V(ud.ybord(1):ud.ybord(2),ud.xbord(1):ud.xbord(2),ud.zbord(1):ud.zbord(2)),...
        [X],[Y],[Z],nv,var_clabel);
  ud.h=[ud.h; ud.slice3cont];
   end

%end 
%pause
end % for i=p
% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
