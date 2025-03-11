#include "Array.h"
#include "Shape.h"

#ifndef Liste_h
#define Liste_h

#include <iostream>
using namespace std;

template <class T>
class Liste
{
    public:
        Liste();
        ~Liste();
        void ajouter(T valeur);
        void supprimer(T valeur);
        void afficher();
        size_t rechercher(T valeur);
        T& acceder(size_t index);
        size_t taille();
        void vider();
    private:
        struct Element
        {
            T valeur;
            Element *suivant;
        };
        Element *premier;
};

template class Liste<Array::Dynamic<Geom2D::Base*>>;
template class Liste<Array::Dynamic<Geom2D::Base*>*>;
template class Liste<Geom2D::Base*>;

#endif