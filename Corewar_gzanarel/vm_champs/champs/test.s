.name "Tching tching(Intercepteur), Bouh!Bouh!(bruits d'anti-jeu)"
.comment ""

live1:	live %66
	sti r1,%:fork0,%1
fork0:	live %66
	fork %:numero1
numero1: live %66
	ld %3,r3
	ld %68436,r2
#	ldi %:live,%-2,r6
	ld %0,r5
	zjmp %:ready
ready:	sti r6,r3,%:ecriture

wait:	live %66
	zjmp %:ecriture

ecriture: zjmp %:wait
