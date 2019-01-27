package equations_solver;
import java.awt.EventQueue;
import javax.swing.JFrame;
import javax.swing.JComboBox;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;

import javax.swing.JButton;
import javax.swing.JScrollPane;
import javax.swing.JOptionPane;
import javax.swing.JSpinner;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
import java.awt.Button;
import java.awt.TextField;
import java.awt.Label;
import java.awt.Font;
import javax.swing.SpinnerNumberModel;

/**
 * GUI of application.
 */
public class GUI {
    public JFrame frame;
    private JSpinner equation_count;
    private JTable table;

    private DefaultTableModel tableModel;
    private JScrollPane scrollPane;
    private JComboBox comboBox;
    private int count_equ = 0;
    private boolean list_editable = true;


    /**
     * Launch the application.
     */

	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					GUI window = new GUI();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

    /**
     * Create the application.
     */
    public GUI() {

        initialize();
    }

    /**
     * Initialize the contents of the frame.
     */
    private void initialize() {
        int ROW_HEIGHT = 20;
        String[] TABLE_COLUMNS = {"Equations"};

        tableModel = new DefaultTableModel(TABLE_COLUMNS,0) {

            @Override
            public boolean isCellEditable(int row, int column) {
                return list_editable;
            }
        };


        frame = new JFrame("Linear Equation Solver");
        frame.setBounds(100, 100, 570, 384);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        JButton btnNewButton = new JButton("Solve!");
        btnNewButton.setBounds(357, 157, 89, 23);
        frame.getContentPane().add(btnNewButton);

        btnNewButton.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {

                Vector<Vector> datas = tableModel.getDataVector();
                String[] equations = new String[datas.size()];


                for (int i= 0; i< datas.size(); ++i) {
                    //System.out.println(datas.elementAt(i).toString().replace("[", "").replace("]", ""));

                    equations[i] = datas.elementAt(i).toString().replace("[", "").replace("]", "");
                }
                //System.out.println("string array");


                LinearEquationSolver solver;
                MethodsOfSolvingLinearEquations solving_methods;

                String selected_method = (String) comboBox.getSelectedItem();
                try {
                    if (selected_method == "Gaussian Elimination")
                        solving_methods = new GE(equations);

                    else
                        solving_methods = new MatrixInverse(equations);



                    solver = new LinearEquationSolver(solving_methods);
                    Double[] solution;
                    try {
                        String solutionString = "";
                        solution = solver.solv();
                        for(int i=0; i<solution.length; ++i) {
                            //System.out.println("X"+i+"= " + solution[i]);
                            solutionString+= "X"+i+"= " + solution[i] + "  ";
                        }
                        JOptionPane.showMessageDialog(null, solutionString, "Solution",JOptionPane.INFORMATION_MESSAGE);
                    } catch (ArithmeticException e1) {
                        String message = "No unique solution!";
                        JOptionPane.showMessageDialog(null,message ,"Error",JOptionPane.ERROR_MESSAGE);


                    } catch (Exception e1) {
                        String message = "No solution!";
                        JOptionPane.showMessageDialog(null,message ,"Error",JOptionPane.ERROR_MESSAGE);

                    }
                    list_editable = false;

                }catch (Exception e2) {
                    String message = "You should release the equations list. Or you did not write equations.";
                    JOptionPane.showMessageDialog(null,message ,"Error",JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        equation_count = new JSpinner();
        equation_count.setModel(new SpinnerNumberModel(new Integer(0), new Integer(0), null, new Integer(1)));
        equation_count.setBounds(131, 11, 70, 20);
        frame.getContentPane().add(equation_count);


        Button Get_equations = new Button("Get Equations!");
        Get_equations.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent arg0) {
                list_editable = true;

                tableModel = new DefaultTableModel(TABLE_COLUMNS, 0) {

                    @Override
                    public boolean isCellEditable(int row, int column) {
                        return list_editable;
                    }
                };

                count_equ = (int) equation_count.getValue();
                //System.out.println(count_equ);
                TextField[] textField = new TextField[count_equ];


                for (int i=0; i<count_equ; ++i)

                    tableModel.addRow(new String[]{""});

                table = new JTable(tableModel);

                scrollPane.setViewportView(table);

                tableModel.getRowCount();


            }
        });


        String[] choices = {"Gaussian Elimination","Matrix Inversion"};

        comboBox = new JComboBox(choices);
        comboBox.setBounds(391, 62, 148, 20);
        frame.getContentPane().add(comboBox);


        Get_equations.setActionCommand("Get_equations");
        Get_equations.setBounds(219, 9, 96, 22);
        frame.getContentPane().add(Get_equations);

        Label label = new Label("Number of Equations:");
        label.setFont(new Font("Dialog", Font.BOLD, 12));
        label.setEnabled(false);
        label.setBounds(0, 11, 125, 23);
        frame.getContentPane().add(label);

        scrollPane = new JScrollPane();
        scrollPane.setBounds(29, 62, 232, 213);
        frame.getContentPane().add(scrollPane);


        Label label_1 = new Label("Select a method:");
        label_1.setFont(new Font("Dialog", Font.BOLD, 12));
        label_1.setEnabled(false);
        label_1.setBounds(276, 59, 109, 23);
        frame.getContentPane().add(label_1);

    }



}
