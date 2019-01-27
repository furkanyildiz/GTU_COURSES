public interface ModernPayment {
    /**
     * Payment method
     * @param cardNo
     * @param amount
     * @param destination
     * @param installments
     * @return 0 with success.
     */
    int pay(String cardNo, double amount, String destination, String installments);
}
