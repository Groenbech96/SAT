import matplotlib.pyplot as plt
f1 = 'rU50SAT_CDCL.out'
f2 = 'rU50SAT_CRYPTO.out'
f3 = 'rU50SAT_S.out'
f4 = 'rU50SAT_S_C.out'

def sumStat(file):
    d = {}
    d['true'] = 0
    d['false'] = 0
    d['totalTime'] = 0
    ms = 0
    skip = False
    with open(file) as f:
        while True:
            s = f.readline()
            temp = f.readline()
            tms = f.readline()
            
            if not s:
                break

            if s.strip() == 't':
                d['true'] = d['true']+1
            else:
                d['false'] = d['false']+1

            ms = int(tms) + ms

    d['totalTime'] = ms      
    return d

def mstomin(time):
    #print(line)
    return float(float(float(time) / 1000) / 60)

def plot(f1, f2, f3):
    CDCLX = []
    CDCLY = []
    CRYPX = []
    CRYPY = []
    SCHX  = []
    SCHY  = []
    prob = 0
    time1 = 0
    with open(f1) as f:
        while True:
            s = f.readline()
            temp = f.readline()
            tms = f.readline()
            
            if not s:
                break

            CDCLX.append(prob)
            time1 = int(tms) + time1
            CDCLY.append(time1)
            prob = prob + 1

    prob = 0
    time2 = 0
    with open(f2) as f:
        while True:
            s = f.readline()
            temp = f.readline()
            tms = f.readline()
            
            if not s:
                break

            CRYPX.append(prob)
            time2 = int(tms) + time2
            CRYPY.append(time2)
            prob = prob + 1
    
    prob = 0
    time3 = 0
    with open(f3) as f:
        while True:
            s = f.readline()
            temp = f.readline()
            tms = f.readline()
            
            if not s:
                break

            SCHX.append(prob)
            time3 = int(tms) + time3
            SCHY.append(time3)
            prob = prob + 1

    

    fig = plt.figure()
    ax1 = fig.add_subplot(111)

    CDCLY = [mstomin(x) for x in CDCLY]
    CRYPY = [mstomin(x) for x in CRYPY]
    SCHY = [mstomin(x) for x in SCHY]

    print(len(CDCLX))
    print(len(CDCLY))
    print(len(CRYPX))
    print(len(CRYPY))
    print(len(SCHX))
    print(len(SCHY))

    ax1.scatter(CDCLX, CDCLY, s=1, c='g', marker="s", label='CDCL')
    ax1.scatter(CRYPX, CRYPY, s=1, c='orange', marker="s", label='CryptoSAT')
    ax1.scatter(SCHX, SCHY, s=1, c='blue', marker="s", label='Schönings')

    time = max(max(time1, time2), max(time2, time3))
    time = (time / 1000) / 60 
    
    plt.legend(loc='upper left');
    plt.xlabel("Problem number")
    plt.axis([-20, 1020, -10, time+10])
    plt.title("SAT - UF50")
    plt.ylabel("Runtime in min")
    plt.savefig("SAT-UF50")


print(sumStat(f1))
print(sumStat(f2))
print(sumStat(f3))
print(sumStat(f4))

#plot(f1,f2,f3)

