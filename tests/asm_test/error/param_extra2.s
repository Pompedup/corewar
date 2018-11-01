.name "zork"
.comment "just a basic living prog"

l2:
		sti r16,%:live,%1
		and r1,%0 aaa,r1
live:   live %1
		zjmp %:live
