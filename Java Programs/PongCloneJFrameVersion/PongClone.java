/* 
 * Author: Derek Coleman
 * Project: Pong Clone
 * Last Update: 3/21/19
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
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.lang.String;

/* Class Declaration */
public class PongClone extends Canvas implements Runnable, MouseListener, MouseMotionListener
{	
	//Debug variables.
	BufferedWriter out = null;
	
	String debugString = "";
	
	int screenWidth = 640; //screenWidth: The width of the screen.
	int screenHeight = 480; //screenHeight: The height of the screen.
	
    //Countdown clock variables.
    int countdown; //countdown: The visible count before each round.
    int count; //count: The current count in between each countdown decrement.
    boolean hasReset; //countdownReset: Indicates if the countdown variables have been reset.
    
    //Time delay variables.
    long startTime; //startTime: Stores the time started during transition screen.
    long timeDelta; //timeDelta: The difference between the current time and the start time.
	
	//Player turn variables.
	enum PlayerTurn {HUMAN, CPU}; //Player is either a human or an AI.
	PlayerTurn playerTurn; //playerTurn: The current server at the start of the round.
	
	//Game state variables.
	enum GameState {MENU, PREROUND, ROUND, OVER}; //Game states that include menu, transition between rounds, round of play, and game over. Will feature an options menu soon.
	GameState gameState; //gameState: The current game state.
	boolean changeToMenu; //changeToMenu: Signals that the user wants to change from the game over screen to the menu.
	boolean changeToPreround; //changeToPreround: Signals that the user wants to change from the menu to the game itself.
	
	//Buffer objects
	Graphics2D g2d; //g2d: Draws the graphics of the app.
	BufferedImage backbuffer; //backbuffer: The buffer containing the image data.        
	
	//Show bounding box
	boolean showBounds = true; //showBounds: Check to enable the rendering of the bounding boxes.
	
	//Create ball instance
	Ball ball = new Ball(); //ball: The ball used in the game.
	
	//Create paddle instances
	Paddle paddle = new Paddle(); //paddle: The player's paddle.
	Paddle paddleAI = new Paddle(); //paddleAI: The AI's paddle.
	
	//Score variables
	int userScore; //userScore: The player's win score.
	int AIScore; //AIscore: The AI's win score.
	int scoreLimit; //scoreLimit: The upper limit of any score.
	
	//Game loop and random number generator
	Thread gameLoop; //gameLoop: The instance of the game itself.
	Random rand = new Random(); //rand: Random number generator.
	
	//AffineTransform
	AffineTransform identity = new AffineTransform(); //identity: Transforms the coordinates of a 2-D object.
	
	//Create audio objects
	boolean songIsRunning; //songIsRunning: Indicates if the MIDI song is currently playing.
	AudioInputStream sample; //sample: Plays an audio clip.
	Sequence song; //song: A MIDI song.
	Sequencer sequencer; //sequencer: Plays a MIDI song.
	String gong = "gong.wav"; //gong: Filename of the gong audio clip.
	String explosion = "explode.wav"; //explosion: Filename of the explosion audio clip.
	String musicFile = "battlestargalactica.mid"; //musicFile: Filename of the MIDI music file.
	Clip audioClip; //audioClip: Plays the a short audio clip.
   
    //Application window:
	private JFrame gameWindow; //gameWindow: Hosts the game in a display window.
	
	//Method Summary: The default constrcutor of the Pong Clone.
	public PongClone()
	{
		super(); //Call the parent class' constructor.
		initialize(); //Initialize the class attributes.
	}
   
	//Method Summary: Finds a file using the URL.
	private URL getURL(String filename)
	{
		URL url = null; //url: The URL of the file.
		
		try
		{
			url = this.getClass().getResource(filename); //Try to retrieve the file.
		}
		catch(Exception e) //Catch a general exception.
		{}
		
		return url; //Return the url.
	}
	
	//Method Summary: Initializes the class attrubutes to their default values.
	public void initialize()
	{
		//Debug operations.
		try
		{
			out = new BufferedWriter(new FileWriter("debug.txt"));
		}
		catch (IOException ioe) {}
		catch (Exception e) {}
		
		songIsRunning = false; //The MIDI song doesn't run until the game is in play.
		
		startTime = 0; //Set the delay start time to 0.
		timeDelta = 3; //Set the time delta to 3 to bypass the check when the application first starts.
		
		userScore = 0; //User score set to 0.
		AIScore = 0; //AI score set to 0.
		scoreLimit = 1; //Set the score limit to 1.
      
		gameState = GameState.MENU; //Start the game state at the menu.
      
		countdown = 3; //The time before each round is 3 seconds.
		count = 150; //Set the count to 150.
		hasReset = true; //Indicate that there is no need to reset the paddle and ball variables.
		
		//Create back buffer
		backbuffer = new BufferedImage(screenWidth, screenHeight, BufferedImage.TYPE_INT_RGB); //Initialize the back buffer with screen information.
		g2d = backbuffer.createGraphics(); //Create the grpahics through the back buffer.
		gameWindow = new JFrame("Pong"); //Set up a new JFrame window.
		gameWindow.setSize(screenWidth + 16, screenHeight + 36); //Set the size of the window to a height and width slightly bigger than the game screen size.
		//gameWindow.getRootPane().setSize(screenWidth, screenHeight);
		gameWindow.setVisible(true); //Set the window to be visible.
		gameWindow.setDefaultCloseOperation(gameWindow.EXIT_ON_CLOSE); //The window will cease execution if the red X on the window is clicked.
		setSize(screenWidth, screenHeight); //Set the size of the game screen.
		gameWindow.add(this); //Add the game to the JFrame window.
		
		initializeBall(); //Place the ball in the appropriate position.
		initializePaddles(); //Place the paddles in their appropriate places.
		
		playerTurn = PlayerTurn.HUMAN; //The first server is human.
	
		addMouseListener(this); //Add a mouse listener for mouse input events.
		addMouseMotionListener(this); //Add a mouse motion listener for mouse motion events.
	}
	
	//Method Summary: Updates the graphics rendering and audio playback.
	public void update(Graphics g)
	{
		//Draw background
		g2d.setTransform(identity);
		g2d.setPaint(Color.BLUE);
		g2d.fillRect(0, 0, gameWindow.getSize().width, gameWindow.getSize().height);
		
		//Call the methid to draw the game menu when needed
		if (gameState == GameState.MENU)
		{
			debugString = "Drawing menu!\n";
			
			try
			{
				out.write(debugString, 0, debugString.length());
			}
			catch(IOException ioe) {}
			catch(Exception e) {}
			
			drawMenu();
		}
		
		//If a round is currently playing or if the preround preparations are occuring, then...
		if (gameState == GameState.ROUND || gameState == GameState.PREROUND)
		{
			//Call the countdown screen when needed.
			if (gameState == GameState.PREROUND)
			{
				debugString = "Drawing countdown!\n";
			
				try
				{
					out.write(debugString, 0, debugString.length());
				}
				catch(IOException ioe) {}
				catch(Exception e) {} 
				
				drawCountdown();
			}
			
			//Create a music stream, if no midi stream is running
			if(!songIsRunning)
			{
				try
				{
					song = MidiSystem.getSequence(getURL(musicFile));
					sequencer = MidiSystem.getSequencer();
					sequencer.setSequence(song);
					sequencer.open();
					sequencer.start();
					songIsRunning = true;
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
			debugString = "Drawing game objects!\n";
			
			try
			{
				out.write(debugString, 0, debugString.length());
			}
			catch(IOException ioe) {}
			catch(Exception e) {}
			
			drawRoundInfo();
			drawBall();
			drawPaddle();
			drawPaddleAI();
		}
		
		//Call the game over screen when needed.
		if (gameState == GameState.OVER)
		{
			debugString = "Drawing game over!\n";
			
			try
			{
				out.write(debugString, 0, debugString.length());
			}
			catch(IOException ioe) {}
			catch(Exception e) {}
			
			drawGameOver();
		}
		
		paint(g); //Redraw the screen.
	}
	
	//Method Summary: Draws the game menu.
	public void drawMenu()
	{
		//Set the scores to 0.
		userScore = 0;
		AIScore = 0;
	
		//Draw, format, and color the title.
		g2d.setFont(new Font("New Times Roman", Font.BOLD, 36));
		g2d.setColor(Color.YELLOW);
		g2d.drawString("Pong Clone", 230, 202);
		
		//Draw, format, and color the programmer's name .
		g2d.setFont(new Font("New Times Roman", Font.BOLD, 30));
		g2d.setColor(Color.YELLOW);
		g2d.drawString("By Derek Coleman", 190, 242);
		
		//Draw, color, and format the intructions to proceed to the next screen.
		g2d.setFont(new Font("Arial", Font.BOLD, 24));
		g2d.setColor(Color.YELLOW);
		g2d.drawString("Click a mouse button to start", 120, 450);
	}
	
	//Method Summary: Draws, transforms, and colors the user paddle.
	public void drawPaddle()
	{
		g2d.setTransform(identity); //Set the transform of the paddle.
		g2d.translate(paddle.getPosition().getX(), paddle.getPosition().getY()); //Translate the paddle's position.
		g2d.setColor(Color.YELLOW); //Set the color of the paddle.
		g2d.fill(paddle.getShape()); //Draw the paddle.
	}
	
	//Method Summary: Draws, transforms, and colors the AI's paddle.
	public void drawPaddleAI()
	{
		g2d.setTransform(identity); //Set the transform of the AI's paddle.
		g2d.translate(paddleAI.getPosition().getX(), paddleAI.getPosition().getY()); //Translate the position of the AI's paddle.
		g2d.setColor(Color.RED); //Set the color of the AI's paddle.
		g2d.fill(paddleAI.getShape()); //Draw the AI's paddle.
	}
	
	//Method Summary: Draws, transforms, and colors the ball.
	public void drawBall()
	{	
		g2d.setTransform(identity); //Set the transform of the ball.
		g2d.translate(ball.getPosition().getX(), ball.getPosition().getY()); //Translate the ball's position.
		g2d.setColor(Color.YELLOW); //Set the color of the ball.
		g2d.fill(ball.getShape()); //Draw the ball.
	}
	
	//Method Summary: Draws, formats, and colors the round information.
	public void drawRoundInfo()
	{
		g2d.setFont(new Font("New Times Roman", Font.BOLD, 40)); //Set the font of the score.
		g2d.setColor(Color.YELLOW); //Set the color of the font.
		g2d.drawString("" + userScore, 10, 460); //Draw the user score.
		g2d.drawString("" + AIScore, 10, 50); //Draw the AI score.
	}
	
	//Method Summary: Draws the countdown.
	public void drawCountdown()
	{
		g2d.setFont(new Font("New Times Roman", Font.BOLD, 40)); //Set the font of the score.
		g2d.setColor(Color.YELLOW); //Set the color of the font.
		g2d.drawString("" +  countdown, screenWidth / 2, screenHeight / 3); //Draw the countdown before the next round.
	}
	
	//Method Summary: Draws the game over screen.
	public void drawGameOver()
	{
		sequencer.stop(); //Stop any midi sequence playing.
		songIsRunning = false; //Set the check on the song's activity to false.
		
		//If userScore is 10, then set the winning message for the user.
		if (userScore == 1)
		{
			g2d.setFont(new Font("New Times Roman", Font.BOLD, 36));
			g2d.setColor(Color.YELLOW);
			g2d.drawString("Meatbag is the winner!", 130, 202);
		}
		
		//If AIScore is 10, then draw the winning message for the AI.
		if (AIScore == 1)
		{
			g2d.setFont(new Font("New Times Roman", Font.BOLD, 36));
			g2d.setColor(Color.RED);
			g2d.drawString("Machine is the winner!", 130, 202);
		}
		
		//Draw the instructions for returning to the main menu.
		g2d.setFont(new Font("New Times Roman", Font.BOLD, 20));
		g2d.drawString("Click the right mouse button to return to the main menu", 50, 450);
	}
	
	//Method Summary: Paints the graphics with the back buffer's information.
	public void paint(Graphics g) 
	{
		//draw the back buffer onto the applet window
		g.drawImage(backbuffer, 0, 0, this);
	}
	
	//Method Summary: Starts the game loop.
	public void start()
	{
		//Create game loop and run it
		gameLoop = new Thread(this);
		gameLoop.start();
	}                                
	
	//Method Summary: Runs the thread.
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
	
	//Method Summary: Stops the thread and performs closing maintenance.
	public void stop()
	{
		try
		{
			out.close();
		}
		catch (IOException ioe) {}
		catch (Exception e) {}
		
		//Make the loop variable null
		gameLoop = null;
		
		//Stop the midi sequence upon exit
		try
		{
			sequencer.stop();
			songIsRunning = false;
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
	
	//Method Summary: Updates the game's information and objects.
	public void gameUpdate()
	{
		//Update the game's objects if the game is running.
		if (gameState == GameState.ROUND)
		{
			updatePaddleAI();
			updateBall();
			updateRoundInfo();
			checkCollision();
		}
		else if (gameState == GameState.PREROUND)
		{
			if (!hasReset)
			{
				prepareNextRound();
				hasReset = true;
			}
			
			updateCountdown();
		}
		
		updateGameState();
	}
	
	//Method Summary: Updates the AI of the opponent.
	public void updatePaddleAI()
	{
		//Find the current ball direction.
		Vector2 currentBallDirection = new Vector2(ball.getVelocity());
		currentBallDirection.normalize();
		
		currentBallDirection.scale(Vector2.distance(paddleAI.getPosition(), ball.getPosition())); //Scale the current ball direction by the distance between the AI's paddle and the ball.
		double closingDistance = Vector2.distance(paddleAI.getPosition(), currentBallDirection);
		
		//Move the paddle if the ball is apporoaching the goal.
		if (closingDistance > paddleAI.getPaddleW() / 2 && ball.getPosition().getY() < screenHeight / 2)
		{
			if (paddleAI.getPosition().getX() != ball.getPosition().getX() - 15)
			{
				if (paddleAI.getPosition().getX() > ball.getPosition().getX())
				{
					paddleAI.getVelocity().setX(-5);
				}
				else if (paddleAI.getPosition().getX() < ball.getPosition().getX() - 15)
				{
					paddleAI.getVelocity().setX(5);
				}
			}
			
			paddleAI.moveShape(); //Move the paddle in the appropriate direction.
		}
	}
	
	//Method Summary: Updates the ball's position.
	public void updateBall()
	{		
		ball.moveShape(); //Update the ball's position.
	}
	
	//Method Summary: Updates the score.
	public void updateRoundInfo()
	{
		//Update the AI's score if the ball leaves the top of the screen.
		if (ball.getPosition().getY() >= screenHeight)
		{
			AIScore += 1;
		}
		
		//Update the user's score if the ball leaves the bottom of the screen.
		if (ball.getPosition().getY() <= 0)
		{
			userScore += 1;
		}
	}
	
	public void updateCountdown()
	{
		if (countdown == 0)
		{
			countdown = 3; //Reset the countdown to 3.
			count = 150; //Reset the count to 150.
			playerTurn = (playerTurn == PlayerTurn.HUMAN) ? PlayerTurn.CPU : PlayerTurn.HUMAN; //Switch the player turn.
		}
		
		if (count % 50 == 0 && count != 150) //If the count is divisible by 50 and is NOT the initial value:
		{
			countdown--; //Decrement the countdown.
		}
          
		count--; //Decrement the count.
	}
	
	//Method Summary: Prepares the next round.
	public void prepareNextRound()
	{
		initializeBall(); //Initialize the ball.
		initializePaddles(); //Initialize the paddles.
	}
	
	//Method Summary: Initializes the ball's properties before the next round.
	public void initializeBall()
	{
		double ballVelY = 5.0; //Set the ball's vertical velocity.
		double ballVelX = rand.nextDouble() * 5.0; //Set the ball's horizontal velocity.
				
		if (playerTurn == PlayerTurn.CPU) //If the CPU is the sever:
		{
			ballVelY *= -1.0; //Flip the polarity of the ball's vertical velocity.
		}
				
		if (rand.nextInt(2) == 0) //If the random integer is correct:
		{
			ballVelX *= -1.0; //Flip the polarity of the ball's horizontal velocity.
		}
				
		ball.setVelocity(ballVelX, ballVelY); //Set the velocity of the ball.
		ball.setPosition((screenWidth / 2) - 5, (screenHeight / 2) - 5); //Start the next round.
	}
	
	//Method Summary: Initialize the paddles' properties before the next round.
	public void initializePaddles()
	{
		//Place the paddles to their respective positions at the top and bottom of the game screen.
		paddle.setPosition(295.0, 380.0);
		paddleAI.setPosition(295.0, 100.0);
	}
	
	//Method Summary: Checks the collision every frame.
	public void checkCollision()
	{
		double xDifference; //Check the difference of the x values.
	
		//Check the collision between the ball and the paddle.
		if (ball.getBounds().intersects(paddle.getBounds()))
		{
			//Reverse the velocity of the ball.
			xDifference = paddle.getPosition().getX() - ball.getPosition().getX() + paddle.getPaddleW() / 2 + ball.getBallW() / 2;
			ball.setVelocity(xDifference * -0.5, -ball.getVelocity().getY());
			ball.getPosition().setY(paddle.getPosition().getY() - ball.getBallH());
			
			//Create gong sound when the ball hits the paddle.
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
		
		//Check collision between the ball and the paddle AI.
		if (ball.getBounds().intersects(paddleAI.getBounds()))
		{
			//Reverse the ball's velocity.
			xDifference = paddleAI.getPosition().getX() - ball.getPosition().getX() + paddleAI.getPaddleW() / 2 + ball.getBallW() / 2;
			ball.setVelocity(xDifference * -0.5, -ball.getVelocity().getY());
			ball.getPosition().setY(paddleAI.getPosition().getY() + ball.getBallH());
			
			//Create a gong sound when the ball hits the paddle.
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
		
		//Check collision between the ball and screen.
		if (ball.getPosition().getX() >= screenWidth || ball.getPosition().getX() <= 0)
		{
			ball.getVelocity().setX(-ball.getVelocity().getX());
		}
		
		//Check the collision between the ball and goal.
		if (ball.getPosition().getY() >= screenHeight || ball.getPosition().getY() <= 0)
		{	
			//Create an explosion sound as the ball enters the goal.
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
         
			//Indicate the paddle and ball properties need to be reset.
			hasReset = false;
		}
	}
	
	public void updateGameState()
	{
		if (gameState == GameState.OVER)
		{
			if (changeToMenu) //If the user wants to transition to the menu, then...
			{
				if (timeDelta >= 3) //If 3 seconds have passed, then...
				{
					gameState = GameState.MENU; //Change the game state to the menu.
					changeToMenu = false; //Signal that the transition to the menu is complete.
					startTime = System.currentTimeMillis() * 1000; //Begin the delay time during the menu.
					timeDelta = 0; //Reset the time delta.
				}
				else
				{
					timeDelta = System.currentTimeMillis() * 1000 - startTime; //Store the current time delta.
				}
			}
		}
		else if (gameState == GameState.ROUND)
		{
			if (userScore == scoreLimit || AIScore == scoreLimit) //Change the game state if any of the scores equals 1.
			{
				gameState = GameState.OVER; //Change the game state to the game over screen.
				startTime = System.currentTimeMillis() * 1000;
			}
			else if (ball.getPosition().getY() >= screenHeight || ball.getPosition().getY() <= 0)
			{
				gameState = GameState.PREROUND; //Change the game state to the preround preparations.
			}
		}
		else if (gameState == GameState.MENU) //If the ball passes any of the goals OR the user wants to transition from the menu, then...
		{
			if (changeToPreround) //If the change to the preround is signaled, then...
			{
				if (timeDelta >= 3) //If 3 seconds have passed, then...
				{
					gameState = GameState.PREROUND; //Change the game state to the menu.
					changeToPreround = false; //Signal that the transition to the preround stage is complete.
					startTime = System.currentTimeMillis() * 1000; //Begin the delay time.
					timeDelta = 0; //Reset the time delta.
				}
				else
				{
					timeDelta = System.currentTimeMillis() * 1000 - startTime; //Store the current time delta.
				}
			}
		}
		else
		{
			if (countdown == 0)
			{
				gameState = GameState.ROUND;
			}
		}
	}
	
	//Method Summary: Listens for mouse dragging events. Not used.
	public void mouseDragged(MouseEvent e)
	{}
	
	//Method Summary: Listens for mouse movement events.
	public void mouseMoved(MouseEvent e)
	{
		paddle.getPosition().setX(e.getX()); //Set the user's paddle movement to the mouse's track ball
		repaint(); //Render the frame.
	}
	
	//Method Summary: Listens for mouse clicking events.
	public void mouseClicked(MouseEvent e)
	{
		//Run the game with a click of the mouse.
		if (gameState == GameState.MENU)
		{
			changeToPreround = true; //Signal the start of a new round.
		}
		
		//Exit the game over screen with a click of the mouse
		if (gameState == GameState.OVER)
		{
			changeToMenu = true; //Signal the transition from the game over screen to the menu.
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
      PongClone game = new PongClone(); //Create a thread for this game.
      game.start(); //Start the thread.
   }
}
