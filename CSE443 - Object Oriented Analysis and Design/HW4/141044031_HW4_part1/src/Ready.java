public class Ready implements State {
    /**
     * LifeTimeOfAStudent object which operates from the states.
     */
    private LifeTimeOfAStudent lifeTimeOfAStudent;

    /**
     * Ready constructure
     * @param s LifeTimeOfAStudent
     */
    public Ready(LifeTimeOfAStudent s) {
        lifeTimeOfAStudent = s;
    }
    /**
     * Exercise activity
     */
    @Override
    public void exercise() {
        System.out.println("You are so fit!");
        lifeTimeOfAStudent.setState(lifeTimeOfAStudent.getFit());
    }
    /**
     * Sleep activity
     */
    @Override
    public void sleep() {
        System.out.println("You are ready, you can't sleep!");
        throw new UnsupportedOperationException();

    }
    /**
     * Perseverance And Hardwork activity
     */
    @Override
    public void perseveranceAndHardwork() {
        System.out.println("Congratulations graduated!");
        lifeTimeOfAStudent.setState(lifeTimeOfAStudent.getGraduate());

    }
    /**
     * Out of Till Late activity
     */
    @Override
    public void outOfTillLate() {
        System.out.println("You need some sleep!");
        lifeTimeOfAStudent.setState(lifeTimeOfAStudent.getNeedingSleep());
    }
    /**
     * Coffee and Work activity
     */
    @Override
    public void coffeeAndWork() {
        throw new UnsupportedOperationException();

    }
    /**
     * Cheating activity
     */
    @Override
    public void cheating() {
        System.out.println("You unable to become a rod for an axe!");
        lifeTimeOfAStudent.setState(lifeTimeOfAStudent.getUnabletoBecomeARodForAnAxe());

    }
    /**
     * Buying a GTX1080 or more activity
     */
    @Override
    public void buyingAGTX1080() {
        System.out.println("You unable to become a rod for an axe!");
        lifeTimeOfAStudent.setState(lifeTimeOfAStudent.getUnabletoBecomeARodForAnAxe());

    }
}


