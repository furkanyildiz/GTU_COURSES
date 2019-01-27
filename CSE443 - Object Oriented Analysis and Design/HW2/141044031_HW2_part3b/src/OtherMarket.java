public class OtherMarket implements InternationalMarketFactory {
    private String info;

    /**
     * Consturction
     */
    public OtherMarket() {
        this.info = new String();
        this.info = "";
    }

    /**
     * Creates Geared Turbofan Inject
     * @return Geared Turbofan Inject
     */
    @Override
    public EngineInjectionType injectEngine() {

        info += "Geared Turbofan Engine Injected!\n";
        return new GearedTurbofanInjection();
    }

    /**
     * Creates Leather Seating Cover
     * @return Leather Seating Cover
     */
    @Override
    public SeatingCover coverSeating() {
        info += "Leather Seat Covered!\n";
        return new LeatherSeatingCover();
    }
    @Override
    public String toString() {
        return info;
    }
}
