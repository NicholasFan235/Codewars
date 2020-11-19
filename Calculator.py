class Calculator(object):
    def evaluate(self, string):
        query = string.replace(' ', '')
        replaceChars = [['(', ' ( '], [')', ' ) '], ['+', ' + '], ['-', ' - '], ['/', ' / '], ['*', ' * ']]
        for i in range(len(replaceChars)):
            query = query.replace(replaceChars[i][0], replaceChars[i][1])
        print(query)
        query = string.split(' ')
        return self.computeHelper(query)
    
    def computeHelper(self, query):
        query = [x for x in query if not x == '']
        #print(query)
        # do brackets
        br = []
        ranges = []
        for i in range(len(query)):
            if query[i] == '(':
                br.append(i)
            if query[i] == ')':
                j = br.pop()
                ranges.append([i, j])
        
        for r in ranges:
            query[r[0]] = self.computeHelper(query[r[1]+1:r[0]])
            query[r[1]:r[0]] = [''] * (r[0]-r[1])

        # do div and mul
        for i in range(len(query)):
            if (query[i] == '/'):
                query[i+1] = float(query[i-1])/float(query[i+1])
                query[i] = ''
                query[i-1] = ''
            if (query[i] == '*'):
                query[i+1] = float(query[i+1]) * float(query[i-1])
                query[i] = ''
                query[i-1] = ''
        
        query = [x for x in query if not x == '']
        # do add and sub
        for i in range(len(query)):
            if (query[i] == '-'):
                query[i+1] = float(query[i-1]) - float(query[i+1])
                query[i] = ''
                query[i-1] = ''
            if (query[i] == '+'):
                query[i+1] = float(query[i-1]) + float(query[i+1])
                query[i] = ''
                query[i-1] = ''

        query = [x for x in query if not x == '']
        #print(query)

        return float(query[0])

s = "1.1 + 2.2 + 3.3"
c = Calculator()
print(c.evaluate(s))