.name		"test_lld"
.comment	"test_lld"

{T_DIR | T_IND, T_REG}
# T_REG r_
# T_DIR %_

#		a decommenter selon les envies
#___________________________________________________________________
#{T_DIR, T_REG} -> 90  size  process->pc += 5;
	lld

#___________________________________________________________________
#{T_IND, T_REG} -> D0  size  process->pc += 7;
	lld
