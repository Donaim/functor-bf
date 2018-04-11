# increments arrays of numers
# todo: make generic, not only for ints

def find_last_ind(indexes: list, base: int):
    for i in range(len(indexes)):
        if indexes[i] < base - 1:
            return i
    return -1
def succ_list(indexes: list, base: int):
    if indexes[0] < base - 1:
        indexes[0] += 1
    else:
        find = find_last_ind(indexes, base)
        if find > 0:
            indexes[find] += 1
        else:
            find = len(indexes)
            indexes.append(1)
        
        for i in range(0, find):
            indexes[i] = 0

def arr_num_str(arr: list):
    return ''.join(map(lambda x: str(x), reversed(arr)))

