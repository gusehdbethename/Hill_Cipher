#include "hillcipher.h"

//	문자열 입력 받는 함수
void Data_Input(char *_string_data){
    printf("문자를 입력해 주세요 : ");
    scanf("%s", _string_data);
}

//	패딩 추가 함수
void Add_Padding(char *_string_data){
    int i;  //  반복문 노예 변수
    int len_input_data;	//	입력 받은 문자열 길이

    //	입력 받은 문자열의 길이
    len_input_data = strlen(_string_data);

    //	패딩 추가
    if((len_input_data%4) != 0){
        for(i=0; i<len_input_data + (4 - (len_input_data%4)); i++){
            if(i>=len_input_data){
                _string_data[i] = 'Z';
            }
        }
    }
}

//	패딩 삭제 함수
void Del_Padding(char *_enc_data, char *_dec_data){
    int len_data; 	// 암호화된 문자열 길이
    char temp_array[4];     //  암호화된 문자열 중 끝 4글자
    int i;  //  반복문 노예 변수

    //  암호화된 문자열 길이 계산
    len_data = strlen(_enc_data);

    //  암호화된 문자열 중 끝 4글자를 temp_array 배열에 저장
    for(i=0;i<4;i++){
        temp_array[i] = _enc_data[(len_data-4)+i];
    }

    //  temp_array 값에 따라 패딩 삭제
    if(temp_array[0]=='Z' && temp_array[2]=='Z' && temp_array[3]=='X'){
        _dec_data[(len_data-4)+1] = NULL;
        _dec_data[(len_data-4)+2] = NULL;
        _dec_data[(len_data-4)+3] = NULL;
    }else if(temp_array[2]=='Z' && temp_array[3]=='X'){
        _dec_data[(len_data-4)+2] = NULL;
        _dec_data[(len_data-4)+3] = NULL;
    }else if(temp_array[2]=='Z') {
        _dec_data[(len_data - 4) + 3] = NULL;
    }
}

//	문자열을 2*2배열에 숫자로 저장 하는 함수
void Data_To_Matrix(int (*_result_matrix)[2], char *_string_data, int *_point_to_data){
    int i, j, k;	//	반복문 노예 변수

    k = *_point_to_data; //  배열 인자값으로 포인터를 쓸 수 없음

    //	문자열을 2*2배열에 숫자로 저장
    for(i=0; i<2;i++){
        for(j=0; j<2; j++){
            _result_matrix[i][j] = _string_data[k] - 65;
            k++;
        }
    }

    *_point_to_data = k;
}

//	숫자 메트릭스를 문자열로 저장하는 함수
void Matrix_To_Data(int (*_temp_matrix)[2], char *_string_data, int *_point_to_data){
    int i, j, k;	//	반복문 노예 변수

    *_point_to_data -= 4;
    k = *_point_to_data;	//	배열 인자값으로 포인터를 쓸 수 없음

    //	암호화된 문자를 1차원 배열에 문자로 저장
    for(i=0; i<2; i++){
        for(j=0; j<2; j++){
            _string_data[k] = _temp_matrix[i][j] + 65;
            k++;
        }
    }

    *_point_to_data = k;
}

//	행렬의 곱셈 계산 함수(암호화)
void Matrix_Mul_Enc(int (*_enc_matrix)[2], int (*_temp_matrix)[2]){
    int key_matrix[2][2] = {{0,1},{1,2}}; 	// 	key 행렬(배열)

    //	행렬 연산
    _enc_matrix[0][0] = _temp_matrix[0][0] * key_matrix[0][0] + _temp_matrix[0][1] * key_matrix[1][0];
    _enc_matrix[0][1] = _temp_matrix[0][0] * key_matrix[0][1] + _temp_matrix[0][1] * key_matrix[1][1];
    _enc_matrix[1][0] = _temp_matrix[1][0] * key_matrix[0][0] + _temp_matrix[1][1] * key_matrix[1][0];
    _enc_matrix[1][1] = _temp_matrix[1][0] * key_matrix[0][1] + _temp_matrix[1][1] * key_matrix[1][1];

    Mod_26(_enc_matrix);
}

//	행렬의 곱셈 계산 함수(복호화)
void Matrix_Mul_Dec(int (*_dec_matrix)[2], int (*_temp_matrix)[2]){
    int key_inverse_matrix[2][2] = {{-2,1},{1,0}}; 	// 	key 역행렬(배열)

    //	행렬 연산
    _dec_matrix[0][0] = _temp_matrix[0][0] * key_inverse_matrix[0][0] + _temp_matrix[0][1] * key_inverse_matrix[1][0];
    _dec_matrix[0][1] = _temp_matrix[0][0] * key_inverse_matrix[0][1] + _temp_matrix[0][1] * key_inverse_matrix[1][1];
    _dec_matrix[1][0] = _temp_matrix[1][0] * key_inverse_matrix[0][0] + _temp_matrix[1][1] * key_inverse_matrix[1][0];
    _dec_matrix[1][1] = _temp_matrix[1][0] * key_inverse_matrix[0][1] + _temp_matrix[1][1] * key_inverse_matrix[1][1];

    Mod_26(_dec_matrix);
}

//  mod26 함수
void Mod_26(int (*target_matrix)[2]){
    int i,j;    //	반복문 노예 변수

    //	mod 26
    for(i=0; i<2; i++){
        for(j=0; j<2; j++) {
            //  행렬의 원소가 - 경우 계산식
            if (target_matrix[i][j] < 0) {
                //  행렬의 원소가 26인 경우 처리
                target_matrix[i][j] += (target_matrix[i][j] % -26 == 0) ? ((target_matrix[i][j] / -26) * 26) : (((target_matrix[i][j] / -26) + 1) * 26);
            } else {    //  행렬의 원소가 + 경우 계산식
                target_matrix[i][j] %= 26;
            }
        }
    }
}

//	Hill 암호화 함수
void Hill_Enc(char *_input_data, char *_enc_data){
    int temp_matrix[2][2];		//	임시 2*2 행렬(배열)
    int encryption_matrix[2][2];	//	암호화된 2*2 행렬(배열)
    int len_input_data; 	// 입력받은 문자열 길이
    int point_input_data = 0;		//	데이터 저장 위치(배열의 인덱스)를 가리키는 변수
    int i;	// 반복문 노예 변수

    //	입력받은 문자열의 길이
    len_input_data = strlen(_input_data);

    //	암호화
    for(i=0; i<len_input_data/4; i++){
        Data_To_Matrix(temp_matrix, _input_data, &point_input_data);
        Matrix_Mul_Enc(encryption_matrix, temp_matrix);
        Matrix_To_Data(encryption_matrix, _enc_data, &point_input_data);
    }
}

//	Hill 복호화 함수
void Hill_Dec(char *_enc_data, char *_dec_data){
    int temp_matrix[2][2];		//	임시 2*2 행렬(배열)
    int decryption_matrix[2][2];	//	복호화된 2*2 행렬(배열)
    int len_input_data; 	// 암호화된 문자열 길이
    int point_input_data = 0;		//	데이터 저장 위치(배열의 인덱스)를 가리키는 변수
    int i;	// 반복문 노예 변수

    //  암호화된 문자열의 길이
    len_input_data = strlen(_enc_data);

    //	복호화
    for(i=0; i<len_input_data/4; i++){
        Data_To_Matrix(temp_matrix, _enc_data, &point_input_data);
        Matrix_Mul_Dec(decryption_matrix, temp_matrix);
        Matrix_To_Data(decryption_matrix, _dec_data, &point_input_data);
    }
}