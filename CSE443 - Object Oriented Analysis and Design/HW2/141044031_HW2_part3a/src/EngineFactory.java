public class EngineFactory {
    /**
     * Creates Engine object according to engine type
     * @param type engine type
     * @return Engine
     */
    public static Engine createEngine(EngineTypes type){

        if (type == EngineTypes.SingleJetEngine )
            return new SingleJetEngine();
        else if (type == EngineTypes.TwinJetEngines)
            return new TwinSetEngine();
        else if (type == EngineTypes.QuadroJetEngines)
            return new QuadroJetEngine();
        else
            throw new IllegalArgumentException();

    }

}
