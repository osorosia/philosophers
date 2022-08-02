import sys
import enum

filename = sys.argv[1]
philo = int(sys.argv[2])
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
    if strs[0] == "is" and strs[1] == "eating":
        return ACT.EAT
    if strs[0] == "is" and strs[1] == "sleeping":
        return ACT.SLEEP
    if strs[0] == "is" and strs[1] == "thinking":
        return ACT.THINK
    if strs[0] == "has":
        return ACT.GET_FORK
    if strs[0] == "died":
        return ACT.DIE
    # print("error: unexpected output")
    exit(1)


dc = dict()
first_line = True
start_timestamp = 0
prev_timestamp = 0
last_timestamp = 0

with open(filename) as f:
    for line in f:
        strs = line.replace("\t", " ").split()

        timestamp = int(strs[0])
        last_timestamp = timestamp
        id = int(strs[1])
        act_kind = get_act_kind(strs[2:])
        
        if first_line:
            first_line = False
            start_timestamp = timestamp
            prev_timestamp = timestamp


        if id not in dc:
            dc[id] = {
                "prev_act": ACT.THINK,
                "prev_act_time": timestamp,
                "prev_eat_time": start_timestamp,
                "forks": 0,
                "eat_count": 0,
            }
        
        if prev_timestamp > timestamp:
            exit(1)
        
        # action ------------------------------------
        if act_kind == ACT.EAT:
            if dc[id]["prev_act"] != ACT.GET_FORK:
                exit(1)
            if dc[id]["forks"] != 2:
                exit(1)
            if dc[id]["prev_eat_time"] > die:
                exit(1)
            dc[id] = {
                "prev_act": act_kind,
                "prev_act_time": timestamp,
                "prev_eat_time": timestamp,
                "forks": 0,
                "eat_count": dc[id]["eat_count"] + 1,
            }
        
        if act_kind == ACT.SLEEP:
            if dc[id]["prev_act"] != ACT.EAT:
                exit(1)
            if timestamp - dc[id]["prev_act_time"] != eat:
                exit(1)
            dc[id] = {
                "prev_act": act_kind,
                "prev_act_time": dc[id]["prev_eat_time"],
                "prev_eat_time": timestamp,
                "forks": 0,
                "eat_count": dc[id]["eat_count"],
            }

        if act_kind == ACT.THINK:
            if dc[id]["prev_act"] != ACT.SLEEP:
                exit(1)
            if timestamp - dc[id]["prev_act_time"] != sleep:
                exit(1)
            dc[id] = {
                "prev_act": act_kind,
                "prev_act_time": timestamp,
                "prev_eat_time": dc[id]["prev_eat_time"],
                "forks": 0,
                "eat_count": dc[id]["eat_count"],
            }

        if act_kind == ACT.GET_FORK:
            if dc[id]["prev_act"] != ACT.THINK and dc[id]["prev_act"] != ACT.GET_FORK:
                exit(1)
            if dc[id]["forks"] >= 2:
                exit(1)
            dc[id] = {
                "prev_act": act_kind,
                "prev_act_time": timestamp,
                "prev_eat_time": dc[id]["prev_eat_time"],
                "forks": dc[id]["forks"] + 1,
                "eat_count": dc[id]["eat_count"],
            }

        if act_kind == ACT.DIE:
            exit(1)

        prev_timestamp = timestamp

for k, v in dc:
    if last_timestamp - v["prev_eat_time"] > die:
        exit(1)

exit(0)
