.name		"test_add"
.comment	"test_add"

#modifie le carry
#{"add",   3, {T_REG, T_REG, T_REG}, 4, 10, 	"addition", 1, 0},
#___________________________________________________________________
	ld	 %10, r3
	add  r1, r3, r10	#le resultat doit etre 11 (10 - (- 1))
	live %-2
	st   r10, 5
	zjmp %100			#ne doit pas bouger

#___________________________________________________________________
	ld	 %0, r3
	ld	 %0, r2
	add  r2, r3, r10	#le resultat doit etre 0 ==> carry = 1
	st   r10, 5
	zjmp %-100			#revient en arriere de 100
