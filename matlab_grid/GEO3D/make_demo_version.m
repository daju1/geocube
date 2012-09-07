% make_demo_version

clear;
egg
disp('Press any key')
pause
ud = get(1,'Userdata')

ax1=ud.axes1
hgS=handle2struct(ax1)


save('C:\Temp\Struct_of_handle','hgS');
clear;close all;

load('C:\Temp\Struct_of_handle');

f=figure;
H_ax=struct2handle(hgS,f)
%@@@@@@@@@@


hgS=handle2struct(4);
H_f=struct2handle(hgS,4)


