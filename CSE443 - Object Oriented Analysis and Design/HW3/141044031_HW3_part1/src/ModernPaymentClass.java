public class ModernPaymentClass implements ModernPayment {

    /**
     * Payment method
     * @param cardNo
     * @param amount
     * @param destination
     * @param installments
     * @return 0 with success.
     */
    @Override
    public int pay(String cardNo, double amount, String destination, String installments) {
        System.out.println("_ModernPaymentClass_ It was paid with card no:" + cardNo + " amount:" + amount +
                " destinationTurboOfCourse:" + destination + " installmentsButInTurbo:" +
                installments);

        return 0;
    }
}
