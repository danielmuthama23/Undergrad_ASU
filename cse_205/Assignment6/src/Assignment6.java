// Assignment #: 6
// Arizona State University - CSE205
//         Name: Tyler Fichiera
//    StudentID: 1218959911
//      Lecture: T/Th 4:30
//  Description: The Assignment6 class creates a Tabbed Pane with
//               two tabs, one for Department Creation and one for
//               Department Selection.

import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.control.Tab;
import javafx.scene.control.TabPane;
import javafx.scene.layout.StackPane;
import java.util.ArrayList;

public class Assignment6 extends Application {
    // init private instance vars
    private TabPane tabPane;
    private GeneratePane createPane;
    private SelectPane selectPane;
    private ArrayList<Department> departList;

    // start method for Application
    public void start(Stage stage) {
        // create root pane
        StackPane root = new StackPane();

        // departList to be used in both generatePane & selectPane
        departList = new ArrayList<Department>();

        // create two tab pane
        selectPane = new SelectPane(departList);
        createPane = new GeneratePane(departList, selectPane);

        tabPane = new TabPane();

        Tab tab1 = new Tab();
        tab1.setText("Add Department");
        tab1.setContent(createPane);

        Tab tab2 = new Tab();
        tab2.setText("Select Department");
        tab2.setContent(selectPane);

        // add tabs to pane
        tabPane.getSelectionModel().select(0);
        tabPane.getTabs().addAll(tab1, tab2);

        // add tabs to root
        root.getChildren().add(tabPane);

        // deploy the scene
        Scene scene = new Scene(root, 900, 400);
        stage.setTitle("Department Selection App");
        stage.setScene(scene);
        stage.show();
    }

    // main method that launches the application
    public static void main(String[] args) {
        launch(args);
    }
}
