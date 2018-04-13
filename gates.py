
def nor (X: int, Y: int):
    if ((X > 0) or (Y > 0)): return 0
    else: return 1
def nand (X: int, Y: int):
    if ((X > 0) and (Y > 0)): return 0
    else: return 1

def tnand (X: list, Y: list):
    re = [0] * len(X)
    for i in range(len(X)):
        re[i] = nand(X[i], Y[i])
    return re
def tnor (X: list, Y: list):
    re = [0] * len(X)
    for i in range(len(X)):
        re[i] = nor(X[i], Y[i])
    return re

# // data
T = [1, 1, 1, 1]
F = [0, 0, 0, 0]
X = [0, 1, 0, 1]
Y = [0, 0, 1, 1]

from indexed_succ import * 

class smgr: # need this because python is stupid
    def __init__(self, poss_count, steps_count):
        self.poss_count = poss_count
        self.steps_count = steps_count
        self.__steps = [None] * (steps_count * poss_count)
        # print("steps = {} (size={}; truesize={})".format(self.__steps, len(self.__steps), steps_count * poss_count))

    def set_ind(self, poss_index: int, step_index: int, val: tuple):
        self.__steps[poss_index * self.steps_count + step_index] = val
        # print("SET [{}][{}] = {}".format(poss_index, step_index, self.get_ind(poss_index, step_index)))
    def get_ind(self, poss_index: int, step_index: int) -> tuple:
        return self.__steps[poss_index * self.steps_count + step_index]
    def __repr__(self):
        re = ""
        for o in range(self.steps_count):
            for k in range(self.poss_count):
                re += "{} ".format(self.get_ind(k, o))
            re += '\n'
        return re

def get_count(num_steps, min_num):
    p = 1
    for k in range(min_num, num_steps + min_num):
        p *= (2 ** k)
    print("count({},{}) = {}".format(num_steps, min_num, p))
    return p

def bruteforce(desired: list) -> list:
    print("searching for: {}".format(desired))

    core = [X, Y]
    # core = [T, F, X, Y]
    
    maxop = 8

    for oplen in range(maxop):
        poss_count = get_count(oplen, len(core))
        sc = smgr(poss_count, oplen)

        for o in range(oplen):
            pair = [0, 0]
            for k in range(poss_count):
                sc.set_ind(k, o, (pair[0], pair[1]))
                succ_list(pair, len(core) + o)

        # print(sc)

        for i in range(sc.poss_count):
            be = core + ([None] * sc.steps_count)

            for k in range(len(core), len(be)):
                pair  = sc.get_ind(i, k - len(core))
                be[k] = tnand(be[pair[0]], be[pair[1]])
                # print("first={}; secon={}; nand={}".format(be[pair[0]], be[pair[1]], be[k]))

            # print("steps={}".format(re))

            if be[-1] == desired: 
                print("be={}".format(be))
                re = [None] * sc.steps_count
                for k in  range(sc.steps_count): 
                    re[k] = sc.get_ind(i, k)
                return re

    raise Exception("Could not find in {} operations".format(maxop))

ind = bruteforce([0, 1, 1, 0])
print("Operations={}".format(ind))
