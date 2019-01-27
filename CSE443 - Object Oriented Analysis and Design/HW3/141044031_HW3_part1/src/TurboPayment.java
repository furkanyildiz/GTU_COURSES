public interface TurboPayment {
    int payInTurbo(String turboCardNo, double turboAmount,
                   String destinationTurboOfCourse, String installmentsButInTurbo);
}
