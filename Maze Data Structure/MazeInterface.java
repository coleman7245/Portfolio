//Author: coleman7245
//Project: Maze Interface
//Last Edit: Thursday, February 14, 2019

public interface MazeInterface {

    public void readFromFile(String filename) throws MazeException;

    public String toString();

    // solveMaze takes one argument with value "stack" or "queue".
    // Returns result String that starts like
    //    "With stack: Goal found! 56 steps tried. unexplored contains 45 positions.
    // and ends like
    //    #........#
    //    ##########"
    public String solveMaze(String stackOrQueue);
}
