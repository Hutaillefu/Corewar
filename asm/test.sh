# Reset
Color_Off='\033[0m'       # Text Reset

# Regular Colors
Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
Yellow='\033[0;33m'       # Yellow

# Executables
myasm=asm
zazasm=ressources/vm_champs/asm

##	Creation repertoire

#	test/myasm 			= .cor de mon asm
#	test/myasm/dump		= hexdump de chaque .cor
#	test/zazasm 		= .cor de l'asm de zaz
#	test/zazasm/dump	= hexdump de chaque .cor
#	test/result			= sortie de chaque executable + valgrind
#	test/result/dump	= sortie du diff

mkdir -p test/{myasm,zazasm,result}/dump
make

for f in `find . -type f -name "*.s"`
do
	## Stocke le nom sans path ni extension
	file=`echo $f | rev | cut -d \/ -f 1 | cut -c 3- | rev`

	## Compile le champion avec l'asm de zaz et stocke la sortie dans un fichier
	./$zazasm $f >> test/result/$file
	if [ -f ${f%.s}.cor ]; then
		hexdump -Cv ${f%.s}.cor >> test/zazasm/dump/$file
		mv ${f%.s}.cor test/zazasm/
	fi

	## Compile le champion avec mon asm et stocke la sortie dans un fichier
	valgrind ./$myasm $f >> test/result/$file 2>&1
	if [ -f ${f%.s}.cor ]; then
		hexdump -Cv ${f%.s}.cor >> test/myasm/dump/$file
		mv ${f%.s}.cor test/myasm/
	fi

	## Test l'existence des 2 fichiers .cor puis fais un diff
	if [ -f test/zazasm/dump/$file ] && [ -f test/myasm/dump/$file ]; then
		diff test/zazasm/dump/$file test/myasm/dump/$file >> test/result/dump/$file
	fi

	## Compare les resultats
	if [ -f test/zazasm/${file}.cor ] && [ -f test/myasm/${file}.cor ]; then
		echo "${Green}$f ✅"
		head -n 15 test/result/$file | tail -2
	elif [ -f test/zazasm/${file}.cor ]; then
		echo "${Red}$f ❌"
		head -n 15 test/result/$file | tail -2
	else
		echo "${Yellow}$f ⚠️"
		head -n 15 test/result/$file | tail -2
	fi
	## Check les hexdump
	if [ -s test/result/dump/$file ]
	then
		echo "Dump : KO${Color_Off}"
	else
		echo "Dump : OK${Color_Off}"
	fi
	echo "==============================="

done