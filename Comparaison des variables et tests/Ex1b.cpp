#include <cstdlib>

int fun1a(const int  x) {
    return x+1;
}

int fun1b(const int &x) {
    return x+1;
}

int fun1c(const int &&x) {
    return x+1;
}

int fun1d(const int *x) {
    return (*x)+1;
}

int fun1e(int const *x) {
    return (*x)+1;
}

int fun1f(const int* const x) {
    return (*x)+1;
}

int funPConst(int * const x) {
    return (*x)+1;
}

int main() {
    // constante
    fun1a(4);
    fun1b(4);
    fun1c(4);
    //fun1d(&4); nécessite une lvalue
    //fun1e(&4); nécessite une lvalue
    //fun1f(&4); nécessite une lvalue

    // variable sans modificateur
    int i = 4;
    fun1a(i);
    fun1b(i);
    //fun1c(i); nécessite une rvalue
    fun1d(&i);
    fun1e(&i);
    fun1f(&i);

    // variable non modifiée
    const int j = 4;
    fun1a(j);
    fun1b(j);
    //fun1c(j); nécessite une rvalue
    fun1d(&j);
    fun1e(&j);
    fun1f(&j);

    // référence sur une lvalue
    int &k = i;
    fun1a(k);
    fun1b(k);
    //fun1c(k); nécessite une rvalue
    fun1d(&k);
    fun1e(&k);
    fun1f(&k);

    // référence sur une lvalue constante
    const int &m = i;
    fun1a(m);
    fun1b(m);
    //fun1c(m); nécessite une rvalue
    fun1d(&m);
    fun1e(&m);
    fun1f(&m);

    // référence sur une rvalue
    fun1a(i+4);
    fun1b(i+4);
    fun1c(i+4);
    //fun1d(&(i+4)); nécessite une lvalue
    //fun1e(&(i+4)); nécessite une lvalue
    //fun1f(&(i+4)); nécessite une lvalue

    return EXIT_SUCCESS;
}
