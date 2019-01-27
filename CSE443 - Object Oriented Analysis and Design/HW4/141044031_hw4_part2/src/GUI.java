import javax.naming.NoPermissionException;
import javax.swing.JFrame;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.MalformedURLException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.Arrays;
import java.util.Map;
import java.util.Set;
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


import java.rmi.Naming;

/**
 * GUI of application.
 */
public class GUI {
    private IGraph graph ;
    private IRemoteService remoteService;
    private Integer clientID;

    public JFrame frame;
    private JSpinner equation_count;
    private JTable table;

    private DefaultTableModel tableModel;
    private JScrollPane scrollPane;
    private int count_equ = 0;
    private boolean list_editable = true;

    private String st;


    /**
     * Create the application.
     * @param hostpath host to connect
     * @param clientID the id of client
     * @throws RemoteException
     */
    public GUI(String hostpath, Integer clientID) throws RemoteException {
        initialize();
        this.clientID = clientID;
        try {
            remoteService = (IRemoteService) Naming.lookup(hostpath);
            remoteService.login(this.clientID);
        }catch (NotBoundException e){
            System.err.println("NotBoundException");
        }catch (MalformedURLException e){
            System.err.println("MalformedURLException");
        }catch (RemoteException e){
            System.err.println("Client not connected to Server.");
            JOptionPane.showMessageDialog(null, e.getMessage(), "Server Error", JOptionPane.ERROR_MESSAGE);
            JOptionPane.showMessageDialog(null, "Please start server with binding 'rmi://localhost/RemoteService'", "Server Error", JOptionPane.ERROR_MESSAGE);

            throw e;
        }
    }

    /**
     * Initialize the contents of the frame.
     */
    private void initialize() {
        int ROW_HEIGHT = 20;
        String[] TABLE_COLUMNS = {"Graph Edges(Source,Destination,Weight)"};

        tableModel = new DefaultTableModel(TABLE_COLUMNS,0) {

            @Override
            public boolean isCellEditable(int row, int column) {
                return list_editable;
            }
        };


        frame = new JFrame("Graph Oriented Services");
        frame.setBounds(100, 100, 570, 384);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);


        //Create Graph Button

        JButton btnNewButton = new JButton("Create Graph!");
        btnNewButton.setBounds(300, 57, 139, 23);
        frame.getContentPane().add(btnNewButton);

        btnNewButton.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                graph = new Graph();


                Vector<Vector> datas = tableModel.getDataVector();
                String[] edges = new String[datas.size()];


                for (int i= 0; i< datas.size(); ++i)
                    edges[i] = datas.elementAt(i).toString().replace("[", "").replace("]", "");

                for(String edge :edges){

                    String[] nodesAndweight = edge.split(",");
                    graph.addItem(nodesAndweight[0],nodesAndweight[1],Double.parseDouble(nodesAndweight[2]));
                }

            }
        });

        //End of Create Graph Button

        //Min Spanning tree button

        JButton operation1 = new JButton("Minimum Spanning Tree");
        operation1.setBounds(320, 190, 179, 23);
        frame.getContentPane().add(operation1);
        operation1.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {

                if (graph == null)
                    JOptionPane.showMessageDialog(null,"First Create a Graph" ,"No Graph Found",JOptionPane.ERROR_MESSAGE);

                else {
                    try {
                        IGraph minimumSpanningTreeGraph = remoteService.minimumSpanningTree(graph,clientID);
                        st = minimumSpanningTreeGraph.print();
                        JOptionPane.showMessageDialog(null, st, "Minimum Spanning Tree", JOptionPane.INFORMATION_MESSAGE);

                    } catch (RemoteException e1) {
                        JOptionPane.showMessageDialog(null, "Server is not available!", "Server Error", JOptionPane.ERROR_MESSAGE);
                    }
                     catch (NoPermissionException e1) {
                         JOptionPane.showMessageDialog(null,  e1.getMessage(),"Credit Error", JOptionPane.ERROR_MESSAGE);
                    }

                }
            }
        });


        // end of min spanning tree button


        //Incidence matrix

        JButton operation2 = new JButton("Incidence matrix");
        operation2.setBounds(320, 230, 179, 23);
        frame.getContentPane().add(operation2);

        operation2.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                String a = new String();

                if (graph == null)
                    JOptionPane.showMessageDialog(null,"First Create a Graph" ,"No Graph Found",JOptionPane.ERROR_MESSAGE);
                else {
                    try {
                        Map<Object, int[]> incidenceMatrix = remoteService.IncidenceMatrix(graph,clientID);

                        Set vertexes = incidenceMatrix.keySet();
                        for (Object vertex : vertexes)
                            a += String.format("%-50s %-50s\n", vertex, Arrays.toString(incidenceMatrix.get(vertex)));

                        System.out.println(a);
                        JOptionPane.showMessageDialog(null, a, "Incidence Matrix", JOptionPane.INFORMATION_MESSAGE);

                    } catch (RemoteException e1) {
                        JOptionPane.showMessageDialog(null, "Server is not available!", "Server Error", JOptionPane.ERROR_MESSAGE);
                    }catch (NoPermissionException e1) {
                        JOptionPane.showMessageDialog(null,  e1.getMessage(),"Credit Error", JOptionPane.ERROR_MESSAGE);
                    }

                }
            }
        });

        //end incidence matrix





        equation_count = new JSpinner();
        equation_count.setModel(new SpinnerNumberModel(new Integer(0), new Integer(0), null, new Integer(1)));
        equation_count.setBounds(131, 11, 70, 20);
        frame.getContentPane().add(equation_count);


        //Get Button

        Button Get_equations = new Button("Get");
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

        //End Get Button




        Get_equations.setActionCommand("Get_equations");
        Get_equations.setBounds(219, 9, 96, 22);
        frame.getContentPane().add(Get_equations);

        Label label = new Label("Number of Edges:");
        label.setFont(new Font("Dialog", Font.BOLD, 12));
        label.setEnabled(false);
        label.setBounds(0, 11, 125, 23);
        frame.getContentPane().add(label);

        scrollPane = new JScrollPane();
        scrollPane.setBounds(29, 62, 232, 213);
        frame.getContentPane().add(scrollPane);



    }



}
