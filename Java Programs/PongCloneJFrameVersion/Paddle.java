/* 
 * Author: Derek Coleman
 * Project: Pong Clone
 * Last Update: 3/13/19
 */ 

import java.awt.Rectangle; //Import the Rectangle class for the bounds.

/* Class Declaration */
public class Paddle extends BaseVectorShape
{
	/* Class Attributes */
	private int paddleX = 0; //paddleX: x value of the starting point coordinates.
	private int paddleY = 0; //paddleY: y value of the starting point coordinates.
	private int paddleW = 40; //paddleW: The width of the paddle.
	private int paddleH = 10; //paddleH: The height of the paddle.
	
	/* Constructors */
	//Method Summary: The default constructor.
	Paddle()
	{
		super(); //Call the base class' constructor.
		//Initialize the class attributes.
		setShape(new Rectangle(paddleX, paddleY, paddleW, paddleH));
		setAlive(true);
	}
	
	/* Get Methods */
	public int getPaddleW()
	{
		return paddleW;
	}
	
	public int getPaddleH()
	{
		return paddleH;
	}
	
	//Method Summary: Returns the bounds of the paddle for collision detection.
	public Rectangle getBounds()
	{
		Rectangle r; //The rectangle that represents the bounds.
		r = new Rectangle((int)getPosition().getX(), (int)getPosition().getY(), paddleW + 5, paddleH + 5); //Initialize the bounds with the attributes of the entire paddle.
		return r; //Return the bounds.
	}
	
	//Method Summary: Returns the left section of the paddle for collision detection.
	public Rectangle getHitAreaLeft()
	{
		Rectangle hitL; //The rectangle that represents the bounds.
		hitL = new Rectangle((int)getPosition().getX(), (int)getPosition().getY(), 13, 10); //Initialize the bounds with the attributes of the left portion of the paddle.
		return hitL; //Return the bounds.
	}
	
	//Method Summary: Returns the center section of the paddle for collision dectection.
	public Rectangle getHitAreaCenter()
	{
		Rectangle hitC; //The rectangle that represents the bounds.
		hitC = new Rectangle((int)getPosition().getX() + 14, (int)getPosition().getY(), 12, 10); //Initialize the bounds with the attributes of the center portion of the paddle.
		return hitC; //Return the bounds.
	}
	
	//Method Summary: Returns the right section of the paddle for collision detection.
	public Rectangle getHitAreaRight()
	{
		Rectangle hitR; //The rectangle that represents the bounds.
		hitR =  new Rectangle((int)getPosition().getX() + 27, (int)getPosition().getY(), 13, 10); //Initialize the bounds with the attributes of the right portion of the paddle.
		return hitR; //Return the bounds.
	}
	
}
