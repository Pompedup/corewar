.name		"test_sub"
.comment	"test_sub"

	ld %10, r3
	sub  r1, r3, r10	#le resultat doit etre 11 (10 - (- 1))
	st   r10, 5
