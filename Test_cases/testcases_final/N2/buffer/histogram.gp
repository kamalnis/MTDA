## histogram for L:16##
reset
set terminal postscript eps enhanced color font "Helvetica, 20"
set output 'waste/compare_d4_5.eps'
set border 15 front linetype 0 linewidth 0.5
set style fill transparent solid 0.7 noborder
set boxwidth 0.9
set key top right
#set bmargin 10 
set style histogram clustered gap 1 title offset character 0.5, 0.25, 0
set style data histograms
set style fill solid border -1
set xrange [-1:6]
set yrange [0:18]
set xtics ("2" 0,"3" 1,"4" 2,"5" 3,"6" 4,"7" 5) font ",14"
set ytics 1 font ",16"
#set xtic rotate by -45 scale 0
set ylabel "Wastage ({/Times-Italics n_W})" font ",20" offset 2, 1 
set xlabel "Number of Segments ({/Times-Italics N})" font ",20" offset 1.5,0.5
#set label "{/Times-Italics N}= 8" offset 2,19
set label "{/Times-Italics d}= 4" offset -2,19
#set label "{/Times-Italics {{/Symbol s}_i}^2}= 0.9" offset 5,17
#set label "{/Times-Italics d}= 4" offset 40,13.5
#set label "where, {/Times-Italics i}= 1, 2, 3" offset 10,12
#set label "{/Time-Italics Testcases}= 5000" offset 37,13.5
set label "{/Time-Italics S_n}=5" offset -2,20
set label "{/Time-Italics n_M}=1" offset -2,18
set datafile separator "\t"
plot 'final_d4_5.txt' u 9 title "FlospaD" lc rgb "red" lw 1,'final_d4_5.txt' u 10 title "MTDA" lc rgb "0xFF8C00" lw 1