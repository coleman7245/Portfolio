/* 
 * Author: Derek Coleman
 * Project: Pong Clone
 * Last Update: 3/6/19
 */ 

import java.awt.*;

/* Class Declaration */
public class BaseVectorShape
{	
	/* Class Attributes */
	private double x; //x: position on the 2-D plane's x-axis.
	private double y; //y: position on the 2-D plane's y-axis.
	private Shape shape; //shape: The basic shape of the vector shape.
	private boolean alive; //alive: Checks to see if the shape is to be rendered or not.
	private double velX; //velX: Velocity of the shape on the x-axis.
	private double velY; //velY: Velocity of the shape on the y-axis.
	private double moveAngle; //moveAngle: The direction of the shape's movement.
	private double faceAngle; //faceAngle: The direction that the shape is facing.
	
	/* Constructors */
	//Method Summary: The default constructor.
	BaseVectorShape()
	{
		setShape(null);
		setAlive(false);
		setX(0.0);
		setY(0.0);
		setVelX(0.0);
		setVelY(0.0);
		setMoveAngle(0.0);
		setFaceAngle(0.0);
	}
	
	/* Set Methods */
	public void setShape(Shape shape)
	{
		this.shape = shape;
	}
	
	public void setAlive(boolean alive)
	{
		this.alive = alive;
	}
	
	public void setX(double x)
	{
		this.x = x;
	}
	
	public void incrementX(double i)
	{
		this.x = x += i;
	}
	
	public void setY(double y)
	{
		this.y = y;
	}
	
	public void incrementY(double i)
	{
		this.y = y += i;
	}
	
	public void setVelX(double velX)
	{
		this.velX = velX;
	}
	
	public void incrementVelX(double i)
	{
		this.velX = velX += i;
	}
	
	public void setVelY(double velY)
	{
		this.velY = velY;
	}
	
	public void incrementVelY(double i)
	{
		this.velY = velY += i;
	}
	
	public void setMoveAngle(double moveAngle)
	{
		this.moveAngle = moveAngle;
	}
	
	public void incrementMoveAngle(double i)
	{
		this.moveAngle = moveAngle += i;
	}
	
	public void setFaceAngle(double faceAngle)
	{
		this.faceAngle = faceAngle;
	}
	
	public void incrementFaceAngle(double i)
	{
		this.faceAngle = faceAngle;
	}
	
	/* Get Methods */
	public Shape getShape()
	{
		return shape;
	}
	
	public boolean isAlive()
	{
		return alive;
	}
	
	public double getX()
	{
		return x;
	}
	
	public double getY()
	{
		return y;
	}
	
	public double getVelX()
	{
		return velX;
	}
	
	public double getVelY()
	{
		return velY;
	}
	
	public double getMoveAngle()
	{
		return moveAngle;
	}
	
	public double getFaceAngle()
	{
		return faceAngle;
	}
}
