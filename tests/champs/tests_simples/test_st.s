.name		"test_st"
.comment	"test_st"

{T_REG, T_IND | T_REG}
# T_REG r_
# T_IND _

#		a decommenter selon les envies
#___________________________________________________________________
#{T_REG, T_REG} -> 50  size  process->pc += 4;

#___________________________________________________________________
#{T_REG, T_IND} -> 70  size  process->pc += 5;
