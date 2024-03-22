#include"function.h"
void check_single(bool mode, bool debugging_mode,int left,int right)
//��Ŀ��������
{
	//���벿�ֿ�ʼ
	//mode1 ȫ��Χ��� 0ѡ��Χ���
	//debugging_mode ����ģʽ��1Ϊ�������������ĺ�����ֵ
	const int INF = (1 << 31) - 1;
	if (left == 0 && right == 0)
	{
		if (mode)
		{
			left = 1 << 31;
			right = (1 << 31) - 1;
			cout << "��Ŀ�����ȫint��Χ( 1<<31 �� (1<<31) - 1 )���";
		}
		else {
			cout << "��Ŀ��������" << endl;
			cout << "���򽫼��[L,R]��Χ�ڵ���������(int)��������L R:";
			cin >> left >> right;
			while (left > right)
			{
				cout << "\n�����������ӦʹL<R,���¶���:";
				cin >> left >> right;
			}
		}
		//���벿�ֽ���
	}
	//����ָ��������name����
	int n = 4;
	int (*array[20])(int x) = {
		absVal,negate,isTmax,bitCount
	};
	int (*array_standard[20])(int x) {
		absVal_standard, negate_standard, isTmax_standard, bitCount_standard
	};
	string name[20] = {
		"absVal","negate","isTmax","bitCount"
	};

	//��Ŀ��������ļ�����
	int flag = 1;
	for (int i = 0; i < n; i++)
	{
		flag = 1;
		if (debugging_mode)
			cout << name[i] << "����" << endl;
		for (int j = left; j <= right; j++)
		{
			if (debugging_mode)//ÿ�αȽ϶�������Ч�ʣ�Ӧ���ⲿ������һ������Σ� ��Ϊ���ۺϲ����ڲ�
			{
				cout << "x=" << j << "\t" << (*array[i])(j) << " " << (*array_standard[i])(j) << endl;
				if (j == INF)
					break;
				if ((*array[i])(j) != (*array_standard[i])(j))
				{
					cout << name[i] << "����!" << endl;
					flag = 0;
					break;
				}
				continue;
			}
			if ((*array[i])(j) != (*array_standard[i])(j))
			{
				cout << name[i] << "����!" << endl;
				flag = 0;
				break;
			}
			if (j == INF)
				break;
		}
		if (flag)
		{
			cout << name[i] << "��ȷ!" << endl;
		}
		if(debugging_mode)
			wait();
	}
}
void check_binary(bool mode_random, bool debugging_mode, bool LMR)
{
	//random���������ģʽ debug��������ģʽ LMRǿ�Ʊ�֤x>=y
	int n = 5;//��������
	int numarray[10] = {
		(1 << 31) - 1,//max��mod32ǡ����31,����Ϊmask������ֵ
		0, 1 << 31, 289, 327,
		10086, 1999, 123456, -1, -8848
	};//�ṩʮ������������
	double helpnum1, helpnum2;
	if (mode_random)
	{
		//random_device seed;//Ӳ���������������
		//ranlux48 engine(seed());//���������������������
		//uniform_int_distribution<> distrib(0, 100);//�����������Χ����Ϊ���ȷֲ�
		//int random = distrib(engine);//�����
		//helpnum1 = random / 100;
		//random = distrib(engine);//�����
		//helpnum2 = random / 100;
		srand(time(0));
		helpnum1 = rand() % 100;
		helpnum2 = rand() % 100;
		helpnum1 /= 100;
		helpnum2 /= 100;
	}
	int (*array[10])(int x, int y) = {
		bitAnd,bitOr,bitXor,bitMask,addOK
	};
	int (*array_standard[10])(int x, int y) = {
		bitAnd_standard,bitOr_standard,bitXor_standard,bitMask_standard,addOK_standard
	};
	string name[10] = {
		"bitAnd","bitOr","bitXor","bitMask","addOK"
	};
	bool flag = 1;
	for (int k = 0; k < n; k++)
	{
		cout << name[k] << "����" << endl;
		flag = 1;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				int x = numarray[i];
				int y = numarray[j];
				if (mode_random)
				{
					x = helpnum1 * x;//double����ǰ 
					y = helpnum2 * y;
				}
				if (k == 3)
				{
					x = ((x % 32) + 32) % 32;
					y = ((y % 32) + 32) % 32;
				}
				if (LMR && x < y)
					continue;
				if (debugging_mode)
				{
					printf("(%d,%d)\t\t\t\t", x, y);
					cout << " " << (*array[k])(x, y) << " " << (*array_standard[k])(x, y) << endl;
					if (flag && (*array[k])(x, y) != (*array_standard[k])(x, y))
						flag = 0;
					continue;
				}
				if ((*array[k])(x, y) != (*array_standard[k])(x, y))
				{
					cout << name[k] << "����!" << endl;
					flag = 0;
					break;
				}
			}
			if (!flag)
				break;
		}
		if (flag)
			cout << name[k] << "��ȷ!" << endl;
		else if(debugging_mode&&!flag)
			cout << name[k] << "����!" << endl;
		if (debugging_mode)
			wait();
	}
}
void check_byteSwap(bool debugging_mode)
{
	int numarray[10] = {
		-10000,-12345567,0,1,10086,(1 << 31),(1 << 31) - 1,1024,2555555,999999
	};
	bool flag = 1;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				if (debugging_mode)
				{
					printf("(%x,\t%d,\t%d)\t", numarray[i], j, k);
					cout <<hex << byteSwap(numarray[i], j, k) << " " << byteSwap_standard(numarray[i], j, k) << endl;
					if (byteSwap(numarray[i], j, k) != byteSwap_standard(numarray[i], j, k))
					{
						flag = 0;
					}
				}
				else
				{
					if (byteSwap(numarray[i], j, k) != byteSwap_standard(numarray[i], j, k))
					{
						flag = 0;
						cout << "byteSwap����!" << endl;
						break;
					}
				}
			}
			if (!flag)
				break;
		}
		if (!flag)
			break;
	}
	if (flag)
		cout << "byteSwap��ȷ!" << endl;
	else if(debugging_mode&&!flag)
		cout << "byteSwap����!" << endl;
}
void wait()
{
	system("pause");
	system("cls");
}
void test()
{
	//void check_single(bool mode, bool debugging_mode,int left,int right)
	bool single_mode = 0;			//1Ϊint��ȫ��Χ���ģʽ  0Ϊ�ֶ������ⷶΧģʽ
	bool single_debugging_mode = 0;	//1Ϊdebugging��ʾ  //left rightȱʡ����ģʽѡ��
	//void check_single(bool mode, bool debugging_mode,int left,int right)
	cout << "��Ŀ����� absVal,negate,isTmax,bitCount[-100,100]��ʼ����" << endl;
	wait();
	check_single(single_mode, single_debugging_mode,-100,100);//0 0 �ֶ����
	wait();
	check_single(0, 1,-100,100);//�ֶ�debug��


	cout << "��Сһ��������" << endl;
	wait();
	check_single(0, 0, (1 << 31), (1 << 31) + 100);//��Сһ�����Զ����(101����)
	wait();


	cout << "��Сһ����debug����" << endl;
	wait();
	check_single(0, 1, (1 << 31), (1 << 31) + 100);//��Сһ�����Զ�debug��


	cout << "���һ��������" << endl;
	wait();
	check_single(0, 0, (1 << 31) - 101, (1 << 31) - 1);//���һ�����Զ����
	wait();

	cout << "���һ����debug����" << endl;
	wait();
	check_single(0, 1, (1 << 31) - 101, (1 << 31) - 1);//���һ�����Զ�debug��

	//void check_binary(bool mode_random, bool debugging_mode, bool LMR)
	cout << "˫Ŀ����� bitAnd,bitOr,bitXor,bitMask,addOK��ʼ����" << endl;
	wait();
	cout << "��ͨ����" << endl;
	wait();
	check_binary(0, 0, 0);
	wait();
	cout << "���������" << endl;
	wait();
	check_binary(1, 0, 0);
	wait();
	cout << "(x,y)����x>yʱ�Ĳ���" << endl;
	wait();
	check_binary(0, 0, 1);
	wait();

	cout << "��ͨdebug����" << endl;
	wait();
	check_binary(0, 1, 0);

	cout << "�����debug����" << endl;
	wait();
	check_binary(1, 1, 0);

	cout << "�����(x,y)����x>y debug����" << endl;
	wait();
	check_binary(1, 1, 1);


	//void check_byteSwap(bool debugging_mode)
	cout << "byteSwap����" << endl;
	wait();
	cout << "byteSwap��ͨ����" << endl;
	check_byteSwap(0);
	wait();
	cout << "byteSwap debug����" << endl;
	check_byteSwap(1);
	wait();

}