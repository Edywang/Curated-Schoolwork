package plane;
import java.util.ArrayList;

class Plane {
	private Shape[] shapes;
	private Shape[] copy;
	private double total;
	private double totalX;
	private double totalY;
	private int counter;
	
	public Plane() {
		shapes = new Shape[0];
	}
	
	public void addShape(Shape shape) {
		copy = new Shape[shapes.length + 1];
		System.arraycopy(shapes, 0, copy, 0, shapes.length);
		copy[shapes.length] = shape;
		shapes = new Shape[copy.length];
		System.arraycopy(copy, 0, shapes, 0, copy.length);
	}
	
	public Shape[] getShape() {
		return shapes;
	}
	
	public double getSumOfAreas() {
		total = 0;
		for(int i = 0; i < shapes.length; ++i) {
			total += shapes[i].getArea();
		}
		return total;
	}
	
	public double getSumOfPerimeters() {
		total = 0;
		for(int i = 0; i < shapes.length; ++i) {
			total += shapes[i].getPerimeter();
		}
		return total;
	}
	
	public Point getCenterOfPointOfSymmetries() {
		totalX = 0;
		totalY = 0;
		counter = 0;
		for(int i = 0; i < shapes.length; ++i) {
			if(shapes[i] instanceof Symmetric) {
				totalX += ((Symmetric) shapes[i]).getPointOfSymmetry().getX();
				totalY += ((Symmetric) shapes[i]).getPointOfSymmetry().getY();
				++counter;
			}
		}
		if(counter == 0) {
			return null;
		}
		else {
		return new Point(totalX / counter, totalY / counter);
		}
	}
	
}

abstract class Shape {
	public abstract double getArea();
	public abstract double getPerimeter();
}

class Point {
	private double x;
	private double y;

	public Point(double x, double y) {
		this.y = y;
		this.x = x;
	}

	public double getX() {
		return x;
	}

	public double getY() {
		return y;
	}

	public double getDistance(Point point) {
		return Math.sqrt((point.getX()-this.x) * (point.getX()-this.x) + (point.getY()-this.y) * (point.getY()-this.y));
	}
}

interface Symmetric {
	public abstract Point getPointOfSymmetry();
}

class Triangle extends Shape {
	private Point first;
	private Point second;
	private Point third;

	public Triangle(Point firstPoint, Point secondPoint, Point thirdPoint) {
		first = firstPoint;
		second = secondPoint;
		third = thirdPoint;
	}

	public double getArea() {
		return Math.abs((first.getX() * (second.getY() - third.getY()) + second.getX() * (third.getY() - first.getY()) + third.getX() * (first.getY() - second.getY())) * .5);
	}

	public double getPerimeter() {
		return first.getDistance(second) + second.getDistance(third) + third.getDistance(first);
	}

	public Point getFirstPoint() {
		return first;
	}

	public Point getSecondPoint() {
		return second;
	}

	public Point getThirdPoint() {
		return third;
	}
}

class Rectangle extends Shape {
	private Point point;
	private double b; //base
	private double h; //height

	public Rectangle(Point topLeftPoint, double length, double width) {
		point = topLeftPoint;
		b = length;
		h = width;
	}

	public double getArea() {
		return Math.abs(b * h);
	}

	public double getPerimeter() {
		return b * 2 + h * 2;
	}

	public double getLength() {
		return b;
	}

	public double getWidth() {
		return h;
	}

	public Point getTopLeftPoint() {
		return point;
	}
}

class Trapezoid extends Shape {
	private Point first; //top left
	private Point second; //bot left
	private double w1; //top side
	private double w2; //bot side
	private Point third; //top right
	private Point fourth; //bot right

	public double getArea() {
		return Math.abs((w1 + w2) / 2 * new Point(first.getX(), second.getY()).getDistance(new Point(first.getX(), first.getY())));
	}

	public double getPerimeter() {
		return first.getDistance(second) + second.getDistance(fourth) + fourth.getDistance(third) + third.getDistance(first);
	}

	public Trapezoid(Point topLeftPoint, Point bottomLeftPoint, double topSide, double bottomSide) {
		first = topLeftPoint;
		second = bottomLeftPoint;
		third = new Point(topLeftPoint.getX()+topSide, topLeftPoint.getY());
		fourth = new Point(bottomLeftPoint.getX()+bottomSide, bottomLeftPoint.getY());
		w1 = topSide;
		w2 = bottomSide;
	}

	public Point getTopLeftPoint() {
		return first;
	}

	public Point getBottomLeftPoint() {
		return second;
	}

	public double getTopSide() {
		return w1;
	}

	public double getBottomSide() {
		return w2;
	}
}

class Circle extends Shape implements Symmetric {
	private Point cent;
	private double rad;

	public Circle(Point center, double radius) {
		cent = center;
		rad = radius;
	}

	public Point getPointOfSymmetry() {
		return cent;
	}

	public Point getCenter() {
		return cent;
	}

	public double getRadius() {
		return rad;
	}

	public double getArea() {
		return Math.abs(Math.PI * Math.pow(rad, 2));
	}

	public double getPerimeter() {
		return 2 * Math.PI * rad;
	}
}

class EquilateralTriangle extends Triangle implements Symmetric {
	private Point point;
	private double length;
	
	public EquilateralTriangle(Point topPoint, double side) {
		super(topPoint, new Point(topPoint.getX() - side * .5, topPoint.getY() - (Math.sqrt(3) * .5 * side)), new Point(topPoint.getX() + side * .5, topPoint.getY() - (Mathsqrt(3) * .5 * side)));
		point = topPoint;
		length = side;
	}

	public Point getPointOfSymmetry() {
		return new Point(point.getX(), point.getY() - (length / Math.pow(3, .5)));
	}

	public double getSide() {
		return length;
	}

	public Point getTopPoint() {
		return super.getFirstPoint();
	}
	
	public double getArea() {
		return super.getArea();
	}
}

class Square extends Rectangle implements Symmetric {
	private Point point;
	
	public Square(Point topLeft, double side) {
		super(topLeft, side, side);
		point = topLeft;
	}
	
	public double getSide() {
		return super.getLength();
	}

	public Point getPointOfSymmetry() {
		return new Point(point.getX() + super.getLength() * .5, point.getY() - super.getLength() * .5);
	}

	public Point getTopLeftPoint() {
		return point;
	}
}