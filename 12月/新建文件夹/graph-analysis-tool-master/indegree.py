from matplotlib import pyplot as plt
import math
import sys

plt.switch_backend('agg')

graph_name = sys.argv[1]
# indegree
with open('./pyplot/indegree.txt', mode='rt') as f:
    while True:
        text=f.readline()
        if not text:
            break
        a=text.split()
        for i in range(len(a)):
            a[i]=int(a[i])
  
        b=[]
        for i in range(a[-1]+1):
            b.append(0)
        degree = list(range(0, a[-1]+1))
        for i in range(len(a)):
            b[a[i]]=b[a[i]]+1
   
        plt.figure(5)
        plt.scatter(degree, b)
        plt.xlabel('indegree')
        plt.ylabel('# of vertex')
        plt.title('indegree')
        fig = plt.gcf()
        fpath="./pyplot/"+str(graph_name)+"_indegree.png"
        fig.savefig(fpath, dpi=300)

        #log scale
        plt.figure(6)
        plt.xscale('log')
        plt.yscale('log')
        xmax = max(degree) * 2
        ymax = max(b) * 2
        plt.xlim(0.8, xmax)
        plt.ylim(0.8, ymax)
        plt.scatter(degree, b)
        plt.xlabel('indegree')
        plt.ylabel('# of vertex')
        plt.title('indegree_log')
        fig = plt.gcf()
        fpath="./pyplot/"+str(graph_name)+"_indegree_log.png"
        fig.savefig(fpath, dpi=300)

