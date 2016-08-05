import numpy as np

def nOnes(nIn,nOut):
    return 2*nOut - nIn


if __name__ == "__main__":
    nInW,nInH = 30, 30
    nOutW = 18 
    nOutH = 18 
    incH = np.ones(nOutH)
    incH[:nOnes(nInH,nOutH)] = 2
    incW = np.ones(nOutW)
    incW[:nOnes(nInW,nOutW)] = 2

    [np.random.shuffle(arr) for arr in [incW,incH]]
    

