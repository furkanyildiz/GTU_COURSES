
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author yldzf
 */
public final class Numerical {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        Numerical o = new Numerical(args);

    }
    public Numerical(String[] args){
        login(args);
    }

   public void login(String[] args){
        double a = Double.parseDouble(args[0]);
        double b = Double.parseDouble(args[1]);
        String criteion = args[2];
        double epsilon = Double.parseDouble(args[3]);
        if(!criteion.equals("DISTANCE_TO_ROOT") && !criteion.equals("ABSOLUTE_ERROR")
                && !criteion.equals("RELATIVE_ERROR") ){
            System.err.println("Invalid stopping criterion");
            System.exit(0);
        }
        if(function(a)*function(b)>0){
            System.err.println("Invalid a-b selection.");
            System.err.println("There is no root between a and b.");

            System.exit(0);
        }
        try {
            bisection(a,b,epsilon,criteion);
        } catch (Exception ex) {
            Logger.getLogger(Numerical.class.getName()).log(Level.SEVERE, null, ex);
        }
   }
   public double function(double x){
       return (Math.pow(Math.E,x) - 3*x );
       //return 2*x +3*Math.cos(Math.toRadians(x))-Math.pow(Math.E,x);
       //return Math.pow(x,2)-4*x+4-Math.log(x);
       //return x+1-2*Math.cos(Math.toRadians(Math.PI * x));
   }
   public void bisection(double a, double b,double epsilon,String errType) throws Exception{
		int i = 1;
		double FA =  function(a);
		double p2 = a;
		int c =  (int) Math.ceil(Math.log((b-a)/epsilon)/Math.log(2));
		while(true){
			double root =a+(b-a)/2;
			double func = function(root);
			// System.out.printf("%d. iteration a:%f b:%f Pn:%f f(an): %f f(pn):%f RelERR:%f\n ",i,a,b,root,function(a),func,RelErr(errType,func,p2));
			System.out.printf("%d. iteration  ABSOLUTE_ERROR:%f RELATIVE_ERROR:%f\n ",i,RelErr("ABSOLUTE_ERROR",root,p2),RelErr("RELATIVE_ERROR",root,p2));
			if ( i==100){
			    System.err.printf("Approximate error!\n");
			    break;
			}
			if (func == 0 || (b-a)/2<epsilon){
			    System.out.printf("Approximate root is: %f\n",root);
			    System.out.printf("The number of iterations that have been executed: %d\n",i);
			    System.out.printf("The theoretically required number of iterations: %d\n",c);

			   break;
			}

			if (func * FA >0){
			  a = root;
			  FA = func;
			}
			else if (func * FA <0)
			   b = root;

			else
			   throw (new Exception());

			++i;
			p2 = root;

		}
       
   }
   public double RelErr(String errType,double pn,double pn1){
       
       if(errType.equals("DISTANCE_TO_ROOT")){
          return Math.abs (function(pn));
          
       }
       else{
           double a = Math.abs(pn-pn1); //ABSOLUTE_ERROR
           if(errType.equals("RELATIVE_ERROR"))
               return a/Math.abs(pn);
           return a;
       }
       
       
   }
    
}

