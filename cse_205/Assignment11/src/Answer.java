// Assignment #: 11
// Name: Tyler Fichiera
// StudentID: 1218959911
// Lecture: T/Th 4:30
// Section: 33116
// Description: This class contains a 2-dimensional array to
//              display the content of the checker board.

import java.util.Stack;

public class Answer
 {
   private char[][] solution;

   //Constructor to create a 2-dimensional array and initialize it.
   public Answer(int size)
    {
     solution = new char[size][size];

     for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++)
        solution[i][j] = '_';
     }

  //This method changes the element at row and col to have 'Q'
  //to say that there is a queen placed at the location.
  public void setQueen(int row, int col)
   {
     solution[row][col] = 'Q';
   }

  //The copySolution method copies the location of queens from
  //the parameter stack into the 2-dimensional array
  public void copySolution(Stack solution)
   {
     while (!solution.isEmpty())
       {
        Pair current = (Pair) solution.pop();
        setQueen(current.getRow(), current.getColumn());
       }
   }

  //The toString method returns a string to display the content of
  //the n queen problem solution
  public String toString()
   {
    String result = "";

    result += " |";

     for (int j = 0; j < solution.length; j++)
      {
       result += j + "|";
      }
     result += "\n";

     for (int i = 0; i < solution.length; i++)
      {
        result += i + "|";
       for (int j = 0; j < solution[i].length; j++)
        {
            result += solution[i][j] + "|";
        }
       result += "\n";
      }

     return result;
   }

}//end of the Answer class

