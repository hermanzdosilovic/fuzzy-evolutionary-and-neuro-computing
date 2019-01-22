set grid
set title "Odstupanje naučene funkcije i uzoraka za učenje za sustav s jednim pravilom"
set xlabel "x"
set ylabel "y"
set zlabel "z"
set view 45,45
set terminal png size 1366,768
set output "task_04d.png"
splot [-4:4] [-4:4] "task_04_gd_1_e.txt"  title "gradijentni spust (η = 1e-5)", \
                    "task_04_ogd_1_e.txt" title "stohastički gradijentni spust (η = 1e-5)"