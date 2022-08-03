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
    print("act_kind")
    exit(1)

mp = {
    ACT.EAT: 'eat',
    ACT.SLEEP: 'sleep',
    ACT.THINK: 'think',
    ACT.GET_FORK: 'get_fork',
    ACT.DIE: 'die',
}

def check_philo(lines, target_id):
    prev_act_time = 0
    prev_eat_time = 0
    prev_act_kind = ACT.THINK
    target_eat_count = 0
    fork_count = 0
    after_die = False

    for strs in lines:
        if after_die:
            print("too long")
            exit(1)
        timestamp = int(strs[0])
        id = int(strs[1])
        if id != target_id:
            continue


        act_kind = get_act_kind(strs)

        if act_kind != ACT.DIE and timestamp - prev_eat_time > die:
            print("over time")
            exit(1)
        if act_kind == ACT.EAT:
            if prev_act_kind != ACT.GET_FORK or fork_count != 2:
                print("eat")
                exit(1)
            prev_eat_time = timestamp
            fork_count = 0
            target_eat_count += 1
        if act_kind == ACT.SLEEP:
            if prev_act_kind != ACT.EAT or timestamp - prev_act_time < eat:
                print("sleep")
                exit(1)
        if act_kind == ACT.THINK:
            if prev_act_kind != ACT.SLEEP or timestamp - prev_act_time < sleep:
                print("think")
                exit(1)
        if act_kind == ACT.GET_FORK:
            if prev_act_kind == ACT.THINK and fork_count == 0:
                fork_count = 1
            elif prev_act_kind == ACT.GET_FORK and fork_count == 1:
                fork_count = 2
            else:
                print("get_fork", fork_count, mp[prev_act_kind])
                exit(1)
        if act_kind == ACT.DIE:
            if die <= timestamp - prev_eat_time <= die + 10:
                after_die = True
            else:
                print("die")
                exit(1)
        prev_act_time = timestamp
        prev_act_kind = act_kind
    if not after_die and target_eat_count < eat_count:
        print(target_eat_count, '<', eat_count);
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
