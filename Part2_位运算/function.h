#pragma once
#include<iostream>
#include<string>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
int absVal_standard(int x);
int negate_standard(int x);
int isTmax_standard(int x);
int bitCount_standard(int x);

int bitAnd_standard(int x, int y);
int bitOr_standard(int x, int y);
int bitXor_standard(int x, int y);
int bitMask_standard(int highbit, int lowbit);
int byteSwap_standard(int x, int n, int m);
int addOK_standard(int x, int y);

int absVal(int x);
int negate(int x);
int isTmax(int x);
int bitCount(int x);
int bitAnd(int x, int y);
int bitOr(int x, int y);
int bitXor(int x, int y);
int bitMask(int highbit, int lowbit);//要求只使用 ! ~ & ^ | + << >> ；运算次数不超过 16次
int byteSwap(int x, int n, int m);
int addOK(int x, int y);
void check_single(bool mode, bool debugging_mode, int left = 0, int right = 0);//单目运算符检测程序
void check_binary(bool mode_random, bool debugging_mode, bool LMR);//双目运算符检测程序
void check_byteSwap(bool debugging_mode);
void test();