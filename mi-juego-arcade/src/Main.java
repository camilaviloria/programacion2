import controller.GameController;
import javax.swing.SwingUtilities;
import model.GameModel;
import view.GameWindow;

public class Main {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            GameModel model = new GameModel(20, 20);
            
            GameWindow window = new GameWindow(model);
            
            GameController controller = new GameController(model, window);

            window.setVisible(true);
            controller.startGame();
        });
    }
}