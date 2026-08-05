import controller.GameController;
import javax.swing.SwingUtilities;
import model.GameModel;
import view.GameWindow;

public class Main {
    public static void main(String[] args) {
        // Ejecutar la interfaz gráfica en el Event Dispatch Thread (EDT) de Swing
        SwingUtilities.invokeLater(() -> {
            // Crear el modelo del juego (tablero de 20x20 casillas)
            GameModel model = new GameModel(20, 20);
            
            // Crear la ventana principal enviándole el modelo
            GameWindow window = new GameWindow(model);
            
            // Instanciar el controlador para vincular el modelo y la vista
            GameController controller = new GameController(model, window);

            // Hacer visible la ventana e iniciar el bucle del juego
            window.setVisible(true);
            controller.startGame();
        });
    }
}