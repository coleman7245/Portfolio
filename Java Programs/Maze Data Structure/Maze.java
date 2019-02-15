//Author: coleman7245
//Project: Maze Class
//Last Edit: Thursday, February 14, 2019

import java.io.BufferedReader; 
import java.io.FileReader; 
import java.io.IOException; 
import java.util.StringTokenizer;


public class Maze implements MazeInterface
{
   private char [][] maze; 
   private int nRows; 
   private int nCols;
   
   //readFromFile method written by Chuck Anderson
   public void readFromFile(String filename) throws MazeException
   {
      BufferedReader input; 
      String line; 
      StringTokenizer tokenizer; 
      
      nRows = 0; 
      try 
      { 
         int currentRow = 0; 
         input = new BufferedReader(new FileReader(filename)); 
         
         while ((line = input.readLine()) != null) 
         { 
            if (nRows == 0) 
            { // true if reading first line in file, containing nRows nColums 
               tokenizer = new StringTokenizer(line); 
               nRows = Integer.parseInt(tokenizer.nextToken()); 
               nCols = Integer.parseInt(tokenizer.nextToken()); 
               maze = new char[nRows][nCols]; 
            } 
            else if (line.length() == 1) 
               break; // in case there is a linefeed at end of file 
            else 
            { 
               for (int c = 0; c < nCols; c++) 
               { 
                  maze[currentRow][c] = line.charAt(c); 
               } 
               currentRow ++; 
            } 
         } 
      } 
      catch (IOException e) 
      { 
         throw new MazeException("Problem reading maze file " + filename);
      }
   }
   
   public String solveMaze(String stackOrQueue)
   {
	   int row = 0;
	   int column = 0;
	   StackQueueInterface<Position> unexplored = null;
	   
	   if (stackOrQueue.equals("stack"))
			unexplored = new Stack<Position>();
	   else if (stackOrQueue.equals("queue"))
			unexplored = new Queue<Position>();
	   
	   
	   for (int i = 0; i < nRows; i++)
	   {
		   for (int j = 0; j < nCols; j++)
		   {
			   if (maze[i][j] == 'S')
			   {
				   row = i;
				   column = j;
			   }
		   }
	   }
	   
	   unexplored.put(new Position(row, column));
      Position temp = unexplored.get();
      int numOfVisited = 0;
      
	   while (maze[temp.getRow()][temp.getColumn()] != 'G')
      {
         if (maze[temp.getRow()][temp.getColumn()] == ' ')
         {
            maze[temp.getRow()][temp.getColumn()] = '.';
            numOfVisited++;
         }
      
         if (maze[temp.up().getRow()][temp.up().getColumn()] == 'G')
            break;
         else if (maze[temp.up().getRow()][temp.up().getColumn()] == ' ')
         {
            unexplored.put(temp.up());
         }
         
         if (maze[temp.right().getRow()][temp.right().getColumn()] == 'G')
            break;
         else if (maze[temp.right().getRow()][temp.right().getColumn()] == ' ')
         {
            unexplored.put(temp.right());
         }
            
         if (maze[temp.down().getRow()][temp.down().getColumn()] == 'G')
            break;
         else if (maze[temp.down().getRow()][temp.down().getColumn()] == ' ')
         {
            unexplored.put(temp.down());
         }
            
         if (maze[temp.left().getRow()][temp.left().getColumn()] == 'G')
            break;
         else if (maze[temp.left().getRow()][temp.left().getColumn()] == ' ')
         {
            unexplored.put(temp.left());
         }
         
         temp = unexplored.get();
      }
	   
      String s = "With " + stackOrQueue + ": Goal found! " + numOfVisited + 
      " explored positions.\nunexplored list contains " + 
      unexplored.size() + " positions.\n";
      
      for (int i = 0; i < nRows; i++)
         for (int j = 0; j < nCols; j++)
         {
            s += maze[i][j];
            
            if (j == (nCols - 1))
               s += "\n";
         }
      
      return s;
   }
   
   public String toString()
   {
      String s = "";
      
      for (int i = 0; i < nRows; i++)
         for (int j = 0; j < nCols; j++)
         {
            s += maze[i][j];
            
            if (j == (nCols - 1))
               s += "\n";
         }
   
      return s;
   }
}
