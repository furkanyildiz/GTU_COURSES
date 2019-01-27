import java.awt.*;

public class DemoMain {

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


//    public static void main(String[] args){
//
//        System.out.println("-----  TPX100 building...  -----");
//        Plane plane1 = PlaneFactory.createPlane(PlaneTypes.TPX100);
//        plane1.buildPlane();
//
//        System.out.println("-----  TPX200 building...  -----");
//        Plane plane2 = PlaneFactory.createPlane(PlaneTypes.TPX200);
//        plane2.buildPlane();
//
//        System.out.println("-----  TPX300 building...  -----");
//        Plane plane3 = PlaneFactory.createPlane(PlaneTypes.TPX300);
//        plane3.buildPlane();
//
//    }

}
