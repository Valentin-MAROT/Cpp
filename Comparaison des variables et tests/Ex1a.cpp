#include <cstdio>
#include <iostream>

int fun1a(int  x) {
    x++;
    return x;
}

int fun1b(int &x) {
    x++;
    return x;
}

int fun1c(int &&x) {
    x++;
    return x;
}

int fun1d(int *x) {
    (*x)++;
    return *x;
}

int main() {
    // constante
    fun1a(4);
    //fun1b(4); Prend une lvalue
    fun1c(4);
    //fun1d(&4); Prend une rvalue

    // variable sans modificateur
    int i = 4;
    fun1a(i);
    fun1b(i);
    //fun1c(i); Prend une rvalue
    fun1d(&i);

    // variable non modifiable
    const int j = 4;
    fun1a(j);
    //fun1b(j); La fonction modifie la variable
    //fun1c(j); La fonction modifie la variable
    //fun1d(&j); La fonction modifie la variable

    // référence sur une lvalue
    int &k = i;
    fun1a(k);
    fun1b(k);
    //fun1c(k); nécessite une rvalue
    fun1d(&k);

    // référence sur une lvalue constante
    const int &m = i;
    fun1a(m);
    //fun1b(m); valeur modifié dans la fonction alors qu'elle est constante
    //fun1c(m); valeur modifié dans la fonction alors qu'elle est constante
    //fun1d(&m); valeur modifié dans la fonction alors qu'elle est constante

    // référence sur une rvalue
    fun1a(i+4);
    //fun1b(i+4); rvalue donnée au lieu d'une lvalue
    fun1c(i+4);
    //fun1d(&(i+4)); nécessite une lvalue

    return EXIT_SUCCESS;
}
