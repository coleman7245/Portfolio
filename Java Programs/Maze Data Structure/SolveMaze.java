//Author: coleman7245
//Project: SolveMaze Class
//Last Edit: Thursday, February 14, 2019

public class SolveMaze
{
   public static void main (String[] args)
   {
      Maze maze1 = new Maze();
      //Maze maze2 = new Maze();
   
      maze1.readFromFile("maze1.txt");
      System.out.print(maze1.solveMaze("stack"));
      System.out.println();
      maze1.readFromFile("maze1.txt");
      System.out.println(maze1.solveMaze("queue"));
      System.out.println();
      /*maze2.readFromFile("maze2.txt");
      System.out.print(maze2.solveMaze("stack"));
      System.out.println();
      maze2.readFromFile("maze2.txt");
      System.out.print(maze2.solveMaze("queue"));*/
   }
}
