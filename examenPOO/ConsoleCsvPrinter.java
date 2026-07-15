package examenPOO;
import java.util.List;

public class ConsoleCsvPrinter implements CsvPrinter {
    @Override
    public void print(CsvTable table) {
        for (List<String> row : table.getData()) {
            System.out.println(String.join(" | ", row));
        }
    }
}