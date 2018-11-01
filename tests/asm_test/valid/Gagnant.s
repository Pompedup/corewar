.name		"Celebration Funebre v0.99pl42"
.comment	"Jour J"

		ld   %0,r3
label:		zjmp %:avantdebut

avantdebut:	sti   r1,%5,%1  # 		#7

		sub  r10,r3,r10		#5
		live %-1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
		live %1
level0:		fork %:level10
level11:	live %-1
		fork %:level111

level110:	live %-1
		ld   %-186, r14			#=$A-6-8
		ld   %0,r2
		zjmp  %:label

level10:	live %42
		fork %:level100
level101:	live %42

		ld   %-190, r14			#=$A-6-4
		ld   %0,r2
		zjmp %:label

level111:	live %42
		ld   %-182, r14			# $A -6 -12
		ld   %0,r2
		zjmp %:label

level100:	live %42
		ld   %-194, r14			# $A -6 -0
		ld   %0,r2			#
		zjmp %:label			#
