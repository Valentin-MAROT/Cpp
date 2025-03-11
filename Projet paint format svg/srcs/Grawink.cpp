
#include "../headers/Shape.h"
#include "../headers/Array.h"
#include "../headers/Liste.h"
#include "../headers/Grawink.h"
#include "../headers/SVG.h"
#include <cstdint>
#include <cmath>

GrawEditor* GrawEditor::editor_ = nullptr;

GrawEditor& GrawEditor::GetEditor(){
    if(editor_ == nullptr){
        editor_ = new GrawEditor();
    }
    return *editor_;
}

GrawEditor::~GrawEditor(){
    if(select_.taille() > 0){
        for(size_t i = 0; i < select_.taille(); i++){
            delete select_.acceder(i);
        }
    }
    
}

GrawEditor& GrawEditor::Resize(size_t width, size_t height){
    cout << endl << "Resize" << endl << endl;
    if(width < width_ || height < height_){
        Crop(width, height);
    }else{
        width_ = width;
        height_ = height;
    }
    return *this;
}

GrawEditor& GrawEditor::Crop(size_t width, size_t height){
    
    cout << endl << "Crop" << endl << endl;
    for(size_t i = 0; i < shapes_.taille(); i++){
        for(size_t j = 0; j < shapes_.acceder(i).taille(); j++){
            if(static_cast<size_t>(shapes_.acceder(i)[j]->centre().getx()) > width || static_cast<size_t>(shapes_.acceder(i)[j]->centre().gety()) > height){
                for(size_t k = 0; k < select_.taille(); k++){
                    if((select_.acceder(k)->find(shapes_.acceder(i)[j]))!=select_.acceder(k)->taille()){
                        select_.acceder(k)->Remove(select_.acceder(k)->find(shapes_.acceder(i)[j]));
                    }
                }
                deleted_.ajouter(shapes_.acceder(i)[j]);
                undo_.ajouter(shapes_.acceder(i)[j]);
                shapes_.acceder(i).Remove(j);
            }
        }
    }
    width_ = width;
    height_ = height;
    Select(type_);
    return *this;
}

GrawEditor& GrawEditor::Add(Geom2D::Base &shape){
    ShapeType type = shape.getType();
    cout << endl << "Add" << endl;
    Geom2D::Base* s = &shape;
    if(s == nullptr){
        return *this;
    }
    if(static_cast<size_t>(s->centre().getx()) > width_ || static_cast<size_t>(s->centre().gety()) > height_){
        cout << "Shape out of bounds" << endl;
        return *this;
    }
    shapes_.acceder(static_cast<size_t>(log2(static_cast<uint64_t>(type)))).Add(s);
    added_.ajouter(s);
    cout << ShapeTypeToString(type) << " added" << endl << endl;
    return *this;
}


GrawEditor& GrawEditor::Delete(Geom2D::Base &shape){
    ShapeType type = shape.getType();
    cout << endl << "Delete" << endl;
    for(size_t i = 0; i < shapes_.acceder(static_cast<size_t>(log2(static_cast<uint64_t>(type)))).taille(); i++){
        if(shapes_.acceder(static_cast<size_t>(log2(static_cast<uint64_t>(type))))[i] == &shape){
            deleted_.ajouter(shapes_.acceder(static_cast<size_t>(log2(static_cast<uint64_t>(type))))[i]);
            undo_.ajouter(shapes_.acceder(static_cast<size_t>(log2(static_cast<uint64_t>(type))))[i]);
            shapes_.acceder(static_cast<size_t>(log2(static_cast<uint64_t>(type)))).Remove(i);
        }
    }
    cout << ShapeTypeToString(type) << " deleted" << endl << endl;
    return *this;
}

GrawEditor& GrawEditor::Print(){
    Select(type_);
    if(select_.taille() == 0){
        Select(ShapeType::All);
    }
    cout << endl << "Shapes :" << endl;
    for(size_t i = 0; i <= select_.taille()-1; i++){
        if(select_.acceder(i)[0].taille() > 0){
        cout << "\t" << ShapeTypeToString(select_.acceder(i)[0][0]->getType()) << " : " << select_.acceder(i)->taille() << " shapes" << endl;
        for(size_t j = 0; j < select_.acceder(i)->taille() ; j++){
            cout << "\t\t";
            select_.acceder(i)[0][j]->info(cout);
            cout << endl;
        }
        cout << endl;
        }
    }
    return *this;
}

GrawEditor& GrawEditor::Undo(size_t n){
    cout << endl << "Undo" << endl;
    for(size_t i = 0; i < n; i++){
        if(added_.taille() == 0){
            return *this;
        }
        cout << ShapeTypeToString(added_.acceder(0)->getType()) << " deleted" << endl << endl;
        undo_.ajouter(added_.acceder(0));
        for(size_t i=0;i<select_.taille();i++){
            if(static_cast<size_t>(log2(static_cast<uint64_t>(added_.acceder(0)->getType()))) == i){
                select_.acceder(i)->Remove(select_.acceder(i)->find(added_.acceder(0)));
            }
        }
        shapes_.acceder(static_cast<size_t>(log2(static_cast<uint64_t>(added_.acceder(0)->getType())))).Remove(shapes_.acceder(static_cast<size_t>(log2(static_cast<uint64_t>(added_.acceder(0)->getType())))).find(added_.acceder(0)));
        added_.supprimer(added_.acceder(0));
    }
    cout << endl;
    return *this;
}

//Permet de d'annuler l'annulation d'une forme n fois et de la rajouter de nouveau
GrawEditor& GrawEditor::Redo(size_t n){
    cout << endl << "Redo" << endl;
    for(size_t i = 0; i < n; i++){
        if(undo_.taille() == 0){
            return *this;
        }
        if(static_cast<size_t>(undo_.acceder(undo_.taille()-1)->centre().getx()) > width_ || static_cast<size_t>(undo_.acceder(undo_.taille()-1)->centre().gety()) > height_){
            cout << "Shape out of bounds" << endl;
            return *this;
        }
        for(size_t i=0;i<select_.taille();i++){
            if(static_cast<size_t>(log2(static_cast<uint64_t>(undo_.acceder(0)->getType()))) == i){
                select_.acceder(i)->Add(undo_.acceder(i));

            }
        }
        cout << ShapeTypeToString(undo_.acceder(0)->getType()) << " added" << endl << endl;
        shapes_.acceder(static_cast<size_t>(log2(static_cast<uint64_t>(undo_.acceder(0)->getType())))).Add(undo_.acceder(0));
        deleted_.supprimer(undo_.acceder(0));
        undo_.supprimer(undo_.acceder(0));
    }
    cout << endl;
    return *this;
}

GrawEditor& GrawEditor::Select(ShapeType type = ShapeType::All){
    type_ = type;
    select_.vider();
    Liste<Array::Dynamic<Geom2D::Base*>*> tmp;
    if(type==static_cast<ShapeType>(0)){
        cout << "No shape selected" << endl;
        return *this;
    }
    if(type==ShapeType::All){
        cout << "All shapes selected" << endl;
        for(size_t i = 0; i < shapes_.taille()-1; i++){
            tmp.ajouter(new Array::Dynamic<Geom2D::Base*>(shapes_.acceder(i)));
        }
        for(size_t i = 0; i < tmp.taille(); i++){
            select_.ajouter(tmp.acceder(i));
        }
        tmp.vider();
        return *this;
    }
    for(int i = log2(static_cast<uint64_t>(ShapeType::Complexe)); i >= 0; i--){
        if((static_cast<uint64_t>(type)>> i) & 1){
            tmp.ajouter(new Array::Dynamic<Geom2D::Base*>(shapes_.acceder(i)));
        }
    }
    for(size_t i = 0; i < tmp.taille(); i++){
        select_.ajouter(tmp.acceder(i));
    }
    tmp.vider();
    return *this;
}

GrawEditor& GrawEditor::ExportSVG(const char* filename){
    SVG::stream output(filename, width_, height_);
    output.open(filename, width_, height_);
    cout << endl << "Export SVG" << endl;
    cout << "Type : " << ShapeTypeToString(type_) << endl;
    Select(type_);
    if(select_.taille() == 0){
        cout << "No shape selected" << endl;
        Select(ShapeType::All);
    }
    for(size_t i = 0; i < select_.taille(); i++){
        for(size_t j = 0; j < select_.acceder(i)->taille(); j++){
            select_.acceder(i)[0][j]->write(output);
        }
    }
    output.close();
    return *this;
}

template <typename T, typename... Ts>
T& GrawEditor::GetNew(Ts... args){
    T& s = *new T(args...);
    return s;
}

//GetNew Circle
template Geom2D::Curve::Circle& GrawEditor::GetNew<Geom2D::Curve::Circle>();
template Geom2D::Curve::Circle& GrawEditor::GetNew<Geom2D::Curve::Circle, const Geom2D::Point&, float>(const Geom2D::Point &c, float r);
template Geom2D::Curve::Circle& GrawEditor::GetNew<Geom2D::Curve::Circle, const Geom2D::Point&, float, const Color&, size_t>(const Geom2D::Point &c, float r, const Color &stroke, size_t width);


//GetNew Rectangle
template Geom2D::Rectangle& GrawEditor::GetNew<Geom2D::Rectangle>();

//GetNew Square
template Geom2D::Square& GrawEditor::GetNew<Geom2D::Square>();
template Geom2D::Square& GrawEditor::GetNew<Geom2D::Square,const Geom2D::Point&,float,const Color &>(const Geom2D::Point &xy, float s, const Color &c);

//GetNew Ellipse
template Geom2D::Ellipse& GrawEditor::GetNew<Geom2D::Ellipse>();
template Geom2D::Ellipse& GrawEditor::GetNew<Geom2D::Ellipse, const Geom2D::Point&, float, float>(const Geom2D::Point &c, float a, float b);
template Geom2D::Ellipse& GrawEditor::GetNew<Geom2D::Ellipse, const Geom2D::Point&, float, float, const Color&, const Color&, size_t>(const Geom2D::Point &c, float a, float b, const Color &fill, const Color &stroke, size_t width);

//GetNew Segment
template Geom2D::Curve::Segment& GrawEditor::GetNew<Geom2D::Curve::Segment>();
template Geom2D::Curve::Segment& GrawEditor::GetNew<Geom2D::Curve::Segment, const Geom2D::Point&, const Geom2D::Point&>(const Geom2D::Point &p1, const Geom2D::Point &p2);
template Geom2D::Curve::Segment& GrawEditor::GetNew<Geom2D::Curve::Segment, const Geom2D::Point&, const Geom2D::Point&, const Color&, size_t>(const Geom2D::Point &p1, const Geom2D::Point &p2, const Color &c, size_t w);

//GetNew Disk
template Geom2D::Disk& GrawEditor::GetNew<Geom2D::Disk>();
template Geom2D::Disk& GrawEditor::GetNew<Geom2D::Disk,Geom2D::Point, float>(Geom2D::Point c, float r);
template Geom2D::Disk& GrawEditor::GetNew<Geom2D::Disk, const Geom2D::Point&, float>(const Geom2D::Point &c, float r);
template Geom2D::Disk& GrawEditor::GetNew<Geom2D::Disk, const Geom2D::Point&,float,const Color&,const Color&, size_t>(const Geom2D::Point &c, float r, const Color &fill, const Color &stroke, size_t width);

//GetNew Polyline
template Geom2D::Curve::Polyline& GrawEditor::GetNew<Geom2D::Curve::Polyline>();
template Geom2D::Curve::Polyline& GrawEditor::GetNew<Geom2D::Curve::Polyline,std::size_t,const Geom2D::Point&,float,const Color&,size_t >(std::size_t npts, const Geom2D::Point &cent, float size, const Color &color, size_t width);
template Geom2D::Curve::Polyline& GrawEditor::GetNew<Geom2D::Curve::Polyline,const std::initializer_list<Geom2D::Point>&,const Color&,size_t>(const std::initializer_list<Geom2D::Point> &pts, const Color &color, size_t width);

//GetNew Triangle
template Geom2D::Triangle& GrawEditor::GetNew<Geom2D::Triangle>();
template Geom2D::Triangle& GrawEditor::GetNew<Geom2D::Triangle, Geom2D::Point, float>(Geom2D::Point, float);
template Geom2D::Triangle& GrawEditor::GetNew<Geom2D::Triangle, Geom2D::Point, float, Color>(Geom2D::Point, float, Color);
template Geom2D::Triangle& GrawEditor::GetNew<Geom2D::Triangle, const std::initializer_list<Geom2D::Point>&, Color>(const std::initializer_list<Geom2D::Point>&, Color);

//GetNew Polygon
template Geom2D::Polygon& GrawEditor::GetNew<Geom2D::Polygon>();
template Geom2D::Polygon& GrawEditor::GetNew<Geom2D::Polygon, std::size_t, Geom2D::Point, float, Color, Color, size_t>(std::size_t, Geom2D::Point, float, Color, Color, size_t);
template Geom2D::Polygon& GrawEditor::GetNew<Geom2D::Polygon, const std::initializer_list<Geom2D::Point>&, Color>(const std::initializer_list<Geom2D::Point>&, Color);