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
