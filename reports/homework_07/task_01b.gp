set pm3d
set hidden3d
set title "Izlaz iz neurona tipa 1 sa dva ulaza za w = 2"
set xlabel "x"
set ylabel "y"
set zlabel "z"
set view 45,45
set terminal png size 1366,768
set output "task_01b.png"
splot [-8:10] [-8:10] 1/(1+abs(x-2)/1 + abs(y-2)/1 ) lw 2 title "s = 1" with lines
