public class GearedTurbofanInjection implements EngineInjectionType {
    /**
     * Description to simulate program.
     * @return String description to simulate program
     */
    @Override
    public String description() {
        String info = "Geared Turbofan Injectioned!";
        System.out.println(info);
        return info;
    }
}
