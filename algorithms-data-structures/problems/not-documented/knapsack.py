def     knapsackNK():
    with open('input.in', 'r') as file:
        K = int(file.readline())
        w = []

        for current in file:
            w.append(int(current))
        n = len(w)
        val = w.copy()
        dp = [[0 for _ in range(K + 1)] for _ in range(n + 1)]
        for i in range (1, n + 1):
            for j in range (0, K + 1):
                if j < w[i - 1]:
                    dp[i][j] = dp[i - 1][j]
                else:
                    dp[i][j] = max(dp[i - 1][j - w[i - 1]] + val[i - 1], dp[i - 1][j])
        i = n
        j = K
        return dp[n][K]

def     knapsackApproximative():
    with open('input.in', 'r') as file:
        K = int(file.readline())
        S = 0

        '''
            Parcurgem numerele. Avem cazurile:
            a)  În care nu se intră pe ramura de else, adică suma tuturor numerele <= K, deci soluția este chiar cea optimă.
            b)  În care se intră pe ramura de else, de unde rezultă că suma dintre numerele adunate până la acest moment și 
                ultimul număr citit este > K, deci cel puțin unul dintre ele este mai mare decât K / 2. În cazul acesta vom alege
                să luăm maximul dintre suma elementelor de până acum și numărul citit, și astfel vom ajunge la un rezultat cel
                puțin egal cu K / 2 => Algoritmul este cel puțin 2-aproximativ deoarece OPT <= K.
        '''
        for current in file:
            current = int(current)
            if (K > current):
                S += current
                K -= current
            else:
                return max(current, S)
        return S