set pm3d
set hidden3d
set grid
set title "Zadana funkcija"
set xlabel "x"
set ylabel "y"
set zlabel "z"
set view 45,45
set terminal png size 1366,768
set output "task_03.png"
splot [-4:4] [-4:4] ((x - 1)**2 + (y + 2)**2 - 5 * x * y + 3) * cos(x/5)**2 lw 2 title "f(x, y)" with lines