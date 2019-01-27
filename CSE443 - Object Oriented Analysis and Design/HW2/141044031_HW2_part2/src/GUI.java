import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GUI {
    public JFrame frame;

    private JButton button1;
    private JPanel window;

    public GUI() {

        frame = new JFrame("ZırhSan A.S");
        frame.setBounds(100, 100, 420, 384);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        button1 = new JButton("Demand!");
        button1.setBounds(250,250,125,30);
        frame.add(button1);


        String[] choices = {"Dec","Ora","Tor"};

        JComboBox comboBox = new JComboBox(choices);
        comboBox.setBounds(72, 62, 148, 20);
        frame.getContentPane().add(comboBox);


        Label choiceSuitLabel = new Label("Select Suit:");
        choiceSuitLabel.setFont(new Font("Dialog", Font.BOLD, 12));
        choiceSuitLabel.setEnabled(false);
        choiceSuitLabel.setBounds(0, 62, 70, 23);
        frame.getContentPane().add(choiceSuitLabel);

        ///// Flamethrower
        Label FlamethrowerLabel = new Label("Select Flamethrower Count:");
        FlamethrowerLabel.setFont(new Font("Dialog", Font.BOLD, 12));
        FlamethrowerLabel.setEnabled(false);
        FlamethrowerLabel.setBounds(0, 101, 160, 23);
        frame.getContentPane().add(FlamethrowerLabel);

        JSpinner FlamethrowerCount = new JSpinner();
        FlamethrowerCount.setModel(new SpinnerNumberModel(0, 0, 20, 1));
        FlamethrowerCount.setBounds(191, 101, 70, 20);
        frame.getContentPane().add(FlamethrowerCount);

        /////

        ///// AutoRifler
        Label AutoRiflerLabel = new Label("Select AutoRifle Count:");
        AutoRiflerLabel.setFont(new Font("Dialog", Font.BOLD, 12));
        AutoRiflerLabel.setEnabled(false);
        AutoRiflerLabel.setBounds(0, 141, 160, 23);
        frame.getContentPane().add(AutoRiflerLabel);

        JSpinner AutoRiflerCount = new JSpinner();
        AutoRiflerCount.setModel(new SpinnerNumberModel(0, 0, 20, 1));
        AutoRiflerCount.setBounds(191, 141, 70, 20);
        frame.getContentPane().add(AutoRiflerCount);

        /////

        ///// RocketLauncher
        Label RocketLauncherLabel = new Label("Select RocketLauncher Count:");
        RocketLauncherLabel.setFont(new Font("Dialog", Font.BOLD, 12));
        RocketLauncherLabel.setEnabled(false);
        RocketLauncherLabel.setBounds(0, 181, 180, 23);
        frame.getContentPane().add(RocketLauncherLabel);

        JSpinner RocketLauncherCount = new JSpinner();
        RocketLauncherCount.setModel(new SpinnerNumberModel(0, 0, 20, 1));
        RocketLauncherCount.setBounds(191, 181, 70, 20);
        frame.getContentPane().add(RocketLauncherCount);

        /////

        ///// Laser
        Label LaserLabel = new Label("Select Laser Count:");
        LaserLabel.setFont(new Font("Dialog", Font.BOLD, 12));
        LaserLabel.setEnabled(false);
        LaserLabel.setBounds(0, 221, 180, 23);
        frame.getContentPane().add(LaserLabel);

        JSpinner LaserCount = new JSpinner();
        LaserCount.setModel(new SpinnerNumberModel(0, 0, 20, 1));
        LaserCount.setBounds(191, 221, 70, 20);
        frame.getContentPane().add(LaserCount);

        /////




        button1.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                String selected_method = (String) comboBox.getSelectedItem();
                ISuit suit = null;
                switch (selected_method){

                    case "Dec":
                        suit = new decSuit();
                        break;
                    case "Ora":
                        suit = new oraSuit();
                        break;
                    case "Tor":
                        suit = new torSuit();
                        break;

                }

                for(int i=0; i<(int)FlamethrowerCount.getValue(); ++i)
                    suit = new Flamethrower(suit);
                for(int i=0; i<(int)AutoRiflerCount.getValue(); ++i)
                    suit = new AutoRifle(suit);
                for(int i=0; i<(int)RocketLauncherCount.getValue(); ++i)
                    suit = new RocketLauncher(suit);
                for(int i=0; i<(int)LaserCount.getValue(); ++i)
                    suit = new Laser(suit);

                JOptionPane.showMessageDialog(null, suit.toString(), "İnfo",JOptionPane.INFORMATION_MESSAGE);


            }
        });




    }




}
