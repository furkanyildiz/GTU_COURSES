public class TPX300 extends Plane {
    /**
     * Construction. Initializes types of Skelethon,Engine,SeatinTypes and Purpose
     */
    TPX300(InternationalMarketFactory internationalMarketFactory){
        super(internationalMarketFactory);
        setSketlonType(SketlonTypes.TitaniumAlloy);
        setEngineTypes(EngineTypes.QuadroJetEngines);
        setSeatingTypes(SeatingTypes.Seats250);
        setPurpose("Transatlantic flights");
    }

}
