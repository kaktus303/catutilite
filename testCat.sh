#!/bin/bash
s21_cat="./s21_cat"
testingText1="TestText1.txt"
testingText2="TestText2.txt"
testingText3="TestText3.txt"
catFile="catFile.txt"
s21_catFile="s21_catFile.txt"
log_memory="log_memory.txt"
log_program="log_program.txt"
touch "$catFile"
touch "$s21_catFile"
touch "$testingText1"
touch "$testingText2"
touch "$testingText3"
echo "" > "$log_memory"
echo "" > "$log_program"
echo -e "123   456\n\n789" > "$testingText1"
echo -e "two files\t   456\n\n\n\n\n789" > "$testingText2"
echo -e "\n\n\nthree\rs files\t\n \n   456\n\n\n\n\n789" > "$testingText3"
# "-E" "-v" "-b" "--number-nonblank" "-n" "--number" "-s" "--squeeze-blank" "-t" "-T"
ARGS=("-e" "-v" "-E" "-b" "--number-nonblank" "-n" "--number" "--squeeze-blank" "-s" "-t" "-T" "-ev" "-be" "-e --number-nonblank" "-en" "-es" "-et" "-eT" "-e -t" "-sn" "-bn")
cur=-1
count_complite=0
for ARGS in "${ARGS[@]}"; do
if [ -x "$s21_cat" ]; then
      "$s21_cat" $ARGS "$testingText1" "$testingText2" "$testingText3" > $s21_catFile
      "cat" $ARGS "$testingText1" "$testingText2" "$testingText3" > $catFile
      echo -e "\n\n\n\n\n Test $cur : \n " >> "$log_memory"
    valgrind --tool=memcheck --leak-check=yes $s21_cat "$ARGS" "$testingText1" "$testingText2" "$testingText3" >> "$log_memory" 2>&1
    ((cur+=1))

else
    echo "Файл $s21_cat не найден или у него нет прав на выполнение."
fi
echo -e "\n Test $cur : \n " >> "$log_program"
diff "$s21_catFile" "$catFile" >> "$log_program" 2>&1

if [ $? -eq 0 ]; then
    echo "Test $cur flags[$ARGS] COMPLITE."
        count_complite=$((count_complite+1))
else
    echo "Test $cur flags[$ARGS] ERROR."
fi
done

echo -e "\n All: \n Test program : $count_complite/"$((cur+1))
printf ' Test memory: %d/%d\n' $(grep -c "no leaks" $log_memory) $((cur+1))
printf ' Test ERROR SUMMARY: %d/%d\n' $(grep -c "0 errors from 0 contexts" $log_memory) $((cur+1))
rm -r TestText1.txt
rm -r TestText2.txt
rm -r TestText3.txt
rm -r $catFile
rm -r $s21_catFile

