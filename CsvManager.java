import java.io.IOException;

public class CsvManager {
    private CsvTable table;

    public void loadFromFile(String filePath, CsvReader reader) throws IOException {
        this.table = reader.read(filePath);
    }

    public void executeModifier(CsvModifier modifier) {
        if (this.table != null) {
            modifier.apply(this.table);
        }
    }

    public void display(CsvPrinter printer) {
        if (this.table != null) {
            printer.print(this.table);
        }
    }

    public CsvTable getTable() {
        return table;
    }
}