import java.awt.Point;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class GameModel {
    // Definición de direcciones
    public enum Direction {
        UP, DOWN, LEFT, RIGHT
    }

    // Configuración del tablero (unidades de cuadrícula)
    private final int gridWidth;
    private final int gridHeight;

    // Estado del juego
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

    // Inicializa o reinicia el estado del juego
    public void resetGame() {
        snake = new ArrayList<>();
        // Iniciar serpiente con tamaño 3 en el centro
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

    // Genera comida en una posición aleatoria no ocupada por la serpiente
    private void spawnFood() {
        Point newFood;
        do {
            int x = random.nextInt(gridWidth);
            int y = random.nextInt(gridHeight);
            newFood = new Point(x, y);
        } while (snake.contains(newFood));

        food = newFood;
    }

    // Avanza el juego un paso/tick
    public void update() {
        if (gameOver) return;

        // Calcular la nueva posición de la cabeza
        Point head = snake.get(0);
        Point newHead = switch (currentDirection) {
            case UP -> new Point(head.x, head.y - 1);
            case DOWN -> new Point(head.x, head.y + 1);
            case LEFT -> new Point(head.x - 1, head.y);
            case RIGHT -> new Point(head.x + 1, head.y);
        };

        // 1. Verificar colisión con bordes del mapa
        if (newHead.x < 0 || newHead.x >= gridWidth || newHead.y < 0 || newHead.y >= gridHeight) {
            gameOver = true;
            return;
        }

        // 2. Verificar colisión con el propio cuerpo
        if (snake.contains(newHead)) {
            gameOver = true;
            return;
        }

        // Mover la serpiente añadiendo la nueva cabeza
        snake.add(0, newHead);

        // 3. Verificar si comió
        if (newHead.equals(food)) {
            score += 10;
            spawnFood(); // Crece la serpiente (no borramos la cola)
        } else {
            snake.remove(snake.size() - 1); // Quitar el último segmento para mantener el tamaño
        }
    }

    // Cambia la dirección evitando giros de 180°
    public void setDirection(Direction newDirection) {
        if ((currentDirection == Direction.UP && newDirection != Direction.DOWN) ||
            (currentDirection == Direction.DOWN && newDirection != Direction.UP) ||
            (currentDirection == Direction.LEFT && newDirection != Direction.RIGHT) ||
            (currentDirection == Direction.RIGHT && newDirection != Direction.LEFT)) {
            this.currentDirection = newDirection;
        }
    }

    // --- Getters para la Vista y el Controlador ---

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