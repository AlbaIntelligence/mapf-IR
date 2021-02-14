auto record by github actions
===
date: 2021-02-14-10-37-36

commit
```
commit f6dd419ff2ceeb5367a11621bdcb1a373b3838c0
Author: Kei18 <keisuke.oku18@gmail.com>
Date:   Sun Feb 14 19:35:13 2021 +0900

    delete redundant functions on LibCBS

```

## sub-optimal solvers
benchmark: ./benchrmark/suboptimal_den520d_300agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| PIBT | 1 | 230 | 58574 | 386 |
| winPIBT | 1 | 379 | 58117 | 388 |
| PushAndSwap | 1 | 330 | 10965159 | 54639 |
| HCA | 1 | 767 | 54784 | 386 |
| WHCA | 1 | 527 | 56588 | 386 |
| RevisitPP | 1 | 723 | 54725 | 392 |
| ECBS | 1 | 9647 | 54666 | 389 |
| PIBT_COMPLETE | 1 | 276 | 58574 | 386 |

## optimal solvers
benchmark: ./benchrmark/optimal_random-32-32-20_30agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| CBS | 1 | 19471 | 678 | 42 |
| ICBS | 1 | 65 | 678 | 42 |

## anytime solvers
benchmark: ./benchrmark/anytime_arena_300agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| IR | 1 | 10006 | 11151 | 79 |
| IR_SINGLE_PATHS | 1 | 550 | 11726 | 79 |
| IR_FIX_AT_GOALS | 1 | 203 | 11359 | 79 |
| IR_FOCUS_GOALS | 1 | 10001 | 9387 | 79 |
| IR_MDD | 1 | 10010 | 12304 | 79 |
| IR_BOTTLENECK | 1 | 10029 | 12426 | 79 |
| IR_HYBRID | 1 | 10001 | 9389 | 79 |
