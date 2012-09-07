[xi,yi]=meshgrid(1:10,1:10)
x=[2.5 4.5 1.2];xad=[1:10 10*ones(1,10) fliplr(1:10) 1*ones(1,10)]
y=[3.5 6.1 9.6];yad=[1*ones(1,10) 1:10 10*ones(1,10) fliplr(1:10)]
z=[1 1.2 2.8] ;zad=zeros(size(xad));
zi = nearest([x xad],[y yad],[z zad],xi,yi)
zi=griddata([x xad],[y yad],[z zad],xi,yi,'linear')
zi=griddata([x xad],[y yad],[z zad],xi,yi,'v4')
zi=griddata([x xad],[y yad],[z zad],xi,yi,'cubic')
surf(zi);hold on, plot3(x,y,z,'r.');hold off