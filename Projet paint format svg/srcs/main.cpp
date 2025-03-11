#include "../headers/Grawink.h"
#include "Grawink.cpp"

using namespace std;

int main()
{
    using namespace Geom2D;
    using namespace Curve;
    GrawEditor& editor = GrawEditor::GetEditor();
    editor.GetNew<Segment>();
    editor.GetNew<Segment>(Point(0,0),Point(1,1));
    editor.GetNew<Segment>(Point(0,0),Point(1,1),Color::blue,2);
    editor.Select();
    editor.ExportSVG("test2.svg");

    editor.GetNew<Rectangle>();
    editor.GetNew<Rectangle>(Point(0,0),2.f,2.f,Color::red);

    editor.GetNew<Square>();
    editor.GetNew<Square>(Point(0,0),2.f,Color::green);
    editor.Select(ShapeType::All);
    editor.ExportSVG("test3.svg");

    editor.GetNew<Triangle>();
    editor.GetNew<Triangle>(Point(10,10),3.f,Color::green);
    initializer_list<Point> l={Point(0,0),Point(1,1),Point(2,2)};
    editor.GetNew<Triangle>(l,Color::yellow);
    editor.Select(ShapeType::All);
    editor.ExportSVG("test4.svg");

    editor.GetNew<Polygon>();
    editor.GetNew<Polygon>(4,Point(0,0),2.f,Color::blue,Color::red,2);
    initializer_list<Point> l2={Point(0,0),Point(1,1),Point(2,2),Point(3,3)};
    editor.GetNew<Polygon>(l2,Color::green);
    editor.Select(ShapeType::All);
    editor.ExportSVG("test5.svg");

    editor.GetNew<Circle>();
    editor.GetNew<Circle>(Point(0,0),1.f);
    editor.GetNew<Circle>(Point(0,0),1.f,Color::red,2);
    editor.Select(ShapeType::All);
    editor.ExportSVG("test6.svg");

    editor.GetNew<Disk>();
    editor.GetNew<Disk>(Point(0,0),1.f);
    editor.GetNew<Disk>(Point(0,0),1.f,Color::blue,Color::red,2);
    editor.Select(ShapeType::All);
    editor.ExportSVG("test7.svg");

    editor.GetNew<Ellipse>();
    editor.GetNew<Ellipse>(Point(0,0),1.f,2.f);
    editor.GetNew<Ellipse>(Point(0,0),1.f,2.f,Color::green,Color::yellow,2);
    editor.Select(ShapeType::All);
    editor.ExportSVG("test8.svg");

    editor.GetNew<Polyline>();
    editor.GetNew<Polyline>(3,Point(0,0),2.f,Color::red,2);
    initializer_list<Point> l3={Point(0,0),Point(100,100),Point(2,200)};
    editor.GetNew<Polyline>(l3,Color::blue,2);

    Segment s1 = editor.GetNew<Segment>();
    s1.setStrokeColor(Color::red);
    s1.setOpacity(0.5);
    s1.setPoints(Point(200,200),Point(300,300));
    s1.setStrokeWidth(2);

    Rectangle r1 = editor.GetNew<Rectangle>();
    r1.setFillColor(Color::green);
    r1.setOpacity(0.5);
    r1.setHeight(100);
    r1.Translate(Point(100,100));
    r1.setStrokeColor(Color::blue);
    r1.setWidth(300);
    Polygon p1 = editor.GetNew<Polygon>();
    editor.Add(s1);
    editor.Select(ShapeType::All);
    editor.ExportSVG("test9.svg");
    editor.Add(r1);
    editor.Select(ShapeType::All);
    editor.ExportSVG("test10.svg");
    editor.Resize(3000,3000);
    editor.Crop(800,800);
    editor.Resize(2000,2000);
    editor.Redo(5);
    editor.Select(ShapeType::All);
    editor.Print();

    editor.ExportSVG("test.svg");
    return 0;
}