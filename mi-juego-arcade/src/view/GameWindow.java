package view;

import java.awt.BorderLayout;
import javax.swing.JFrame;
import model.GameModel;

public class GameWindow extends JFrame {
    private final GamePanel gamePanel;
    private final ScoreBoardPanel scoreBoardPanel;

    public GameWindow(GameModel model) {
        setTitle("Snake Arcade");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);
        setLayout(new BorderLayout());

        gamePanel = new GamePanel(model);
        scoreBoardPanel = new ScoreBoardPanel();

        add(gamePanel, BorderLayout.CENTER);
        add(scoreBoardPanel, BorderLayout.EAST);

        pack();
        setLocationRelativeTo(null);
    }

    public GamePanel getGamePanel() {
        return gamePanel;
    }

    public void updateScoreBoard() {
        scoreBoardPanel.refreshScores();
    }
}