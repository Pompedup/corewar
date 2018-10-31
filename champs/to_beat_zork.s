.name "to_beat_zork"
.comment "ZORK WILL BE DEAD"

#strategie 1 atteindre l'emplacement de zork pour corrompre ses instructions
#strategie 2 instructions identiques et etre place en premier
#strategie 3 faire des loops en forkant pour faire le dernier live

		#strategie 1 echec j'arrive pas a me decaler jusqua zork
#________________________________________________________________________
#getting_to_zork1:	sti	r1, %256, %255
#getting_to_zork2:	sti	r1, %255, %:getting_to_zork1
#getting_to_zork3:	sti	r1, %255, %:getting_to_zork2
#
#					and r1, %0, r16			#resultat nul donc carry devient actif
#					zjmp %:getting_to_zork3

#lldi 	2048, %0, r2
#aff r2
#sti 	r2, %1, %1


		#strategie 2 copie colle exact de zork mais nul
#________________________________________________________________________
#l2:		sti r1, %:live, %1
#		and r1, %0, r1

#live:	live %1
#		zjmp %:live


		#strategie 3
#________________________________________________________________________
		and r1, %0, r16			#resultat nul donc carry devient actif
		and r1, %0, r16			#pour etre en decaler par rapport a zork
		fork %:troisieme_partie	#pour encadrer les lives de zork par nos lives

deuxieme_partie: 	sti r1, %:troisieme_partie, %1 #pour faire un live a notre numero de joueur

troisieme_partie: 	live %1
					zjmp %:troisieme_partie #pour boucler
