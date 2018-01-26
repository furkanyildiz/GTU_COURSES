import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

/**
 *
 * @author yldzf
 */
public class main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)  {

        FamilyTree f = null;
        try {
            BufferedReader reader = new BufferedReader(new FileReader("test.txt"));
            String[] broken_text = null;
            String text = "";
            BinaryTree<Integer> bTree = new BinaryTree (null);
            boolean first = true;
            while((text = reader.readLine()) != null && !text.isEmpty()) {
                if(first){
                    f = new FamilyTree(text);
                    first = false;
                }
                else{
                    broken_text = text.split(", ");
                    f.add(broken_text[0], broken_text[1], broken_text[2]);
                }
            }
        } catch (FileNotFoundException ex) {
            System.err.println("File not found!");
            System.exit(0);
        } catch (IOException ex) {
            System.err.println("File input-output error!");
            System.exit(0);
        } catch (Exception ex) {
            System.err.println(ex.getMessage());
            System.exit(0);
        }


        System.out.println(f);
        System.out.println(f.LevelOrderTraverse());

    }

}
