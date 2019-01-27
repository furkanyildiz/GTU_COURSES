public class TurbofanInjection implements EngineInjectionType {

    /**
     * Description to simulate program.
     * @return String description to simulate program
     */
    @Override
    public String description() {
        String info = "Turbofan Injectioned!";
        System.out.println(info);
        return info;
    }

}
