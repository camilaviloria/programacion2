package examenPOO;
import java.util.ArrayList;
import java.util.List;

public class DefaultCsvTable implements CsvTable {
    private List<List<String>> data;

    public DefaultCsvTable() {
        this.data = new ArrayList<>();
    }

    @Override
    public void addRow(List<String> row) {
        data.add(new ArrayList<>(row));
    }

    @Override
    public void removeRow(int index) {
        if (index >= 0 && index < data.size()) {
            data.remove(index);
        }
    }

    @Override
    public void addColumn(List<String> columnData) {
        for (int i = 0; i < data.size(); i++) {
            if (i < columnData.size()) {
                data.get(i).add(columnData.get(i));
            } else {
                data.get(i).add("");
            }
        }
    }

    @Override
    public void removeColumn(int index) {
        for (List<String> row : data) {
            if (index >= 0 && index < row.size()) {
                row.remove(index);
            }
        }
    }

    @Override
    public List<List<String>> getData() {
        return this.data;
    }
}