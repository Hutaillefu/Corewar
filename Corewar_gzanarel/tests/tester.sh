cycle=500

for corfile in ./*.cor; do

    for i in {1..50}; do

        y=$(($i * 500))
        echo $y
        ./zaz_cor $corfile -d $y -v 23 | tail -n +3 > zaz_res
        ./grp_cor $corfile -d $y | tail -n +2 > grp_res

        res=$(diff zaz_res grp_res -q)

        if [ "$res" = "" ]; then
            echo "$corfile OK"
        else
            echo "$corfile KO at cycle $y"
            break
        fi

    done

done