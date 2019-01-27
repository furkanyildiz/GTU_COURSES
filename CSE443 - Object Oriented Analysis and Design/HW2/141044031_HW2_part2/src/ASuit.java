public abstract class ASuit implements ISuit {
    /**
     * cost of suit
     */
    private double TL;
    /**
     * Weight of suit
     */
    private double Weight;

    /**
     * Set cost
     * @param TL new cost
     */
    protected void setTL(double TL) {
        this.TL = TL;
    }

    /**
     * Set Weight
     * @param weight new Weight
     */
    protected void setWeight(double weight) {
        Weight = weight;
    }

    /**
     * return cost
     * @return cost
     */
    @Override
    public double getCost() {
        return TL;
    }

    /**
     * return weight
     * @return weight
     */
    @Override
    public double getWeight() {
        return Weight;
    }

    /**
     * Prints cost and weights of suit
     * @return String as cost and weights of suit
     */
    @Override
    public String toString() {
        return "Cost:" + getCost() + " Weight:" + getWeight();
    }
}
