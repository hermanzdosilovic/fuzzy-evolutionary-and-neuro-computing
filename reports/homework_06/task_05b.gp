set grid
set title "Naučene funkcije pripadnosti stohastičkim gradijentnim spustom (η = 1e-3)"
set xlabel "x"
set ylabel "μ(x)"
set terminal png size 1366,768
set output "task_05b.png"
plot 1/(1+exp(-1.44342*(x-1.203))) title "μA1(x)", \
     1/(1+exp(0.735661*(x-4.8034))) title "μB1(x)", \
     1/(1+exp(1.02994*(x-0.700765))) title "μA2(x)", \
     1/(1+exp(-13.8906*(x+0.431555))) title "μB2(x)", \
     1/(1+exp(-1.96622*(x+0.71428))) title "μA3(x)", \
     1/(1+exp(-0.606202*(x+5.46956))) title "μB3(x)", \
     1/(1+exp(0.928933*(x+2.77493))) title "μA4(x)", \
     1/(1+exp(2.29043*(x-4.45882))) title "μB4(x)"