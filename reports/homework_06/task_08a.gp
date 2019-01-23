set grid
set title "Pogreška koju sustav s četiri pravila radi nakon svake epohe"
set xlabel "epoha"
set ylabel "kvadratna pogreška"
set terminal png size 1366,768
set output "task_08a.png"
plot "task_08_gd_4_e_3e-3.txt"  title "gradijentni spust (η = 3e-3)", \
     "task_08_gd_4_e_1e-4.txt"  title "gradijentni spust (η = 1e-4)", \
     "task_08_gd_4_e_1e-8.txt"  title "gradijentni spust (η = 1e-8)"