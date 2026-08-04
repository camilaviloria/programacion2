package model;
import java.awt.Point;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class GameModel {
    public enum Direction {
        UP, DOWN, LEFT, RIGHT
    }

    private final int gridWidth;
    private final int gridHeight;

    private List<Point> snake;
    private Point food;
    private Direction currentDirection;
    private boolean gameOver;
    private int score;

    private final Random random;

    public GameModel(int gridWidth, int gridHeight) {
        this.gridWidth = gridWidth;
        this.gridHeight = gridHeight;
        this.random = new Random();
        resetGame();
    }

    public void resetGame() {
        snake = new ArrayList<>();
        int startX = gridWidth / 2;
        int startY = gridHeight / 2;
        snake.add(new Point(startX, startY));
        snake.add(new Point(startX - 1, startY));
        snake.add(new Point(startX - 2, startY));

        currentDirection = Direction.RIGHT;
        gameOver = false;
        score = 0;

        spawnFood();
    }

    private void spawnFood() {
        Point newFood;
        do {
            int x = random.nextInt(gridWidth);
            int y = random.nextInt(gridHeight);
            newFood = new Point(x, y);
        } while (snake.contains(newFood));

        food = newFood;
    }

    public void update() {
        if (gameOver) return;

        Point head = snake.get(0);
        Point newHead = switch (currentDirection) {
            case UP -> new Point(head.x, head.y - 1);
            case DOWN -> new Point(head.x, head.y + 1);
            case LEFT -> new Point(head.x - 1, head.y);
            case RIGHT -> new Point(head.x + 1, head.y);
        };

        if (newHead.x < 0 || newHead.x >= gridWidth || newHead.y < 0 || newHead.y >= gridHeight) {
            gameOver = true;
            return;
        }

        if (snake.contains(newHead)) {
            gameOver = true;
            return;
        }

        snake.add(0, newHead);

        if (newHead.equals(food)) {
            score += 10;
            spawnFood(); // Crece la serpiente (no borramos la cola)
        } else {
            snake.remove(snake.size() - 1); // Quitar el último segmento para mantener el tamaño
        }
    }

    public void setDirection(Direction newDirection) {
        if ((currentDirection == Direction.UP && newDirection != Direction.DOWN) ||
            (currentDirection == Direction.DOWN && newDirection != Direction.UP) ||
            (currentDirection == Direction.LEFT && newDirection != Direction.RIGHT) ||
            (currentDirection == Direction.RIGHT && newDirection != Direction.LEFT)) {
            this.currentDirection = newDirection;
        }
    }


    public List<Point> getSnake() {
        return snake;
    }

    public Point getFood() {
        return food;
    }

    public boolean isGameOver() {
        return gameOver;
    }

    public int getScore() {
        return score;
    }

    public int getGridWidth() {
        return gridWidth;
    }

    public int getGridHeight() {
        return gridHeight;
    }
}