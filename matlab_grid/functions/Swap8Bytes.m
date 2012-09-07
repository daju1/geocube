function [swapped] = Swap8Bytes(v)
% inline void 
% vtkByteSwap::Swap8Bytes(char* &data)
% { 
%   char one_byte;
%   one_byte = data[0]; data[0] = data[7]; data[7] = one_byte;
%   one_byte = data[1]; data[1] = data[6]; data[6] = one_byte;
%   one_byte = data[2]; data[2] = data[5]; data[5] = one_byte;
%   one_byte = data[3]; data[3] = data[4]; data[4] = one_byte; 
% }

h = num2hex(v);
t1 = h(1); t2 = h(2); h(1) = h(15); h(2) = h(16); h(15) = t1; h(16) = t2;
t1 = h(3); t2 = h(4); h(3) = h(13); h(4) = h(14); h(13) = t1; h(14) = t2;
t1 = h(5); t2 = h(6); h(5) = h(11); h(6) = h(12); h(11) = t1; h(12) = t2;
t1 = h(7); t2 = h(8); h(7) = h(9); h(8) = h(10); h(9) = t1; h(10) = t2;
swapped = hex2num(h);

