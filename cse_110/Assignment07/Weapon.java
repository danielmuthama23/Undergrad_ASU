/*
CSE 110
Assignment: Assignment 07
Author: Tyler Fichiera 1218959911
Description: Source for Weapon class
*/

public class Weapon {
    // declare private vars
    private String name;
    private int maxDamage;
    
    // default constructor for Weapon
    public Weapon() {
        this.name = "Pointy Stick";
        this.maxDamage = 1;
    }

    // overload constructor for Weapon
    public Weapon(String fname, int fmaxDamage) {
        this.name = fname;
        this.maxDamage = fmaxDamage;
    }

    // getter for Weapon's name
    public String getName() {
        return this.name;
    }

    // setter for Weapon's name
    public void setName(String fname) {
        this.name = fname;
    }

    // getter for Weapon's max damage
    public int getMaxDamage() {
        return this.maxDamage;
    }
    
    // setter for Weapon's max damage
    public void setMaxDamage(int fmaxDamage) {
        this.maxDamage = fmaxDamage;
    }
}