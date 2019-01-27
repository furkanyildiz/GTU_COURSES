import java.io.*;
import java.util.ArrayList;
import java.util.List;

public abstract class DiscreateTransform1D {
    /**
     * Output file name to write results.
     */
    private String OUTPUTFILENAME = "output.txt";

    /**
     * Calculating 1D discreate transform algorithm.
     * @param filename reading file of name.
     */
    public void calculateTransform(String filename){

        List<Double> reel = new ArrayList<>();
        List<Double> imag = new ArrayList<>();

        try {
            readFile(filename,reel,imag);
            List<List<Double>> result = transform(reel,imag);
            writeOutputToFile(result);
            if (customerWantsExtra())
                addExtra();
        } catch (IOException e) {
            System.err.println("File not found!");
        }

    }

    /**
     * Read files and split equations to reel and imag. Then add them to list
     * @param filename Filename to read
     * @param reel first empty list. The list will fill with reel numbers of equations.
     * @param imag first empty list. The list will fill with imag numbers of equations.
     * @throws IOException if there is no file.
     */
    private void readFile(String filename,List<Double> reel,List<Double> imag) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader(filename));
        String sCurrentLine;
        List<String> s = new ArrayList<String>();

        while ((sCurrentLine = br.readLine()) != null)
            s.add(sCurrentLine);

        for (String line : s)
            parseALine(line,reel,imag);

    }

    /**
     * Parse and add to list a string as real numbers and complex numbers (string can include several of them)
     * @param line a line from file.
     * @param reel first empty list. The list will fill with reel numbers of equations.
     * @param imag first empty list. The list will fill with imag numbers of equations.
     */
    private static void parseALine(String line,List<Double> reel,List<Double> imag){

        String[] parse = line.split(",");

        for (String complex_num : parse){
            String[] nums = complex_num.split(" ");

            reel.add(Double.parseDouble(nums[0]));
            String num_comp = nums[2].substring(0,nums[2].indexOf("i"));

            if (nums[1].contains("-"))
                imag.add(-1 * Double.parseDouble(num_comp));
            else
                imag.add(Double.parseDouble(num_comp));

        }
    }

    /**
     * Writes 1D Discreate Transfrom to file.
     * @param res results of 1D Discreate Transfrom
     * @throws FileNotFoundException if there is no file.
     * @throws UnsupportedEncodingException if encoding is not support.
     */
    private void writeOutputToFile(List<List<Double>> res) throws FileNotFoundException, UnsupportedEncodingException {

        int N = res.get(0).size();

        StringBuffer s=new StringBuffer("");

        for(int i=0; i<N; ++i){

            double reel = res.get(0).get(i);
            double img = 0.0;

            if (res.size()>1)
                img = res.get(1).get(i);

            s.append(reel ) ;
            if (res.size()>1) {

                if (img < 0) {
                    s.append(" - ");
                    img *= -1;
                } else
                    s.append(" + ");
                s.append(img + "i, ");
            }
            s.append("\n");
        }


        System.out.println("---Results---:");
        System.out.println(s);

        PrintWriter writer = new PrintWriter(OUTPUTFILENAME, "UTF-8");
        writer.print(s);
        writer.close();

    }

    /**
     * For customer to offer any new extra.
     * @return
     */
    protected boolean customerWantsExtra(){
        return false;
    }

    /**
     * Any extra operation.
     */
    protected void addExtra(){}

    /**
     * apply discreate transform 1D implementation
     * @param reel real numbers of equations
     * @param img imaginar numbers of equations
     * @return discreate transform 1D results as real numbers list and imaginary numbers list.
     */
    protected abstract List<List<Double>> transform(List<Double> reel, List<Double> img);
}
