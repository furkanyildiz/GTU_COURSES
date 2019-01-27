public class ModernPaymentAdapter implements TurboPayment {
    /**
     * New payment instance
     */
    private ModernPayment payment;

    /**
     * Constucture of the class
     * @param t modenrn payment instance
     */
    ModernPaymentAdapter(ModernPayment t){
        this.payment = t;
    }

    /**
     * Payment method
     * @param turboCardNo
     * @param turboAmount
     * @param destinationTurboOfCourse
     * @param installmentsButInTurbo
     * @return 0 if pay is successfull else 1
     */
    @Override
    public int payInTurbo(String turboCardNo, double turboAmount, String destinationTurboOfCourse, String installmentsButInTurbo) {
        return payment.pay(turboCardNo,turboAmount,destinationTurboOfCourse,installmentsButInTurbo);

    }
}
