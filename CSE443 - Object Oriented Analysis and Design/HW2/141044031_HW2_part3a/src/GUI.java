import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GUI {
    public JFrame frame;
    IPlane plane;
    private JButton button1;

    public GUI() {

        frame = new JFrame("Turkish Aerospace Industries");
        frame.setBounds(100, 100, 420, 384);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        button1 = new JButton("Simulate!");
        button1.setBounds(250,250,125,30);
        frame.add(button1);


        String[] choices = {"TPX100","TPX200","TPX300"};

        JComboBox comboBox = new JComboBox(choices);
        comboBox.setBounds(72, 62, 148, 20);
        frame.getContentPane().add(comboBox);


        button1.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                String selected_method = (String) comboBox.getSelectedItem();
                PlaneTypes typeOfPlane = convertStringToEnum(selected_method);
                plane = PlaneFactory.createPlane(typeOfPlane);
                plane.buildPlane();

                JOptionPane.showMessageDialog(null, plane.toString(), "İnfo",JOptionPane.INFORMATION_MESSAGE);


            }
        });



    }

    private PlaneTypes convertStringToEnum(String type){
        switch (type){
            case "TPX100":
                return PlaneTypes.TPX100;
            case "TPX200":
                return PlaneTypes.TPX200;
            case "TPX300":
                return PlaneTypes.TPX300;
        }
        return null;
    }




}
