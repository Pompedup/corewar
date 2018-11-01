.name "Test pour valeur carry"
.comment ""

ld		%0, r2
ld		%0, r3
ld		%50, r4
#st		r3, r2
sti		r3, r2, r6
zjmp	%100
