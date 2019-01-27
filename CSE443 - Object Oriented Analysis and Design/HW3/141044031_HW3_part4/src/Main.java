public class Main {

    public static void main(String[] args)  {

        String filename = "numbers.txt"; //read equations from the file.
        DiscreateTransform1D discreteCosineTransform= new DiscreteCosineTransform();
        DiscreateTransform1D discreteFourierTransform = new DiscreteFourierTransform();

        System.out.println("Discrete Cosine Transform");
        discreteCosineTransform.calculateTransform(filename);
        System.out.println("Discrete Fourier Transform");
        discreteFourierTransform.calculateTransform(filename);


    }

}
