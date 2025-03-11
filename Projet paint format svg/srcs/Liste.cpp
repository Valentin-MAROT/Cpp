#include "../headers/Liste.h"

template <class T>
Liste<T>::Liste()
{
    premier = nullptr;
}

template <class T>
Liste<T>::~Liste()
{
    while (premier != nullptr)
    {
        Element *temp = premier;
        premier = premier->suivant;
        delete temp;
    }
}

template <class T>
void Liste<T>::ajouter(T valeur)
{
    Element *nouveau = new Element;
    nouveau->valeur = valeur;
    nouveau->suivant = premier;
    premier = nouveau;
}

template <class T>
void Liste<T>::supprimer(T valeur)
{
    if (premier == nullptr)
    {
        return;
    }
    if (premier->valeur == valeur)
    {
        Element *temp = premier;
        premier = premier->suivant;
        delete temp;
        return;
    }
    Element *courant = premier;
    while (courant->suivant != nullptr)
    {
        if (courant->suivant->valeur == valeur)
        {
            Element *temp = courant->suivant;
            courant->suivant = courant->suivant->suivant;
            delete temp;
            return;
        }
        courant = courant->suivant;
    }
}

template <class T>
void Liste<T>::afficher()
{
    std::cout << "Liste : " << std::endl;
    Element *courant = premier;
    while (courant != nullptr)
    {
        std::cout << courant->valeur << std::endl;
        courant = courant->suivant;
    }
}

template <class T>
size_t Liste<T>::rechercher(T valeur)
{
    size_t index = 0;
    Element *courant = premier;
    while (courant != nullptr)
    {
        if (courant->valeur == valeur)
        {
            return index;
        }
        index++;
        courant = courant->suivant;
    }
    return -1;
}

template <class T>
T& Liste<T>::acceder(size_t index)
{
    Element *courant = premier;
    for (size_t i = 0; i < index; i++)
    {
        courant = courant->suivant;
    }
    return courant->valeur;
}

template <class T>
size_t Liste<T>::taille()
{
    size_t taille = 0;
    Element *courant = premier;
    while (courant != nullptr)
    {
        taille++;
        courant = courant->suivant;
    }
    return taille;
}

template <class T>
void Liste<T>::vider()
{
    while (premier != nullptr)
    {
        Element *temp = premier;
        premier = premier->suivant;
        delete temp;
    }
}
