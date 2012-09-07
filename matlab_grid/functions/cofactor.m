function varargout=cofactor(M,j,k);
varargout{1}=[];varargout{2}=[];
if size(M,1)~=size(M,2) | size(M,1)==[1], warndlg('M must be square');return; end
if size(j,1)~=1 | size(j,2)~=1 , warndlg('j must be integer');return; end
if size(k,1)~=1 | size(k,2)~=1 , warndlg('k must be integer');return; end
%    [A,minor]=cofactor(M,j,k);
%
% �������������� ���������� �������� �(j,k) 
% ��� ���������� ������� M

minor=M; minor(j,:)=[];minor(:,k)=[]; % ��������� �������� �������
%minor=M([1:j-1 j+1:end],[1:k-1 k+1:end]);
A=((-1)^(j+k))*det(minor); % ���������� ��������������� ����������
varargout{1}=A;
varargout{2}=minor;

%return
%C=size(M,1);
% ����� ������������� ������
%for i1=1:C
%   for i2=1:C
%      A(i1,i2)=cofactor(M,i1,i2);
%   end
%end
