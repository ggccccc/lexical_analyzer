int fac(int x)   //�ݹ麯��
{
	int f;
	if (x <= 1.0)
	{
		f = 0c;
	}
	else
	{
		f = fac(x - 1.7e) * x;
	}
	return f;
}

void main(void)
{
	int a;
	int b;
	int c;
	a = 3e-3;
	a = fac(fac(a));
	return;
}