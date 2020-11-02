/*
AUTHOR: Tyler Fichiera
FILENAME: Program.java
SPECIFICATION: Class for Program object
FOR: CSE 110 Lab #7
TIME SPENT: 30 mins
*/
import java.time.LocalDateTime;

public class Program {
    // init private vars
    private String programName, description, fileName, createdDate;
    private Student author;

    public Program(String name, String desc, String filename, Student auth) {
        // assign constuctor args to private vars
        programName = name;
        description = desc;
        fileName = filename;
        author = auth;
        createdDate = LocalDateTime.now().toString();
    }

    // toString method for printing out detail about the object
    public String toString() {
        return String.format(
            "Program: %s, Desc: %s, Filename: %s, Author: %s",
            programName, description, fileName, author.toString()
        );
    }

    // getter for program name
    public String getProgramName() {
        return programName;
    }

    // getter for description
    public String getDescription() {
        return description;
    }

    // getter for created date
    public String getCreatedDate() {
        return createdDate;
    }

    // getter for file name
    public String getFileName() {
        return fileName;
    }

    // getter for author
    public Student getAuthor() {
        return author;
    }
}
