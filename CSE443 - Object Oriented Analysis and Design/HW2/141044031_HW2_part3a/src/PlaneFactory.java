public class PlaneFactory {
    /**
     * Creates Plane according to Plane type.
     * @param type Plane type
     * @return Plane
     */
    public static IPlane createPlane(PlaneTypes type){

        if (type == PlaneTypes.TPX100 )
            return new TPX100();
        else if (type == PlaneTypes.TPX200)
            return new TPX200();
        else if (type == PlaneTypes.TPX300)
            return new TPX300();
        else
            throw new IllegalArgumentException();

    }

}
