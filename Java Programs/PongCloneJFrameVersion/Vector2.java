/* 
 * Author: Derek Coleman
 * Project: Pong Clone
 * Last Update: 3/13/19
 */
 
import java.lang.Math; //Import the Math class to compute the vector2's magnitude.

/* Class Declaration */
public class Vector2
{
	/* Class Attributes */
	private double x; //x: x-axis value.
	private double y; //y: y-axis value.
	private double magnitude; //magnitude: The length of the Vector2.
	
	/* Constructor */
	//Method Summary: Default Constructor
	public Vector2()
	{
		//Set all class attributes to 0.
		x = 0;
		y = 0;
		magnitude = 0;
	}
	
	//Method Summary: Constuctor that initializes the class attributes with the given parameters.
	public Vector2(double _x, double _y)
	{
		//Set the class attributes to the cooresponding parameters.
		x = _x;
		y = _y;
		magnitude = Math.sqrt((x * x) + (y * y));
	}
	
	//Method Summary: Clone constructor.
	public Vector2(Vector2 rhs)
	{
		//Copy all class attributes from the rhs Vector2.
		x = rhs.getX();
		y = rhs.getY();
		magnitude = rhs.getMagnitude();
	}
	
	/* Accessors */
	public double getMagnitude()
	{
		return magnitude;
	}
	
	public double getX()
	{
		return x;
	}
	
	public double getY()
	{
		return y;
	}
	
	/* Mutator Methods */
	public void setMagnitude()
	{
		magnitude = Math.sqrt((x * x) + (y * y));
	}
	
	public void setX(double _x)
	{
		x = _x;
	}
	
	public void setY(double _y)
	{
		y = _y;
	}
	
	/* Other methods */
	//Method Summary: The distance between the two Vector2 objects.
	public static double distance(Vector2 lhs, Vector2 rhs)
	{
		//Add the lhs Vector2 with the inverse of the rhs Vector2.
		double distanceX = lhs.getX() - rhs.getX();
		double distanceY = lhs.getY() - rhs.getY();
		
		//Return the magnitude of the two added Vector2 objects.
		return Math.sqrt((distanceX * distanceX) + (distanceY * distanceY));
	}
	
	//Method Summary: Computes the dot product of this vector2 and the parameter Vector2.
	public double dotProduct(Vector2 rhs)
	{
		return (x * rhs.getX()) + (y + rhs.getY()); //Return the dot product.
	}
	
	//Method Summary: Scales the Vector2 by a floating point number.
	public void scale(double scalar)
	{
		x *= scalar;
		y *= scalar;
		setMagnitude();
	}
	
	//Method Summary: Normalize the vector2.
	public void normalize()
	{
		x /= magnitude; //Divide the x value by the magnitude.
		y /= magnitude; //Divide the y value by te magnitude.
		setMagnitude();
	}
}
