public class PlaneFactory {
    /**
     * Creates Plane according to Plane type.
     * @param type Plane type
     * @return Plane
     */
    public static IPlane createPlane(PlaneTypes type,MarketTypes typeOfMarket){

        InternationalMarketFactory market = MarketFactory.identify(typeOfMarket);

        if (type == PlaneTypes.TPX100 )
            return new TPX100(market);
        else if (type == PlaneTypes.TPX200)
            return new TPX200(market);
        else if (type == PlaneTypes.TPX300)
            return new TPX300(market);
        else
            throw new IllegalArgumentException();

    }

}
