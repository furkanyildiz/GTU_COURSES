library verilog;
use verilog.vl_types.all;
entity mux_2_1 is
    port(
        outp            : out    vl_logic_vector(4 downto 0);
        d0              : in     vl_logic_vector(4 downto 0);
        d1              : in     vl_logic_vector(4 downto 0);
        \select\        : in     vl_logic
    );
end mux_2_1;
