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
	
	/* Constructor */
	//Method Summary: Default Constructor
	public Vector2()
	{
		//Set all class attributes to 0.
		x = 0;
		y = 0;
	}
	
	//Method Summary: Constuctor that initializes the class attributes with the given parameters.
	public Vector2(double _x, double _y)
	{
		//Set the class attributes to the cooresponding parameters.
		x = _x;
		y = _y;
	}
	
	/* Accessors */
	//Method Summary: Returns the magnitude of the vector2.
	public double getMagnitude()
	{
		return Math.sqrt((x * x) + (y * y)); //Return the magnitude.
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
	public void setX(double _x)
	{
		x = _x;
	}
	
	public void setY(double _y)
	{
		y = _y;
	}
	
	/* Other methods */
	//Method Summary: Computes the dot product of this vector2 and the parameter vector2.
	public double dotProduct(Vector2 rhs)
	{
		return (x * rhs.getX()) + (y + rhs.getY()); //Return the dot product.
	}
	
	//Method Summary: Normalize the vector2.
	public void normalize()
	{
		x /= getMagnitude(); //Divide the x value by the magnitude.
		y /= getMagnitude(); //Divide the y value by te magnitude.
	}
}
