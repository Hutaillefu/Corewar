cycle=500

./zaz_cor helltrain.cor -d $cycle -v 23 | tail -n +3 > zaz_res
./grp_cor helltrain.cor -d $cycle | tail -n +2 > grp_res

res=$(diff zaz_res grp_res -q)

if [ "$res" = "" ]; then
    echo "OK"
else
    echo "KO"
fi

for each corfile in ./*.cor do
    echo "$corfile"
done