library verilog;
use verilog.vl_types.all;
entity five_bit_adder is
    port(
        A               : in     vl_logic_vector(4 downto 0);
        B               : in     vl_logic_vector(4 downto 0);
        cout            : out    vl_logic;
        S               : out    vl_logic_vector(4 downto 0)
    );
end five_bit_adder;
