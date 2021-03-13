// Assignment #7: Arizona State University CSE205
//          Name: Tyler Fichiera
//     StudentID: 1218959911
//       Lecture: T/Th 4:30
//   Description: CirclePane class creates a pane where we can use
//                mouse key to drag on canvass and there will be some color following
//                the mouse. We can also use combo boxes to change its colors and stroke widths

import javafx.geometry.Insets;
import javafx.event.ActionEvent; 
import javafx.event.EventHandler;
import javafx.scene.input.MouseEvent;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.shape.Circle;
import javafx.scene.layout.*;
import javafx.scene.paint.Color;

public class CirclePane extends BorderPane {
    /* init private instance variables */
    // constants
    private final int NUM_ROW = 6, NUM_COL = 6, RADIUS = 40;

    // canvas for circles
    private GridPane canvas = new GridPane();

    // combo boxes
    private ComboBox<String> primaryColorCombo = new ComboBox<String>();
    private ComboBox<String> bgColorCombo = new ComboBox<String>();
    private ComboBox<Integer> widthCombo = new ComboBox<Integer>();

    // shapes
    private Circle[][] circleArray = new Circle[this.NUM_ROW][this.NUM_COL];

    /* Constructor for CirclePane */
    public CirclePane() {
        // init combo box items
        this.primaryColorCombo.getItems().addAll("black", "red", "green", "blue");
        this.primaryColorCombo.setValue("black");

        this.bgColorCombo.getItems().addAll("white", "beige", "alice-blue", "gold");
        this.bgColorCombo.setValue("white");
        // bind handler with background color combo box
        this.bgColorCombo.setOnAction(new BackgroundColorHandler());
        
        this.widthCombo.getItems().addAll(1, 3, 5, 7);
        this.widthCombo.setValue(1);
        // bind handler with width combo box
        this.widthCombo.setOnAction(new WidthHandler());

        // configure main center canvas width and height
        this.canvas.setPrefWidth(2 * this.RADIUS * this.NUM_COL);
        this.canvas.setPrefHeight(2 * this.RADIUS * this.NUM_ROW);

        // iterate through all rows and cols to init circles
        for (int r = 0; r < this.NUM_ROW; r++) {
            for (int c = 0; c < this.NUM_COL; c++) {
                // create circle
                Circle circle = new Circle(
                    this.RADIUS + (2 * this.RADIUS * r),
                    this.RADIUS + (2 * this.RADIUS * c),
                    this.RADIUS
                );

                // style the circle
                circle.setFill(Color.WHITE);
                circle.setStroke(Color.BLACK);

                // create handler and bind to listeners
                MouseHandler handler = new MouseHandler(r, c);
                circle.setOnMouseEntered(handler);
                circle.setOnMouseExited(handler);

                // add circle to the grid
                this.canvas.add(circle, r, c);

                // add circle to the array
                this.circleArray[r][c] = circle;
            }
        }
        
        // add canvas to BorderPane
        this.setCenter(this.canvas);

        // create left pane for three combo boxes
        VBox leftPane = new VBox();

        // style left pane
        leftPane.setSpacing(20);
        leftPane.setPadding(new Insets(10, 10, 10, 10));
        leftPane.setStyle("-fx-border-color: black");

        // add combo boxes and labels to left pane
        leftPane.getChildren().addAll(
            new Label("Primary Color"),
            this.primaryColorCombo,
            new Label("Background Color"),
            this.bgColorCombo,
            new Label("Stroke Width"),
            this.widthCombo
        );

        // add left pane to BorderPane
        this.setLeft(leftPane);
    }

    /* getter to convert string value to Color */
    private Color getColorFromValue(String value) {
        switch (value) {
            case "black":
                return Color.BLACK;
            case "red":
                return Color.RED;
            case "green":
                return Color.GREEN;
            case "blue":
                return Color.BLUE;
            case "white":
                return Color.WHITE;
            case "beige":
                return Color.BEIGE;
            case "alice-blue":
                return Color.ALICEBLUE;
            case "gold":
                return Color.GOLD;
            default:
                return null;
        }
    }

    /* getter to convert primary string value to secondary Color */
    private Color getSecondaryColor(String primaryColor) {
        switch (primaryColor) {
            case "black":
                return Color.GRAY;
            case "red":
                return Color.PINK;
            case "green":
                return Color.LIGHTGREEN;
            case "blue":
                return Color.POWDERBLUE;
            default:
                return null;
        }
    }

    // MouseHandler to handle circle hovering
    private class MouseHandler implements EventHandler<MouseEvent> {
        // init private instance variables to hold row and col
        private int circleRow, circleCol;

        /* Constructor for MouseHandler */
        public MouseHandler(int row, int col) {
            this.circleRow = row;
            this.circleCol = col;
        }

        /* handler for MouseHandler */
        public void handle(MouseEvent event) {
            // convert strings to Color objects
            Color primaryColor = getColorFromValue(primaryColorCombo.getValue());
            Color secondaryColor = getSecondaryColor(primaryColorCombo.getValue());
            Color bgColor = getColorFromValue(bgColorCombo.getValue());

            // set the color of the primary (hovered) circle
            circleArray[this.circleRow][this.circleCol].setFill(
                event.getEventType() == MouseEvent.MOUSE_ENTERED ? primaryColor : bgColor
            );

            // check circle above the hovered circle then fill
            if (this.circleCol > 0) {
                circleArray[this.circleRow][this.circleCol - 1].setFill(
                    event.getEventType() == MouseEvent.MOUSE_ENTERED ? secondaryColor : bgColor
                );
            }

            // check circle to the right of the hovered circle then fill
            if (this.circleRow < 5) {
                circleArray[this.circleRow + 1][this.circleCol].setFill(
                    event.getEventType() == MouseEvent.MOUSE_ENTERED ? secondaryColor : bgColor
                );
            }

            // check circle below the hovered circle then fill
            if (this.circleCol < 5) {
                circleArray[this.circleRow][this.circleCol + 1].setFill(
                    event.getEventType() == MouseEvent.MOUSE_ENTERED ? secondaryColor : bgColor
                );
            }
            
            // check circle to the left of the hovered circle then fill
            if (this.circleRow > 0) {
                circleArray[this.circleRow - 1][this.circleCol].setFill(
                    event.getEventType() == MouseEvent.MOUSE_ENTERED ? secondaryColor : bgColor
                );
            }
        }
    }

    // UNUSED!: handler for primary color combo box
    private class PrimaryColorHandler implements EventHandler<ActionEvent> {
        public void handle(ActionEvent event) {
            /*
                I found that since your cursor will never hover
                over circles while you're selecting a new primary
                color, there is no need to handle any events
                for the combo box
            */
		}
    }

    // handler for background color combo box
    private class BackgroundColorHandler implements EventHandler<ActionEvent> {
        public void handle(ActionEvent event) {
            for (int r = 0; r < NUM_ROW; r++) {
                for (int c = 0; c < NUM_COL; c++) {
                    circleArray[r][c].setFill(
                        getColorFromValue(bgColorCombo.getValue())
                    );
                }
            }
		}
    }



    // handler for the width combo box
    private class WidthHandler implements EventHandler<ActionEvent> {
        public void handle(ActionEvent event) {
            for (int r = 0; r < NUM_ROW; r++) {
                for (int c = 0; c < NUM_COL; c++) {
                    circleArray[r][c].setStrokeWidth(widthCombo.getValue());
                }
            }
        }
    }
}