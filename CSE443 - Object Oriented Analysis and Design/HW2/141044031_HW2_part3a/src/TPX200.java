public class TPX200 extends Plane {
    /**
     * Construction. Initializes types of Skelethon,Engine,SeatinTypes and Purpose
     */
    TPX200(){
        setSketlonType(SketlonTypes.NickelAlloy);
        setEngineTypes(EngineTypes.TwinJetEngines);
        setSeatingTypes(SeatingTypes.Seats100);
        setPurpose("Domestic and short international flights");
    }

}
