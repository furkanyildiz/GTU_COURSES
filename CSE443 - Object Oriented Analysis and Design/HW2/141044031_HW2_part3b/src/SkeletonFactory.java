
public class SkeletonFactory {
    /**
     * Creates Skeleton according to skelethon type
     * @param type skelethon type
     * @return Skeleton
     */
    public static Skeleton createSkeleton(SketlonTypes type){

        if (type == SketlonTypes.AliminumAlloy )
            return new AluminumAlloy();
        else if (type == SketlonTypes.NickelAlloy)
            return new NickelAlloy();
        else if (type == SketlonTypes.TitaniumAlloy)
            return new TitaniumAlloy();
        else
            throw new IllegalArgumentException();

    }

}
