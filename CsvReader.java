import java.io.IOException;

public interface CsvReader {
    CsvTable read(String filePath) throws IOException;
}