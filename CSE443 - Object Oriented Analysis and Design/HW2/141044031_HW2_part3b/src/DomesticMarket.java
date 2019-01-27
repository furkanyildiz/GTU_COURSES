public class DomesticMarket implements InternationalMarketFactory {

    private String info;

    /**
     * Construction
     */
    public DomesticMarket() {
        this.info = "";
    }

    /**
     * Creates Turbojet Injection
     * @return Turbojet Injection
     */
    @Override
    public EngineInjectionType injectEngine() {
        info +="Turbojet Engine Injected! \n";
        return new TurbojetInjection();
    }

    /**
     * Creates Velvet Seating Cover
     * @return Velvet Seating Cover
     */
    @Override
    public SeatingCover coverSeating() {
        info +="Velvet Seating Covered! \n";
        return new VelvetSeatingCover();
    }

    @Override
    public String toString() {
        return info;
    }
}
