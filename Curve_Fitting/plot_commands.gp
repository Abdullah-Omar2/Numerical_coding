set title 'Linear Curve Fitting'
set xlabel 'X'
set ylabel 'Y'
set grid
plot 'data.txt' with points pointtype 7 title 'Data Points', 1.520000 * x + 0.660000 with lines title 'Fitted Line'
pause -1
