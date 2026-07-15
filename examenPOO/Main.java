package examenPOO;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        try {
            CsvManager manager = new CsvManager();
            
            manager.loadFromFile("prueba.txt", new StandardCsvReader(","));

            CsvModifier convertToUpper = new CsvModifier() {
                @Override
                public void apply(CsvTable table) {
                    for (List<String> row : table.getData()) {
                        for (int i = 0; i < row.size(); i++) {
                            row.set(i, row.get(i).toUpperCase());
                        }
                    }
                }
            };

            manager.executeModifier(convertToUpper);
            manager.display(new ConsoleCsvPrinter());

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}