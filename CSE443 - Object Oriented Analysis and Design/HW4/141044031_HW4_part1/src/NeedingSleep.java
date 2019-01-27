public class NeedingSleep implements State {
    /**
     * LifeTimeOfAStudent object which operates from the states.
     */
    private LifeTimeOfAStudent lifeTimeOfAStudent;
    /**
     * NeedingSleep constructure
     * @param s LifeTimeOfAStudent
     */
    public NeedingSleep(LifeTimeOfAStudent s) {
        lifeTimeOfAStudent = s;
    }
    /**
     * Sleep activity
     */
    @Override
    public void sleep() {
        System.out.println("You slept, so you are ready!");
        lifeTimeOfAStudent.setState(lifeTimeOfAStudent.getReady());
    }
    /**
     * Coffee and Work activity
     */
    @Override
    public void coffeeAndWork() {
        System.out.println("Your need to sleep but you want to work with Coffee, It's a Chronic Illness");
        lifeTimeOfAStudent.setState(lifeTimeOfAStudent.getChronicIllness());
    }
    /**
     * Exercise activity
     */
    @Override
    public void exercise() {
        throw new UnsupportedOperationException();

    }
    /**
     * Perseverance And Hardwork activity
     */

    @Override
    public void perseveranceAndHardwork() {
        throw new UnsupportedOperationException();

    }
    /**
     * Out of Till Late activity
     */
    @Override
    public void outOfTillLate() {
        throw new UnsupportedOperationException();

    }
    /**
     * Cheating activity
     */
    @Override
    public void cheating() {
        throw new UnsupportedOperationException();

    }
    /**
     * Buying a GTX1080 or more activity
     */
    @Override
    public void buyingAGTX1080() {
        throw new UnsupportedOperationException();

    }


}
