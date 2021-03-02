// Assignment #: 6
// Arizona State University - CSE205
//         Name: Tyler Fichiera
//    StudentID: 1218959911
//      Lecture: T/Th 4:30
// Description: SelectPane displays a list of available department
//              from which a user can select and compute total number of faculties in multiple departments.

import java.util.ArrayList;
import javafx.event.ActionEvent; 
import javafx.event.EventHandler;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Label;
import javafx.scene.control.ScrollPane;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;

/**
* SelectPane displays a list of available departments from which a user
* can select and compute total number of faculties for selected departments.
*/
public class SelectPane extends BorderPane {
    // init private instance variables
    private ArrayList<Department> departList;

    private int totalFaculty = 0;

    private ScrollPane scrollPane = new ScrollPane();

    private VBox checkboxContainer = new VBox(new Label("No Departments"));

    // default constructor for this pane
    public SelectPane(ArrayList<Department> list) {
        this.departList = list;

        this.scrollPane.setContent(this.checkboxContainer);

        // fill in BorderPane
        this.setTop(new Label("Select Department(s)"));
        this.setCenter(this.scrollPane);
        this.setBottom(new Label("The total number of faculties selected: 0"));
    }

    // This method uses the newly added parameter Department object
    // to create a CheckBox and add it to a pane created in the constructor
    // Such check box needs to be linked to its handler class
    public void updateDepartList(Department newdep) {
        this.departList.add(newdep);

        CheckBox checkbox = new CheckBox(newdep.toString());
        checkbox.setOnAction(new SelectionHandler(newdep.getNumberOfMembers()));

        this.checkboxContainer.getChildren().add(checkbox);
    }

    // setter method to be able to access the `this`
    private void setBottomLabel(int numFac) {
        this.setBottom(new Label("The total number of faculties selected: " + numFac));
    }

    /**
     * SelectionHandler This class handles a checkbox toggle event. When the
     * checkbox is toggled, this number will be added/subtracted from the total
     * number of selected faculties.
     */
    private class SelectionHandler implements EventHandler<ActionEvent> {
        // init private instance vars
        private int faculties;

        // default constructor
        public SelectionHandler(int members) {
            this.faculties = members;
        }

        // handler for selections
        @Override
        public void handle(ActionEvent event) {
            // cast to CheckBox and check if it is selected
            // then add or subtract the faculty #
            if (((CheckBox)event.getSource()).isSelected()) {
                totalFaculty += this.faculties;
            } else {
                totalFaculty -= this.faculties;
            }
            setBottomLabel(totalFaculty);
        }
    }
}
