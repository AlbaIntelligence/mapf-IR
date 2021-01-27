auto record by github actions
===
date: 2021-01-27-03-15-29

commit
```
commit 707bfc2b554258eb8446499591692649dc4d9dee
Author: Kei18 <keisuke.oku18@gmail.com>
Date:   Wed Jan 27 12:11:57 2021 +0900

    add instances

```

## sub-optimal solvers
benchmark: ./benchrmark/suboptimal_den520d_300agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| PIBT | 1 | 286 | 58791 | 386 |
| HCA | 1 | 3966 | 54784 | 386 |
| WHCA | 1 | 2294 | 56589 | 386 |
| RevisitPP | 1 | 4363 | 54725 | 392 |
| ECBS | 1 | 15023 | 54669 | 389 |
| PIBT_COMPLETE | 1 | 373 | 58791 | 386 |

## optimal solvers
benchmark: ./benchrmark/optimal_random-32-32-20_30agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| CBS | 1 | 24964 | 678 | 42 |
| ICBS | 1 | 78 | 678 | 42 |

## anytime solvers
benchmark: ./benchrmark/anytime_arena_300agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| IR | 1 | 10006 | 10946 | 79 |
| IR_SINGLE_PATHS | 1 | 2238 | 11451 | 79 |
| IR_FIX_AT_GOALS | 1 | 4213 | 11506 | 79 |
| IR_FOCUS_GOALS | 1 | 10006 | 9391 | 79 |
| IR_MDD | 1 | 10005 | 12321 | 79 |
| IR_BOTTLENECK | 1 | 10332 | 12489 | 79 |
| IR_HYBRID | 1 | 10004 | 9435 | 79 |
