/*
// Author: Raunak Sarkar
// Purpose: Explanation of Curiously Reccurring Template Pattern with an Example
// Def: The curiously recurring template pattern (CRTP) is an idiom in C++ in which a class X derives 
//		from a class template instantiation using X itself as template argument. [Wikipedia]
// 
*/

#pragma once

// Constants
static constexpr double PIE = static_cast<double>(3.14);
static constexpr double AREA_RECT(double l, double w) { return l * w; }
static constexpr double AREA_CIRCLE(double radius) { return PIE*radius*radius; }
static constexpr double AREA_SQRE(double side) { return side * side; }

// Base class defined to maintain uniformity of the object type so that a list of Shape class objects can be stored 
// in a vector and iterated over later.
class BaseShape
{
public:
	virtual void computeArea() = 0;
	virtual double& getArea() = 0;
	virtual std::string getName() = 0;
	virtual ~BaseShape() {};
};

template<typename Concrete>
class Shape : public BaseShape
{
private :
	double area;
	Shape() : area((double)0) {};
	public:
		friend Concrete; // To avoid an unintentional mistake of having 2 classes with same instantiation
		~Shape() {}
		void computeArea()
		{
			static_cast<Concrete*>(this)->computeArea();
			std::cout << "Hello: " << area << std::endl;
		}
		double& getArea()
		{
			return area;
		}
		std::string getName()
		{
			return static_cast<Concrete*>(this)->getName();			 
		}
};

class Rectangle : public Shape<Rectangle>
{
private:
	double length;
	double breadth;

public:
	Rectangle(double l, double b) : length(l), breadth(b) {};
	~Rectangle(){}
	void computeArea()
	{
		getArea() =  AREA_RECT(length,breadth);
	}
	std::string getName()
	{
		return std::string("Rectangle");
	}
};

class Circle : public Shape<Circle>
{
private:
	double radius;
public:
	Circle(double r) : radius(r){};
	~Circle() {}
	void computeArea()
	{
		getArea() = AREA_CIRCLE(radius);
	}
	std::string getName()
	{
		return std::string("Circle");
	}
};

class Square : public Shape<Square>
{
private:
	double length;
public:
	Square(double l) : length(l){};
	~Square() {}
	void computeArea()
	{
		getArea() = AREA_SQRE(length);
	}
	std::string getName()
	{
		return std::string("Square");
	}
};
