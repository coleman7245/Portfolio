/* 
 * Author: coleman7245
 * Project: Pong Clone
 * Last Update: 2/25/19
 */ 

import java.awt.*;

public class BaseVectorShape
{	
	//Variables
	private double x, y;
	private Shape shape;
	private boolean alive;
	private double velX, velY;
	private double moveAngle, faceAngle;
	
	//default constructor
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
	
	//mutators
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
	
	//accessor methods
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
