.name		"test_ldi"
.comment	"test_ldi"

{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}
# T_REG r_
# T_DIR %_
# T_IND _

# 2 index et 1 registre, additionne les 2 premiers,
# traite ca comme une adresse,
# y lit une valeur de la taille d’un registre et la met dans le 3eme.
# modifie le carry

#		a decommenter selon les envies
#___________________________________________________________________
#{T_REG , T_DIR, T_REG} -> 64  size  process->pc += 6;
	ld %1 r2			# 0000 0001
	ldi r2, %5, r10		# 0000 0001 + 0000 0101 = 0000 0110 (6)
	st r10, 5			#le resultat doit etre PC + 5 (0000 0110)

#___________________________________________________________________
#{T_REG, T_REG, T_REG} -> 54  size  process->pc += 5;
	ld %1 r2			# 0000 0001
	ld %1 r3			# 0000 0001
	ldi r2, r3, r10		# 0000 0001 + 0000 0001 = 0000 0010 (2)
	st r10, 5			#le resultat doit etre PC + 5 0000 0010 (2)

#___________________________________________________________________
#{T_DIR , T_DIR , T_REG} -> A4  size  process->pc += 7;
	ldi %2, %5, r10		# 0000 0010 + 0000 0101 = 0000 0111 (7)
	st r10, 5			#le resultat doit etre PC + 5 (0000 0111)

#___________________________________________________________________
#{T_DIR, T_REG, T_REG} -> 94  size  process->pc += 6;
	ld %1 r2			# 0000 0001
	ldi %5, r2, r10		# 0000 0001 + 0000 0101 = 0000 0110 (6)
	st r10, 5			#le resultat doit etre PC + 5 (0000 0111)
	zjmp %-100

#___________________________________________________________________
#{T_IND, T_DIR, T_REG} -> E4  size  process->pc += 7;
	ldi 2, %5, r10		# 0000 0010 + 0000 0101 = 0000 0111 (7)
	st r10, 5			#le resultat doit etre PC + 5 (0000 0111)

#___________________________________________________________________
#{T_IND, T_REG, T_REG} -> D4  size  process->pc += 6;
	ld %1 r2			# 0000 0001
	ldi 5, r2, r10		# 0000 0001 + 0000 0101 = 0000 0110 (6)
	st r10, 5			#le resultat doit etre PC + 5 (0000 0111)
	zjmp %-100
