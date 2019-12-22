from matplotlib import pyplot as plt
from matplotlib.ticker import MaxNLocator
import math
import sys

plt.switch_backend('agg')

graph_name = sys.argv[1]
# label-vertex
with open('./pyplot/label-vertex.txt', mode='rt') as f:
    l=[]
    n=[]
    while True:
        text=f.readline()
        if not text:
            break
        text=text.split()
        l=l+[int(text[0])]
        n=n+[int(text[1])]

    plt.figure(1)
    ax = plt.figure(1).gca()
    ax.xaxis.set_major_locator(MaxNLocator(integer=True))
    plt.bar(l,n)
    plt.xlabel('label')
    plt.ylabel('# of vertex')
    plt.title('label-vertex')
    fig = plt.gcf()
    fpath = "./pyplot/"+str(graph_name)+"_label-vertex.png"
    fig.savefig(fpath, dpi=300)

    #log scale
    plt.figure(2)
    plt.xscale('log')
    plt.yscale('log')
    xmax = max(l) * 2
    ymax = max(n) * 2
    plt.xlim(0.8, xmax)
    plt.ylim(0.8, ymax)
    plt.scatter(l,n)
    plt.xlabel('label')
    plt.ylabel('# of vertex')
    plt.title('label-vertex_log')
    fig = plt.gcf()
    fpath = "./pyplot/"+str(graph_name)+"_label-vertex_log.png"
    fig.savefig(fpath, dpi=300)

