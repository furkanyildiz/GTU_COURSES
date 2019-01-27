public class Fit implements State {
    /**
     * LifeTimeOfAStudent object which operates from the states.
     */
    private LifeTimeOfAStudent lifeTimeOfAStudent;
    /**
     * Fit constructure
     * @param s LifeTimeOfAStudent
     */
    public Fit(LifeTimeOfAStudent s) {
        lifeTimeOfAStudent = s;
    }
    /**
     * Perseverance And Hardwork activity
     */
    @Override
    public void perseveranceAndHardwork() {
        System.out.println("You are Graduate!");
        lifeTimeOfAStudent.setState(lifeTimeOfAStudent.getGraduate());
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
