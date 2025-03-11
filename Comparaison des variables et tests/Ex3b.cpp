#include <cstdio>
#include <cstdlib>
#include <utility>

// But: comprendre quels sont les différentes déclarations possibles et les différentes combinaisons d'appel.
// A savoir:
// 1) décommenter une fonction, et regarder quels sont les appels qui fonctionnent
// 2) essayer de décommenter deux fonctions, et voir quelles celles qui sont compatibles, et les appels qu'elles prennent en charge.

 int fun(int *x)             { printf("call fun(int *x)\n"); return *x; }
// int fun(const int *x)       { printf("call fun(const int *x)\n"); return *x; }
// int fun(int const *x)       { printf("call fun(int const *x)\n"); return *x; }
 int fun(const int* const x) { printf("call fun(const int* const x)\n"); return *x; }

int main() {
    // pointeur
    int                 a = 3;
    int*                A = &a;
    const int*          B = A;
    int* const          C = A;
    const int* const    D = A;

    printf("calling fun with %-11s => ","int*"); //1,2,3,4
    fun(A);
    printf("calling fun with %-11s => ","const int*");//2,3,4
    fun(B);
    printf("calling fun with %-11s => ","int* const"); //1,2,3,4
    fun(C);
    printf("calling fun with %-11s => ","const int* const");//2,3,4
    fun(D);

    return EXIT_SUCCESS;
}
