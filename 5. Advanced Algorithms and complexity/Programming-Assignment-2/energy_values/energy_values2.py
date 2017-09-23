#python 3
debug = False

def from_input():
    m = int(input())
    idx_matrix = []
    for _ in range(m):
        row = list(map(float, input().split()))
        idx_matrix.append(row)
    return idx_matrix

def to_str(x):
    return list(map(lambda a: format(a, '.6f'), x))

def gauss(A):
    n = len(A)
    for i in range(n):
        maxEl = abs(A[i][i])
        maxRow = i
        for k in range(i+1, n):
            if abs(A[k][i]) > maxEl:
                maxEl = abs(A[k][i])
                maxRow = k
        for k in range(i, n+1):
            tmp = A[maxRow][k]
            A[maxRow][k] = A[i][k]
            A[i][k] = tmp
        for k in range(i+1, n):
            c = -A[k][i]/A[i][i]
            for j in range(i, n+1):
                if i == j:
                    A[k][j] = 0
                else:
                    A[k][j] += c * A[i][j]
    x = [0 for i in range(n)]
    for i in range(n-1, -1, -1):
        x[i] = A[i][n]/A[i][i]
        for k in range(i-1, -1, -1):
            A[k][n] -= A[k][i] * x[i]
    return to_str(x)

def test():
    def run(data, expected, f=gauss):
        result = f(data)
        if result != expected:
            raise Exception("Expected %s, Actual: %s" % (expected, result))
    run([], [])
    run([[1.0, 0.0, 0.0, 0.0, 1.0], [0.0, 1.0, 0.0, 0.0, 5.0],
        [0.0, 0.0, 1.0, 0.0, 4.0], [0.0, 0.0, 0.0, 1.0, 3.0]],
        ["1.000000", "5.000000", "4.000000", "3.000000"])
    run([[5.0, -5.0, -1.0], [-1.0, -2.0, -1.0]], ["0.200000", "0.400000"])
    run([[1.0, 1.0, 3.0], [2.0, 3.0, 7.0]], ["2.000000", "1.000000"])
    print("Tests passed")


if __name__ == '__main__':
    if debug:
        test()
    else:
        s = gauss(from_input())
        print(" ".join(s))