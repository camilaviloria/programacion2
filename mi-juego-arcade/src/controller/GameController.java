package controller;

import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import javax.swing.JOptionPane;
import javax.swing.Timer;
import model.GameModel;
import model.ScoreManager;
import view.GamePanel;
import view.GameWindow;

public class GameController {
    private final GameModel model;
    private final GameWindow window;
    private final GamePanel panel;
    private final Timer gameLoop;
    private static final int DELAY = 120; // Velocidad del juego en milisegundos

    public GameController(GameModel model, GameWindow window) {
        this.model = model;
        this.window = window;
        this.panel = window.getGamePanel();

        // Registrar escuchador de teclado en la ventana o panel
        this.window.addKeyListener(new DirectionKeyListener());
        this.window.setFocusable(true);

        // Bucle principal del juego (Timer que actualiza el modelo y repinta la vista)
        this.gameLoop = new Timer(DELAY, e -> {
            if (!model.isGameOver()) {
                model.update();
                panel.repaint();
            } else {
                gameLoop.stop();
                handleGameOver();
            }
        });
    }

    public void startGame() {
        model.resetGame();
        panel.repaint();
        gameLoop.start();
    }

    private void handleGameOver() {
        int finalScore = model.getScore();
        String name = JOptionPane.showInputDialog(
            window,
            "¡Juego Terminado!\nTu puntuación fue: " + finalScore + "\nIngresa tu nombre:",
            "Game Over",
            JOptionPane.PLAIN_MESSAGE
        );

        if (name != null && !name.trim().isEmpty()) {
            ScoreManager.saveScore(name.trim(), finalScore);
            window.updateScoreBoard();
        }
    }

    // Clase interna para capturar el teclado
    private class DirectionKeyListener extends KeyAdapter {
        @Override
        public void keyPressed(KeyEvent e) {
            int key = e.getKeyCode();

            switch (key) {
                case KeyEvent.VK_UP -> model.setDirection(GameModel.Direction.UP);
                case KeyEvent.VK_DOWN -> model.setDirection(GameModel.Direction.DOWN);
                case KeyEvent.VK_LEFT -> model.setDirection(GameModel.Direction.LEFT);
                case KeyEvent.VK_RIGHT -> model.setDirection(GameModel.Direction.RIGHT);
                case KeyEvent.VK_R -> {
                    if (model.isGameOver()) {
                        startGame();
                    }
                }
            }
        }
    }
}