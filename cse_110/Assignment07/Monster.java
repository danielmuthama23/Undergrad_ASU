/*
CSE 110
Assignment: Assignment 07
Author: Tyler Fichiera 1218959911
Description: Source for Monster class
*/

package Assignment07;

public class Monster {
    // declare private vars
    private String name;
    private int healthScore;
    private Weapon weapon;

    // overload constructor for Monster 
    public Monster(String fname, int fhealthScore, Weapon fweapon) {
        this.name = fname;
        this.healthScore = fhealthScore;
        this.weapon = fweapon;
    }

    // getter for Monster's name
    public String getName() {
        return this.name;
    }

    // getter for Monster's health score
    public int getHealthScore() {
        return this.healthScore;
    }

    // getter for Monster's weapon name
    public String getWeaponName() {
        return this.weapon.getName();
    }

    // method for attacking another monster
    // returns an int for the amount of damage inflicted
    public int attack(Monster fmonster) {
        // inclusive number picker: [0, this.weapon.getMaxDamage()]
        int damage = (int)(Math.random() * this.weapon.getMaxDamage());
        fmonster.healthScore -= damage;
        return damage;
    }
}