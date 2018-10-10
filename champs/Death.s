.name "Death"
.comment "Fork"


	st	r1, 4
	st	r1, 4
	st	r1, 4
	st	r1, 4
	live	%-3
	live	%-3
	live	%-3
	live	%-3
	st	r1, :golive
	st	r1, :live
	xor	r2,r2,r2
	fork	%:f1
	ld	%-15, r3
	ld	%1, r4
loop:	add	r3, r4, r3
	zjmp	%:golive
	xor	r5, r5, r5
	zjmp	%:loop
golive:	live	%-3
	ld	%-25, r3
	ld	%1, r4
lock:	add	r3, r4, r3
	zjmp	%:nolock
	xor	r5, r5, r5
	zjmp	%:lock
nolock:
	xor	r1, r1, r1
	add	r1, r1, r1
live:	live	%-3


f1:	fork	%:f2
f2:	fork	%:f3
f3:	fork	%:f4
f4:	fork	%:f5
f5:	fork	%:f6
f6:	fork	%:f7
f7:	fork	%:f8
f8:	fork	%:f9
f9:	fork	%:f10
f10:
