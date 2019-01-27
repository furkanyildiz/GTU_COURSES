public class Graduate implements State {
    /**
     * LifeTimeOfAStudent object which operates from the states.
     */
    private LifeTimeOfAStudent lifeTimeOfAStudent;
    /**
     * Graduate constructure
     * @param s LifeTimeOfAStudent
     */
    public Graduate(LifeTimeOfAStudent s) {
        lifeTimeOfAStudent = s;
    }

    /**
     * Exercise activity
     */
    @Override
    public void exercise() {
        throw new UnsupportedOperationException();

    }
    /**
     * Sleep activity
     */
    @Override
    public void sleep() {
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
    /**
     * Coffee and Work activity
     */
    @Override
    public void coffeeAndWork() {
        throw new UnsupportedOperationException();

    }
}
