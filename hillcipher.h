#ifndef HILL_CRYPTO_HILLCIPHER_H
#define HILL_CRYPTO_HILLCIPHER_H

#include <stdio.h>
#include <string.h>

void Data_Input(char *_string_data);    //	문자열 입력 받는 함수
void Add_Padding(char *_string_data);   //	패딩 추가 함수
void Mod_26(int (*target_matrix)[2]);   //  mod26 함수
void Hill_Dec(char *_enc_data, char *_dec_data);    //	Hill 복호화 함수
void Hill_Enc(char *_input_data, char *_enc_data);  //	Hill 암호화 함수
void Del_Padding(char *_enc_data, char *_dec_data); //  패딩 삭제 함수
void Matrix_Mul_Enc(int (*_enc_matrix)[2], int (*_temp_matrix)[2]);     //	행렬의 곱셈 계산 함수(암호화)
void Matrix_Mul_Dec(int (*_dec_matrix)[2], int (*_temp_matrix)[2]);     //	행렬의 곱셈 계산 함수(복호화)
void Matrix_To_Data(int (*_temp_matrix)[2], char *_string_data, int *_point_to_data);       //	숫자 메트릭스를 문자열로 저장 하는 함수
void Data_To_Matrix(int (*_result_matrix)[2], char *_string_data, int *_point_to_data);     //	문자열을 2*2배열에 숫자로 저장 하는 함수

#endif HILL_CRYPTO_HILLCIPHER_H
