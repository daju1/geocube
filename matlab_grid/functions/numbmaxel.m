function output = numbmaxel(frk)
% Вектор-строка номер максимального элемента 
% каждого столбца матрицы аргумента

for j2 = 1:size(frk,2)
output(j2) = 1;
for j1 = 2:size(frk,1)
   if frk(j1,j2) > frk(output(j2),j2)
      output(j2) = j1;
   else
      
   end
end
end
