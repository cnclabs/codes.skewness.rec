# Skewness Ranking Optimization for Personalized Recommendation (Skew-OPT)

## 1. Introduction
Skew-OPT framework is a ranking optimization criterion by utilizing the characteristics of skew normal distribution on personalized recommendation task, and this framework is published in UAI 2020.

In specific, without giving the restriction while generating the embedding distribution, the Skew-OPT framework provides an alternative optimization criterion on constraining the learned embedding distribution by leverages the characteristics of the skew normal distribution. Moreover, the learned embedding distribution under the Skew-OPT framework is proven to be beneficial to personalized recommendation task, whereas the further justification and theoretical analysis are provided in our paperwork.

### 1.1 Developed Environment
- g++ > 4.9 (In macOS, it needs OpenMP-enabled compilers. or try installing lateast version of gcc)

### 1.2 Compilation
```
$ git clone https://github.com/cnclabs/codes.skewness.rec.git
$ cd codes.skewness.rec
$ make
```

### 1.3 Task
Given a network input **net.txt**:
```txt
userA itemA 3
userA itemC 5
userB itemA 1
userB itemB 5
userC itemA 4
```

The model learns the representations of each vertex:
```
6 5
userA 0.0815412 0.0205459 0.288714 0.296497 0.394043
itemA -0.207083 -0.258583 0.233185 0.0959801 0.258183
itemC 0.0185886 0.138003 0.213609 0.276383 0.45732
userB -0.0137994 -0.227462 0.103224 -0.456051 0.389858
itemB -0.317921 -0.163652 0.103891 -0.449869 0.318225
userC -0.156576 -0.3505 0.213454 0.10476 0.259673
```

## 2. Usage
Directly call the execution file to see the usage like:

### 2.1 Run
```
./cli/SkewOPT  # for Skew-OPT
```
then you will see the options description like:

### 2.2 Parameters
```
[SkewOPT] command nerank interface for [SMORe](https://github.com/cnclabs/smore)

Options Description:
        -train <string>
            Train the Network data
        -save <string>
            Save the representation data
        -dimensions <int>
            Dimension of vertex representation; default is 64
        -sample_times <int>
            Number of training samples *Million; default is 10
        -threads <int>
            Number of training threads; default is 1
        -alpha <float>
            Init learning rate; default is 0.025
        -reg <float>
            Regularization term; default is 0.01
        -xi <float>
            Location parameter \xi for Skew-OPT
        -omega <float>j
            Scale parameter \omega for Skew-OPT
        -eta <int>
            Power parameter for Skew-OPT; this parameter must be an odd integer.

Usage:

[SkewOPT]
./SkewOPT -train input.txt -save rep/skew.rep -sample_times 10 -threads 4 -dimensions 64 -omega 11 -xi 3 -eta 3

```

### 2.3 Parameter tuning
We here suggest users to follow the tuning strategy under the following instruction:

- Large `-xi` is suggest to be with larger `-omega`. ( E.g. `-xi`= 11 with `-omega`= 3 )
- Small `-xi` is suggest to be with smaller `-omega`. ( E.g. `-xi`= 7 with `-omega`= 2 )
- Large `-eta` requires smaller `-reg` on training progress.


## 3. Citation
```
```


