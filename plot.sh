set view 60,330
set dgrid3d ,,3
splot [-4:4] [-4:4] 'trainingSet.txt' pt 7 ps 1 title 'Primjer za učenje' with lines, \
      'gd1.txt'  pt 7 ps 1 title 'Gradient Descent for 1 rule'  with lines, \
      'gd2.txt'  pt 7 ps 1 title 'Gradient Descent for 2 rules' with lines, \
      'gd4.txt'  pt 7 ps 1 title 'Gradient Descent for 4 rules' with lines

# splot [-4:4] [-4:4] 'trainingSet.txt' pt 7 ps 1 title 'Primjer za učenje', \
#       ((x - 1)**2 + (y + 2)**2 - 5 * x * y + 3) * cos(x/5)**2 lc rgb '#0000ff' title 'Zadana funkcija', \
#       'ogd1.txt' pt 7 ps 1 title 'Online Gradient Descent for 1 rule', \
#       'ogd2.txt' pt 7 ps 1 title 'Online Gradient Descent for 2 rules', \
#       'ogd4.txt' pt 7 ps 1 title 'Online Gradient Descent for 4 rules',
