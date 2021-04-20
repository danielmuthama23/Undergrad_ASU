// Assignment #: 11
// Name: Tyler Fichiera
// StudentID: 1218959911
// Lecture: T/Th 4:30
// Section: 33116
// Description: The pair class pairs a row number and a column number.

public class Pair
 {
  private int row;
  private int col;

  //Initializes the pair object using two parameters
  public Pair(int row, int col)
   {
     this.row = row;
     this.col = col;
   }

  //Accessor method for the row number
  public int getRow()
   {
     return row;
   }

  //Accessor method for the column number
  public int getColumn()
   {
     return col;
   }
 }
