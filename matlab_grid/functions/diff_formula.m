function varargout=diff_formula(arg,flag)
% Функция выводит формулы дифференцирования, обращаясь к ядру Maple
%  flag='all';
%    or
%  flag='center';

% if nargin<2,flag='center';end
   
if nargin<1,
   m=menu('Вывод формулы дифференцирования по ',...
      '3-м точкам',...
      '5-м точкам',...
      '7-м точкам',...
      '9-м точкам',...
      '11-м точкам');
   switch m
   case 1, N=3; 
   case 2, N=5; 
   case 3, N=7; 
   case 4, N=9; 
   case 5, N=11;
   end
   m2=menu('Дифференцирование','в центральной точке','во всех точках');
   switch m2
   case 1, flag='center';
   case 2, flag='all';
   end
   displ=1;
else
   N=arg;displ=0;
end

if N/2-fix(N/2)~=0.5 | N < 3,
   errordlg(str2mat('Число точек должно быть нечётным',...
      '         и не меньшим 3'));
   return
end

nn=num2str(fix(N/2));

text_t='[t1,';
text_x='[x1,';
for ii=2:N
   text_t=[text_t 't1+dt*' num2str(ii-1) ','];
   text_x=[text_x 'x' num2str(ii) ','];
end
text_t(end)='';text_t=[text_t '],'];
text_x(end)='';text_x=[text_x '],'];

maple(['f:=(t)->interp('text_t text_x 't):' ]);
for order=1:N-1
   q0=num2str(order);
   maple(['d' q0 'f:=(t)->diff(f(t),t$' q0 '):']);
   if strcmp(flag,'center'),
      formula=maple(['simplify(subs(t=t1+' nn '*dt,d' q0 'f(t)));']);
      if displ disp(formula);end
   elseif strcmp(flag,'all'),
      for n=0:N-1,
         formul=maple(['simplify(subs(t=t1+' num2str(n) '*dt,d' q0 'f(t)));']);
         formula{n+1}=formul;
         if displ disp(formul);end
      end
   end
   if displ disp(' ');end
   if ~displ,varargout{order}=formula;end
   clear formula;
end

