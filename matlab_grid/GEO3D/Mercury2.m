function varargout=Mercury2;

% Mercury1  c*10^-4 = % ����.
%
% ������� ������� �������. E-mail: alexey_drozdov@mail.ru
% "������-��������������� �������� ������������ ���������� � ����������".
% �. �������. 8-0572-19-55-77
%
close all;clear;%pack;
ud=[];ude=[];FILENAME='';
mwork=0;
%while mwork<3
   mwork=menu('��������� ���������� ������ ��� 3D-Geo ������������',...
      '���������','C��������','������������','�����');
%if mwork==1
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@   ���� �������� �����   @@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

f00=0;way=[];
while f00<3
   f00=menu('������� ����?','wk1','mat','���');
   if f00==1
      [FILENAME, PATHNAME]=uigetfile('*.wk1','open data file.wk1');   
      if all(FILENAME==0) 
         f00=0;
      else
         tp=FILENAME(end-3:end);
         if  strcmp(tp,'.wk1')
            M=wk1read([PATHNAME FILENAME]);f00=2;
         else
            errordlg(['���������� ����� ������ ���� .wk1'],'ERROR','CREATEMODE');
            f00=0;
         end
      end;
      if f00==2
         [d1,d2]=size(M);
         if d2<8
            errordlg(['����� �������� ������� ������ ���� �� ������ 8. ' ...
               '������ ������� ������������� X ����������. ' ...
               '������ ������� ������������� Y ����������.'],'ERROR','CREATEMODE');
            f00=0;
         else f00=3;way=1;
         end 
      end
   end
   if f00==2
      [FILENAME, PATHNAME]=uigetfile('*.mat','open data file.mat');   
      if all(FILENAME==0) 
         f00=0;
      else
         tp=FILENAME(end-3:end);
         if  strcmp(tp,'.mat')
            %PA=FILENAME(1:end-4);ud=[]; eval([PA '=[];']);
            load([PATHNAME FILENAME]);
            if ~isempty(ud) | ~isempty(ude); 
            %elseif ~isempty(eval(PA)) ud=eval(PA);
            else f00=0; errordlg('sorry incorrect data or variable name','ERROR','CREATEMODE');
            end;   
            f00=3;way=2;
         else
            errordlg(['���������� ����� ������ ���� .mat'],'ERROR','CREATEMODE');
            f00=0;
         end
      end;
   end
end
clear PATHNAME d1 d2 f00 tp;
ud.FILENAME=FILENAME;

%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@  ����� ����� �������� �����   @@@@@@@@@@@@@@@@@
%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
