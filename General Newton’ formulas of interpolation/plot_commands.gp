set title 'Newton Interpolation Polynomial'
set xlabel 'X'
set ylabel 'Y'
set grid
plot 'data.txt' with points pointtype 7 title 'Data Points', 'poly_data.txt' with lines title 'Interpolated Polynomial'
pause -1
