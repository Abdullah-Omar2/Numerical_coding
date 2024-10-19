set title 'Linear Curve Fitting'
set xlabel 'X'
set ylabel 'Y'
set grid
plot 'data.txt' with points pointtype 7 title 'Data Points', 4.500000 * x + -0.820000 with lines title 'Fitted Line'
pause -1
