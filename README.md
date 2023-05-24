# CEMIG (Cis rEgulatory Motif Influence using de Bruijn Graph)

CEMIG is a new motif prediction algorithm which takes k-mer as the basic unit, finds motif seeds by introducing hash table and describing the relationship between k-mers constituting motif by using de Bruijn graph model, and then merges and extends among motif seeds, so as to more accurately predict the transcriptional motifs in ATAC-seq data.

## Prerequisites and Dependencies

- C++11
- bedtools

## Motif Prediction

```
cd code/
./cemig -i test.fa
```

| Arguments                  | Description                                                               |
| -------------------------- | ------------------------------------------------------------------------- |
| --InputFile(-I)            | Input file with standard FASTA file format in default                     |
| --GenomeFile(-G)           | Genome files with standard FASTA file format                              |
| --OutFileNamePrefix(-O)    | Number of flanking base pairs at each side of peak summit (default is 50) |
| --Paired-end(-P)           | Whether the input data is paired-end (true in defalut)                    |
| --MaxMotifs                | Maximum number of output motifs (100 in default)                          |

## Citation
