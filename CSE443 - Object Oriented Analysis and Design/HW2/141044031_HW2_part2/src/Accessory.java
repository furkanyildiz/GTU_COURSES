public abstract class Accessory implements ISuit{
    /**
     * cost of Suit
     */
    double cost;
    /**
     * Weight of Suit
     */
    double weight;

    /**
     * Suit to add new accesories
     */
    ISuit suit;

    /**
     * Constuction
     * @param suit Suit referance
     */
    public Accessory(ISuit suit) {
        this.suit = suit;
    }

    /**
     * Returns cost of new Suit
     * @return cost of new Suit
     */
    @Override
    public double getCost() {
        return cost + suit.getCost();
    }

    /**
     * Returns weight of new Suit
     * @return weight of new Suit
     */
    @Override
    public double getWeight() {
        return weight + suit.getWeight();
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