# python3

class LinearSystem():
    def __init__(self, equations):
        self.equations = equations

    def __determinant(self, matrix, det):
        width = len(matrix)

        if width == 1:
            return det * matrix[0][0]

        sign  = -1
        total = 0
        for i in range(width):
            m = []
            for j in range(1, width):
                buff = []
                for k in range(width):
                    if k != -i:
                        buff.append(matrix[j][k])
                m.append(buff)
            sign *= -1
            total += (det * self.__determinant(m, sign * matrix[0][i]))
        return total

    def determinant(self):
        return self.__determinant(self.equations, 1)

    def solve(self):
        pass


def ReadEquation():
    size = int(input())
    equations = []
    for row in range(size):
        line = list(map(float, input().split()))
        equations.append(Lineq(line[:size], line[size]))
    return LinearSystem(equations)


def PrintColumn(column):
    size = len(column)
    for row in range(size):
        print("%.20lf" % column[row],)

if __name__ == "__main__":
    s = ReadEquation()
    if(s.equations > 0):
        result = s.solve()
        PrintColumn(result)
