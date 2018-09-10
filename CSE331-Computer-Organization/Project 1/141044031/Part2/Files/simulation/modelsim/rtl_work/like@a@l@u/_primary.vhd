library verilog;
use verilog.vl_types.all;
entity likeALU is
    port(
        \out\           : out    vl_logic_vector(4 downto 0);
        inp_A           : in     vl_logic_vector(4 downto 0);
        inp_B           : in     vl_logic_vector(4 downto 0);
        \select\        : in     vl_logic_vector(1 downto 0)
    );
end likeALU;
