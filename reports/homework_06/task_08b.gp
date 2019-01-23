set grid
set title "Pogreška koju sustav s četiri pravila radi nakon svake epohe"
set xlabel "epoha"
set ylabel "kvadratna pogreška"
set terminal png size 1366,768
set output "task_08b.png"
plot "task_08_ogd_4_e_1e-2.txt"  title "stohastički gradijentni spust (η = 1e-2)", \
     "task_08_ogd_4_e_1e-3.txt"  title "stohastički gradijentni spust (η = 1e-3)", \
     "task_08_ogd_4_e_1e-7.txt"  title "stohastički gradijentni spust (η = 1e-7)"