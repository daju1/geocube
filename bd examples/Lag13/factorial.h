// ���������
long int fact(long int x)
{
	if (x==0 || x==1)
		return 1;
	return x * fact(x - 1);
}
// ��������� �����������
long int fact_relation(long int N, long int m)
{
	if (N == m)
		return 1;
	if (N > m)
		return N * fact_relation(N - 1, m);
	return 0;
}
// ������������� ������������
long int BinominalQuotient(long int n, long int N)
{
	long int m = N - n;
	if (m > n)
		return fact_relation(N, m) / fact(n);
	else
		return fact_relation(N, n) / fact(m);
}
// ���������
int fact(int x)
{
	if (x==0 || x==1)
		return 1;
	return x * fact(x - 1);
}
// ��������� �����������
int fact_relation(int N, int m)
{
	if (N == m)
		return 1;
	if (N > m)
		return N * fact_relation(N - 1, m);
	return 0;
}
// ������������� ������������
int BinominalQuotient(int n, int N)
{
	int m = N - n;
	if (m > n)
		return fact_relation(N, m) / fact(n);
	else
		return fact_relation(N, n) / fact(m);
}
