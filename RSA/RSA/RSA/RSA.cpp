// RSA.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include<stdio.h> 
#include<conio.h> 
#include<stdlib.h> 
#include<math.h> 
#include<string.h> 

int cypher;
long int PU[2], PR[2];//��Կ ˽Կ

int IsPrime(long int);
void gen_e();
long int gen_d(long int);
int encrypt();

unsigned int DJBHash(char*, long int);
long int p, q, n, msg, fn, flag, e, d, i, j;

int IsPrime(long int pr)
{
	int i;
	j = sqrt(pr);
	for (i = 2; i <= j; i++)
	{
		if (pr%i == 0)
			return 0;
	}
	return 1;
}



void gen_e()
{
	int k, i;
	k = 0;
	for (i = 2; i < fn; i++)
	{
		if (fn%i == 0)
			continue;
		flag = IsPrime(i);
		if (flag == 1 && i != p&&i != q)
		{
			e = i;
			flag = gen_d(e);
			if (flag>0)
			{
				d = flag;
				break;
			}
		}
	}
}

long int gen_d(long int x)
{
	long int k = 1;
	while (1)
	{
		k = k + fn;
		if (k%x == 0)
			return(k / x);
	}
}

int encrypt()
{


	int temp = msg%n;

	int result = 1;
	//�������϶����Ƶķ��� 
	while (PU[0] >= 1) {
		if (PU[0] % 2 != 0) {
			result = (result*temp) % n;
		}
		temp = (temp*temp) % n;
		PU[0] /= 2;
	}
	return result;
}


long int RSA_En(long int M)
{
	printf("\n������һ������\n");
	scanf_s("%d", &p);
	flag = IsPrime(p);
	if (flag == 0)
	{
		printf("\n���������\n");
		getchar();
		exit(1);
	}

	printf("\n��������һ������\n");
	scanf_s("%d", &q);
	flag = IsPrime(q);
	if (flag == 0 || p == q)
	{
		printf("\n��������\n");
		getchar();
		exit(1);
	}


	msg = M;
	n = p*q;

	fn = (p - 1)*(q - 1);
	gen_e();
	printf("\neֵ��dֵ\n");
	printf("\n%d  %d\n", e, d);

	PU[0] = e;
	PR[0] = d;

	PU[1] = PR[1] = n;


	cypher = encrypt();
	printf("ͨ��RSA�����Ľ��Ϊ��%d\n", cypher);


	return cypher;
}



int RSA_De(int cypher)
{
	int temp = cypher%n;

	int result = 1;
	//�������϶����Ƶķ��� 
	while (PR[0] >= 1) {
		if (PR[0] % 2 != 0) {
			result = (result*temp) % n;
		}
		temp = (temp*temp) % n;
		PR[0] /= 2;
	}

	printf("ͨ��RSA�������Ľ��Ϊ��%d\n", result);
	return result;
}


int hash(long int m, long int n)
{
	long int result;
	result = ((m << 5) + m) + n; /* hash * 33 + m */
	result = (int)result % 100;
	return result;
}

int HMAC(int P[400], int len) {
	int IV = 17;
	int K_ = 17, ipad = 54, opad = 97;
	int Si, So, temp, temp1, temp2;

	//����S1��S0
	Si = K_^ipad;
	So = K_^opad;

	temp1 = hash(Si, IV);
	temp2 = hash(So, IV);
	temp = hash(P[0], temp1);
	temp = hash(temp, temp2);
	//֮���Hash
	for (int i = 1; i<len; i++) {
		temp = hash(P[i], temp);
		temp = hash(temp, temp1);
		temp = hash(temp, temp2);
		printf("temp = %d\n", temp);
	}
	
	return temp;
}

int mystrlen(const char s[])
{
	int i = 0;
	if (s == NULL)
	{
		return 0;
	}

	while (s[i] != '\0')
	{
		++i;
	}
	return i;
}

void main() {
	long int M, M_1, M_2, num_rsa;
	char input[400];
	int len, OrigText[400];


	printf("�༶ :   ��Ϣ����1304\n");
	printf("���� :   ���ෲ\n");
	printf("ѧ�� :   3130100597\n\n");
	
	/*printf("��������Ҫ���ܵ�����(RSA):\n");
	scanf_s("%d", &num_rsa);
	M_1 = RSA_En(num_rsa);
	M_2 = RSA_De(M_1);
	if (M_2 == num_rsa) {
		printf("RSA�����㷨��֤��ȷ!\n");
	}*/

	printf("��������Ҫ���ܵ���Ϣ(���400):\n");
	getchar();
	gets_s(input);
	len = mystrlen(input);

	for (int i = 0; i<len; i++) {
		OrigText[i] = input[i];
	}


	printf("\n");
	M = HMAC(OrigText, len);

	printf("\n����HMAC����ǩ�����ܺ��M = %d\n", M);


	M_1 = RSA_En(M);

	M_2 = RSA_De(M_1);

	if (M_2 == M) {
		printf("RSA_HMAC����ǩ����֤��ȷ!\n");
	}

	system("PAUSE");

}


