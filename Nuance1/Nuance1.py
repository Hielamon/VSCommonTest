from numpy import *

class Solution(object):
    def topKNgramCount(self, strs, n, k):
        strsN = len(strs)
        words = []

        for i in range(0, strsN):
            strs[i] = strs[i].split(' ')
            iN = len(strs[i])
            for j in range(0, iN):
                if strs[i][j] not in words:
                    words.append(strs[i][j])

        wN = len(words)
        numberstrs = []
        for i in range(0, strsN):
            iN = len(strs[i])
            instrs = ''
            for j in range(0, iN):
                if strs[i][j] not in words:
                    instrs = instrs + str(words.index(strs[i][j]))
            numberstrs.append(instrs)

        group_words = []
        group_words_count = []
        for i in range(0, strsN):
            iN = len(strs[i])
            if k > iN:
                continue
            
            igramN = iN - k + 1
            for j in range(0, igramN):
                group_word = ''
                for ik in range(0, k):
                    group_word = group_word + numberstrs[i][j + ik]
                
                if group_word not in group_words:
                    group_words.append(group_word)
                    group_words_count.append(1)
                else:
                    group_words_count[group_words_count.index(group_word)] += 1

        
