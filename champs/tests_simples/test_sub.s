.name		"test_sub"
.comment	"test_sub"

#{"sub",   3, {T_REG, T_REG, T_REG}, 5, 10, 	"soustraction", 	1, 0},
#___________________________________________________________________
	ld %10, r3
	sub  r1, r3, r10	#le resultat doit etre 11 (10 - (- 1))
	st   r10, 5
