#include <iostream>
#include <cmath>

using namespace std;

struct complex{
    float re;
    float im;
    complex():re(0),im(0){
        cout << "Default constructor" << endl;
    };
    complex(float r):re(r),im(0){
        cout << "Constructor with one argument" << endl;
    };
    complex(float r, float i):re(r),im(i){
        cout << "Constructor with two arguments" << endl;
    };
    ~complex(){
        cout << "Destructor" << endl;
    };
    complex(const complex& c):re(c.re),im(c.im){
        cout << "Copy constructor" << endl;
    };
    void const view(){
        cout << re << " + " << im << "i" << endl;
    }

    //Cette fonction appelle le constructeur car on ne donne pas une réference à un objet mais un objet
    float norm(complex c){ 
        cout << "Norm" << endl;
        return sqrt(c.re*c.re+c.im*c.im);
    }

    complex& operator=(const complex& c){
        cout << "Operator = in:" << this << " out:" << &c << endl;
        if(this == &c) return *this;
        re = c.re;
        im = c.im;
        return *this;
    }
    friend ostream& operator<<(ostream& os, const complex& c){
        os << c.re << " + " << c.im << "i";
        return os;
    }
};

complex sqr(const complex &c){
    cout << "Sqr" << endl;
    return complex(c.re*c.re-c.im*c.im,2*c.re*c.im);
}


complex operator+(const complex& c1, const complex& c2){
    cout << "Operator + c1:" << c1 << " c2:" << c2 << endl;
    return complex(c1.re+c2.re,c1.im+c2.im);
}

complex operator+(const complex& c1, const float& f){
    cout << "Operator + float c1:" << c1 << " f:"<< f << endl;
    return complex(c1.re+f,c1.im);
}

int main(){
    complex c1;
    complex c2(1);
    complex c3(1,2);
    complex c4(c3);
    complex c5;
    complex c6;
    c5 = c4;
    c1.view();
    c2.view();
    c3.view();
    c4.view();
    cout << c1.norm(c3) << endl;
    cout << "\n" << endl;
    
    /*6 appels de fonctions:
        copy constructor,
        sqr,
        constructor with two arguments,
        operator=,
        destructor,
        destructor
    */
    c6 = sqr(c3);
    cout << "\n" << endl;
    
    /*4 appels de fonctions:
        copy constructor,
        sqr,
        constructor with two arguments,
        destructor

        RVO: Return Value Optimization
        On peut voir que le constructeur par copie n'est pas appelé, le compilateur a optimisé le code en renvoyant directement l'objet c7 sans le copier
    */
    complex c7 = sqr(c3);
    cout << "\n" << endl;

    /*complex(3.f) est le constructeur avec 1 argument, sqr retourne un complex donc c8 peut être construit depuis sqr*/

    cout << "\t c8" << endl;
    complex c8 = sqr(complex(3.f));
    cout << "\t sqr(complex(3.f)).view()" << endl;
    sqr(complex(3.f)).view();
    cout << "\t c8.view()" << endl;
    c8.view();
    cout << "\n" << endl;
    cout << "\t c8 = sqr(3.f)" << endl;
    c8 = sqr(3.f);
    cout << "\t c8.view()" << endl;
    c8.view();
    cout << "\n" << endl;
    c1.view();
    c2.view();
    c3.view();
    c1 = c2 + c3 + 3.f;
    c1.view();
    cout << "\n" << endl;

    return EXIT_SUCCESS;
}

