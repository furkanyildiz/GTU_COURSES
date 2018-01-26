def compareScales (leftScaleList, rightScaleList):
    result = sum(leftScaleList) - sum(rightScaleList)
    if result < 0:
        return 1
    elif result > 0:
        return -1
    else:
        return 0


def foo(walnuts):
    if len(walnuts) % 2 == 1: #liste tek elemanlı ise
        #den = walnuts[len(walnuts)-2:len(walnuts)]
        test = compareScales([walnuts[len(walnuts)-2]],[walnuts[len(walnuts)-1]])
        if test == 1:
            return len(walnuts)-2
        elif test == -1:
            return len(walnuts)-1
        walnuts = walnuts[0:len(walnuts)-1]
    if len(walnuts) == 2:
        r = compareScales([walnuts[0]],[walnuts[1]])
        if r== -1:
            return 1
        elif r == 1:
            return 0
        else:
            return -1

    r = compareScales(walnuts[0:(len(walnuts)//2)], walnuts[(len(walnuts)//2):len(walnuts)])
    if r == -1:
        return  foo(walnuts[(len(walnuts)//2):len(walnuts)]) +(len(walnuts)//2)
    elif r == 1:
        return foo(walnuts[0:(len(walnuts)//2)])

listem =  [1, 1, 1, 1, 1, 1, 1, 0.5]
print(foo(listem))