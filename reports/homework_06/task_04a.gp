set grid
set title "Naučena funkcija s jednim pravilom"
set xlabel "x"
set ylabel "y"
set zlabel "z"
set view 45,45
set terminal png size 1366,768
set output "task_04a.png"
splot [-4:4] [-4:4] "task_04_gd_1.txt"  title "gradijentni spust (η = 1e-5)", \
                    "task_04_ogd_1.txt" title "stohastički gradijentni spust (η = 1e-5)"