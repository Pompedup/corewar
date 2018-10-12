.name		"test_lldi"
.comment	"test_lldi"

{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}
# T_REG r_
# T_DIR %_
# T_IND _

#		a decommenter selon les envies
#___________________________________________________________________
#{T_REG , T_DIR, T_REG} -> 64  size  process->pc += 6;
#___________________________________________________________________
#{T_REG, T_REG, T_REG} -> 54  size  process->pc += 5;
#___________________________________________________________________
#{T_DIR , T_DIR , T_REG} -> A4  size  process->pc += 7;
#___________________________________________________________________
#{T_DIR, T_REG, T_REG} -> 94  size  process->pc += 6;
#___________________________________________________________________
#{T_IND, T_DIR, T_REG} -> E4  size  process->pc += 7;
#___________________________________________________________________
#{T_IND, T_REG, T_REG} -> D4  size  process->pc += 6;
