.name		"test_and"
.comment	"test_and"


#label_1:
#
#ld      %10, r2
#ld      %8, r4
#ld      %6, r3
#ld      %4278322192, r5
#and     r2, r4, r16
#st      r5, -4
#fork    %:label_1

label_0:  
ld      %4278322192, r5 #==> FF
ld      %132112, r5
ld      %4093772816, r5 #==> f4
label_1:
ld      %10, r2
ld      %8, r4
ld      %6, r3
and     r2, r4, r16
fork    %:label_1
ld      %10, r2
ld      %8, r4
ld      %6, r3
st      r5, -28




# le champion mat contre le champion slider 
#zaz fini en 8966 tour
# nous on fini en 6094 tour :s a verifier!!!!