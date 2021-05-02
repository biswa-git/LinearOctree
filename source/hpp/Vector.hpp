#pragma once
#include<Preprocessor.hpp>

class Vector
{
public:
    static Vector* New(const double& = 0.0, const double& = 0.0, const double& = 0.0);
    Vector(const double& = 0.0, const double& = 0.0, const double& = 0.0);
    virtual ~Vector();

    Vector operator+(const Vector&);
    Vector operator-(const Vector&);
    Vector operator*(const double&); // SCALAR PRODUCT
    Vector operator/(const double&); // DOT PRODUCT
    double operator*(const Vector&); // DOT PRODUCT
    Vector operator^(const Vector&); // CROSS PRODUCT
    double Abs();
    Vector Unit();

    void SetDx(const double&);
    void SetDy(const double&);
    void SetDz(const double&);
    double Vector::operator [](const int&);

    double GetDx() const;
    double GetDy() const;
    double GetDz() const;

    void Reassign(const double&, const double&, const double&);

    void Print() const;

private:
    double m_c[3];
};

static Vector NULL_VECTOR(0, 0, 0);