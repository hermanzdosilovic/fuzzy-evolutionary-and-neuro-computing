set grid
set title "Pogreška koju sustav s četiri pravila radi nakon svake epohe"
set xlabel "epoha"
set ylabel "kvadratna pogreška"
set terminal png size 1366,768
set output "task_07.png"
plot "task_07_gd_4_e.txt"  title "gradijentni spust (η = 1e-5)", \
     "task_07_ogd_4_e.txt" title "stohastički gradijentni spust (η = 1e-5)"