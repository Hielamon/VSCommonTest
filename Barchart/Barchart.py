import numpy as np
import matplotlib.pyplot as plt

N = 3
ind = np.arange(N) * 5  # the x locations for the groups
width = 0.5       # the width of the bars

fig, ax = plt.subplots()

A_means = [23.988, 22.328, 21.984]
A_std = [1.72129892813538, 1.675625256, 1.77573365119885]
rects1 = ax.bar(ind, A_means, width, color='r', yerr=A_std, capsize = 10)

B_means = [18.712, 20.222, 19.918]
B_std = [6.714377857, 6.411775885, 5.642217649]
rects2 = ax.bar(ind + width, B_means, width, color='g', yerr=B_std, capsize = 10)

C_means = [24.24, 24.506, 22.372]
C_std = [5.756900208, 4.372788584, 6.102566673]
rects2 = ax.bar(ind + 2*width, C_means, width, color='b', yerr=C_std, capsize = 10)

D_means = [26.594, 25.402, 25.946]
D_std = [2.319381383, 1.922321513, 1.657190393]
rects2 = ax.bar(ind + 3*width, D_means, width, color='gold', yerr=D_std, capsize = 10)

E_means = [27.942, 26.026, 25.594]
E_std = [2.213711815, 2.126036218, 2.048238267]
rects2 = ax.bar(ind + 4*width, E_means, width, color='lime', yerr=E_std, capsize = 10)

		

# add some text for labels, title and axes ticks
ax.set_ylabel('Scores')
ax.set_title('Scores by group and gender')
ax.set_xticks(ind + width / 2)
ax.set_xticklabels(('8', '14', '20'))

ax.legend((rects1[0], rects2[0]), ('Men', 'Women'))


def autolabel(rects):
    """
    Attach a text label above each bar displaying its height
    """
    for rect in rects:
        height = rect.get_height()
        ax.text(rect.get_x() + rect.get_width()/2., 1.05*height,
                '%d' % int(height),
                ha='center', va='bottom')

autolabel(rects1)
autolabel(rects2)

plt.grid()

plt.show()