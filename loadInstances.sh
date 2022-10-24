for VARIABLE in 1 2 3 4 5 6 7 8 9
do
    echo "test"$VARIABLE".txt"
    cat "$PWD/test$VARIABLE.txt" | "./build/Debug/outDebug.exe"
    echo
done

read -p "Press enter to continue"