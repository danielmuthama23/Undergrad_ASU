/*
CSE 110
Assignment: Assignment 08
Author: Tyler Fichiera 1218959911
Description: Source for Player class
*/

package Assignment07;

public class Player {
    // init private variables
    private String name;
    private double attackStat, blockStat;

    // overload constructor that accepts name, attack and block stats
    public Player(String fname, double fattackStat, double fblockStat) {
        // assign args to private vars
        this.name = fname;
        this.attackStat = fattackStat;
        this.blockStat = fblockStat; 
    }

    // print player info method, returns nothing
    public void printPlayerInfo() {
        // format stats with two decimal places using `%.2f`
        System.out.printf("%s (attack = %.2f, block = %.2f)\n", this.name, this.attackStat, this.blockStat);
    }

    // getter for name
    public String getName() {
        return this.name;
    }

    // getter for attack stats
    public double getAttackStat() {
        return this.attackStat;
    }

    // getter for block stats
    public double getBlockStat() {
        return this.blockStat;
    }

    // setter for attack stat
    public void setAttackStat(double fattackStat) {
        this.attackStat = fattackStat;
    }

    // setter for block stat
    public void setBlockStat(double fblockStat) {
        this.blockStat = fblockStat;
    }
}