public abstract class Plane implements IPlane {
    /**
     * Purpose of Plane
     */
    private String purpose;
    /**
     * Engine of the Plane
     */
    private Engine engine;
    /**
     * Seating of the Plane
     */
    private Seating seating;
    /**
     * Skeleton of the Plane
     */
    private Skeleton skeleton;

    /**
     * Skeleton type
     */
    protected SketlonTypes sketlonType;
    /**
     * Engine type
     */
    protected EngineTypes engineTypes;
    /**
     * Seating type
     */
    protected SeatingTypes seatingTypes;

    /**
     * Engine type according to market of plane.
     */
    private EngineInjectionType engineInjectionType;
    /**
     * Seating type according to market of plane.
     */
    private SeatingCover seatingCover;
    /**
     * Market type according to market of plane.
     */
    private InternationalMarketFactory internationalMarketFactory;

    private String informationOfBuilding;

    /**
     * calls skeleton factory and creates skeleton object
     */
    private void constructSkeleton(){
        this.skeleton = SkeletonFactory.createSkeleton(sketlonType);
        informationOfBuilding+= skeleton.description() + "\n";
    }

    /**
     * calls Engine factory and creates engine object
     */
    private void placeEngines(){
        this.engine = EngineFactory.createEngine(engineTypes);
        informationOfBuilding+= engine.description() + "\n";

    }


    public Plane(InternationalMarketFactory internationalMarketFactory) {
        this.internationalMarketFactory = internationalMarketFactory;
    }


    /**
     * calls Seat factory and creates seat object
     */
    private void placeSeats(){
        this.seating = SeatingFactory.createEngine(seatingTypes);
        informationOfBuilding+= seating.description() + "\n";
    }

    /**
     * Builds the plane with calling constructSkeleton,placeEngines then placeSeats.
     */
    public void buildPlane(){
        this.informationOfBuilding = "";

        engineInjectionType = internationalMarketFactory.injectEngine();
        seatingCover = internationalMarketFactory.coverSeating();
        informationOfBuilding += internationalMarketFactory.toString();


        constructSkeleton();
        placeEngines();
        placeSeats();

        this.informationOfBuilding += "Plane is ready!\n";

    }

    /**
     * Set purpose
     * @param purpose purpose of the plane
     */
    protected void setPurpose(String purpose) {
        this.purpose = purpose;
    }

    /**
     * Set Sketlon type
     * @param sketlonType sketlonType
     */
    protected void setSketlonType(SketlonTypes sketlonType) {
        this.sketlonType = sketlonType;
    }

    /**
     * Set engineTypes
     * @param engineTypes engineTypes
     */
    protected void setEngineTypes(EngineTypes engineTypes) {
        this.engineTypes = engineTypes;
    }

    /**
     * Set seatingTypes
     * @param seatingTypes seatingTypes
     */
    protected void setSeatingTypes(SeatingTypes seatingTypes) {
        this.seatingTypes = seatingTypes;
    }

    @Override
    public String toString() {
        return informationOfBuilding;
    }
}
