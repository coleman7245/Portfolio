/* 
 * Author: Derek Coleman
 * Project: Pong Clone
 * Last Update: 3/13/19
 */ 

import java.awt.Shape;

/* Class Declaration */
public class BaseVectorShape
{	
	/* Class Attributes */
	private Vector2 position; //position: The position of the BaseVectorShape within the game world.
	private Vector2 velocity; //velocity: The movement of the BaseVectorShape within the game world.
	private Vector2 rotation; //rotation: The rotation of the BaseVectorShape within the game world.
	private Shape shape; //shape: The basic shape of the vector shape.
	private boolean alive; //alive: Checks to see if the shape is to be rendered or not.
	
	/* Constructors */
	//Method Summary: The default constructor.
	BaseVectorShape()
	{
		//Set the class attributes to their default constructors. Set alive to false.
		position = new Vector2();
		velocity = new Vector2();
		rotation = new Vector2();
		shape = null;
		alive = false;
	}
	
	/* Set Methods */
	public void setAlive(boolean _alive)
	{
		alive = _alive;
	}
	
	public void setPosition(double _x, double _y)
	{
		position.setX(_x);
		position.setY(_y);
	}
	
	public void setRotation(double _x, double _y)
	{
		rotation.setX(_x);
		rotation.setY(_y);
	}
	
	public void setShape(Shape _shape)
	{
		shape = _shape;
	}
	
	public void setVelocity(double _x, double _y)
	{
		velocity.setX(_x);
		velocity.setY(_y);
	}
	
	/* Get Methods */
	public Vector2 getPosition()
	{
		return position;
	}
	
	public Vector2 getRotation()
	{
		return rotation;
	}
	
	public Shape getShape()
	{
		return shape;
	}
	
	public Vector2 getVelocity()
	{
		return velocity;
	}
	
	public boolean isAlive()
	{
		return alive;
	}
	
	/* Other Methods */
	//Method Summary: Moves the BaseVectorShape to a new position by a directed velocity.
	public void moveShape()
	{
		//Set the new position to the sum of the current position and the velocity.
		position.setX(position.getX() + velocity.getX());
		position.setY(position.getY() + velocity.getY());
	}
}
