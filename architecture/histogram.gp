## histogram for L:16##
reset
set terminal postscript eps enhanced color font "Helvetica, 24"
set output 'mixer_diff_parameters.eps'
set border 15 front linetype 0 linewidth 0.5
set style fill transparent solid 0.7 noborder
set boxwidth 0.9
set key box
set key top right
#set bmargin 10 
set style histogram clustered gap 1 title offset character 0.5, 0.25, 0
set style data histograms
set style fill solid border -1
set xrange [-1:9]
set yrange [0:3000]
set xtics ("2" 0,"3" 1,"4" 2,"5" 3,"6" 4,"7" 5,"8" 6,"9" 7,"10" 8,"11" 9) font ",24"
set ytics 500 font ",24"
#set xtic rotate by -45 scale 0
set ylabel "# Testcases " font ",24" offset 2, 1 
set xlabel "# Segments ({/Times-Italics N})" font ",24" offset 1.5,0.5
set label "{/Times-Italics {/Symbol-Oblique h}} = 10" offset 0,20.5
set label "{/Times-Italics {/Symbol-Oblique a}_1} = 0.5, {/Times-Italics {/Symbol-Oblique a}_2} = 0.1" offset -3,15.5
set label "{/Times-Italics {/Symbol-Oblique a}_3} = 0.1, {/Times-Italics {/Symbol-Oblique a}_4} = 0.3" offset -3,14.5
#set label "{/Times-Italics {/Symbol a}_3} = 0.1" offset 0,13.5
#set label "{/Times-Italics {/Symbol a}_4} = 0.3" offset 0,12.5
set datafile separator " "
plot 'res_01.txt' u 2 title "{/Symbol-Oblique e} = 0.01" lc rgb "0xFFEE00" lw 1,'res_001.txt' u 2 title "{/Symbol-Oblique e} = 0.001" lc rgb "0xFF0000" lw 1,'res_0001.txt' u 2 title "{/Symbol-Oblique e} = 0.0001" lc rgb "0x000000" lw 1