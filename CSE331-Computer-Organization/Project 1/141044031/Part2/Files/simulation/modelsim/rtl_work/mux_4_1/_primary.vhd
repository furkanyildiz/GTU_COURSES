library verilog;
use verilog.vl_types.all;
entity mux_4_1 is
    port(
        \out\           : out    vl_logic_vector(4 downto 0);
        d0              : in     vl_logic_vector(4 downto 0);
        d1              : in     vl_logic_vector(4 downto 0);
        d2              : in     vl_logic_vector(4 downto 0);
        d3              : in     vl_logic_vector(4 downto 0);
        \select\        : in     vl_logic_vector(1 downto 0)
    );
end mux_4_1;
