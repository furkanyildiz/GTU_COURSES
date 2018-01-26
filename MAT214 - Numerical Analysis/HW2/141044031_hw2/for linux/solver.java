import java.io.FileNotFoundException;
/**
 *
 * @author yldzf
 */
public class solver {

  
    public static void main(String[] args) {
        GESP gesp;
        Jacobi jcb;
        
        if(args.length != 4){
            System.err.println("Usage error! java solver ­i system.txt ­m GESP");
            System.err.println("Use:java solver ­-i system.txt ­-m GESP");
            System.exit(0);
        }
        
        
        if (args[3].equals("GESP"))
            try {
                gesp = new GESP(args[1]);
                //System.err.println(r);
            } catch (FileNotFoundException ex) {
                System.err.println("File not found!");
                System.exit(0);
            }catch(ArithmeticException ex){
                System.err.println(ex.getMessage());
                System.err.println("So the system has no (unique) solution!");
                System.exit(0);
            } 
            catch (Exception ex) {
            System.err.println(ex.getMessage());
            System.err.println("So the system has no (unique) solution!");
            System.exit(0);
        }
        else if(args[3].equals("JCB"))
            try {
                jcb = new Jacobi(args[1]) ;
        } catch (FileNotFoundException ex) {
            System.err.println("File not found!");
            System.exit(0);
        } catch (Exception ex) {
            System.err.println(ex.getMessage());
            System.err.println("So the system has no (unique) solution!");
            System.exit(0);
        }
    }
    
}
