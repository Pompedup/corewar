.name "TEST"
.comment "commentaires pour test"

#lfork %5
sti r1, %5, %7
and 1, 2, r3
zjmp %106


##TEST POUR XOR AVEC IND
#xor r1, 0, r3
#aff r3
#doit affichier r3 = 0 car indirect 0 (=08) revient a r1 (num_player = 8)
# 0x08 ^ 0x08 = 0
# 0x08 ^ 0x07 = 1111 0xf
