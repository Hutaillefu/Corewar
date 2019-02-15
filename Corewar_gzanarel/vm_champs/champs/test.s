.name "Tching tching(Intercepteur), Bouh!Bouh!(bruits d'anti-jeu)"
.comment ""

	sti r1,%7,%1
	live %1
	fork %-12
	add r2,r1,r3
	zjmp %20
