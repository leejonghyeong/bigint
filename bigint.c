#include <stdio.h>
#include <stdlib.h>

struct bigint_t{
    int* bignum;
    int length;
};

void bigint_free(struct bigint_t bigint){
    free(bigint.bignum);
}

void bigint_print(struct bigint_t bigint){
    int i;
    for(i = bigint.length - 1; i >= 0; i--){
        printf("%d",bigint.bignum[i]);
    }
}

// 주어진 숫자열과 길이를 받아 구조체 생성
//(포인터를 받으므로 길이를 따로 받아줘야 함)
struct bigint_t bigint_new(int *arr, int size){
    struct bigint_t bigint;

    bigint.bignum = arr;

    bigint.length = size;

    return bigint;
}

// 두 구조체가 각각 가르키는 숫자열의 '합'을 새로운 배열에 저장.
struct bigint_t bigint_add(struct bigint_t newint, struct bigint_t prevint){
    int *ArrOfNum;
    int i;
    int size, size1, size2;

    size1 = newint.length;
    size2 = prevint.length;
    
    if(size1>= size2){
        size = size1 + 1;
    }else{
        size = size2 + 1;
    }

    ArrOfNum = (int *)malloc(sizeof(int) * (size));
    
    for(i = 0; i < size; i++){
        ArrOfNum[i] = 0;
    }

    for(i = 0; i < size - 1; i++){
        ArrOfNum[i] += newint.bignum[i] + prevint.bignum[i];
        if(ArrOfNum[i] >= 10){
            ArrOfNum[i] -= 10;
            ArrOfNum[i + 1] += 1;
        }        
    }
    
    if(ArrOfNum[size - 1] == 0){
        size -= 1;
    }

    return bigint_new(ArrOfNum, size);
}


int main(){
    int i;
    int one[1] = {1};

    struct bigint_t prevint = bigint_new(one, 1);
    struct bigint_t newint = bigint_new(one, 1);
    struct bigint_t temp;

    for(i = 3; i <= 200; i++){
        temp = newint;
        newint = bigint_add(newint, prevint);
        if(i >= 5){
        bigint_free(prevint);
        }
        prevint = temp;
    }
    // 피보나치 합.
    // 3번 째부터 malloc으로 할당함 -> 3번째부터 free

    bigint_print(newint);
    bigint_free(prevint);
    bigint_free(newint);
}