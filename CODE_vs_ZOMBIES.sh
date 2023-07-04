# Save humans, destroy zombies!

declare -a humans
declare -a zombies
declare -i nearX=0
declare -i nearY=0


# game loop
while true; do
    read -r x y
    read -r humanCount

    for ((i = 0; i < 100; i++)); do
        humans[$i]="0 0 0"
    done

    for ((i = 0; i < 100; i++)); do
        zombies[$i]="0 0 0 0 0"
    done

    for (( i=0; i<humanCount; i++ )); do
        read -r humanId humanX humanY
        humans[$i]="$humanId $humanX $humanY"
        echo "human $humanId at ($humanX, $humanY)" >&2
    done
    read -r zombieCount
    for (( i=0; i<zombieCount; i++ )); do
        read -r zombieId zombieX zombieY zombieXNext zombieYNext
        zombies[$i]="$zombieId $zombieX $zombieY $zombieXNext $zombieYNext"
        echo "zombie $zombieId at ($zombieX, $zombieY) moving to ($zombieXNext, $zombieYNext)" >&2
    done

    # Write an action using echo
    # To debug: echo "Debug messages..." >&2

    distanceNearest=0
    distance=0
    
    for ((i = 0; i < 100; i++)); do
        creature="${humans[$i]}"

        if [[ $creature == "0 0 0" ]]; then
            break
        fi

        read -r pid px py <<<"$creature"
        echo "Player$pid: $px $py" >&2

        distanceZombieNearest=0
        distanceZombie=0


        for ((j = 0; j < 100; j++)); do
            creature="${zombies[$j]}"

            if [[ $creature == "0 0 0 0 0" ]]; then
                break
            fi

            read -r zid zx zy zxnext zynext <<<"$creature"
            echo "Zombie$zid: $zx $zy" >&2

            distanceZombie=$((($px - $zx) ** 2 + ($py - $zy) ** 2))
            if [[ $humanCount -lt 3 ]] && [[ $zombieCount -lt 3 ]]; then
                distanceZOmbie=$(echo "sqrt($distanceZombie)" | bc) #Time Out Risk
            fi
            echo "Distance between zombie $j and human $i is $distanceZombie" >&2

            if [[ $j == 0 || $distanceZombie -lt $distanceZombieNearest ]]; then
                distanceZombieNearest=$distanceZombie
            fi
        done

        distancePlayer=$((($x - $px) ** 2 + ($y - $py) ** 2))
        if [[ $humanCount -lt 3 ]] && [[ $zombieCount -lt 3 ]]; then
                distancePlayer=$(echo "sqrt($distancePlayer)" | bc) #Time Out Risk
        fi
        echo "Distance from Player$pid to human is $distancePlayer" >&2

        distance=$((distancePlayer - distanceZombieNearest))
        echo "Sum of Distance is $distance" >&2

        if [[ $i == 0 || $distance -lt $distanceNearest ]]; then
            distanceNearest=$distance
            nearX=$px
            nearY=$py
        fi
    done

    echo "$nearX $nearY" # Your destination coordinates
    
done
