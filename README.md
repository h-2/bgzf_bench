# Benchmark of BGZF implementations

This repository provides a small benchmark of different library implementations of the blocked GZip compression format.

## Decoding

### Setup

* Input file: [ALL.chr20.phase3_shapeit2_mvncall_integrated_v5a.20130502.genotypes.vcf.gz](http://hgdownload.cse.ucsc.edu/gbdb/hg19/1000Genomes/phase3/ALL.chr20.phase3_shapeit2_mvncall_integrated_v5a.20130502.genotypes.vcf.gz)
* Hardware: Thinkpad T14s, AMD Ryzen 7 PRO 4750U, WDC SN730
* The file is given as argument and the output is piped to `/dev/null`.
* Results are median out of three.
* "SeqAn2 4x" is the `seqan2_4threads` binary.
* "b.i.o. 4x" is the `bio` binary with `4` as second argument.

### Results

| Implementation | wallclock time | max RSS | % CPU |
|----------------|---------------:|--------:|------:|
| htslib         |         24.0s  |   3.5MB |   99% |
| ShrinkWrap     |         22.7s  |   2.9MB |   99% |
| SeqAn2         |         23.6s  |   3.8MB |  112% |
| b.i.o          |         22.6s  |   5.3MB |   99% |
| SeqAn2 4x      |          8.1s  |   5.9MB |  316% |
| b.i.o. 4x      |          8.1s  |   6.8MB |  317% |

### Observations

* The single-threaded implementations are quite similar in performance.
* C++ "iostream" based implementations are not slower than htslib!
* SeqAn2 single-threaded spawns two threads and thus uses more CPU than requested.
* The multi-threaded options provide noticeable speed-up.
* The multi-threaded options can't saturate their four threads. Using 5 threads instead of 4, reduces runtime to 6.3s and increases CPU usage to 417%.

## Encoding

TODO
