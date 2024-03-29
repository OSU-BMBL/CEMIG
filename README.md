# CEMIG (Cis rEgulatory Motif Influence using de Bruijn Graph)

## Overview

`CEMIG` is a new motif prediction algorithm which takes *k*-mer as the basic unit, finds motif seeds by introducing hash table and describing the relationship between *k*-mers constituting motif by using de Bruijn graph model, and then merges and extends among motif seeds, so as to more accurately predict the transcriptional motifs in ATAC-seq data.

![image](overview.jpg)

Figure showns the illustration of the `CEMIG` framework. 

(A) Determines the P-values of *k*-mer in background data utilizing Markov models. 

(B) Constructs Hamming distance graph ($G$) and DBG ($G_{DB}$) graphs using *k*-mer.

(C) Clusters *k*-mera on $G$ to form $G_C$, merging same-cluster *k*-mers from $G_{DB}$.

(D) Identifies motifs via path extension in $G_C$.

## How CEMIG works

`CEMIG` framework encompasses four stages:

### 1. *P*-value calculation for *k*-mers

Initially, `CEMIG` evaluates input sequences (footprints) to determine *k*-mer *P*-values using a Poisson distribution. This is informed by nucleotide frequencies estimated via zero to second-order Markov models.

### 2. Construction of hamming distance graph and de Bruijn graph

`CEMIG` constructs a Hamming distance graph ($G$) and a de Bruijn graph ($G_{DB}$) using *k*-mers. The *k*-mers are sorted by ascending *P*-values and classified into three tiers, which facilitates the construction of the Hamming distance graph and the $G_{DB}$.

### 3. Detection of *k*-mer clusters

`CEMIG` detects *k*-mer clusters through graph clustering on the Hamming distance graph and constructs a secondary directed graph (digraph) by amalgamating vertices from identical clusters in the $G_{DB}$.

### 4. Motif identification

`CEMIG` forecasts motifs and their respective lengths by extending paths within the digraph. It employs a greedy algorithm for path extension, starting with an ‘uncovered’ cluster vertex with the highest f(•) value and sequentially adding vertices from edges with maximum weight. This process continues until the path reaches the desired length or three *k*-mer vertices have been added in the same direction. The starting cluster and other cluster vertices on the path are then considered ‘covered’. `CEMIG` outputs the identified paths and iterates the procedure until all clusters are covered.

## Sequence set

The sequence set refers to the collection of DNA sequences that are used as input data for motif discovery algorithms. The sequence set is specifically derived from ChIP-seq data or ATAC-seq data. The ChIP-seq data usually includes a narrow peak file in `FASTA` format. For ATAC-seq data, either a narrow peak file or a footprint file in `FASTA` format is used as input for the `CEMIG` algorithm to identify DNA binding motifs.

## Installation

Enter the folder `code` and type `make` then the compiled codes are within the same directory as the source.

```
cd code/
make clean && make
```

## Motif prediction using CEMIG

```
cd code/
./cemig -i [INPUT_FILE]
```

For Example:

```
./cemig -i ../Example/test.fa
```

## Enrichment Score

We use the following algorithm to calculate the enrichment score for the motif found by `CEMIG`.

Step 1: Tecord the number of site occurrences of a motif in all sequences, for example 2000 times assuming a total of 10000 sequences.

Step 2: Use the PWM matrix of the modules found by `CMEIG` to score each site in the motif. Every site in motif that appears in any input sequence is recorded, and this step is repeated for all sites and the lowest score is recorded as the threshold.

Step 3: Randomly generates a background sequence of `100` based on the frequency of specific base pairs appearing in the input sequence; Using similar steps as in the first step, scan these background sequences based on motif's PWM. If the score of the fragments reaches or exceeds the threshold, it is considered that the background sequence contains the motif site. 

Step 4: Based on the steps below, the number of background sequences containing motif sites is obtained and based on both the number of motif sites in the original and background sequences. Enrichment score is defined as the number of motif sites in the original and background sequences and *P*-value was calculated using `Fisher`'s exact test. The following is a table for Fisher's exact test:

|   | Contain | Not contain | Row Total |
| ------------- | ------------- | ------------- | ------------- |
| Input Sequence  | a | b | a + b |
| Background Sequence  | c | d | c + d |
| Column Total  | a + c | b + d | a + b + c + d (=n) |

And *P*-value was calculated using `Fisher`'s exact test accompanied by the enrichment score:

$$p=\frac{\left(\begin{array}{c}a+b \\ a\end{array}\right)\left(\begin{array}{c}c+d \\ c\end{array}\right)}{\left(\begin{array}{c}n \\ a+c\end{array}\right)}=\frac{(a+b) !(c+d) !(a+c) !(b+d) !}{a ! b ! c ! d ! n !}$$

Both the enrichment scores and *P*-values will be output together with motif in the output file with `MEME` format.

## Parameters

| Option  | Parameter | Description | Default |
| ------------- | ------------- | ------------- | ------------- |
| -I  | `inputfile` | Specify input file. | The program uses input file with standard FASTA file format in default.|
| -O  | `outfile` | Specify the output file prefix name and location. | The program uses the input file path and prefix name as default values. |
| -P  | `paired-end` | Specify Whether the input data is paired-end. | This flag is set as `TRUE` in default. |
| -M | `maxmotifs` | Maximum number of output motifs. | The default number is `100`. |  
| -W | `Width` | Specify *k* value which determines the length of *k*-mer.  | The *k*-mer uses 6-mer in default. This parameter is not recommended to be modified. |
| -G | `gap` | The maximum number of gaps allowed for the cluster to extend on the path. | The default number is `6`. |  

## Citation
Any questions, problems, bugs are welcome and should be dumped to
Cankun Wang <cankun.wang@osumc.edu>.
