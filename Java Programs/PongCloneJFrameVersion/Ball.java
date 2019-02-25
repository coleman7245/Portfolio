/* 
 * Author: coleman7245
 * Project: Pong Clone
 * Last Update: 2/25/19
 */ 

import java.awt.geom.*;
import java.awt.Rectangle;

public class Ball extends BaseVectorShape
{
	private double ballX = 0.0;
	private double ballY = 0.0;
	private double ballW = 10.0;
	private double ballH = 10.0;
	private double arcWidth = 0.5;
	private double arcHeight = 0.5;
	
	//mutator
	Ball()
	{
		setShape(new RoundRectangle2D.Double(ballX, ballY, ballW, ballH, arcWidth, arcHeight));
		setAlive(true);
	}
	
	public double getBallW()
	{
		return ballW;
	}
	
	public double getBallH()
	{
		return ballH;
	}	
	
	//bounding retangle
	public RoundRectangle2D.Double getBounds()
	{
		RoundRectangle2D.Double rrd;
		rrd = new RoundRectangle2D.Double(getX(), getY(), ballW, ballH, arcWidth, arcHeight);
		return rrd;
	}
	
}
