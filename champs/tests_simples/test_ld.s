.name		"test_ld"
.comment	"test_ld"

{T_DIR | T_IND, T_REG}
# T_REG r_
# T_DIR %_
# T_IND _

# modifie le carry

#		a decommenter selon les envies
#___________________________________________________________________
#{T_IND, T_REG} -> D0  size  process->pc += 7;
	ld 5, r5		#==>	carry = 0
	st   r5, 5
	zjmp	%-200	#ne doit pas bouger




#___________________________________________________________________
#{T_DIR, T_REG} -> 90  size  process->pc += 5;
	ld %26, r5			#26 = 0001 1010
	st   r5, 5

	ld %0, r5		#==>	carry = 1
	st   r5, 5
	zjmp	%-200	# doit bouger
