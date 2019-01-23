set grid
set title "Naučene funkcije pripadnosti gradijentnim spustom (η = 1e-4)"
set xlabel "x"
set ylabel "μ(x)"
set terminal png size 1366,768
set output "task_05a.png"
plot 1/(1+exp(-0.667118*(x-4.62455))) title "μA1(x)", \
     1/(1+exp(-0.383362*(x+4.61003))) title "μB1(x)", \
     1/(1+exp(0.807828*(x-0.107014))) title "μA2(x)", \
     1/(1+exp(-0.230332*(x+4.9369))) title "μB2(x)", \
     1/(1+exp(-0.52292*(x+0.623015))) title "μA3(x)", \
     1/(1+exp(0.196327*(x-2.04179))) title "μB3(x)", \
     1/(1+exp(2.92841*(x+3.34851))) title "μA4(x)", \
     1/(1+exp(0.0748675*(x-0.221363))) title "μB4(x)"