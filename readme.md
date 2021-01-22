auto record by github actions
===
date: 2021-01-22-06-53-18

commit
```
commit ba1fe7055502cdc03f1493ffa64511cba0d5cbdd
Author: Kei18 <keisuke.oku18@gmail.com>
Date:   Fri Jan 22 15:50:50 2021 +0900

    modify bugs

```

## sub-optimal solvers
benchmark: ./benchrmark/suboptimal_arena_300agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| PIBT | 1 | 14 | 12489 | 79 |
| HCA | 1 | 1089 | 10126 | 79 |
| WHCA | 1 | 646 | 11865 | 79 |
| RevisitPP | 1 | 1752 | 9603 | 79 |
| ECBS | 1 | 5021 | 9481 | 79 |
| PIBT_COMPLETE | 1 | 18 | 12489 | 79 |

## optimal solvers
benchmark: ./benchrmark/optimal_random-32-32-20_30agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| CBS | 1 | 16127 | 678 | 42 |
| ICBS | 1 | 98 | 678 | 42 |
