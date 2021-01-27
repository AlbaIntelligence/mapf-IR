auto record by github actions
===
date: 2021-01-27-03-54-08

commit
```
commit da2d16a11c52b519c1c92f44f3ffc690e63b7952
Author: Kei18 <keisuke.oku18@gmail.com>
Date:   Wed Jan 27 12:51:03 2021 +0900

    add exp scripts

```

## sub-optimal solvers
benchmark: ./benchrmark/suboptimal_den520d_300agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| PIBT | 1 | 248 | 58791 | 386 |
| HCA | 1 | 3446 | 54784 | 386 |
| WHCA | 1 | 1964 | 56589 | 386 |
| RevisitPP | 1 | 3707 | 54725 | 392 |
| ECBS | 1 | 13247 | 54669 | 389 |
| PIBT_COMPLETE | 1 | 332 | 58791 | 386 |

## optimal solvers
benchmark: ./benchrmark/optimal_random-32-32-20_30agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| CBS | 1 | 22035 | 678 | 42 |
| ICBS | 1 | 66 | 678 | 42 |

## anytime solvers
benchmark: ./benchrmark/anytime_arena_300agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| IR | 1 | 10005 | 10674 | 79 |
| IR_SINGLE_PATHS | 1 | 1900 | 11451 | 79 |
| IR_FIX_AT_GOALS | 1 | 3814 | 11506 | 79 |
| IR_FOCUS_GOALS | 1 | 10004 | 9379 | 79 |
| IR_MDD | 1 | 10015 | 12483 | 79 |
| IR_BOTTLENECK | 1 | 10436 | 12489 | 79 |
| IR_HYBRID | 1 | 10004 | 9388 | 79 |
