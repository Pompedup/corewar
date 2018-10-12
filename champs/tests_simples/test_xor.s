.name		"test_xor"
.comment	"test_xor"

#{T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}
# T_REG r_
# T_DIR %_
# T_IND _

#		a decommenter selon les envies
#{T_REG , T_REG , T_REG} -> 54  size  process->pc += 5;
#	ld %26, r3			#26 = 0001 1010
#	ld %21, r6			#21 = 0001 0101
#	or  r6, r3, r10	#le resultat doit etre 0001 0000 (16)
#	or  %4, %1, r11	#le resultat doit etre 0000 0000 (0) donc carry == 1

#{T_REG , T_IND, T_REG} -> 74  size  process->pc += 6;
#	ld %21, r6			#21 = 0001 0101 compare a 5 0000 0101
#	st   r10, 5

#___________________________________________________________________
#{T_REG, T_DIR, T_REG} -> 64 size  process->pc += 8;
	ld %21, r6			#21 = 0001 0101 compare a 4 0000 0100
	st   r10, 5

#___________________________________________________________________
#{T_DIR , T_REG, T_REG} -> 94  size  process->pc += 8;
	ld %21, r6			#21 = 0001 0101 compare a 4 0000 0100
	st   r10, 5

#___________________________________________________________________
#{T_DIR, T_IND , T_REG} -> B4  size  process->pc += 9;
	st   r10, 5


#___________________________________________________________________
#{T_DIR, T_DIR, T_REG} -> A4  size  process->pc += 11;
						#21 = 0001 0101 compare a 4 0000 0100
	and  %4, %21, r10	#le resultat doit etre 0000 0100 (4))
	st   r10, 5

#___________________________________________________________________
#{T_IND, T_REG, T_REG} ->D4  size  process->pc += 6;
	ld %21, r6			#21 = 0001 0101 compare a 5 0000 0100
	and  4, r6, r10		#le resultat doit etre 0000 0100 (4))
	st   r10, 5

#___________________________________________________________________
#{T_IND, T_IND, T_REG} -> F4  size  process->pc += 7;
						# 4 = 0000 0100 compare a 5 0000 0101
	and  4, 5, r10		#le resultat doit etre 0000 0100 (4))
	st   r10, 5

#___________________________________________________________________
#{T_IND, T_DIR, T_REG} -> E4  size  process->pc += 9;
						# 4 = 0000 0100 compare a 5 0000 0101
	and  4, %5, r10		#le resultat doit etre 0000 0100 (4))
	st   r10, 5
