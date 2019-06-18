package sample;

import java.net.URL;
import java.util.HashMap;
import java.util.ResourceBundle;
import javafx.fxml.FXML;
import javafx.scene.chart.*;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import javafx.scene.text.Text;

public class Controller {

    @FXML // ResourceBundle that was given to the FXMLLoader
    private ResourceBundle resources;

    @FXML // URL location of the FXML file that was given to the FXMLLoader
    private URL location;

    @FXML // fx:id="homePage"
    private Pane homePage; // Value injected by FXMLLoader

    @FXML // fx:id="menu"
    private Pane menu; // Value injected by FXMLLoader

    @FXML // fx:id="homeBttn"
    private ImageView homeBttn; // Value injected by FXMLLoader

    @FXML // fx:id="heartBttn"
    private ImageView heartBttn; // Value injected by FXMLLoader

    @FXML // fx:id="emergencyBttn"
    private ImageView emergencyBttn; // Value injected by FXMLLoader

    @FXML // fx:id="aboutBttn"
    private ImageView aboutBttn; // Value injected by FXMLLoader

    @FXML // fx:id="heartPage"
    private Pane heartPage; // Value injected by FXMLLoader

    @FXML // fx:id="heartChart"
    private LineChart<?, ?> heartChart; // Value injected by FXMLLoader

    @FXML // fx:id="time"
    private CategoryAxis time; // Value injected by FXMLLoader

    @FXML // fx:id="bpm"
    private NumberAxis bpm; // Value injected by FXMLLoader

    @FXML // fx:id="emergencyPage"
    private Pane emergencyPage; // Value injected by FXMLLoader

    @FXML // fx:id="callHelpBttn"
    private ImageView callHelpBttn; // Value injected by FXMLLoader

    @FXML // fx:id="callHelpMssg"
    private Text callHelpMssg; // Value injected by FXMLLoader

    @FXML // fx:id="aboutPage"
    private Pane aboutPage; // Value injected by FXMLLoader

    @FXML
    void callHelp(MouseEvent event) {
        System.err.println("Emergency called");

        callHelpMssg.setVisible(true);
    }

    @FXML
    void openAboutPage(MouseEvent event) {
        menu.setVisible(true);
        homePage.setVisible(false);
        heartPage.setVisible(false);
        emergencyPage.setVisible(false);
        aboutPage.setVisible(true);


    }

    @FXML
    void openEmergencyPage(MouseEvent event) {
        menu.setVisible(true);
        homePage.setVisible(false);
        heartPage.setVisible(false);
        emergencyPage.setVisible(true);
        aboutPage.setVisible(false);

        callHelpMssg.setVisible(false);


    }

    @FXML
    void openHeartPage(MouseEvent event) {
        heartChart.getData().clear();
        heartChart.setLegendVisible(false);

        menu.setVisible(true);
        homePage.setVisible(false);
        heartPage.setVisible(true);
        emergencyPage.setVisible(false);
        aboutPage.setVisible(false);

        JsonHttpParser jsonHttpParser = new JsonHttpParser();



        heartChart.getData().
                addAll(
                addHeartRateData(
                jsonHttpParser.
                parseHeartRate("/watchdata/data")));
    }

    @FXML
    void openHomePage(MouseEvent event) {
        menu.setVisible(true);
        homePage.setVisible(true);
        heartPage.setVisible(false);
        emergencyPage.setVisible(false);
        aboutPage.setVisible(false);

    }

    @FXML // This method is called by the FXMLLoader when initialization is complete
    void initialize() {
        assert homePage != null : "fx:id=\"homePage\" was not injected: check your FXML file 'HeartBeatUser.fxml'.";
        assert menu != null : "fx:id=\"menu\" was not injected: check your FXML file 'HeartBeatUser.fxml'.";
        assert homeBttn != null : "fx:id=\"homeBttn\" was not injected: check your FXML file 'HeartBeatUser.fxml'.";
        assert heartBttn != null : "fx:id=\"heartBttn\" was not injected: check your FXML file 'HeartBeatUser.fxml'.";
        assert emergencyBttn != null : "fx:id=\"emergencyBttn\" was not injected: check your FXML file 'HeartBeatUser.fxml'.";
        assert aboutBttn != null : "fx:id=\"aboutBttn\" was not injected: check your FXML file 'HeartBeatUser.fxml'.";
        assert heartPage != null : "fx:id=\"heartPage\" was not injected: check your FXML file 'HeartBeatUser.fxml'.";
        assert heartChart != null : "fx:id=\"heartChart\" was not injected: check your FXML file 'HeartBeatUser.fxml'.";
        assert time != null : "fx:id=\"time\" was not injected: check your FXML file 'HeartBeatUser.fxml'.";
        assert bpm != null : "fx:id=\"bpm\" was not injected: check your FXML file 'HeartBeatUser.fxml'.";
        assert emergencyPage != null : "fx:id=\"emergencyPage\" was not injected: check your FXML file 'HeartBeatUser.fxml'.";
        assert callHelpBttn != null : "fx:id=\"callHelpBttn\" was not injected: check your FXML file 'HeartBeatUser.fxml'.";
        assert callHelpMssg != null : "fx:id=\"callHelpMssg\" was not injected: check your FXML file 'HeartBeatUser.fxml'.";
        assert aboutPage != null : "fx:id=\"aboutPage\" was not injected: check your FXML file 'HeartBeatUser.fxml'.";

    }

    XYChart.Series addHeartRateData(HashMap<String,Integer> data){
        XYChart.Series heartrate = new XYChart.Series();

        for (String timestamp: data.keySet()) {
            heartrate.getData().add(new XYChart.Data(timestamp,data.get(timestamp)));
        }

        return heartrate;
    }
}
