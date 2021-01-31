auto record by github actions
===
date: 2021-01-31-09-52-09

commit
```
commit ffcbe7dab14d1418ddb67dc559169ba7a42a53c9
Author: Kei18 <keisuke.oku18@gmail.com>
Date:   Sun Jan 31 18:48:28 2021 +0900

    add header

```

## sub-optimal solvers
benchmark: ./benchrmark/suboptimal_den520d_300agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| PIBT | 1 | 288 | 58791 | 386 |
| PushAndSwap | 1 | 1171 | 1885902 | 8292 |
| HCA | 1 | 4328 | 54784 | 386 |
| WHCA | 1 | 2448 | 56589 | 386 |
| RevisitPP | 1 | 4712 | 54725 | 392 |
| ECBS | 1 | 18429 | 54669 | 389 |
| PIBT_COMPLETE | 1 | 327 | 58791 | 386 |

## optimal solvers
benchmark: ./benchrmark/optimal_random-32-32-20_30agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| CBS | 1 | 27084 | 678 | 42 |
| ICBS | 1 | 87 | 678 | 42 |

## anytime solvers
benchmark: ./benchrmark/anytime_arena_300agents.txt

|solver | solved | comp_time(ms) | sum-of-costs | makespan |
| ---: | ---: | ---: | ---: | ---: |
| IR | 1 | 10023 | 10870 | 79 |
| IR_SINGLE_PATHS | 1 | 2377 | 11451 | 79 |
| IR_FIX_AT_GOALS | 1 | 4320 | 11506 | 79 |
| IR_FOCUS_GOALS | 1 | 9914 | 9391 | 79 |
| IR_MDD | 1 | 10007 | 12449 | 79 |
| IR_BOTTLENECK | 1 | 10013 | 12489 | 79 |
| IR_HYBRID | 1 | 10005 | 9414 | 79 |
