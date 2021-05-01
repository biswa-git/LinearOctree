#include<Vector.hpp>

Vector::Vector(const double& m_dx, const double& m_dy, const double& m_dz) :m_dx(m_dx), m_dy(m_dy), m_dz(m_dz)
{
}

Vector* Vector::New(const double& m_dx, const double& m_dy, const double& m_dz)
{
	return new Vector(m_dx,m_dy,m_dz);
}

Vector::~Vector()
{
}

Vector Vector::operator+(const Vector& v)
{
	return Vector(this->m_dx + v.m_dx, this->m_dy + v.m_dy, this->m_dz + v.m_dz);
}

Vector Vector::operator-(const Vector& v)
{
	return Vector(this->m_dx - v.m_dx, this->m_dy - v.m_dy, this->m_dz - v.m_dz);
}

Vector Vector::operator*(const double& s)
{
	return Vector(this->m_dx * s, this->m_dy * s, this->m_dz * s);
}

Vector Vector::operator/(const double& s)
{
	return Vector(this->m_dx / s, this->m_dy / s, this->m_dz / s);
}

double Vector::operator*(const Vector& v)
{
	return (this->m_dx * v.m_dx + this->m_dy * v.m_dy + this->m_dz * v.m_dz);
}

//3d implementation needed
Vector Vector::operator^(const Vector& v)
{
	return Vector(
		this->m_dy * v.m_dz - this->m_dz * v.m_dy,
		this->m_dz * v.m_dx - this->m_dx * v.m_dz,
		this->m_dx * v.m_dy - this->m_dy * v.m_dx);
}

double Vector::Abs()
{
	return sqrt(m_dx * m_dx + m_dy * m_dy + m_dz * m_dz);
}

Vector Vector::Unit()
{
	return (*this / this->Abs());
}

void Vector::SetDx(const double& x)
{
    m_dx = x;
}

void Vector::SetDy(const double& y)
{
    m_dy = y;
}

void Vector::SetDz(const double& z)
{
    m_dz = z;
}

double Vector::GetDx() const
{
    return m_dx;
}

double Vector::GetDy() const
{
	return m_dy;
}

double Vector::GetDz() const
{
	return m_dz;
}

void Vector::Reassign(const double& m_dx, const double& m_dy, const double& m_dz)
{
	this->m_dx = m_dx;
	this->m_dy = m_dy;
	this->m_dz = m_dz;
}

void Vector::Print() const
{
	std::cout << "[" << m_dx << "," << m_dy << "," << m_dz << "]" << std::endl;
}
