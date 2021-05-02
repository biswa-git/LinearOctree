#include<Vector.hpp>

Vector::Vector(const double& m_dx, const double& m_dy, const double& m_dz) :m_c{ m_dx, m_dy, m_dz }
{
}

Vector* Vector::New(const double& m_dx, const double& m_dy, const double& m_dz)
{
	return new Vector(m_dx, m_dy, m_dz);
}

Vector::~Vector()
{
}

Vector Vector::operator+(const Vector& v)
{
	return Vector(this->m_c[0] + v.m_c[0], this->m_c[1] + v.m_c[1], this->m_c[2] + v.m_c[2]);
}

Vector Vector::operator-(const Vector& v)
{
	return Vector(this->m_c[0] - v.m_c[0], this->m_c[1] - v.m_c[1], this->m_c[2] - v.m_c[2]);
}

Vector Vector::operator*(const double& s)
{
	return Vector(this->m_c[0] * s, this->m_c[1] * s, this->m_c[2] * s);
}

Vector Vector::operator/(const double& s)
{
	return Vector(this->m_c[0] / s, this->m_c[1] / s, this->m_c[2] / s);
}

double Vector::operator*(const Vector& v)
{
	return (this->m_c[0] * v.m_c[0] + this->m_c[1] * v.m_c[1] + this->m_c[2] * v.m_c[2]);
}

//3d implementation needed
Vector Vector::operator^(const Vector& v)
{
	return Vector(
		this->m_c[1] * v.m_c[2] - this->m_c[2] * v.m_c[1],
		this->m_c[2] * v.m_c[0] - this->m_c[0] * v.m_c[2],
		this->m_c[0] * v.m_c[1] - this->m_c[1] * v.m_c[0]);
}

double Vector::Abs()
{
	return sqrt(m_c[0] * m_c[0] + m_c[1] * m_c[1] + m_c[2] * m_c[2]);
}

Vector Vector::Unit()
{
	return (*this / this->Abs());
}

void Vector::SetDx(const double& x)
{
    m_c[0] = x;
}

void Vector::SetDy(const double& y)
{
    m_c[1] = y;
}

void Vector::SetDz(const double& z)
{
    m_c[2] = z;
}

double Vector::GetDx() const
{
    return m_c[0];
}

double Vector::GetDy() const
{
	return m_c[1];
}

double Vector::GetDz() const
{
	return m_c[2];
}

double Vector::operator [](const int& i)
{
	return m_c[i];
}
void Vector::Reassign(const double& m_dx, const double& m_dy, const double& m_dz)
{
	this->m_c[0] = m_dx;
	this->m_c[1] = m_dy;
	this->m_c[2] = m_dz;
}

void Vector::Print() const
{
	std::cout << "[" << m_c[0] << "," << m_c[1] << "," << m_c[2] << "]" << std::endl;
}
