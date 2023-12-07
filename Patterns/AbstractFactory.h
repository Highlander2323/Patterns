#pragma once
#include <iostream>
using namespace std;
#define pi 3.14159265359

class Shape {
    string name;
public:
    string getName() {
        return name;
    }

    void setName(string n) {
        name = n;
    }

    virtual double area() = 0;
    virtual double perimeter() = 0;
    virtual void display() = 0;
};

class Circle : public Shape {
    double radius;
public:

    Circle() {
        radius = 0;
    }

    Circle(double r) {
        radius = r;
    }

    void setRadius(double r) {
        radius = r;
    }

    double getRadius() {
        return radius;
    }

    void display() {
        cout << "I have drawn a Circle!\n";
    }

    double area() {
        return radius * radius * pi;
    }

    double perimeter() {
        return pi * radius * 2;
    }
};

class Rectangle : public Shape {
    double side_length, side_breadth;
public:

    Rectangle() {
        side_length = 0;
        side_breadth = 0;
    }

    Rectangle(double l, double b) {
        side_length = l;
        side_breadth = b;
    }
    void display() {
        cout << "I have drawn a Rectangle!\n";
    }

    void setSides(double l, double b) {
        side_length = l;
        side_breadth = b;
    }

    double getLength() {
        return side_length;
    }

    double getBreadth() {
        return side_breadth;
    }

    double area() {
        return side_breadth * side_length;
    }

    double perimeter() {
        return side_length * 2 + side_breadth * 2;
    }
};

class Square : public Shape {
    double side;
public:

    Square() {
        side = 0;
    }

    Square(double s) {
        side = s;
    }

    void display() {
        cout << "I have drawn a Square!\n";
    }

    void setSide(double s) {
        side = s;
    }

    double getSide() {
        return side;
    }

    double area() {
        return side * side;
    }

    double perimeter() {
        return side * 4;
    }
};

class Ellipse : public Shape {
    double minor_axis, major_axis;
public:

    Ellipse() {
        minor_axis = 0;
        major_axis = 0;
    }

    Ellipse(double maj, double min) {
        major_axis = maj;
        minor_axis = min;
    }

    void display() {
        cout << "I have drawn an Ellipse!\n";
    }

    void setAxis(double maj, double min) {
        minor_axis = min;
        major_axis = maj;
    }

    double getMajor() {
        return major_axis;
    }

    double getMinor() {
        return minor_axis;
    }

    double area() {
        return (major_axis / 2) * (minor_axis / 2) * pi;
    }

    double perimeter() {
        return pi * (3 * (major_axis / 2 + minor_axis / 2) - sqrt((3 * minor_axis + major_axis) * (minor_axis + 3 * major_axis)));
    }
};


class ShapeFactory {
public:
    ShapeFactory() = default;
    virtual Shape* createCurvedShape() = 0;
    virtual Shape* createRightShape() = 0;
};

class SimpleShapeFactory : public ShapeFactory {
public:

    Shape* createCurvedShape() {
        return new Circle;
    }

    Shape* createRightShape() {
        return new Square;
    }
};

class GeneralShapeFactory : public ShapeFactory {
public:
    Shape* createCurvedShape() {
        return new Ellipse;
    }

    Shape* createRightShape() {
        return new Rectangle;
    }
};

