set -x
mkdir -p rep
xi=(6 7 8 9 10 11 12)
omega=(2.0 2.0 2.0 2.0 2.5 3.0 3.0)

# this gives the example on choosing -xi and -omega.
for index in 0 1 2 3 4 5
do
    # train
    ../codes.skewness.rec/cli/SkewOPT -train net.txt  -save rep/skew.$index.rep -sample_times 10 -threads 8 -dimensions 64 -omega ${omega[$index]} -xi ${xi[$index]} -eta 3
done

