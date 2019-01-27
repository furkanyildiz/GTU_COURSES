public class MainDemo {

    public static void main(String[] args){

        LifeTimeOfAStudent student = new LifeTimeOfAStudent();

        System.out.println("---- Student 1 ----\n");
        try {
            System.out.println("Current State:" + student);
            student.outOfTillLate();
            System.out.println("Current State:" + student);
            student.sleep();
            System.out.println("Current State:" + student);
            student.exercise();
            System.out.println("Current State:" + student);
            student.perseveranceAndHardwork();
            System.out.println("Current State:" + student);
        }catch (UnsupportedOperationException e){
            System.err.println("Unsupported Operation!");
        }

        /////////////

        System.out.println("\n\n---- Student 2 ----\n");
        LifeTimeOfAStudent student2 = new LifeTimeOfAStudent();

        try {
            System.out.println("Current State:" + student2);
            student2.outOfTillLate();
            System.out.println("Current State:" + student2);
            student2.sleep();
            System.out.println("Current State:" + student2);
            student2.outOfTillLate();
            System.out.println("Current State:" + student2);
            student2.coffeeAndWork();
            System.out.println("Current State:" + student2);
        }catch (UnsupportedOperationException e){
            System.err.println("Unsupported Operation!");
        }


        /////////////

        System.out.println("\n\n---- Student 3 ----\n");
        LifeTimeOfAStudent student3 = new LifeTimeOfAStudent();

        try {
            System.out.println("Current State:" + student3);
            student3.buyingAGTX1080();
            System.out.println("Current State:" + student3);

        }catch (UnsupportedOperationException e){
            System.err.println("Unsupported Operation!");
        }

        /////

        System.out.println("\n\n---- Student 4 ----\n");
        LifeTimeOfAStudent student4 = new LifeTimeOfAStudent();

        try {
            System.out.println("Current State:" + student4);
            student4.cheating();
            System.out.println("Current State:" + student4);

        }catch (UnsupportedOperationException e){
            System.err.println("Unsupported Operation!");
        }

    }

}
