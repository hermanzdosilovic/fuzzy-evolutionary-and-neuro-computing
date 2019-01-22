set grid
set title "Naučena funkcija s četiri pravila"
set xlabel "x"
set ylabel "y"
set zlabel "z"
set view 45,45
set terminal png size 1366,768
set output "task_04c.png"
splot [-4:4] [-4:4] "task_04_gd_4.txt"  title "gradijentni spust (η = 1e-5)", \
                    "task_04_ogd_4.txt" title "stohastički gradijentni spust (η = 1e-5)"