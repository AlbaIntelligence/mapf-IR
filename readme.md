auto record by github actions
===
date: 2021-02-14-07-04-47

commit
```
commit a9db54a28b142b4f7542e869084465f9df716aff
Author: Kei18 <keisuke.oku18@gmail.com>
Date:   Sun Feb 14 16:01:41 2021 +0900

    update solver

```

## sub-optimal solvers
benchmark: ./benchrmark/suboptimal_den520d_300agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| PIBT | 1 | 253 | 58574 | 386 |
| winPIBT | 1 | 421 | 58117 | 388 |
| PushAndSwap | 1 | 352 | 10965159 | 54639 |
| HCA | 1 | 934 | 54784 | 386 |
| WHCA | 1 | 588 | 56588 | 386 |
| RevisitPP | 1 | 893 | 54725 | 392 |
| ECBS | 1 | 10541 | 54666 | 389 |
| PIBT_COMPLETE | 1 | 298 | 58574 | 386 |

## optimal solvers
benchmark: ./benchrmark/optimal_random-32-32-20_30agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| CBS | 1 | 24300 | 678 | 42 |
| ICBS | 1 | 76 | 678 | 42 |

## anytime solvers
benchmark: ./benchrmark/anytime_arena_300agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| IR | 1 | 10003 | 10832 | 79 |
| IR_SINGLE_PATHS | 1 | 750 | 11726 | 79 |
| IR_FIX_AT_GOALS | 1 | 275 | 11359 | 79 |
| IR_FOCUS_GOALS | 1 | 10002 | 9390 | 79 |
| IR_MDD | 1 | 10003 | 12190 | 79 |
| IR_BOTTLENECK | 1 | 10009 | 12426 | 79 |
| IR_HYBRID | 1 | 10005 | 9391 | 79 |
