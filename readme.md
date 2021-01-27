auto record by github actions
===
date: 2021-01-27-09-27-06

commit
```
commit d1eec566b447294e9bf959d193b9b946bc043c32
Author: Kei18 <keisuke.oku18@gmail.com>
Date:   Wed Jan 27 18:23:31 2021 +0900

    add slack notification

```

## sub-optimal solvers
benchmark: ./benchrmark/suboptimal_den520d_300agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| PIBT | 1 | 290 | 58791 | 386 |
| HCA | 1 | 3801 | 54784 | 386 |
| WHCA | 1 | 2207 | 56589 | 386 |
| RevisitPP | 1 | 4228 | 54725 | 392 |
| ECBS | 1 | 14913 | 54669 | 389 |
| PIBT_COMPLETE | 1 | 390 | 58791 | 386 |

## optimal solvers
benchmark: ./benchrmark/optimal_random-32-32-20_30agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| CBS | 1 | 24630 | 678 | 42 |
| ICBS | 1 | 71 | 678 | 42 |

## anytime solvers
benchmark: ./benchrmark/anytime_arena_300agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| IR | 1 | 10007 | 10881 | 79 |
| IR_SINGLE_PATHS | 1 | 2198 | 11451 | 79 |
| IR_FIX_AT_GOALS | 1 | 4066 | 11506 | 79 |
| IR_FOCUS_GOALS | 1 | 10001 | 9384 | 79 |
| IR_MDD | 1 | 10051 | 12449 | 79 |
| IR_BOTTLENECK | 1 | 10350 | 12489 | 79 |
| IR_HYBRID | 1 | 10009 | 9400 | 79 |
