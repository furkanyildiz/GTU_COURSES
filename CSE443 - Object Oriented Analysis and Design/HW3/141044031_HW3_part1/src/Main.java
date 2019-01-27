public class Main {

    public static void main(String[] args){

        ModernPayment modelPayment = new ModernPaymentClass();

        TurboPayment modelPay = new ModernPaymentAdapter(modelPayment);

        modelPay.payInTurbo("3456",230.99,"ist","3");
        modelPay.payInTurbo("2323",219.99,"kocaeli","5");

    }

}
