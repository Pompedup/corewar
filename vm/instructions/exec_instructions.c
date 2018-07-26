

#include "op.h"

/*
** pour connaitre le type de notre argument on a 1 octet qui nous indique :
** si l'arg et un registre -> 01
** si l'arg et un direct -> 10
** si l'arg et un indirect -> 11
** ex : r2,23,%34 donne l’octet de codage 0b 01 11 10 00, soit 0x78
**                                           re id di les 2 derniers bits tjr a 00
*/


t_func instruction_tab[] =
{
	{&live, 0x01}, {&ld, 0x02}, {&st, 0x03}, {&add, 0x04}, {&sub, 0x05},
	{&and, 0x06}, {&or, 0x07}, {&xor, 0x08}, {&zjmp, 0x09}, {&ldi, 0x0a},
	{&sti, 0x0b}, {&fork, 0x0c}, {&lld, 0x0d}, {&lldi, 0x0e}, {&lfork, 0x0f},
	{&aff, 0x010}, {NULL, 0}
}