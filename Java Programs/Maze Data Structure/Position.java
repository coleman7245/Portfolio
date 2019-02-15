//Author: coleman7245
//Project: Position Class
//Last Edit: Thursday, February 14, 2019

public class Position {

   protected int row;
   protected int column;

   public Position(int rowArg, int columnArg) {
      row = rowArg;
      column = columnArg;
   }

   public String toString() {
      return "(" + row + "," + column + ")";
   }

   public int getRow() {
      return row;
   }
   public int getColumn() {
      return column;
   }

   public Position up() {
      return new Position(row-1,column);
   }
   public Position down() {
      return new Position(row+1,column);
   }

   public Position right() {
      return new Position(row,column+1);
   }
   public Position left() {
      return new Position(row,column-1);
   }

   // Test it.
   public static void main(String[] args) {

      Position a = new Position(10,20);

      System.out.println("a = new Position(10,20) assigns " + a);
      System.out.println("a.getRow() is " + a.getRow());
      System.out.println("a.getColumn() is " + a.getColumn());
      System.out.println("a.up() is " + a.up());
      System.out.println("a.down() is " + a.down());
      System.out.println("a.left() is " + a.left());
      System.out.println("a.right() is " + a.right());
   }
}
