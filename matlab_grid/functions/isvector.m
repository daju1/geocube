function b=isvector(v);

b=0;
s=size(v);
if length(s)==2,
   if (s(1)==1 | s(2)==1),
      b=1;
   end
end
