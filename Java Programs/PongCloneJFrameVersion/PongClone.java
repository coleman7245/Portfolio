/* 
 * Author: Derek Coleman
 * Project: Pong Clone
 * Last Update: 3/6/19
 */ 

import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.applet.*;
import java.util.*;
import java.net.*;
import java.awt.geom.AffineTransform;
import javax.swing.*;
import java.io.*;
import javax.sound.sampled.*;
import javax.sound.midi.*;
import javax.swing.JFrame;

/* Class Declaration */
public class PongClone extends Canvas implements Runnable, MouseListener, MouseMotionListener
{
	//Screen variables
	int screenWidth = 640; //screenWidth: The width of the screen.
	int screenHeight = 480; //screenHeight: The height of the screen.
	
	boolean isRunning; //Variable for checking if a midi stream is running or not.
   
	boolean ballInPlay; //Boolean variable for checking if the ball is in play or not.
	
    //Countdown clock that decrements before the ball is in play.
    int count;
    int countdown;
	
	int gameState; //Game state variable
	
	//Game state constants
	final int GAME_MENU = 0;
	final int GAME_RUNNING = 1;
	final int GAME_OVER = 2; 
	
	//Buffer objects
	Graphics2D g2d;
	BufferedImage backbuffer;         
	
	//Show bounding box
	boolean showBounds = true;
	
	//Create ball instance
	Ball ball = new Ball();
	
	//Create paddle instances
	Paddle paddle = new Paddle();
	Paddle paddleAI = new Paddle();
	
	//Score variables
	int userScore; 
	int AIScore;
	
	//Game loop and random generator
	Thread gameLoop;
	Random rand = new Random();
	
	//AffineTransform
	AffineTransform identity = new AffineTransform();
	
	//Create audio objects
	AudioInputStream sample;
	Sequence song;
	Sequencer sequencer;
	String gong = "gong.wav";
	String explosion = "explode.wav";
	String musicFile = "battlestargalactica.mid";
	Clip audioClip;
   
   private JFrame gameWindow;
	
   public PongClone()
   {
      super();
      initialize();
   }
   
	//File finder
	private URL getURL(String filename)
	{
		URL url = null;
		try
		{
			url = this.getClass().getResource(filename);
		}
		catch(Exception e)
		{}
		return url;
	}
	
	//Method for initalizing variables and objects
	public void initialize()
	{
		userScore = 0;
		AIScore = 0;
      
		gameState = GAME_MENU;
		isRunning = false;
      
      countdown = 3;
      count = 150;
      ballInPlay = false;
		
		//Create back buffer
		backbuffer = new BufferedImage(screenWidth, screenHeight, BufferedImage.TYPE_INT_RGB);
		g2d = backbuffer.createGraphics();
      gameWindow = new JFrame("Pong");
		gameWindow.setSize(screenWidth + 16, screenHeight + 36);
      //gameWindow.getRootPane().setSize(screenWidth, screenHeight);
      gameWindow.setVisible(true);
      gameWindow.setDefaultCloseOperation(gameWindow.EXIT_ON_CLOSE);
      setSize(screenWidth, screenHeight);
      gameWindow.add(this);
		
		//Place paddles
		paddle.setX(295.0);
		paddle.setY(380.0);
		paddleAI.setX(295.0);
		paddleAI.setY(100.0);
		
		//Place ball
		ball.setX(screenWidth / 2);
		ball.setY(screenHeight / 2);
		
		//Set ball velocity
		if (rand.nextInt(2) == 0)
		{
			ball.setVelX(5);
		}
		else if (rand.nextInt(2) == 0) 
		{
			ball.setVelX(-5);
		}
		else 
      {
         ball.setVelX(0);
      }
      
		ball.setVelY(5);
	
		//Add Mouse Input
		addMouseListener(this);
		addMouseMotionListener(this);
	}
	
	//Method for updating graphics and music
	public void update(Graphics g)
	{
		//Draw background
		g2d.setTransform(identity);
		g2d.setPaint(Color.BLUE);
		g2d.fillRect(0, 0, gameWindow.getSize().width, gameWindow.getSize().height);
		
		//Call the methid to draw the game menu when needed
		if (gameState == GAME_MENU)
		{
			drawMenu();
		}
		
		if (gameState == GAME_RUNNING)
		{
			//Create a music stream, if no midi stream is running
			if(!isRunning)
			{
				try
				{
					song = MidiSystem.getSequence(getURL(musicFile));
					sequencer = MidiSystem.getSequencer();
					sequencer.setSequence(song);
					sequencer.open();
					sequencer.start();
					isRunning = true;
				}
				catch (InvalidMidiDataException e)
				{}
				catch (MidiUnavailableException e)
				{}
				catch (IOException e)
				{}
			}
			
			//Draw the line dividing the territories when the game is running
			g2d.setColor(Color.ORANGE);
			g2d.drawLine(0, screenHeight / 2, screenWidth, screenHeight / 2);
			
			//Call the methods to draw the game's objects when the game is running
			drawScore();
         drawBall();
			drawPaddle();
			drawPaddleAI();
		}
		
		//Call the game over screen when needed
		if (gameState == GAME_OVER)
		{
			isRunning = false;
			drawGameOver();
		}
		
		//Redraw the screen
		paint(g);
	}
	
	//For drawing the menu
	public void drawMenu()
	{
		userScore = 0;
		AIScore = 0;
	
		//Draw, format, and color the title
		g2d.setFont(new Font("New Times Roman", Font.BOLD, 36));
		g2d.setColor(Color.YELLOW);
		g2d.drawString("Pong Clone", 230, 202);
		
		//Draw, format, and color the programmer's name 
		g2d.setFont(new Font("New Times Roman", Font.BOLD, 30));
		g2d.setColor(Color.YELLOW);
		g2d.drawString("By coleman7245", 190, 242);
		
		//Draw, color, and format the intructions to proceed to the next screen
		g2d.setFont(new Font("Arial", Font.BOLD, 24));
		g2d.setColor(Color.YELLOW);
		g2d.drawString("Click the right mouse button to start", 120, 450);
	}
	
	//Method for drawing, transforming, and coloring the user paddle
	public void drawPaddle()
	{
		g2d.setTransform(identity);
		g2d.translate(paddle.getX(), paddle.getY());
		g2d.setColor(Color.YELLOW);
		g2d.fill(paddle.getShape());
	}
	
	//Method for drawing, transforming, and coloring the AI's paddle
	public void drawPaddleAI()
	{
		g2d.setTransform(identity);
		g2d.translate(paddleAI.getX(), paddleAI.getY());
		g2d.setColor(Color.RED);
		g2d.fill(paddleAI.getShape());
	}
	
	//Method for drawing, transforming, and coloring the ball
	public void drawBall()
	{	
		g2d.setTransform(identity);
		g2d.translate(ball.getX(), ball.getY());
		g2d.setColor(Color.YELLOW);
		g2d.fill(ball.getShape());
	}
	
	//Method for drawing, formatting, and coloring the score
	public void drawScore()
	{
		g2d.setFont(new Font("New Times Roman", Font.BOLD, 40));
		g2d.setColor(Color.YELLOW);
		g2d.drawString("" + userScore, 10, 460);
		g2d.drawString("" + AIScore, 10, 50);
      
      if (!ballInPlay)
      {
         g2d.drawString("" +  countdown, screenWidth / 2, screenHeight / 3);
      }
	}
	
	//Method for drawing the game over screen
	public void drawGameOver()
	{
		//Stop any midi sequence playing
		sequencer.stop();
		
		//if userScore is 10, then set the winning message for the user
		if (userScore == 10)
		{
			g2d.setFont(new Font("New Times Roman", Font.BOLD, 36));
			g2d.setColor(Color.YELLOW);
			g2d.drawString("Meatbag is the winner!", 130, 202);
		}
		
		//if AIScore is 10, then draw the winning message for the AI
		if (AIScore == 10)
		{
			g2d.setFont(new Font("New Times Roman", Font.BOLD, 36));
			g2d.setColor(Color.RED);
			g2d.drawString("Machine is the winner!", 130, 202);
		}
		
		//Draw the instructions for returning to the main menu
		g2d.setFont(new Font("New Times Roman", Font.BOLD, 20));
		g2d.drawString("Click the right mouse button to return to the main menu", 50, 450);
	}
	
	public void paint(Graphics g) 
	{
		//draw the back buffer onto the applet window
		g.drawImage(backbuffer, 0, 0, this);
	}
	
	public void start()
	{
		//Create game loop and run it
		gameLoop = new Thread(this);
		gameLoop.start();
	}                                
	
	public void run()
	{
		//Create and initialize a new thread
		Thread t = Thread.currentThread();
		
		//Update and repaint the game constantly if the loop is valid
		while (t == gameLoop)
		{
			try
			{
				gameUpdate();
				Thread.sleep(20);
			}
			catch (InterruptedException e)
			{
				e.printStackTrace();
			}
         
			repaint();
		}
		
	}
	
	//Method for stopping the game
	public void stop()
	{
		//Make the loop variable null
		gameLoop = null;
		
		//Stop the midi sequence upon exit
		try
		{
			sequencer.stop();
		}
		catch (NullPointerException e)
		{}
      
      try
      {
         audioClip.stop();
      }
      catch(NullPointerException e)
      {}
	}
	
	public void gameUpdate()
	{
		//Update the game's objects if the game is running
		if (gameState == GAME_RUNNING)
		{
			updatePaddleAI();
			updateBall();
			updateScore();
			checkCollision();
		}
	}
	
	public void updatePaddleAI()
	{
		//Create paddle AI algorithm
		if (ball.getY() <= screenHeight - 120)
		{
			if (paddleAI.getX() != ball.getX() - 15)
			{
				if (paddleAI.getX() > ball.getX())
				{
					paddleAI.setVelX(-5);
				}
				else if (paddleAI.getX() < ball.getX() - 15)
				{
					paddleAI.setVelX(5);
				}
			}
			else paddleAI.setVelX(0);
		}
		paddleAI.incrementX(paddleAI.getVelX()); 
	}
	
	public void updateBall()
	{
      if (ballInPlay)
      {
         count = 150;
         countdown = 3;
      
		   //Update ball's position
		   ball.incrementX(ball.getVelX());
		   ball.incrementY(ball.getVelY());
      }
      else
      {
         //Start the next round
			ball.setX((screenWidth / 2) - 5);
			ball.setY((screenHeight / 2) - 5);
			
         if (countdown == 0)
         {
            ballInPlay = true;
         
			   //Set ball velocity
			   if (rand.nextInt(2) == 0)
			   {
				   ball.setVelX(rand.nextInt(2) * 5);
			   }
			   else 
            {
               ball.setVelX(-5);
            }
            
			   ball.setVelY(5);
          }
          else
          {
            if (count % 50 == 0 && count != 150)
            {
               countdown--;
            }
          
            ball.setVelX(0);
            ball.setVelY(0);
            count--;
          }
      }
	}
	
	public void updateScore()
	{
		//update the AI's score if the ball leaves the top of the screen
		if (ball.getY() >= screenHeight)
		{
			AIScore += 1;
		}
		
		//Update the user's score if the ball leaves the bottom of the screen
		if (ball.getY() <= 0)
		{
			userScore += 1;
		}
		
		//Change the game state if any of the scores equals 10
		if (userScore == 10 || AIScore == 10)
		{
			gameState = GAME_OVER;
		}
	}
	
	public void checkCollision()
	{
		double xDifference;
	
		//Check collision between the ball and the paddle
		if (ball.getBounds().intersects(paddle.getBounds()))
		{
			//Reverse velocity
			
			ball.setVelY(-ball.getVelY());
			xDifference = paddle.getX() - ball.getX() + paddle.getPaddleW() / 2 + ball.getBallW() / 2;
			ball.setVelX(xDifference * -0.5);
			ball.setY(paddle.getY() - ball.getBallH());
			
			//Create gong sound when the ball hits the paddle
			try
			{
				sample = AudioSystem.getAudioInputStream(getURL(gong));
				audioClip = AudioSystem.getClip();
				audioClip.open(sample);
				audioClip.start();
			}
			catch (MalformedURLException e)
			{}
			catch (IOException e)
			{}
			catch (LineUnavailableException e)
			{}
			catch (UnsupportedAudioFileException e)
			{}
			catch (Exception e)
			{}
		}
		
		//Check collision between the ball and the paddle AI
		if (ball.getBounds().intersects(paddleAI.getBounds()))
		{
			//Reverse ball's velocity
			ball.setVelY(-ball.getVelY());
			xDifference = paddleAI.getX() - ball.getX() + paddleAI.getPaddleW() / 2 + ball.getBallW() / 2;
			ball.setVelX(xDifference * -0.5);
			ball.setY(paddleAI.getY() + paddleAI.getPaddleH());
			
			//Create a gong sound when the ball hits the paddle
			try
			{
				sample = AudioSystem.getAudioInputStream(getURL(gong));
				Clip audioClip = AudioSystem.getClip();
				audioClip.open();
				audioClip.start();
			}
			catch (MalformedURLException e)
			{}
			catch (IOException e)
			{}
			catch (LineUnavailableException e)
			{}
			catch (UnsupportedAudioFileException e)
			{}
			catch (Exception e)
			{}
		}
		
		//Check collision between ball and screen
		if (ball.getX() >= screenWidth || ball.getX() <= 0)
		{
			ball.setVelX(-ball.getVelX());
		}
      
		if (ball.getY() >= screenHeight || ball.getY() <= 0)
		{	
			//Create an explosion sound as the ball enters the goal
			try
			{
				sample = AudioSystem.getAudioInputStream(getURL(explosion));
				Clip audioClip = AudioSystem.getClip();
				audioClip.open(sample);
				audioClip.start();
			}
			catch (MalformedURLException e)
			{}
			catch (IOException e)
			{}
			catch (LineUnavailableException e)
			{}
			catch (UnsupportedAudioFileException e)
			{}
			catch (Exception e)
			{}
         
         //The ball is now out of play.
         ballInPlay = false;
		}
	}
	
	public void mouseDragged(MouseEvent e)
	{}
	
	public void mouseMoved(MouseEvent e)
	{
		//Set the user's paddle movement to the mouse's track ball
		paddle.setX(e.getX());
		repaint();
	}
	
	//Method Summary: 
	public void mouseClicked(MouseEvent e)
	{
		//Run the game with a click of the mouse
		if (gameState == GAME_MENU)
		{
			gameState = GAME_RUNNING; //Signal that the game needs to run.
			repaint(); //Render the frame.
		}
		
		//Exit the game over screen with a click of the mouse
		if (gameState == GAME_OVER)
		{
			gameState = GAME_MENU; //Signal that the game menu needs to be displayed.
			repaint(); //Render the frame.
		}
	}
	
	//Method Summary: Runs code if a mouse event occured. Not used for this program.
	public void mouseEntered(MouseEvent e) {}
	
	//Method Summary: Runs code if a mouse event occured. Not used for this program.
	public void mouseExited(MouseEvent e) {}
	
	//Method Summary: Runs code if a mouse event occured. Not used for this program.
	public void mousePressed(MouseEvent e) {}
	
	//Method Summary: Runs code if a mouse event occured. Not used for this program.
	public void mouseReleased(MouseEvent e) {}
   
   //Method Summary: The main method of execution.
   public static void main(String[] args)
   {
      PongCloneFinal game = new PongCloneFinal(); //Create a thread for this game.
      game.start(); //Start the thread.
   }
}
