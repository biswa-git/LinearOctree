#pragma once
#include<Preprocessor.hpp>

class Vector
{
public:
    static Vector* New(const double& = 0.0, const double& = 0.0, const double& = 0.0);
    Vector(const double& = 0.0, const double& = 0.0, const double& = 0.0);
    virtual ~Vector();

    Vector operator+(const Vector&) const;
    Vector operator-(const Vector&) const;
    Vector operator*(const double&) const; // SCALAR PRODUCT
    Vector operator/(const double&) const; // DOT PRODUCT
    double operator*(const Vector&) const; // DOT PRODUCT
    Vector operator^(const Vector&) const; // CROSS PRODUCT
    double Abs();
    Vector Unit();

    void SetDx(const double&);
    void SetDy(const double&);
    void SetDz(const double&);
    double Vector::operator [](const int&) const;

    void Reassign(const double&, const double&, const double&);

    void Print() const;

private:
    double m_c[3];
};

static Vector NULL_VECTOR(0, 0, 0);