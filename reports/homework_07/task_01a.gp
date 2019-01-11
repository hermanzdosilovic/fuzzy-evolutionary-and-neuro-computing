set grid
set title "Izlaz iz neurona tipa 1 sa jednim ulazom za w = 2"
set xlabel "x"
set ylabel "y"
set terminal png size 1366,768
set output "task_01a.png"
plot [-8:10] 1/(1+abs(x-2)/abs(1   )) lw 2 title "s = 1"   , \
             1/(1+abs(x-2)/abs(0.25)) lw 2 title "s = 0.25", \
             1/(1+abs(x-2)/abs(2   )) lw 2 title "s = 2"
