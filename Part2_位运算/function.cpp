#include"function.h"
int absVal_standard(int x) { return (x < 0) ? -x : x; }
int negate_standard(int x) { return -x; }
int isTmax_standard(int x) { return x == (1 << 31) - 1; }
int bitAnd_standard(int x, int y) { return x & y; }
int bitOr_standard(int x, int y) { return x | y; }
int bitXor_standard(int x, int y) { return x ^ y; }
int bitAnd(int x, int y) { return ~((~x) | (~y)); }
int bitOr(int x, int y) { return ~((~x) & (~y)); }
int bitXor(int x, int y) { return ~bitOr(((~x) & (~y)), (x & y)); }//����ķǡ� �� ���� ������

int absVal(int x)
{
	//���� x �ľ���ֵ
	//��ʹ�� !�� ~�� & ��^ �� | �� + �� << �� >> �� ������������� 10��
	int temp = 1 << 31;
	if (!(temp & x))//if��������true ��0Ϊfalse
		return x;
	return (~x) + 1;
}
int negate(int x) {
	//	��ʹ�ø��ţ�ʵ�� - x
	return (~x) + 1;
}
int isTmax(int x)//�˴�����ĳ�bool ������������Ϊint ����int����ʵ����ݵ�Ŀ��ⷵ��ֵint,����һ��)
{
	/*�ж�x�Ƿ�Ϊ������������7FFFFFFF����
	ֻ��ʹ�� !�� ~�� & ��^ �� | �� +*/
	int temp = 1 << 31;
	return !(~(temp ^ x));
}
int bitCount(int x)
{
	/*ͳ��x�Ķ����Ʊ�ʾ�� 1 �ĸ���
	ֻ��ʹ�ã�!~&^| +<< >> ��������������� 40��*/
	int count = 0;
	while (x)//��1��ѭ��
	{
		count++;
		x = x & (x - 1);//ʹx�е�1����һ��
	}
	return count;
}
int bitCount_standard(int x)
{
	//���� ���￼�ǵ�������1�������� ��������ԭʼ��λ����
	int count = 0;
	int temp = 1;
	for (int i = 0; i < 32; i++)
	{
		if (temp & x)
			count++;
		x = x >> 1;//������ɼ����� x��������һλ���о�Ӧ�ò�����bug
	}
	return count;
}
int bitMask(int highbit, int lowbit)
//Ҫ��ֻʹ�� ! ~ & ^ | + << >> ��������������� 16��
//(5,3)=0x38  0011 1000 �����λΪ31 ���λΪ0
{
	highbit = ((highbit % 32) + 32) % 32;//ͬʱ�𵽱�����������
	lowbit = ((lowbit % 32) + 32) % 32;//������Ϊ����check_binary ����������дһ�����Ժ���
	if (highbit < 0 || lowbit < 0)
		return 0;
	if (highbit < lowbit)
		return 0;
	//����ʹ������һλ-1���ɴ�1�� �ʵ�highbitΪ31ʱ ��ʽ������
	if (highbit != 31)
		return ((1 << (highbit + 1)) - 1) - ((1 << lowbit) - 1);
	else return (((1 << 31) - 1) | (1 << 31)) - ((1 << lowbit) - 1);
}
int bitMask_standard(int highbit, int lowbit)
{
	highbit = ((highbit % 32) + 32) % 32;//ͬʱ�𵽱�����������
	lowbit = ((lowbit % 32) + 32) % 32;//������Ϊ����check_binary ����������дһ�����Ժ���
	if (highbit < 0 || lowbit < 0)
		return 0;
	if (highbit < lowbit)
		return 0;
	//������λ��ֵ
	int ans = 0;
	int temp = 1 << lowbit;
	for (int i = 0; i < highbit - lowbit + 1; i++)
	{
		ans = ans | temp;
		temp = temp << 1;
	}
	return ans;
}
int addOK(int x, int y)
{
	int temp = 1 << 31;
	bool sig1 = temp & x;
	bool sig2 = temp & y;
	bool sig3 = (x + y) & temp;
	if (sig1 ^ sig2)
		return 0;
	if (sig1 ^ sig3)
		return 1;
	return 0;
}
int addOK_standard(int x, int y)
{
	int temp;
	if (x > 0 && y > 0)
		return (1 << 31) - 1 - x < y;
	else if (x < 0 && y < 0)
		return (1 << 31) - x > y;
	return 0;
}
int byteSwap(int x, int n, int m)
{//0<=n,m<=3 n<m
	if (n > m)
	{
		int temp = n;
		n = m;
		m = temp;
	}
	int mask_n = bitMask(n * 8 + 7, n * 8);
	int mask_m = bitMask(m * 8 + 7, m * 8);
	int temp_n = mask_n & (x >> (8 * (m - n)));
	int temp_m = mask_m & (x << (8 * (m - n)));
	x = x & (~mask_n);
	x = x & (~mask_m);
	x = x | temp_n;
	x = x | temp_m;
	return x;
}
int byteSwap_standard(int x, int n, int m)
{
	if (n > m)
	{
		int temp = n;
		n = m;
		m = temp;
	}
	int index1 = 1 << (8 * n);
	int index2 = 1 << (8 * m);
	bool sig = 0;
	for (int i = 0; i < 8; i++)
	{
		sig = x & index1;
		if (x & index2)//1
			x = x | index1;
		else x = x & (~index1);
		if (sig)//1
			x = x | index2;
		else x = x & (~index2);

		index1 = index1 << 1;
		index2 = index2 << 1;
	}
	return x;
}