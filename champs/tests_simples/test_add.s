.name		"test_add"
.comment	"test_add"

	ld %10, r3
	add  r1, r3, r10	#le resultat doit etre 11 (10 - (- 1))
	st   r10, 5
