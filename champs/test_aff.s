.name "test_aff"
.comment "pour s'assurer que aff active le carry"

ld	%0,r9
aff r9
zjmp %-56
