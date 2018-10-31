.name		"test_fork"
.comment	"test_fork"

#{T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}
# T_REG r_
# T_DIR %_
# T_IND _

#		a decommenter selon les envies
#{"fork",  1, {T_DIR}, 12, 800,	 "fork", 0, 1},
#___________________________________________________________________
	fork	%5
	fork	%:voir

	voir:	fork %-8987

	#etiquette: etiquette #(voir comment les labels fonctionnent si en boucle)
