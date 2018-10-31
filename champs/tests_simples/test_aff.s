.name		"test_aff"
.comment	"test_aff"

#{"aff",   1, {T_REG}, 16, 2, "aff", 1, 0},
#___________________________________________________________________
	ld	 %65, r3	#	'A'
	ld	%40, r6		#	'('
	aff		r3
	ld		%97, r3	#	'a'
	aff		r3
	aff r6
