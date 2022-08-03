import sys
import enum
from time import time

filename = sys.argv[1]
philo_num = int(sys.argv[2])
die = int(sys.argv[3])
eat = int(sys.argv[4])
sleep = int(sys.argv[5])
eat_count = int(sys.argv[6])

class ACT:
    EAT = enum.auto()
    SLEEP = enum.auto()
    THINK = enum.auto()
    GET_FORK = enum.auto()
    DIE = enum.auto()

def get_act_kind(strs):
    if strs[2] == "is" and strs[3] == "eating":
        return ACT.EAT
    if strs[2] == "is" and strs[3] == "sleeping":
        return ACT.SLEEP
    if strs[2] == "is" and strs[3] == "thinking":
        return ACT.THINK
    if strs[2] == "has":
        return ACT.GET_FORK
    if strs[2] == "died":
        return ACT.DIE
    exit(1)

def check_philo(lines, target_id):
    prev_act_time = 0
    prev_eat_time = 0
    prev_act_kind = ACT.THINK
    target_eat_count = 0
    fork = 0

    for strs in lines:
        timestamp = int(strs[0])
        target_id = int(strs[1])
        if id != target_id:
            continue

        act_kind = get_act_kind(strs)
        if act_kind == ACT.EAT:
            if prev_act_kind != ACT.THINK \
                or fork != 2 \
                or timestamp - prev_eat_time > die:
                pass
                exit(1)
            prev_eat_time = timestamp
            fork = 0
            target_eat_count += 1
        if act_kind == ACT.SLEEP:
            if prev_act_kind != ACT.EAT \
                or timestamp - prev_eat_time > die \
                or timestamp - prev_act_time < eat:
                pass
                exit(1)
        if act_kind == ACT.THINK:
            if prev_act_kind != ACT.SLEEP \
                or timestamp - prev_eat_time > die \
                or timestamp - prev_act_time < sleep:
                pass
                exit(1)
        if act_kind == ACT.GET_FORK:
            if prev_act_kind == ACT.THINK and fork == 0 \
                or prev_act_kind == ACT.GET_FORK and fork == 1 :
                fork += 1
            else:
                pass
                exit(1)
        if act_kind == ACT.DIE:
            if die <= timestamp - prev_eat_time <= die + 10:
                pass
            else:
                pass
                exit(1)
        prev_act_time = timestamp
    if target_eat_count < eat_count:
        pass
        exit(1)

if __name__ == '__main__':
    lines = []
    with open(filename) as f:
        for line in f:
            strs = line.replace("\t", " ").split()
            lines.append(strs)
    
    for i in range(1, philo_num + 1):
        check_philo(lines, i)
    exit(0)
