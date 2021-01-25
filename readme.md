auto record by github actions
===
date: 2021-01-25-04-59-21

commit
```
commit 91364f666c679740a4418f601e3db7ba90954930
Author: Kei18 <keisuke.oku18@gmail.com>
Date:   Mon Jan 25 13:57:03 2021 +0900

    modify tests

```

## sub-optimal solvers
benchmark: ./benchrmark/suboptimal_arena_300agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| PIBT | 1 | 13 | 12489 | 79 |
| HCA | 1 | 1070 | 10126 | 79 |
| WHCA | 1 | 655 | 11865 | 79 |
| RevisitPP | 1 | 1782 | 9603 | 79 |
| ECBS | 1 | 5028 | 9481 | 79 |
| PIBT_COMPLETE | 1 | 21 | 12489 | 79 |

## optimal solvers
benchmark: ./benchrmark/optimal_random-32-32-20_30agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| CBS | 1 | 16147 | 678 | 42 |
| ICBS | 1 | 100 | 678 | 42 |

## anytime solvers
benchmark: ./benchrmark/anytime_arena_300agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| IR | 1 | 10005 | 10587 | 79 |
| IR_SINGLE_PATHS | 1 | 1762 | 11451 | 79 |
| IR_FIX_AT_GOALS | 1 | 3660 | 11506 | 79 |
| IR_FOCUS_GOALS | 1 | 9849 | 9388 | 79 |
| IR_MDD | 1 | 10014 | 12481 | 79 |
| IR_BOTTLENECK | 1 | 10008 | 12489 | 79 |
| IR_HYBRID | 1 | 10001 | 9405 | 79 |
