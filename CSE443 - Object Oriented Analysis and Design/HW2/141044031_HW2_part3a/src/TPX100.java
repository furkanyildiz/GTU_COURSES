public class TPX100 extends Plane {
    /**
     * Construction. Initializes types of Skelethon,Engine,SeatinTypes and Purpose
     */
    TPX100(){
        setSketlonType(SketlonTypes.AliminumAlloy);
        setEngineTypes(EngineTypes.SingleJetEngine);
        setSeatingTypes(SeatingTypes.Seats50);
        setPurpose("Domestic flights");
    }

}
