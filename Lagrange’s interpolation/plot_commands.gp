set title 'Lagrange Interpolation'
set xlabel 'X'
set ylabel 'P(X)'
set grid
plot 'data.dat' with lines title 'Lagrange Polynomial', '-' with points pointtype 7 title 'Data Points'
3.000000 6.000000
5.000000 10.000000
6.000000 15.000000
e
pause -1
