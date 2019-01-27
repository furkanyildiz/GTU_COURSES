public class EurasiaMarket implements InternationalMarketFactory {

    private String info;

    /**
     * Construction
     */
    public EurasiaMarket() {
        this.info = new String();
        this.info = "";
    }

    /**
     * Creates Turbofan Injection
     * @return Turbofan Injection
     */
    @Override
    public EngineInjectionType injectEngine() {

        info += "Turbofan Engine Injected! \n";
        return new TurbofanInjection();
    }

    /**
     * Creates Linen Cover
     * @return Linen Cover
     */
    @Override
    public SeatingCover coverSeating() {
        info += "Linen Seat Covered! \n";

        return new LinenSeatingCover();
    }
    @Override
    public String toString() {
        return info;
    }
}
