package view;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Point;
import javax.swing.JPanel;
import model.GameModel;

public class GamePanel extends JPanel {
    private final GameModel model;
    private final int tileSize = 20; 

    public GamePanel(GameModel model) {
        this.model = model;
        int width = model.getGridWidth() * tileSize;
        int height = model.getGridHeight() * tileSize;
        setPreferredSize(new Dimension(width, height));
        setBackground(Color.BLACK);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        if (model == null) return;

        Point food = model.getFood();
        if (food != null) {
            g.setColor(Color.RED);
            g.fillRect(food.x * tileSize, food.y * tileSize, tileSize, tileSize);
        }

        boolean isHead = true;
        for (Point p : model.getSnake()) {
            if (isHead) {
                g.setColor(new Color(46, 204, 113)); 
                isHead = false;
            } else {
                g.setColor(new Color(130, 224, 170)); 
            }
            g.fillRect(p.x * tileSize, p.y * tileSize, tileSize - 1, tileSize - 1);
        }

        if (model.isGameOver()) {
            g.setColor(Color.WHITE);
            g.drawString("¡GAME OVER! Presiona 'R' para reiniciar.", 50, getHeight() / 2);
        }
    }
}
