#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 8           /* 解を格納する配列の要素数 */
#define ULIMIT 100     /* 累乗の繰り返し回数 */
#define RESLIMIT 10000000UL /* 7桁の符号なし整数の最大値+1 */

void printresult(unsigned long result[]); /* 結果の出力 */
void power3(unsigned long result[]);      /* 3を掛ける */

int main(void)
{
    unsigned long result[N] = {0};
    int i; /* 繰り返しのカウンタ */

    /* 初期値の設定 */
    result[0] = 1; /* 3の0乗 */

    /* 累乗の計算 */
    for(i=0; i<=ULIMIT; ++i){
        printf("n=%3d: ", i);
        printresult(result); /* 結果の出力 */
        power3(result);      /* 3を掛ける */
    }

    return 0;
}

/* 結果の出力 */
void printresult(unsigned long result[])
{
    int j;
    int started = 0; /* 先頭の0をスキップするためのフラグ */

    for (j=N-1; j>=0; --j){
        if(!started){
            if(result[j] != 0){
                printf("%lu", result[j]);
                started = 1;
            }
        } else {
            printf("%07lu", result[j]); /* 7桁ゼロ埋め */
        }
    }
    if(!started) printf("0"); /* 全部0なら0を出力 */
    printf("\n");
}

/* power3, 3を掛ける */
void power3(unsigned long result[])
{
    int i;
    unsigned long midres[N] = {0};

    for (i=0; i<N; ++i){
        midres[i] += result[i]*3;
        if(midres[i] >= RESLIMIT){ /* 桁あふれ */
            if(i != N-1){
                midres[i+1] += midres[i] / RESLIMIT;
            } else { /* 多倍長変数が桁あふれ */
                fprintf(stderr,"桁あふれが発生しました\n");
                exit(1);
            }
            midres[i] %= RESLIMIT;
        }
    }
    for(i=0; i<N; ++i)
        result[i] = midres[i];
}
