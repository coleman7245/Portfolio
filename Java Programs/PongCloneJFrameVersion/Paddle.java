/* 
 * Author: coleman7245
 * Project: Pong Clone
 * Last Update: 2/25/19
 */ 

import java.awt.geom.*;
import java.awt.Rectangle;

public class Paddle extends BaseVectorShape
{
	private int paddleX = 0;
	private int paddleY = 0;
	private int paddleW = 40;
	private int paddleH = 10;
	
	Paddle()
	{
		setShape(new Rectangle(paddleX, paddleY, paddleW, paddleH));
		setAlive(true);
	}
	
	public int getPaddleW()
	{
		return paddleW;
	}
	
	public int getPaddleH()
	{
		return paddleH;
	}
	
	public Rectangle getBounds()
	{
		Rectangle r;
		r = new Rectangle((int)getX(), (int)getY(), paddleW + 5, paddleH + 5);
		return r;
	}
	
	public Rectangle getHitAreaLeft()
	{
		Rectangle hitL;
		hitL = new Rectangle((int)getX(), (int)getY(), 13, 10);
		return hitL;
	}
	
	public Rectangle getHitAreaCenter()
	{
		Rectangle hitC;
		hitC = new Rectangle((int)getX() + 14, (int)getY(), 12, 10);
		return hitC;
	}
	
	public Rectangle getHitAreaRight()
	{
		Rectangle hitR;
		hitR =  new Rectangle((int)getX() + 27, (int)getY(), 13, 10);
		return hitR;
	}
	
}
