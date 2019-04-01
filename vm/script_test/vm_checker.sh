verb="31";max="99";numb="0";d=""
stop="0"
y=""
count="0"
GooD="0";False="0";res="0"
lock_n="0";lock_m="0";lock_v="0"
corfile_1="";corfile_2="";corfile_3="";corfile_4=""


function rm_files {
    if [ -f zaz_res ]; then
    rm -f zaz_res
    fi
    if [ -f grp_res ]; then
        rm -f grp_res
    fi
}

function usage {
    echo "Usage:        ./tester.sh [*.cor ...] -d -n [1 - 4] -v [1 - 31] -m [1 - 99]"
    echo "              Verbose:    -v [1 - 31] by default 31"
    echo "              Dump:       -d (20.000 cycles)"
    echo "              Number:     Number of champions [1 - 4]"
    echo "              Max tests:  -m [1 - 99]"
}

function max_tests {
    if [ "$max" -ge "1" ] && [ "$count" -ge "$max" ]; then
        break
    fi
}

function parse_files {
    stop=$(($stop+1))
    numb=$(($numb+1))
    if [ "$i" == "1" ]; then
        corfile_1="$var"
    elif [ "$i" == "2" ]; then
        corfile_2="$var"
    elif [ "$i" == "3" ]; then
        corfile_3="$var"
    elif [ "$i" == "4" ]; then
        corfile_4="$var"
    fi
}

function parse {
    i="1"
    res="^[0-9]"
    for var in "$@" 
    do
        if [ -f "$var" ]; then
            parse_files
        elif [ "$var" = "-d" ]; then
            y="20000"
            d="-d"
        elif [ "$var" = "-v" ]; then
            lock_v="1"
        elif [ "$var" = "-n" ]; then
            lock_n="1"
        elif [ "$var" = "-m" ]; then
            lock_m="1"
        elif [ "$lock_v" == "1" ] && [ "$var" -ge 1 ] && [ "$var" -le 31 ]; then
            lock_v="0"
            verb="$var"
        elif [ "$lock_n" == "1" ] && [ "$var" -ge 1 ] && [ "$var" -le 4 ]; then
            lock_n="0"
            numb="$var"
        elif [ "$lock_m" == "1" ] && [ "$var" -ge 1 ] && [ "$var" -le 99 ]; then
            lock_m="0"
            max="$var"
        elif [ "$var" -ge "1" ] && [ "$var" -le "31" ]; then
            verb="$var"
        else
            usage
            exit
        fi
        i=$((i+1))
    done
}


function exec_cor {
    echo "\033[44;1m./zaz_cor $corfile_1 $corfile_2 $corfile_3 $corfile_4 running...\033[0m"
    ./zaz_cor $corfile_1 $corfile_2 $corfile_3 $corfile_4 $d $y -v $verb > zaz_res
    echo "\033[46;1m./grp_cor $corfile_1 $corfile_2 $corfile_3 $corfile_4 running...\033[0m"
    ./grp_cor $corfile_1 $corfile_2 $corfile_3 $corfile_4 $d $y -v $verb > grp_res
    
    res=$(diff zaz_res grp_res -q)

    if [ "$res" = "" ]; then
        echo "\033[32m$corfile_1 $corfile_2 $corfile_3 $corfile_4 FINISH !\033[0m"
        GooD=$((GooD+1))
    else
        echo "\033[31m$corfile_1 $corfile_2 $corfile_3 $corfile_4 KO at cycle $y !\033[0m"
        False=$((False+1))
    fi
    count=$((GooD+False))
}

function one {
    if [ "$corfile_1" != "" ]; then
        if [ "$numb" == "1" ]; then
            exec_cor
        else
            two
        fi
    else
        for corfile_1 in chmps/*.cor; do
            max_tests "$count" "$max"
            if [ "$numb" == "1" ]; then
                exec_cor
            else
                two
            fi
            if [ $stop -ge "1" ]; then
                break
            fi
        done
    fi
}

function two {
    if [ "$corfile_2" != "" ]; then
        if [ "$numb" == "2" ]; then
            exec_cor
        else
            three
        fi
    else
        for corfile_2 in chmps/*.cor; do
            max_tests "$count" "$max"
            if [ "$numb" == "2" ]; then
                exec_cor
            else
                three
            fi
            if [ "$stop" -ge "2" ]; then
                break
            fi
        done
    fi
}

function three {
    if [ "$corfile_3" != "" ]; then
        if [ "$numb" == "3" ]; then
            exec_cor
        else
            four
        fi
    else
        for corfile_3 in chmps/*.cor; do
            max_tests "$count" "$max"
            if [ "$numb" == "3" ]; then
                exec_cor
            else
                four
            fi
            if [ "$stop" -ge "3" ]; then
                break
            fi
        done
    fi
}

function four {
    if [ "$corfile_4" != "" ] && [ "$numb" == "4" ]; then
            exec_cor
    else
        for corfile_4 in chmps/*.cor; do
            max_tests "$count" "$max"
            exec_cor
        done
    fi
}

function result {
    res=$(($GooD+$False))

    printf "\n\033[7m--------------------------------\033[0m\n"
    printf "\033[7m| \033[32;21m     Success:    %02d/%02d      \033[0m\033[7m |\033[0m\n" $GooD $res
    printf "\033[7m| \033[31;21m     Fail:       %02d/%02d      \033[0m\033[7m |\033[0m\n" $False $res
    printf "\033[7m--------------------------------\033[0m\n"
}

function print_param {
    printf "\033[33m\nRunning checker with parameters: \n"
    printf "Verbose: %d | Number of chmps: %d | Nb_tests: %d\n\n\033[0m" $verb $numb $max
}

if [ "$#" -ge 1 ]; then
    rm_files
    parse "$@"
    if [ "$stop" -le "0" ] && [ "$numb" -le "0" ]; then
        usage
        exit
    elif [ "$numb" -ge 1 ] && [ "$numb" -ge "$stop" ]; then
        print_param
        one
    else
        print_param
        exec_cor
    fi
    result
else
    usage
    exit
fi
