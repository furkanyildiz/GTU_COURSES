public class MarketFactory {
    /**
     * Creates Plane according to Plane type.
     * @param type Plane type
     * @return Plane
     */
    public static InternationalMarketFactory identify(MarketTypes type){

        if (type == MarketTypes.DomesticMarket )
            return new DomesticMarket();
        else if (type == MarketTypes.EurasiaMarket)
            return new EurasiaMarket();
        else if (type == MarketTypes.OtherMarket)
            return new OtherMarket();
        else
            throw new IllegalArgumentException();

    }

}
