// Assignment #: 6
// Arizona State University - CSE205
//         Name: Tyler Fichiera
//    StudentID: 1218959911
//      Lecture: T/Th 4:30
// Description: GeneratePane creats a pane where a user can enter
//              department information and create a list of available departments.

import java.util.ArrayList;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.paint.Color;

/**
 * GeneratePane builds a pane where a user can enter a department
 * information and create a list of available departments.
 */
public class GeneratePane extends HBox {
    // declare private instance variables
    ArrayList<Department> departList; // aggregation
    private SelectPane selectPane;

    // text fields
    private TextField titleField = new TextField();
    private TextField facultyField = new TextField();
    private TextField universityField = new TextField();

    // labels
    private Label alertLabel = new Label("");

    // buttons
    private Button addButton = new Button("Add a Department");

    // text areas
    private TextArea textArea = new TextArea("No Departments");

    /**
     * GeneratePane constructor
     *
     * @param list   the list of departments
     * @param sePane the SelectPane instance
     */
    public GeneratePane(ArrayList<Department> list, SelectPane sePane) {
        this.departList = list;
        this.selectPane = sePane;

        // create left sub pane
        GridPane leftSubPane = new GridPane();
        leftSubPane.setPadding(new Insets(10, 10, 10, 10));

        this.alertLabel.setTextFill(Color.RED);
        leftSubPane.add(alertLabel, 0, 0);

        // add all the fields and labels
        leftSubPane.add(new Label("Department Title"), 0, 1);
        leftSubPane.add(this.titleField, 1, 1);

        leftSubPane.add(new Label("Number of Faculty"), 0, 2);
        leftSubPane.add(this.facultyField, 1, 2);

        leftSubPane.add(new Label("Name of University"), 0, 3);
        leftSubPane.add(this.universityField, 1, 3);

        // add button and tie it to a handler
        this.addButton.setOnAction(new ButtonHandler());
        leftSubPane.add(this.addButton, 1, 4);

        GridPane rightSubPane = new GridPane();
        rightSubPane.setPadding(new Insets(10, 10, 10, 10));

        rightSubPane.add(this.textArea, 0, 0);

        // create main plane for the two different columns
        GridPane mainPane = new GridPane();
        mainPane.add(leftSubPane, 0, 0);
        mainPane.add(rightSubPane, 1, 0);

        ColumnConstraints halfWidth = new ColumnConstraints();
		halfWidth.setPercentWidth(50);
        mainPane.getColumnConstraints().addAll(halfWidth, halfWidth);

        // add main plane to the root
        this.getChildren().add(mainPane);
    }

    /**
     * ButtonHandler ButtonHandler listens to see if the button "Add a department" is pushed
     * or not, When the event occurs, it get a department's Title, number of faculties,
     * and its university information from the relevant text fields, then create a
     * new department and adds it to the departList. Meanwhile it will display the department's
     * information inside the text area. using the toString method of the Department
     * class. It also does error checking in case any of the text fields are empty,
     * or a non-numeric value was entered for number of faculty
     */
    private class ButtonHandler implements EventHandler<ActionEvent> {
        /** handle Override the abstract method handle() */
        @Override
        public void handle(ActionEvent event) {
            // if fields are empty display message
            if (
                titleField.getText().isEmpty() ||
                facultyField.getText().isEmpty() ||
                universityField.getText().isEmpty()
            ) {
                alertLabel.setText("Please fillout all fields");
                return;
            }

            // If all fields are filled, try to add the department
            try {
                // get text from fields
                String title = titleField.getText();
                int numberOfFaculty = Integer.parseInt(facultyField.getText());
                String university = universityField.getText();

                Department newDepart = new Department(title, numberOfFaculty, university);

                // check for dups
                for (Department depart : departList) {
                    if (
                        depart.getDeptName().toLowerCase().equals(title.toLowerCase()) &&
                        depart.getUniversity().toLowerCase().equals(university.toLowerCase())
                    ) {
                        alertLabel.setText("Department not added - already exist");
                        return;
                    }
                }

                // update the list
                selectPane.updateDepartList(newDepart);
                
                // build text area value
                String textAreaValue = "";
                for (Department depart : departList)
                    textAreaValue += depart;
                textArea.setText(textAreaValue);

                // set label for department added
                alertLabel.setText("Department added");
            } catch (NumberFormatException e) {
                // catch non-int error
                alertLabel.setText("Please enter an integer for a number of faculty");
            } catch (Exception e) {
                // catch all other errors
                alertLabel.setText("Department not added - unknown error");
            }
        }
    }
}


