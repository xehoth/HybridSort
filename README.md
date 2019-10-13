# HybridSort

[![Build status](https://ci.appveyor.com/api/projects/status/tur6g0hwvfv9qjj7?svg=true)](https://ci.appveyor.com/project/xehoth/learnopengl) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/79115a9a253a42c68da54e87ef2eda2a)](https://www.codacy.com/manual/xehoth/HybridSort?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=xehoth/HybridSort&amp;utm_campaign=Badge_Grade)

HybridSort is a combination of some sorting method, which performs better in sorting basic types than `std::sort`.  
We use dual-pivot quick sort, which is ported from java7 `Arrays.sort`, as the main sorting method.  
When the data size is extemely large, we use radix sort for integers.

## Example

``` cpp
#include <vector>
#include "HybridSort.hpp"

int main() {
    std::vector<int> a;
    // initialize a
    HybridSort::sort(a.begin(), a.end());
}
```

## Compile

``` bash
git clone https://github.com/xehoth/HybridSort.git
cd HybridSort
mkdir build && cd build
cmake ../ -DCMAKE_BUILD_TYPE=RELEASE
make
```

## Benchmarks

### Compile Benchmarks

You should install [google benchmark](https://github.com/google/benchmark) first.

``` bash
cmake ../ -DCMAKE_BUILD_TYPE=RELEASE -DBUILD_BENCHMARK=ON
```

Compared with `std::sort`.

### Random Int

``` plain
--------------------------------------------------------------
Benchmark                    Time             CPU   Iterations
--------------------------------------------------------------
hybridSort/1              4.31 ns         4.30 ns    160000000
hybridSort/2              5.29 ns         5.31 ns    100000000
hybridSort/4              6.80 ns         6.84 ns    112000000
hybridSort/8              17.2 ns         17.3 ns     40727273
hybridSort/16             51.0 ns         51.6 ns     10000000
hybridSort/32              158 ns          157 ns      4480000
hybridSort/64              312 ns          307 ns      2240000
hybridSort/128             781 ns          767 ns       896000
hybridSort/256            1594 ns         1604 ns       448000
hybridSort/512            4137 ns         4171 ns       172308
hybridSort/1024           8736 ns         8719 ns        89600
hybridSort/2048          20017 ns        20089 ns        24889
hybridSort/4096         120565 ns       122070 ns         6400
hybridSort/8192         270142 ns       272770 ns         2635
hybridSort/16384        605230 ns       599888 ns         1120
hybridSort/32768       1329081 ns      1339286 ns          560
hybridSort/65536       2885846 ns      2846928 ns          236
hybridSort/131072      6090210 ns      6138393 ns          112
hybridSort/262144     12911173 ns     13113839 ns           56
hybridSort/524288     27373756 ns     26875000 ns           25
hybridSort/1048576    57072400 ns     56818182 ns           11
hybridSort/2097152   123979150 ns    125000000 ns            6
hybridSort/4194304    92639983 ns     91145833 ns            6
hybridSort/8388608   220078133 ns    218750000 ns            3
hybridSort/10000000  247331000 ns    244791667 ns            3
stdSort/1                 4.99 ns         5.00 ns    100000000
stdSort/2                 7.65 ns         7.50 ns     89600000
stdSort/4                 9.28 ns         9.21 ns     74666667
stdSort/8                 22.3 ns         22.5 ns     32000000
stdSort/16                60.3 ns         61.4 ns     11200000
stdSort/32                 115 ns          115 ns      6400000
stdSort/64                 271 ns          270 ns      2488889
stdSort/128                716 ns          715 ns       896000
stdSort/256               1688 ns         1688 ns       407273
stdSort/512               4001 ns         3990 ns       172308
stdSort/1024              9389 ns         9417 ns        74667
stdSort/2048             49906 ns        50000 ns        10000
stdSort/4096            128534 ns       128691 ns         4978
stdSort/8192            280023 ns       276215 ns         2489
stdSort/16384           626390 ns       627790 ns         1120
stdSort/32768          1351722 ns      1349147 ns          498
stdSort/65536          2897666 ns      2846928 ns          236
stdSort/131072         6188406 ns      6277902 ns          112
stdSort/262144        13152636 ns     13125000 ns           50
stdSort/524288        27619100 ns     27644231 ns           26
stdSort/1048576       59024120 ns     59375000 ns           10
stdSort/2097152      122228733 ns    122395833 ns            6
stdSort/4194304      262480967 ns    260416667 ns            3
stdSort/8388608      551961100 ns    546875000 ns            1
stdSort/10000000     669224700 ns    671875000 ns            1
```

### Sorted Int

``` plain
--------------------------------------------------------------
Benchmark                    Time             CPU   Iterations
--------------------------------------------------------------
hybridSort/1              4.09 ns         4.08 ns    172307692
hybridSort/2              4.87 ns         4.88 ns    112000000
hybridSort/4              6.21 ns         6.28 ns    112000000
hybridSort/8              8.79 ns         8.79 ns     74666667
hybridSort/16             13.9 ns         13.8 ns     49777778
hybridSort/32             26.1 ns         26.1 ns     26352941
hybridSort/64             65.9 ns         67.0 ns     11200000
hybridSort/128             114 ns          112 ns      5600000
hybridSort/256             306 ns          307 ns      2240000
hybridSort/512             170 ns          169 ns      4072727
hybridSort/1024            320 ns          321 ns      2240000
hybridSort/2048            619 ns          614 ns      1120000
hybridSort/4096           1223 ns         1228 ns       560000
hybridSort/8192           2533 ns         2511 ns       280000
hybridSort/16384          5071 ns         5156 ns       100000
hybridSort/32768         10245 ns        10045 ns        74667
hybridSort/65536         20839 ns        20403 ns        34462
hybridSort/131072        60962 ns        59375 ns        10000
hybridSort/262144       123602 ns       122768 ns         5600
hybridSort/524288       251316 ns       251116 ns         2800
hybridSort/1048576      501126 ns       500000 ns         1000
hybridSort/2097152     1083558 ns      1074219 ns          640
hybridSort/4194304    93112833 ns     93750000 ns            6
hybridSort/8388608   220028433 ns    218750000 ns            3
hybridSort/10000000  253188133 ns    255208333 ns            3
stdSort/1                 4.95 ns         5.00 ns    100000000
stdSort/2                 6.34 ns         6.28 ns    112000000
stdSort/4                 8.60 ns         8.72 ns     89600000
stdSort/8                 12.8 ns         12.8 ns     56000000
stdSort/16                20.8 ns         20.9 ns     34461538
stdSort/32                57.9 ns         57.8 ns     10000000
stdSort/64                 170 ns          169 ns      4072727
stdSort/128                434 ns          430 ns      1600000
stdSort/256               1075 ns         1074 ns       640000
stdSort/512               2400 ns         2407 ns       298667
stdSort/1024              5303 ns         5301 ns       112000
stdSort/2048             11652 ns        11719 ns        64000
stdSort/4096             24938 ns        25112 ns        28000
stdSort/8192             53802 ns        53013 ns        11200
stdSort/16384           115038 ns       114397 ns         5600
stdSort/32768           245545 ns       245536 ns         2800
stdSort/65536           522381 ns       531250 ns         1000
stdSort/131072         1123240 ns      1123047 ns          640
stdSort/262144         2376015 ns      2343750 ns          280
stdSort/524288         4992900 ns      5000000 ns          100
stdSort/1048576       10551528 ns     10742188 ns           64
stdSort/2097152       22088522 ns     22460938 ns           32
stdSort/4194304       48933143 ns     47991071 ns           14
stdSort/8388608      100997700 ns     98958333 ns            6
stdSort/10000000     126863860 ns    125000000 ns            5
```
