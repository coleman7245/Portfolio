/* 
 * Author: Derek Coleman
 * Project: Pong Clone
 * Last Update: 3/6/19
 */ 

import java.awt.geom.*;
import java.awt.Rectangle;

/* Class Declaration */
public class Ball extends BaseVectorShape
{
	/* Class Attributes */
	private double ballX = 0.0; //ballX: position on the 2-D plane's x-axis.
	private double ballY = 0.0; //ballY: position on the 2-D plane's y-axis.
	private double ballW = 10.0; //ballW: The ball's width.
	private double ballH = 10.0; //ballH: The ball's height.
	private double arcWidth = 0.5; //arcWidth: The width of the ball's arc.
	private double arcHeight = 0.5; //arcHeight: The height of the ball's arc.
	
	/* Constructors */
	//Method Summary: The default constructor.
	Ball()
	{
		setShape(new RoundRectangle2D.Double(ballX, ballY, ballW, ballH, arcWidth, arcHeight));
		setAlive(true);
	}
	
	/* Get Methods */
	public double getBallW()
	{
		return ballW;
	}
	
	public double getBallH()
	{
		return ballH;
	}	
	
	//Method Summary: Gets the bounds of the ball as a round rectangle.
	public RoundRectangle2D.Double getBounds()
	{
		RoundRectangle2D.Double rrd; //The round rectangle that represents the bounds.
		rrd = new RoundRectangle2D.Double(getX(), getY(), ballW, ballH, arcWidth, arcHeight); //Initialize the bounds with the attributes of the ball.
		return rrd; //Return the bounds.
	}
	
}
