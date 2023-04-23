// PHYS 30762 Programming in C++
// Assignment 6: A set of classes for shapes
// Tobias Fox 10475873

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <vector>

// -- Classes --

// Defines an abstract base class for all shapes
class shape
{
public:
    virtual ~shape() {};

    virtual double area() const = 0;
    virtual double volume() const = 0;
};

// Defines a derived class for 2D shapes
class two_d_shape : public shape
{
public:
    virtual ~two_d_shape() {};

    virtual double perimeter() const = 0;
    virtual double volume() const
    {
        return 0;
    }
};

// Defines a derived class for 3D shapes
class three_d_shape : public shape
{
public:
    virtual ~three_d_shape() {};
};

// Defines a derived class for a square
class square : public two_d_shape
{
private:
    double length;

public:
    square() = default;
    square(double len_1) : length{ len_1 } {};
    ~square()
    {
        std::cout << "Removing square" << area() << std::endl;
    }

    double perimeter() const;
    double area() const;
};

// Defines a derived class for a rectangle
class rectangle : public two_d_shape
{
private:
    double width, length;

public:
    rectangle() = default;
    rectangle(double len_1, double len_2) : length{ len_1 }, width{ len_2 } {};
    ~rectangle()
    {
        std::cout << "Removing rectangle" << area() << std::endl;
    }

    double perimeter() const;
    double area() const;
};

// Defines a derived class for a circle
class circle : public two_d_shape
{
private:
    double radius;

public:
    circle() = default;
    circle(double r) : radius{ r } {};
    ~circle()
    {
        std::cout << "Removing circle" << area() << std::endl;
    }

    double perimeter() const;
    double area() const;
};

// Defines a derived class for an ellipse
class ellipse : public two_d_shape
{
private:
    double major, minor;

public:
    ellipse() = default;
    ellipse(double len_1, double len_2) : major{ len_1 }, minor{ len_2 } {};
    ~ellipse()
    {
        std::cout << "Removing ellipse" << area() << std::endl;
    }

    double perimeter() const;
    double area() const;
};

// Defines a derived class for a cuboid
class cuboid : public three_d_shape
{
private:
    double width, length, height;

public:
    cuboid() = default;
    cuboid(double len_1, double len_2, double len_3) : width{ len_1 }, length{ len_2 }, height{ len_3 } {};
    ~cuboid()
    {
        std::cout << "Removing cuboid" << area() << std::endl;
    };

    double area() const;
    double volume() const;
};

// Defines a derived class for a cube
class cube : public three_d_shape
{
private:
    double length;

public:
    cube() = default;
    cube(double len_1) : length{ len_1 } {};
    ~cube()
    {
        std::cout << "Removing cube" << area() << std::endl;
    }

    double area() const;
    double volume() const;
};

// Defines a derived class for a sphere
class sphere : public three_d_shape
{
private:
    double radius;

public:
    sphere() = default;
    sphere(double r) : radius{ r } {};
    ~sphere()
    {
        std::cout << "Removing sphere" << area() << std::endl;
    }

    double area() const;
    double volume() const;
};

// Defines a derived class for an ellipsoid
class ellipsoid : public three_d_shape
{
private:
    double major, minor, z_axis;

public:
    ellipsoid() = default;
    ellipsoid(double len_1, double len_2, double len_3) : major{ len_1 }, minor{ len_2 }, z_axis{ len_3 } {};
    ~ellipsoid()
    {
        std::cout << "Removing ellipsoid" << area() << std::endl;
    };

    double area() const;
    double volume() const;
};

// Defines a derived class for a prism
class prism : public three_d_shape
{
private:
    double depth;
    two_d_shape* face_shape;

public:
    prism() = default;
    prism(double d, two_d_shape* s) : depth{ d }, face_shape{ s } {};
    ~prism()
    {
        std::cout << "Removing prism" << area() << std::endl;
    }

    double volume() const;
    double area() const;
};

// -- Member functions --

// Defines member functions of the square class
double square::perimeter() const
{
    return 4 * length;
}

double square::area() const
{
    return pow(length, 2);
}

// Defines member functions of the rectangle class
double rectangle::perimeter() const
{
    return 2 * length + 2 * width;
}

double rectangle::area() const
{
    return width * length;
}

// Defines member functions of the circle class
double circle::perimeter() const
{
    return  2 * radius * M_PI;
}

double circle::area() const
{
    return  pow(radius, 2) * M_PI;
}

// Defines the member functions of the ellipse class
double ellipse::perimeter() const
{
    return  (major + minor) * M_PI;
}

double ellipse::area() const
{
    return major * minor * M_PI;
}

// Defines the member functions of the cuboid class
double cuboid::area() const
{
    return 2 * (width * length + length * height + height * width);
}

double cuboid::volume() const
{
    return width * length * height;
}

// Defines the member functions of the cube class
double cube::area() const
{
    return 6 * pow(length, 2);
}

double cube::volume() const
{
    return pow(length, 3);
}

// Defines the member functions of the sphere class
double sphere::area() const
{
    return 4 * M_PI * pow(radius, 2);
}

double sphere::volume() const
{
    return (4 / 3) * M_PI * pow(radius, 3);
}

// Defines the member functions of the ellipsoid class
double ellipsoid::area() const
{
    return 4 * M_PI * pow(((pow(major * minor, 1.6) + pow(minor * z_axis, 1.6) + pow(z_axis * major, 1.6)) / 3), 1 / 1.6);
}

double ellipsoid::volume() const
{
    return major * minor * z_axis * M_PI;
}

// Defines the member functions of the prism class
double prism::volume() const
{
    return depth * face_shape->area();
}

double prism::area() const
{
    return 2 * face_shape->area() + depth * face_shape->perimeter();
}

// -- Main --

int main()
{
    std::cout.precision(3);

    // Creates base class pointer for each shape
    shape* square_pointer = new square{ 2 };
    shape* rectangle_pointer = new rectangle{ 2, 3 };
    shape* circle_pointer = new circle{ 2 };
    shape* ellipse_pointer = new ellipse{ 2, 3 };

    shape* cube_pointer = new cube{ 2 };
    shape* cuboid_pointer = new cuboid{ 2, 3, 4 };
    shape* sphere_pointer = new sphere{ 3 };
    shape* ellipsoid_pointer = new ellipsoid{ 2, 3, 4 };

    shape* prism_pointer = new prism{ 4, new square{ 2 } };

    // Defines a vector of base class pointers
    std::vector<shape*> shapes = { square_pointer, rectangle_pointer, circle_pointer, ellipse_pointer, cube_pointer,
        cuboid_pointer, sphere_pointer, ellipsoid_pointer, prism_pointer };

    // Outputs the area and volume of each shape
    for (int i{ 0 }; i < shapes.size(); i++) {
        std::cout << "--Shape " << i + 1 << "--" << std::endl;
        std::cout << "The area of this shape = " << shapes[i]->area() << std::endl;
        std::cout << "The volume of this shape = " << shapes[i]->volume() << std::endl;
        std::cout << "\n";
    }

    // Deletes the objects in the vector
    shapes.clear();
    std::cout << "The vector of shapes now has size " << shapes.size() << std::endl;

    return 0;
}