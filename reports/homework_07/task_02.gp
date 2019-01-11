set terminal png size 1366,768
set output "task_02.png"
set title "Zadani skup podataka"
set xlabel "x"
set ylabel "y"
plot "../../files/homework_07/dataset.txt" using 1:($3==1?$2:1/0) pt 5 ps 2 title "A", \
     "../../files/homework_07/dataset.txt" using 1:($4==1?$2:1/0) pt 7 ps 2 title "B", \
     "../../files/homework_07/dataset.txt" using 1:($5==1?$2:1/0) pt 9 ps 2 title "C",

