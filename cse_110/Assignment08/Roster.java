/*
CSE 110
Assignment: Assignment 08
Author: Tyler Fichiera 1218959911
Description: Source for Roster class
*/

package Assignment08;

import java.util.ArrayList;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class Roster {
    // declare private arraylist variable
    private ArrayList<Player> players;

    // default constructor with no args
    public Roster() {
        this.players = new ArrayList<Player>();
    }

    // overload constructor that accepts a file name
    public Roster(String fileName) throws FileNotFoundException, IOException {
        // init array list
        this.players = new ArrayList<Player>();

        try {
            // create filereader for the specified txt file
            FileReader fr = new FileReader(fileName);
            // create buffer reader from the contents of lab10_student_data.txt
            BufferedReader inFile = new BufferedReader(fr);

            // use while true and then break when line is null
            while (true) {
                // read line one at a time
                String line = inFile.readLine();
                // break while loop if line is not defined
                if (line == null) break;
                // parse fullname
                String fullName = line.substring(0, line.indexOf(" ", line.indexOf(" ") + 1));
                // parse attack stat and convert to double
                double attack = Double.parseDouble(
                    line.substring(fullName.length() + 1, line.lastIndexOf(" "))
                );
                // parse block stat and convert to double
                double block = Double.parseDouble(line.substring(line.lastIndexOf(" ") + 1));
                // add player to array
                this.addPlayer(fullName, attack, block);
            }

            inFile.close(); // close file
        } catch (IOException ex) {
            // print exception
            System.out.println(ex);
        }
    }

    // void method for adding a player
    public void addPlayer(String fname, double fattackStat, double fblockStat) {
        // create new Player inline and add to arraylist
        this.players.add(new Player(fname, fattackStat, fblockStat));
    }

    // getter for the number of elements in this.players
    public int countPlayers() {
        return this.players.size();
    }

    // get a player by full name
    public Player getPlayerByName(String fname) {
        // iterate over all players
        for (Player player : this.players) {
            // if name matches, return it
            if (player.getName().equals(fname))
                return player;
        }
        // if not return null
        return null;
    }

    // method for printing out the two best attackers
    public void printTopAttackers() {
        // variable to track the first top player
        Player topAttacker1 = this.players.get(0);
        // iterate over all players besides the first since it is already set to topAttacker1
        for (int i = 1; i < this.players.size(); i++) {
            if (this.players.get(i).getAttackStat() > topAttacker1.getAttackStat()) {
                // if higher stat, set as topAttacker1
                topAttacker1 = this.players.get(i);
            }
        }
        // remove the top player before finding the second best
        this.players.remove(topAttacker1);

        // variable to track the second top player
        Player topAttacker2 = this.players.get(0);
        // iterate over all players besides the first since it is already set to topAttacker2
        for (int i = 1; i < this.players.size(); i++) {
            if (this.players.get(i).getAttackStat() > topAttacker2.getAttackStat()) {
                // if higher stat, set as topAttacker2
                topAttacker2 = this.players.get(i);
            }
        }

        // print the two stored players
        topAttacker1.printPlayerInfo();
        topAttacker2.printPlayerInfo();
    }

    // method for printing out the two best blockers
    public void printTopBlockers() {
        // variable to track the first top player
        Player topBlocker1 = this.players.get(0);
        // iterate over all players besides the first since it is already set to topBlocker1
        for (int i = 1; i < this.players.size(); i++) {
            if (this.players.get(i).getBlockStat() > topBlocker1.getBlockStat()) {
                // if higher stat, set as topBlocker1
                topBlocker1 = this.players.get(i);
            }
        }
        // remove the top player before finding the second best
        this.players.remove(topBlocker1);

        // variable to track the second top player
        Player topBlocker2 = this.players.get(0);
        // iterate over all players besides the first since it is already set to topBlocker2
        for (int i = 1; i < this.players.size(); i++) {
            if (this.players.get(i).getBlockStat() > topBlocker2.getBlockStat()) {
                // if higher stat, set as topBlocker2
                topBlocker2 = this.players.get(i);
            }
        }

        // print the two stored players
        topBlocker1.printPlayerInfo();
        topBlocker2.printPlayerInfo();
    }

    // method for printing all players
    public void printAllPlayers() {
        // for each loop and then print player info using helper method
        for (Player player : this.players)
            player.printPlayerInfo();
    }
}