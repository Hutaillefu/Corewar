verb="-1"
stop="0"
d=""
cycle="-1"
GooD="0"
False="0"

if [ -f zaz_res ]; then
    rm -f zaz_res
fi
if [ -f grp_res ]; then
    rm -f grp_res
fi

for corfile in chmps/*.cor; do

    for corfile_2 in chmps/*.cor; do

        if [ $# -ge 1 ] && [ $# -le 2 ]; then
            
            if [ -f $1 ]; then
                corfile="$1"
                stop="1"
            elif [ $1 -ge "1" ] && [ $1 -le "31" ]; then
                verb="$1"
            else
                break
            fi
            
            if [ $# -ge 2 ]; then
                
                if [ -f $2 ]; then
                    corfile_2="$2"
                    stop="2"
                
                elif [ $# == 2 ] && [ $2 = "-d" ]; then
                    cycle="1000"
                    d="-d"

                elif [ $2 -ge "1" ] && [ $2 -le "31" ]; then
                    if [ $verb = "-1" ]; then
                        verb="$2"
                    else
                        echo "Usage: ./tester.sh *.cor X [1 - 31]"
                        break
                    fi
                
                else
                    break
                fi
            fi

        elif [ $# -ge 3 ]; then
            echo "Usage: ./tester.sh *.cor X [1 - 31]"
            break
        fi

        if [ $verb = "-1" ]; then
            verb="31"
        fi

        echo "Verbose is \033[7m$verb\033[0m !"
        echo "Corefile is \033[7m$corfile\033[0m !"

        for i in {1..ch28}; do
            
            if [ $cycle -ge 0 ]; then
                y=$(($cycle * $i))
            fi
            
            echo "\033[44;1m./zaz_cor/$corfile $corfile_2\033[0m"
            ./zaz_cor $corfile $corfile_2 $d $y -v $verb | cat -e > zaz_res
            echo "\033[46;1m./grp_cor/$corfile $corfile_2\033[0m"
            ./grp_cor $corfile $corfile_2 $d $y -v $verb | cat -e > grp_res

            res=$(diff zaz_res grp_res -q)

            if [ "$res" = "" ]; then
                if [ $cycle -ge 0 ]; then
                    echo "\033[32m$corfile $corfile_2 OK at cycle $y !\033[0m"
                else
                    echo "\033[32m$corfile $corfile_2 FINISH !\033[0m"
                    GooD=$(($GooD+1))
                fi
            else
                echo "\033[31m$corfile $corfile_2 KO at cycle $y !\033[0m"
                False=$(($False+1))
            fi
            
            if [ $cycle = "-1" ]; then
                break
            fi
        
        done
        
        if [ $stop = "2" ]; then
            break
        fi
    done
    if [ $stop = "1" ] || [ $stop = "2" ]; then
        break
    fi
done

echo "Success: $GooD"
echo "Fail: $False"