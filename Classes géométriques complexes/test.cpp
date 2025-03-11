#include "disc.h"
#include "square.h"
#include "triangle.h"
#include "polygon.h"
#include "figure.h"

int main(){
    Figure f = Figure();
    std::cout << "Ajout de figures dans le tableau : \n" << std::endl;
    f.addFigure(new Square());
    f.addFigure(new Triangle());
    std::cout << "Affichage des figures : \n" << std::endl;
    std::cout << f << std::endl;
    std::cout << "Suppression de la première figure : \n" << std::endl;
    f.removeFigure(0);
    std::cout << "Ajout d'une figure dans le tableau : \n" << std::endl;
    f.addFigure(new Disc());
    std::cout << "Affichage des figures : \n" << std::endl;
    std::cout << f << std::endl;
    std::cout << "Affichage de la première figure : \n" << std::endl;
    std::cout << f[0] << std::endl; // print du triangle
    std::cout << "Affichage de la deuxième figure : \n" << std::endl;
    std::cout << f[1] << std::endl; // print du disk
    std::cout << "Rotation de 90 degrés des figures : \n" << std::endl;
    f.rotate(90);
    std::cout << "Affichage des figures : \n" << std::endl;
    std::cout << f << std::endl;
    std::cout << "Translation de 10, 10 des figures : \n" << std::endl;
    f.translate(10, 10);
    std::cout << "Affichage des figures : \n" << std::endl;
    std::cout << f << std::endl;
    std::cout << "Scale de 2 des figures : \n" << std::endl;
    f.scale(2);
    std::cout << "Affichage des figures : \n" << std::endl;
    std::cout << f << std::endl;

    
    std::cout << f << std::endl;
    SVGstream svg("Result.svg");
    svg << f;
    svg.close();
    return 0;
}