.name	"Booster !"
.comment "Alors la, si ca marche, trop content !  :)"

boost:	ld %12,r2
	ld %3,r3
	ld %4,r4
	ld %5,r7

	sti r1,%:live1,%1
live1:	live %66

	sti r1,%:wait,%1
	sti r1,%:master,%1
	sti r1,%:numero1,%1
	sti r1,%:numero2,%1

	sti r1,%:live,%-4
	ldi %:live,%-2,r6

master:	live %66
	ld %0,r3
	ld %16777216,r6
#	ldi %:master,%0,r6
	ld %0,r5
	zjmp %:ready

numero1: live %66
	ld %3,r3
	ld %68436,r2
#	ldi %:live,%-2,r6
	ld %0,r5
	zjmp %:ready

numero2: live %66
	ld %6,r3
	ld %1409680135,r6
#	ldi %:tampon,%1,r6
	ld %0,r5
	zjmp %:ready

tampon:	sti r6,r3,r5
live:	sti r1,r5,r5

ready:	sti r6,r3,%:ecriture

wait:	live %66
	zjmp %:ecriture

ecriture: zjmp %:wait



