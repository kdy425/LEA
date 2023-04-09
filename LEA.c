#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LEA.h"

static const uint32_t LEA_delta[8] = {	//delta 정의
	0xc3efe9db,
	0x44626b02,
	0x79e27c8a,
	0x78df30ec,
	0x715ea49e,
	0xc785da0a,
	0xe04ef22a,
	0xe5c40957
};


static int LEA_ROL(uint32_t number, uint32_t value)	//value 를 number 만큼 ROL
{
	return (value << number) | (value >> (32 - number));
}

static int LEA_ROR(uint32_t number, uint32_t value)
{
	return (value >> number) | (value << (32 - number));
}

static uint32_t LEA_Add(uint32_t a, uint32_t b)
{
	return (a + b);
}

static uint32_t LEA_Sub(uint32_t a, uint32_t b)
{
	return (a - b);
}





void LEA_KeySchedule(unsigned char* K, uint32_t* RK)	//K : 비밀키 RK : 라운드키
{
	int i;
	uint32_t T[4] = { 0 };	//라운드키 유도 임시 변수

	memcpy(T, K, 16);	//T = K

	for (i = 0; i < 24; i++)
	{
		T[0] = LEA_ROL(1, LEA_Add(T[0], LEA_ROL(i, LEA_delta[i % 4]))); 
		T[1] = LEA_ROL(3, LEA_Add(T[1], LEA_ROL(i + 1, LEA_delta[i % 4])));
		T[2] = LEA_ROL(6, LEA_Add(T[2], LEA_ROL(i + 2, LEA_delta[i % 4])));
		T[3] = LEA_ROL(11, LEA_Add(T[3], LEA_ROL(i + 3, LEA_delta[i % 4])));

		RK[i * 6 + 0] = T[0];
		RK[i * 6 + 1] = T[1];
		RK[i * 6 + 2] = T[2];
		RK[i * 6 + 3] = T[1];
		RK[i * 6 + 4] = T[3];
		RK[i * 6 + 5] = T[1];
	}
}




static void LEA_Encrypt(uint32_t* Xout, uint32_t* Xin, uint32_t* RKe)
{
	Xout[0] = LEA_ROL(9, LEA_Add(Xin[0] ^ RKe[0], Xin[1] ^ RKe[1]));
	Xout[1] = LEA_ROR(5, LEA_Add(Xin[1] ^ RKe[2], Xin[2] ^ RKe[3]));
	Xout[2] = LEA_ROR(3, LEA_Add(Xin[2] ^ RKe[4], Xin[3] ^ RKe[5]));
	Xout[3] = Xin[0];
}


void LEA_Encrypt_(uint32_t* RoundKey, unsigned char* plaintext, unsigned char* ciphertext)
{
	int i;
	uint32_t X_out[4];
	uint32_t X_in[4];
	

	memcpy(X_in, plaintext, 16);

	for (i = 0; i < 24; i++)
	{
		LEA_Encrypt(X_out, X_in, &RoundKey[i * 6]);
		memcpy(X_in, X_out, 16);
	}

	memcpy(ciphertext, X_in, 16);
}



int main()
{
	int i;

	u1 K[16] =
	{
		0x52, 0x33, 0x76, 0x65, 0x40, 0x6c, 0x69, 0x6e, 0x47, 0x74, 0x48, 0x65, 0x4b, 0x45, 0x59, 0x21
	};

	u1 P[16] =
	{
		0x1f, 0x31, 0x22, 0x39, 0x28, 0x56, 0x14, 0x37, 0x8d, 0xd9, 0xfa, 0xdb, 0xc1, 0xa5, 0x5e, 0x7a
	};

	u4 RoundKey[144] = { 0, };
	u1 C[16] = { 0 };

	LEA_KeySchedule(K, RoundKey);

	printf("Key : ");
	for (i = 0; i < 16; i++)
	{
		printf("0x%02x ", K[i]);
	}
	printf("\n\n");

	printf("Plaintext :  ");
	for (i = 0; i < 16; i++)
	{
		printf("0x%02x ", P[i]);
	}
	printf("\n\n");

	LEA_Encrypt_(RoundKey, P, C);
	printf("Ciphertext : ");
	for (i = 0; i < 16; i++)
	{
		printf("0x%02x ", C[i]);
	}
	printf("\n\n");

	return 0;
}
