def normalize(a,b):
    a,b = max(a,0), max(b,0)
    total = a + b
    if not total:
        return .5, .5
    return a/total, b/total

def new_strat(regret,total,player):
    for i in range(1,4,2):
        a,b = normalize(regret[i-1],regret[i])
        player[i-1],player[i] = a,b
        total[i-1] += a
        total[i] += b

def cfrm(p1,p2, r1, r2,card1, card2):
    
    #CALCULATING EV
    scaler = 1 if card1 > card2 else -1
    ev_cc = p1[0] * p2[0] * scaler
    ev_cbc = p1[0] * p2[1] * p1[2] * -1
    ev_cbb = p1[0] * p2[1] * p1[3] * 2 * scaler
    ev_bb = p1[1] * p2[3] * 2 * scaler
    ev_bc = p1[1] * p2[2]
    total = ev_cc + ev_cbc + ev_cbb + ev_bb + ev_bc
    
    #REGRETS FOR PLAYER 1    
    r1[0] += (p2[0] * scaler + p2[1] * p1[2] * -1 + p2[1] * p1[3] * 2 * scaler) - total
    r1[1] += (p2[2] + p2[3] * 2 * scaler) - total
    temp = 2 * scaler * p1[3] + -1 * p1[2]
    r1[2] += (-1 -  temp) * p2[1]
    r1[3] += (2 * scaler - temp) * p2[1]
    
    #REGRETS FOR PLAYER 2 
    scaler = -scaler
    temp = scaler * p2[0] + p2[1] * p1[2] + p2[1] * p1[3] * 2 * scaler
    r2[0] += (scaler - temp) * p1[0]
    r2[1] += ((p1[2] + p1[3] * 2 * scaler) - temp) * p1[0]
    r2[2] += (-1 - (-1 * p2[2] + 2 * scaler * p2[3])) * p1[1]
    r2[3] += (2 * scaler - (2 * scaler * p2[3] + p2[2] * -1)) * p1[1]


def main():
    s1 = [[.5 for _ in range(4)] for _ in range(3)]
    s2 = [[.5 for _ in range(4)] for _ in range(3)]
    regs1 = [[0 for _ in range(4)] for _ in range(3)]
    regs2 = [[0 for _ in range(4)]for _ in range(3)]
    t1 = [[0 for _ in range(4)]for _ in range(3)]
    t2 = [[0 for _ in range(4)] for _ in range(3)]
    iterations = 10000 
    for _ in range(iterations):
        for i in range(3):
            for x in range(3):
                if i != x:
                    cfrm(s1[i], s2[x], regs1[i], regs2[x], i, x)
        for i in range(3):
            new_strat(regs1[i],t1[i],s1[i])
            new_strat(regs2[i],t2[i],s2[i])

    print("Final strat averaged over all iterations")
    for i in range(3):
        for x in range(1,4,2):
            t1[i][x-1], t1[i][x] = normalize(t1[i][x-1], t1[i][x])
            t2[i][x-1], t2[i][x] = normalize(t2[i][x-1], t2[i][x])
    print('player 1')
    print(t1)
    print("Player 2")
    print(t2)





if __name__ == '__main__':
    main()
