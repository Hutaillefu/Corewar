cycle=500

for corfile in ./*.cor; do

    for i in {1..50}; do

        y=$(($i * 500))
        echo $y
        ./zaz_cor $corfile -d $y -v 31 | cat -e > zaz_res
        ./grp_cor $corfile -d $y -v 31 | cat -e > grp_res

        res=$(diff zaz_res grp_res -q)

        if [ "$res" = "" ]; then
            echo "$corfile OK"
        else
            echo "$corfile KO at cycle $y"
            break
        fi

    done

done