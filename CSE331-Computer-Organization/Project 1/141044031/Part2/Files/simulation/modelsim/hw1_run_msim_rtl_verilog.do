transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+D:/altera/13.1/workspace/hw1 {D:/altera/13.1/workspace/hw1/half_adder.v}
vlog -vlog01compat -work work +incdir+D:/altera/13.1/workspace/hw1 {D:/altera/13.1/workspace/hw1/full_adder.v}
vlog -vlog01compat -work work +incdir+D:/altera/13.1/workspace/hw1 {D:/altera/13.1/workspace/hw1/five_bit_adder.v}
vlog -vlog01compat -work work +incdir+D:/altera/13.1/workspace/hw1 {D:/altera/13.1/workspace/hw1/mux_2_1.v}
vlog -vlog01compat -work work +incdir+D:/altera/13.1/workspace/hw1 {D:/altera/13.1/workspace/hw1/mux_4_1.v}
vlog -vlog01compat -work work +incdir+D:/altera/13.1/workspace/hw1 {D:/altera/13.1/workspace/hw1/likeALU.v}

