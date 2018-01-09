#include "stdafx.h"
#include "stdio.h"
//#include <iostream>
#include "stdlib.h"
#include "math.h"


static int SBox[256] = { 0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, //0
0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, //1
0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, //2
0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, //3
0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, //4
0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, //5
0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, //6
0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, //7
0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, //8
0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, //9
0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, //A
0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, //B
0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, //C
0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, //D
0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, //E
0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16  //F
};

static int Inv_SBox[256] = { 0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,//0 
0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,//1 
0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,//2 
0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,//3 
0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,//4 
0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,//5 
0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,//6 
0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,//7 
0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,//8 
0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,//9 
0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,//A 
0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,//B
0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,//C
0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,//D
0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,//E
0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d //F
};

static int Rcon[4][11] = {                                                                                                 //轮常量
	{ 0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36 },
	{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
	{ 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 }
};

//字节替代
void SubByte(int a[4][4]) {
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++)
			a[i][j] = SBox[a[i][j]];
	}
}

//逆字节替代
void Inv_SubByte(int a[4][4]) {
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++)
			a[i][j] = Inv_SBox[a[i][j]];
	}
}

//行移位
void ShiftRow(int a[4][4]) {
	int t[4][4];
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++)
			t[i][j] = a[i][j];
	}
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++)
			a[i][j] = t[i][(j + i) % 4];
	}
}

//逆行移位
void Inv_ShiftRow(int a[4][4]) {
	int t[4][4];
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++)
			t[i][j] = a[i][j];
	}
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++)
			a[i][j] = t[i][(j - i + 4) % 4];
	}
}

//列混淆变换
int Mul2(int b) {
	if (b<0x80)
		return (b << 1) & 0xff;
	else
		return((b << 1) ^ 0x1b) & 0xff;
}

int Mul3(int b) {
	return Mul2(b) ^ b;
}

void MixColumn(int a[4][4]) {
	int t[4][4];
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++)
			t[i][j] = a[i][j];
	}
	for (int j = 0; j<4; j++) {
		a[0][j] = Mul2(t[0][j]) ^ Mul3(t[1][j]) ^ t[2][j] ^ t[3][j];
		a[1][j] = t[0][j] ^ Mul2(t[1][j]) ^ Mul3(t[2][j]) ^ t[3][j];
		a[2][j] = t[0][j] ^ t[1][j] ^ Mul2(t[2][j]) ^ Mul3(t[3][j]);
		a[3][j] = Mul3(t[0][j]) ^ t[1][j] ^ t[2][j] ^ Mul2(t[3][j]);
	}
}

//逆列混淆变化
int Mul9(int b) {
	return Mul2(Mul2(Mul2(b))) ^ b;
}

int Mulb(int b) {
	return Mul2(Mul2(Mul2(b))) ^ Mul2(b) ^ b;
}

int Muld(int b) {
	return Mul2(Mul2(Mul2(b))) ^ Mul2(Mul2(b)) ^ b;
}

int Mule(int b) {
	return Mul2(Mul2(Mul2(b))) ^ Mul2(Mul2(b)) ^ Mul2(b);
}

void Inv_MixColumn(int a[4][4]) {
	int t[4][4];
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++)
			t[i][j] = a[i][j];
	}
	for (int j = 0; j<4; j++) {
		a[0][j] = Mule(t[0][j]) ^ Mulb(t[1][j]) ^ Muld(t[2][j]) ^ Mul9(t[3][j]);
		a[1][j] = Mul9(t[0][j]) ^ Mule(t[1][j]) ^ Mulb(t[2][j]) ^ Muld(t[3][j]);
		a[2][j] = Muld(t[0][j]) ^ Mul9(t[1][j]) ^ Mule(t[2][j]) ^ Mulb(t[3][j]);
		a[3][j] = Mulb(t[0][j]) ^ Muld(t[1][j]) ^ Mul9(t[2][j]) ^ Mule(t[3][j]);
	}
}

//轮密钥相加
void AddRoundKey(int a[4][4], int Ekey[4][44], int nr) {
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			a[i][j] ^= Ekey[i][j + 4 * nr];
}

//密钥扩展
void KeyExpansion(int key[4][4], int Ekey[4][44], int nk, int nr) {
	int k, temp;
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<44; j++)
			Ekey[i][j] = 0;
	}
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++)
			Ekey[i][j] = key[i][j];
	}
	int t[4];
	k = nk;
	while (k<(4 * (nr + 1))) {
		for (int i = 0; i<4; i++)
			t[i] = Ekey[i][k - 1];
		if (k%nk == 0) {
			temp = t[0];
			t[0] = t[1];
			t[1] = t[2];
			t[2] = t[3];
			t[3] = temp;
			for (int i = 0; i<4; i++)
				t[i] = SBox[t[i]];
			for (int j = 0; j<4; j++)
				t[j] ^= Rcon[j][k / 4];
		}
		for (int i = 0; i<4; i++)
			Ekey[i][k] = Ekey[i][k - 1] ^ t[i];
		k++;
	}
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

//AES加密
int Encrypt(int key[4][4], int EnResult[25][4][4], int block) {
	
	int nk = 4, nr = 10;
	int Ekey[4][44];
	int OrigText[25][4][4];
	//int temp[4][4];
	char input[400];
	int len;
	int flag = 0;
	int t = 0;

	printf("\n请输入要加密的消息(以回车键结束)：\n");
	getchar();
	gets_s(input);
	len = mystrlen(input);
	block = len / 16 + 1;
	for (int i = 0; i<block - 1; i++) {
		for (int j = 0; j<4; j++) {
			for (int k = 0; k<4; k++) {
				OrigText[i][j][k] = input[i * 16 + j * 4 + k];
			}
		}
	}

	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++) {
			if ((input[(block - 1) * 16 + i * 4 + j] != '\0') && (!flag))
				OrigText[block - 1][i][j] = input[(block - 1) * 16 + i * 4 + j];
			else {
				flag = 1;
				OrigText[block - 1][i][j] = ' ';
			}
		}
	}

	while (t<block) {
		KeyExpansion(key, Ekey, nk, nr);
		AddRoundKey(OrigText[t], Ekey, 0);
		printf("\n");

		for (int i = 1; i<nr; i++) {
			SubByte(OrigText[t]);
			ShiftRow(OrigText[t]);
			MixColumn(OrigText[t]);
			AddRoundKey(OrigText[t], Ekey, i);
		}

		SubByte(OrigText[t]);
		ShiftRow(OrigText[t]);
		AddRoundKey(OrigText[t], Ekey, nr);

		t++;
	}
	for (int i = 0; i<block; i++)
		for (int j = 0; j<4; j++)
			for (int k = 0; k<4; k++)
				EnResult[i][j][k] = OrigText[i][j][k];
	printf("\n\n\n");
	return block;
}


//AES解密
void Decrypt(int key[4][4], int EnResult[25][4][4], int block) {
	//system("cls");
	int nk = 4, nr = 10;
	int Ekey[4][44];
	char input[400];
	int t = 0;

	while (t<block) {
		KeyExpansion(key, Ekey, nk, nr);
		AddRoundKey(EnResult[t], Ekey, nr);

		for (int i = nr - 1; i>0; i--) {
			Inv_SubByte(EnResult[t]);
			Inv_ShiftRow(EnResult[t]);
			AddRoundKey(EnResult[t], Ekey, i);
			Inv_MixColumn(EnResult[t]);

		}

		Inv_SubByte(EnResult[t]);
		Inv_ShiftRow(EnResult[t]);
		AddRoundKey(EnResult[t], Ekey, 0);

		t++;
	}

	printf("\n\n\n");
}

//CMAC
void AES4CMACL(int key[4][4],int Zero[4][4],int L[4][4]) {
	int nk = 4, nr = 10;
	int Ekey[4][44];
	int a[4][4];
	for (int i = 0; i < 4; i++) 
		for (int j = 0; j < 4; j++) 
			a[i][j] = Zero[i][j];
	KeyExpansion(key, Ekey, nk, nr);
	AddRoundKey(a, Ekey, 0);
	
	for (int i = 1; i < nr; i++) {
		SubByte(a);
		ShiftRow(a);
		MixColumn(a);
		AddRoundKey(a, Ekey, i);
	}
	SubByte(a);
	ShiftRow(a);
	AddRoundKey(a, Ekey, nr);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			L[i][j] = a[i][j];
	
}

void GenerateK1K2(int key[4][4], int K1[4][4], int K2[4][4]) {
	int L[4][4],t[4][4];
	int MSB = 0;
	int Zero[4][4] = {
		{ 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00 },
	};
	AES4CMACL(key, Zero, L);
	for (int i = 3; i >= 0; i--) {
		for (int j = 3; j >= 0; j--) {
			t[i][j] = L[i][j];
			K1[i][j] = Mul2(t[i][j]) + MSB;
			MSB = ((L[i][j] & 0x80) == 0x80);
		}
	}

	for (int i = 3; i >= 0; i--) {
		for (int j = 3; j >= 0; j--) {
			t[i][j] = L[i][j];
			t[i][j] = Mul2(t[i][j]) + MSB;
			K2[i][j] = Mul2(t[i][j]) + MSB;
			MSB = ((L[i][j] & 0x80) == 0x80);
		}
	}
	MSB = 0;
}

void CMAC(int key[4][4]) {
	int K1[4][4], K2[4][4];
	int M[25][4][4], C[25][4][4];
	int len = 0, block = 0;
	char input[400];

	GenerateK1K2(key, K1, K2);
	printf("\n请输入要加密的消息(最大400,以回车键结束):\n");
	getchar();
	gets_s(input);
	len = mystrlen(input);

	if (len % 16 == 0) {
		block = len / 16;
		for (int i = 0; i<block; i++) 
			for (int j = 0; j<4; j++) 
				for (int k = 0; k<4; k++)
					M[i][j][k] = input[i * 16 + j * 4 + k];
		
		AES4CMACL(key, M[0], C[0]);
		for (int i = 1; i < block - 1; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					C[i - 1][j][k] = M[i][j][k] & C[i - 1][j][k];
					AES4CMACL(key, C[i-1], C[i]);
				}
			}
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				C[block - 2][i][j] = C[block - 2][i][j] & M[block - 1][i][j];
				C[block - 2][i][j] = C[block - 2][i][j] & K1[i][j];
				AES4CMACL(key, C[block - 2], C[block - 1]);
			}
		}
		printf("CMAC加密结果为:\n");
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				printf("%x ", C[block-1][i][j]);
	}

	if (len % 16 != 0) {
		block = len / 16 + 1;
		input[len] = 1;
		for (int i = len + 1; i < block * 16; i++)
			input[i] = 0;
		for (int i = 0; i<block; i++)
			for (int j = 0; j<4; j++)
				for (int k = 0; k<4; k++)
					M[i][j][k] = input[i * 16 + j * 4 + k];

		AES4CMACL(key, M[0], C[0]);
		for (int i = 1; i < block - 1; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					C[i - 1][j][k] = M[i][j][k] & C[i - 1][j][k];
					AES4CMACL(key, C[i - 1], C[i]);
				}
			}
		}

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				C[block - 2][i][j] = C[block - 2][i][j] & M[block - 1][i][j];
				C[block - 2][i][j] = C[block - 2][i][j] & K2[i][j];
				AES4CMACL(key, C[block - 2], C[block - 1]);
			}
		}
		printf("CMAC加密结果为:\n");
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				printf("%x ", C[block-1][i][j]);
	}
}

int main()
{
	system("cls");
	int choose;
	int key[4][4];
	//int Col[4][4];
	int EnResult[25][4][4];
	int block = 0;
	int T[4][4];

	printf("班级 :   信息工程1304\n");
	printf("姓名 :   王亦凡\n");
	printf("学号 :   3130100597\n\n");

	printf("\n请输入加密密钥（128bit，16进制）：\n");
	for (int i = 0; i<4; i++)
		for (int j = 0; j<4; j++)
			scanf_s("%x", &key[i][j], 17);

loop:
	printf("\n 0 :Exit\n 1 :AES消息加解密\n 2: AES_CMAC_128 \n");
	printf("\nPlease input your choice: ");
	scanf_s("%d", &choose);
	switch (choose)
	{
	case 1:
		block=Encrypt(key, EnResult, block);
		printf("经过AES加密后的消息为:\n");
		for (int i = 0; i < block;i++)
			for (int j = 0; j<4; j++)
				for (int k = 0; k < 4; k++)
					printf("  %x", EnResult[i][j][k]);

		printf("\n");
		printf("\n\n经过AES解密后的消息为:\n");
		Decrypt(key, EnResult, block);
		for (int i = 0; i < block;i++)
			for (int j = 0; j<4; j++)
				for (int k = 0; k < 4; k++)
					printf("%c", EnResult[i][j][k]);
		goto loop;

	case 2: 
		CMAC(key);
		printf("\n");
		goto loop;

	case 0: exit(0);
	}
	//system("pause");    
	return 0;
}



