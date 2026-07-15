package examenPOO;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;

public class StandardCsvReader implements CsvReader {
    private final String separator;

    public StandardCsvReader(String separator) {
        this.separator = separator;
    }

    @Override
    public CsvTable read(String filePath) throws IOException {
        CsvTable table = new DefaultCsvTable();
        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] values = line.split(this.separator);
                table.addRow(Arrays.asList(values));
            }
        }
        return table;
    }
}