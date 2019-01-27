import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GUI {
    public JFrame frame;
    private JButton button1;

    InternationalMarketFactory market;
    IPlane plane;

    public GUI() {

        frame = new JFrame("Turkish Aerospace Industries");
        frame.setBounds(100, 100, 420, 384);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        button1 = new JButton("Simulate!");
        button1.setBounds(250,250,125,30);
        frame.add(button1);

        //MARKET
        Label marketLabel = new Label("Select Market:");
        marketLabel.setFont(new Font("Dialog", Font.BOLD, 12));
        marketLabel.setEnabled(false);
        marketLabel.setBounds(0, 62, 90, 20);
        frame.getContentPane().add(marketLabel);

        String[] choices = {"Domestic Market","Eurasia Market","Other Market"};

        JComboBox comboBox = new JComboBox(choices);
        comboBox.setBounds(95, 62, 148, 20);
        frame.getContentPane().add(comboBox);

        // MODEL
        Label modelLabel = new Label("Select Model:");
        modelLabel.setFont(new Font("Dialog", Font.BOLD, 12));
        modelLabel.setEnabled(false);
        modelLabel.setBounds(0, 102, 90, 20);
        frame.getContentPane().add(modelLabel);


        String[] choices2 = {"TPX100","TPX200","TPX300"};

        JComboBox comboBox2 = new JComboBox(choices2);
        comboBox2.setBounds(95, 102, 148, 20);
        frame.getContentPane().add(comboBox2);

        button1.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                String selected_market= (String) comboBox.getSelectedItem();
                String selected_model= (String) comboBox2.getSelectedItem();
                PlaneTypes typeOfModel = convertModelStringToEnum(selected_model);
                MarketTypes typeOfMarket = convertMarketStringToEnum(selected_market);

                plane = PlaneFactory.createPlane(typeOfModel,typeOfMarket);
                plane.buildPlane();

                JOptionPane.showMessageDialog(null, plane.toString(), "İnfo",JOptionPane.INFORMATION_MESSAGE);


            }
        });



    }

    private PlaneTypes convertModelStringToEnum(String type){
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
    private MarketTypes convertMarketStringToEnum(String type){
        switch (type){
            case "Domestic Market":
                return MarketTypes.DomesticMarket;
            case "Eurasia Market":
                return MarketTypes.EurasiaMarket;
            case "Other Market":
                return MarketTypes.OtherMarket;
        }
        return null;
    }

}
