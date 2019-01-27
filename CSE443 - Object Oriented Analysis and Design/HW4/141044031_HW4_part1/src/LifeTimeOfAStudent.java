public class LifeTimeOfAStudent {
    /**
     * Ready State.
     */
    private State Ready;
    /**
     * Fit State.
     */
    private State Fit;
    /**
     * Graduate State.
     */
    private State Graduate;
    /**
     * NeedingSleep State.
     */
    private State NeedingSleep;
    /**
     * ChronicIllness State.
     */
    private State ChronicIllness;
    /**
     * UnabletoBecomeARodForAnAxe State.
     */
    private State UnabletoBecomeARodForAnAxe;
    /**
     * State of student.
     */
    private State state;

    /**
     * Constructure of class. Creates States and set states to Ready first.
     */
    public LifeTimeOfAStudent() {

        Ready = new Ready(this);
        Fit = new Fit(this);
        Graduate = new Graduate(this);
        NeedingSleep = new NeedingSleep(this);
        ChronicIllness = new ChronicIllness(this);
        UnabletoBecomeARodForAnAxe = new UnabletoBecomeARodForAnAxe(this);
        this.state = Ready;
    }

    /**
     * Exercise activity
     */
    public void exercise(){
        state.exercise();
    }
    /**
     * Sleep activity
     */
    public void sleep(){
        state.sleep();
    }
    /**
     * Perseverance And Hardwork activity
     */
    public void perseveranceAndHardwork(){
        state.perseveranceAndHardwork();
    }
    /**
     * Out of Till Late activity
     */
    public void outOfTillLate(){
        state.outOfTillLate();
    }
    /**
     * Cheating activity
     */
    public void cheating(){
        state.cheating();
    }
    /**
     * Buying a GTX1080 or more activity
     */
    public void buyingAGTX1080(){
        state.buyingAGTX1080();
    }
    /**
     * Coffee and Work activity
     */
    public void coffeeAndWork(){
        state.coffeeAndWork();
    }

    /**
     * Change state of student.
     * @param newState new state
     */
    void  setState(State newState){
        this.state = newState;
    }

    /**
     * Getter for ready state.
     * @return ready state.
     */
    public State getReady() {
        return Ready;
    }
    /**
     * Getter for Fit state.
     * @return Fit state.
     */
    public State getFit() {
        return Fit;
    }
    /**
     * Getter for Graduate state.
     * @return Graduate state.
     */
    public State getGraduate() {
        return Graduate;
    }
    /**
     * Getter for Sleep state.
     * @return Sleep state.
     */
    public State getNeedingSleep() {
        return NeedingSleep;
    }
    /**
     * Getter for ChronicIllness state.
     * @return ChronicIllness state.
     */
    public State getChronicIllness() {
        return ChronicIllness;
    }
    /**
     * Getter for UnabletoBecomeARodForAnAxe state.
     * @return UnabletoBecomeARodForAnAxe state.
     */
    public State getUnabletoBecomeARodForAnAxe() {
        return UnabletoBecomeARodForAnAxe;
    }
    /**
     * Getter for state.
     * @return state of student.
     */
    public State getState() {
        return state;
    }

    /**
     * Returns state of student as a string.
     * @return state of student
     */
    @Override
    public String toString() {
        String stateString =  getState().toString();
        return stateString.split("@")[0];
    }
}

