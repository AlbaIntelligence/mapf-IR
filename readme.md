auto record by github actions
===
date: 2021-01-22-07-26-12

commit
```
commit 6ef57a251d2b4d542f86512baeb544c249d3db89
Author: Kei18 <keisuke.oku18@gmail.com>
Date:   Fri Jan 22 16:23:29 2021 +0900

    modify build systems

```

## sub-optimal solvers
benchmark: ./benchrmark/suboptimal_arena_300agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| PIBT | 1 | 16 | 12489 | 79 |
| HCA | 1 | 1219 | 10126 | 79 |
| WHCA | 1 | 724 | 11865 | 79 |
| RevisitPP | 1 | 2014 | 9603 | 79 |
| ECBS | 1 | 5649 | 9481 | 79 |
| PIBT_COMPLETE | 1 | 20 | 12489 | 79 |

## optimal solvers
benchmark: ./benchrmark/optimal_random-32-32-20_30agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| CBS | 1 | 17907 | 678 | 42 |
| ICBS | 1 | 108 | 678 | 42 |
