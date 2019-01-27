public class SeatingFactory {
    /**
     * Creates Seating object according to seating type
     * @param type seating type
     * @return Seating
     */
    public static Seating createEngine(SeatingTypes type){

        if (type == SeatingTypes.Seats50 )
            return new seats50();
        else if (type == SeatingTypes.Seats100)
            return new seats100();
        else if (type == SeatingTypes.Seats250)
            return new seats250();
        else
            throw new IllegalArgumentException();

    }

}
