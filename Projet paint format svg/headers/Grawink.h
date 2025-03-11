#ifndef _GRAWINK_H_
#define _GRAWINK_H_
#include "shapetype.h"
#include "Liste.h"
#include "Array.h"
using namespace std;
class GrawEditor{
  protected:
      static const size_t DefaultWidth = 1920;
      static const size_t DefaultHeight = 1080;
      static GrawEditor* editor_;
      Liste<Array::Dynamic<Geom2D::Base*>> shapes_;
      size_t width_;
      size_t height_;
      Liste<Geom2D::Base*> deleted_;
      Liste<Geom2D::Base*> added_;
      Liste<Geom2D::Base*> undo_;
      Liste<Array::Dynamic<Geom2D::Base*>*> select_;
      ShapeType type_;
      GrawEditor() : width_(DefaultWidth), height_(DefaultHeight) {
          shapes_.ajouter(Array::Dynamic<Geom2D::Base*>()); // Segment
          shapes_.ajouter(Array::Dynamic<Geom2D::Base*>()); // Polygone
          shapes_.ajouter(Array::Dynamic<Geom2D::Base*>()); // Triangle
          shapes_.ajouter(Array::Dynamic<Geom2D::Base*>()); // Rectangle
          shapes_.ajouter(Array::Dynamic<Geom2D::Base*>()); // Cercle
          shapes_.ajouter(Array::Dynamic<Geom2D::Base*>()); // Ellipse
          shapes_.ajouter(Array::Dynamic<Geom2D::Base*>()); // Complexe
      }
    public:

      
      GrawEditor &operator=(const GrawEditor&) = delete;
      GrawEditor(const GrawEditor&) = delete;
      ~GrawEditor();
      size_t width() const { return width_; }
      size_t height() const { return height_; }

    static GrawEditor& GetEditor();

    // Ajoute un nouveau objet au canevas
    GrawEditor& Add(Geom2D::Base &shape);

    // Supprime un objet du canevas
    GrawEditor& Delete(Geom2D::Base &shape);

    // Annule le dernier ajout d'objet
    GrawEditor& Undo(size_t n = 1);

    // Réinsère le dernier objet supprimé
    GrawEditor& Redo(size_t n = 1);

    // Redimensionne le canevas
    GrawEditor& Resize(size_t width, size_t height);

    // Redimensionne le canevas en supprimant les objets extérieurs */
    GrawEditor& Crop(size_t width, size_t height);

    // Sélectionne les objets à exporter/afficher.
    // La sélection pourra se faire sous la forme d'une disjonction ("OU" binaires) de `enum ShapeType`.
    // Par exemple pour sélectionner uniquement les triangles, les rectangles et les octogones, on pourra passer en paramètre :
    //  ShapeType::Triangle | ShapeType::Rectangle | ShapeType::Octogon, ou
    //  bien l'équivalent en hexadécimal (0x46ULL), ou en décimal (70ULL).
    // Passer ShapeType::All resélectionne l'ensemble des formes du canevas.
    GrawEditor& Select(ShapeType type);

    // Affiche l'ensemble des objets contenus dans le canevas, triés par
    // catégorie, dans la sortie standard.
    GrawEditor& Print();

    // Écrit le code SVG résultant des objets contenus dans le canevas
    GrawEditor& ExportSVG(const char *filename);

    // Crée une nouvelle instance de la classe `Shape` (i.e. Rectangle,
    // Triangle, Stroke, Circle, etc.) et retourne un pointeur vers l'objet nouvellement alloué.
    // Cet objet peut ensuite être transformé, passé en paramètre à `Add` ou à `Delete`.
    template <typename T,class... Ts> T& GetNew(Ts... args);
};
#endif


