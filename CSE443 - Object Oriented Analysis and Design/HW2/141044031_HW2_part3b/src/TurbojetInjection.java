public class TurbojetInjection implements EngineInjectionType {
    /**
     * Description to simulate program.
     * @return String description to simulate program
     */
    @Override
    public String description() {
        String info = "Turbojet Injectioned!";
        System.out.println(info);
        return info;
    }}
