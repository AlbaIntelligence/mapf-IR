auto record by github actions
===
date: 2021-01-22-10-58-30

commit
```
commit 5526110275d92a5cc758ce24981b5a6f2a0fb3ab
Author: Kei18 <keisuke.oku18@gmail.com>
Date:   Fri Jan 22 19:54:26 2021 +0900

    refactoring

```

## sub-optimal solvers
benchmark: ./benchrmark/suboptimal_arena_300agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| PIBT | 1 | 15 | 12489 | 79 |
| HCA | 1 | 1254 | 10126 | 79 |
| WHCA | 1 | 757 | 11865 | 79 |
| RevisitPP | 1 | 1984 | 9603 | 79 |
| ECBS | 1 | 5603 | 9481 | 79 |
| PIBT_COMPLETE | 1 | 23 | 12489 | 79 |

## optimal solvers
benchmark: ./benchrmark/optimal_random-32-32-20_30agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| CBS | 1 | 18759 | 678 | 42 |
| ICBS | 1 | 111 | 678 | 42 |

## anytime solvers
benchmark: ./benchrmark/anytime_arena_300agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| IR | 1 | 10009 | 10781 | 79 |
| IR_SINGLE_PATHS | 1 | 2135 | 11451 | 79 |
| IR_FIX_AT_GOALS | 1 | 4028 | 11506 | 79 |
| IR_FOCUS_GOALS | 1 | 10003 | 9389 | 79 |
| IR_MDD | 1 | 10010 | 12449 | 79 |
| IR_BOTTLENECK | 1 | 10429 | 12489 | 79 |
| IR_HYBRID | 1 | 10004 | 9986 | 79 |
