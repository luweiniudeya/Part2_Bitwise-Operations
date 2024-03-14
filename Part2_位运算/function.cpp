#include"function.h"
int absVal_standard(int x) { return (x < 0) ? -x : x; }
int negate_standard(int x) { return -x; }
int isTmax_standard(int x) { return x == (1 << 31) - 1; }
int bitAnd_standard(int x, int y) { return x & y; }
int bitOr_standard(int x, int y) { return x | y; }
int bitXor_standard(int x, int y) { return x ^ y; }
int bitAnd(int x, int y) { return ~((~x) | (~y)); }
int bitOr(int x, int y) { return ~((~x) & (~y)); }
int bitXor(int x, int y) { return ~bitOr(((~x) & (~y)), (x & y)); }//“与的非” 和 “或” 与起来

int absVal(int x)
{
	//返回 x 的绝对值
	//仅使用 !、 ~、 & 、^ 、 | 、 + 、 << 、 >> ， 运算次数不超过 10次
	int temp = 1 << 31;
	if (!(temp & x))//if中正负均true 仅0为false
		return x;
	return (~x) + 1;
}
int negate(int x) {
	//	不使用负号，实现 - x
	return (~x) + 1;
}
int isTmax(int x)//此处我想改成bool 但鉴于任务书为int 仍用int（其实想兼容单目检测返回值int,方便一点)
{
	/*判断x是否为最大的正整数（7FFFFFFF），
	只能使用 !、 ~、 & 、^ 、 | 、 +*/
	int temp = 1 << 31;
	return !(~(temp ^ x));
}
int bitCount(int x)
{
	/*统计x的二进制表示中 1 的个数
	只能使用，!~&^| +<< >> ，运算次数不超过 40次*/
	int count = 0;
	while (x)//有1即循环
	{
		count++;
		x = x & (x - 1);//使x中的1减少一个
	}
	return count;
}
int bitCount_standard(int x)
{
	//遍历 这里考虑到负数的1个数计算 所以用最原始的位运算
	int count = 0;
	int temp = 1;
	for (int i = 0; i < 32; i++)
	{
		if (temp & x)
			count++;
		x = x >> 1;//最终完成计数后 x还会右移一位，感觉应该不会有bug
	}
	return count;
}
int bitMask(int highbit, int lowbit)
//要求只使用 ! ~ & ^ | + << >> ；运算次数不超过 16次
//(5,3)=0x38  0011 1000 故最高位为31 最低位为0
{
	highbit = ((highbit % 32) + 32) % 32;//同时起到保护程序作用
	lowbit = ((lowbit % 32) + 32) % 32;//两语句仅为兼容check_binary 这样可以少写一个测试函数
	if (highbit < 0 || lowbit < 0)
		return 0;
	if (highbit < lowbit)
		return 0;
	//由于使用了上一位-1生成纯1串 故当highbit为31时 该式不成立
	if (highbit != 31)
		return ((1 << (highbit + 1)) - 1) - ((1 << lowbit) - 1);
	else return (((1 << 31) - 1) | (1 << 31)) - ((1 << lowbit) - 1);
}
int bitMask_standard(int highbit, int lowbit)
{
	highbit = ((highbit % 32) + 32) % 32;//同时起到保护程序作用
	lowbit = ((lowbit % 32) + 32) % 32;//两语句仅为兼容check_binary 这样可以少写一个测试函数
	if (highbit < 0 || lowbit < 0)
		return 0;
	if (highbit < lowbit)
		return 0;
	//采用逐位赋值
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