#ifndef _LEA_H_
#define _LEA_H_



typedef unsigned char u1; //1byte
typedef unsigned long int u4; //4byte 

typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;


extern void LEA_KeySchedule(unsigned char* K, uint32_t* RoundKey);
extern void LEA_Encrypt_(uint32_t* RoundKey, unsigned char* plaintext, unsigned char* ciphertext);

#else
#endif
