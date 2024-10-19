set title 'Lagrange Interpolation'
set xlabel 'X'
set ylabel 'P(X)'
set grid
plot 'data.dat' with lines title 'Lagrange Polynomial', '-' with points pointtype 7 title 'Data Points'
0.000000 2.000000
1.000000 4.000000
3.000000 10.000000
6.000000 18.000000
e
pause -1
