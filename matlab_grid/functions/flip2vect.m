function [x,y] = flip2vect(x1,y1);
% дополняет горизонтальный сигнал справа и слева зеркально отражённым
cuty1 = fliplr(y1); cuty2 = cuty1;
cuty1(length(y1))=[]; cuty2(1)=[];
y = [cuty1 y1 cuty2];
dx = x1(2) - x1(1);
Lx = dx*(length(x1)-1);
x = (x1(1)-Lx):dx:(x1(length(x1))+Lx);

