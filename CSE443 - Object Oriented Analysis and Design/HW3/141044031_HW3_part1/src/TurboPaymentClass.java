public class TurboPaymentClass implements TurboPayment {


    @Override
    public int payInTurbo(String turboCardNo, double turboAmount, String destinationTurboOfCourse, String installmentsButInTurbo) {

        System.out.println("_TurboPaymentClass_ It was paid with card no:" + turboCardNo +" amount:" + turboAmount +
                " destinationTurboOfCourse:" + destinationTurboOfCourse + " installmentsButInTurbo:" +
                installmentsButInTurbo);

        return 0;
    }
}
