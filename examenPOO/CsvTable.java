package examenPOO;
import java.util.List;

public interface CsvTable {
    void addRow(List<String> row);
    void removeRow(int index);
    void addColumn(List<String> columnData);
    void removeColumn(int index);
    List<List<String>> getData();
}