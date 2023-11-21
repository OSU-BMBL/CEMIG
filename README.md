# CEMIG (Cis rEgulatory Motif Influence using de Bruijn Graph)

## Overview

`CEMIG` is a new motif prediction algorithm which takes *k*-mer as the basic unit, finds motif seeds by introducing hash table and describing the relationship between *k*-mers constituting motif by using de Bruijn graph model, and then merges and extends among motif seeds, so as to more accurately predict the transcriptional motifs in ATAC-seq data.

![image](overview.jpg)

Figure showns the illustration of the `CEMIG` framework. 

(A) Determines the P-values of *k*-mer in background data utilizing Markov models. 

(B) Constructs Hamming distance graph ($G$) and DBG ($G_{DB}$) graphs using *k*-mer.

(C) Clusters *k*-mera on $G$ to form $G_C$, merging same-cluster *k*-mers from $G_{DB}$.

(D) Identifies motifs via path extension in $G_C$.

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

We use the following algorithm to calculate the enrich score for the motif found by `CEMIG`

Firstly, record the number of site occurrences of a motif in all sequences, for example: 2000 times (assuming a total of 10000 sequences).

Then, for each motif, use the PWM (position weight matrix) of the phantom to score each site and record the lowest score as the threshold.

Next, based on the frequency of specific base pairs appearing in the input sequence, a series of background sequences are randomly generated, with a quantity set to `100`; Scan these background sequences using the PWM of the phantom, and if the score of the fragments reaches or exceeds the threshold in step 2, it is considered that the background sequence contains the phantom site. Based on this, the number of background sequences containing motif sites is obtained.

Finally, based on the number of motif sites (2000 and 300) in the original and background sequences, Fisher's exact test was used to calculate *P*-value as the enrichment score.

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
