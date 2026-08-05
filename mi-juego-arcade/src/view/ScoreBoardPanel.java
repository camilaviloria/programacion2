package view;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import java.util.List;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.SwingConstants;
import javax.swing.table.DefaultTableModel;
import model.PlayerScore;
import model.ScoreManager;

public class ScoreBoardPanel extends JPanel {
    private final JTable scoreTable;
    private final DefaultTableModel tableModel;

    public ScoreBoardPanel() {
        setLayout(new BorderLayout());
        setPreferredSize(new Dimension(220, 400));

        JLabel titleLabel = new JLabel("Tabla de Posiciones", SwingConstants.CENTER);
        titleLabel.setFont(new Font("Arial", Font.BOLD, 14));
        add(titleLabel, BorderLayout.NORTH);

        String[] columnNames = {"Jugador", "Puntos"};
        tableModel = new DefaultTableModel(columnNames, 0) {
            @Override
            public boolean isCellEditable(int row, int column) {
                return false; 
            }
        };

        scoreTable = new JTable(tableModel);
        scoreTable.setFillsViewportHeight(true);

        JScrollPane scrollPane = new JScrollPane(scoreTable);
        add(scrollPane, BorderLayout.CENTER);

        refreshScores();
    }

    public void refreshScores() {
        tableModel.setRowCount(0); 
        List<PlayerScore> scores = ScoreManager.loadScores();

        for (PlayerScore ps : scores) {
            tableModel.addRow(new Object[]{ps.getName(), ps.getScore()});
        }
    }
}