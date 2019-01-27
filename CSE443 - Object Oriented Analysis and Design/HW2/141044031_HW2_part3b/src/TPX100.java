public class TPX100 extends Plane {
    /**
     * Construction. Initializes types of Skelethon,Engine,SeatinTypes and Purpose
     */
    TPX100(InternationalMarketFactory internationalMarketFactory){
        super(internationalMarketFactory);
        setSketlonType(SketlonTypes.AliminumAlloy);
        setEngineTypes(EngineTypes.SingleJetEngine);
        setSeatingTypes(SeatingTypes.Seats50);
        setPurpose("Domestic flights");
    }

}
