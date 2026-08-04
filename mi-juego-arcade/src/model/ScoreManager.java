package model;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class ScoreManager {
    private static final String FILE_NAME = "scores.dat";
    private static final int MAX_SCORES = 10; 

    @SuppressWarnings("unchecked")
    public static List<PlayerScore> loadScores() {
        File file = new File(FILE_NAME);
        if (!file.exists()) {
            return new ArrayList<>();
        }

        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(file))) {
            return (List<PlayerScore>) ois.readObject();
        } catch (IOException | ClassNotFoundException e) {
            System.err.println("Error al leer el archivo de puntajes: " + e.getMessage());
            return new ArrayList<>();
        }
    }

    public static void saveScore(String name, int score) {
        List<PlayerScore> scores = loadScores();
        scores.add(new PlayerScore(name, score));

        scores.sort(Comparator.comparingInt(PlayerScore::getScore).reversed());

        if (scores.size() > MAX_SCORES) {
            scores = new ArrayList<>(scores.subList(0, MAX_SCORES));
        }

        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(FILE_NAME))) {
            oos.writeObject(scores);
        } catch (IOException e) {
            System.err.println("Error al guardar el archivo de puntajes: " + e.getMessage());
        }
    }
}
