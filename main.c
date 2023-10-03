#include "hillcipher.h"

int main(void){
    char input_data[32] = "";	//	입력 받은 문자열 저장 배열
    char encryption_data[32] = "";	//	암호화 된 문자열 저장 배열
    char decryption_data[32] = "";	//	복호화 된 문자열 저장 배열

    Data_Input(input_data);	//	문자열 입력 함수 호출
//    Add_Padding(input_data);	//	패딩 추가 함수 호출

    Hill_Enc(input_data, encryption_data);	//	Hill 암호화 함수 호출
    printf("암호화 된 데이터 : %s\n", encryption_data);	//	암호화 결과 출력

    Hill_Dec(encryption_data, decryption_data);  //	Hill 복호화 함수 호출
//    Del_Padding(encryption_data, decryption_data);  //  패딩 삭제 함수 호출
    printf("복호화 된 데이터 : %s\n", decryption_data);	//	복호화 결과 출력

    return 0;
}