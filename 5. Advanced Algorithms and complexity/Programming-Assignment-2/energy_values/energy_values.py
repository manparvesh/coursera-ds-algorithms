# python3

class LinearSystem():
    def __init__(self, matrix):
        self.matrix = matrix

    def __determinant(self, matrix, det):
        width = len(matrix)

        if width == 1:
            return det * matrix[0][0]

        sign  = -1
        total = 0
        for i in range(width):
            sub_matrix = []
            for j in range(1, width):
                buff = []
                for k in range(width):
                    if k != i:
                        buff.append(matrix[j][k])
                sub_matrix.append(buff)
            sign *= -1
            total += (det * self.__determinant(sub_matrix, sign * matrix[0][i]))
        return total

    def determinant(self):
        return self.__determinant(self.matrix, 1)

    def inverse(self):
        this_determinant = self.determinant()
        new_matrix = [[item / this_determinant for item in sub_matrix] for sub_matrix in self.matrix]
        return new_matrix

    def solve(self):
        pass

    def is_empty(self):
        return len(self.matrix) == 0


def ReadEquation():
    size = int(input())
    equations = []
    for row in range(size):
        line = list(map(float, input().split()))
        equations.append(line[:size])
    return LinearSystem(equations)


def PrintColumn(column):
    size = len(column)
    for row in range(size):
        print("%.20lf" % column[row],)

if __name__ == "__main__":
    s = ReadEquation()
    if not s.is_empty():
        # result = s.solve()
        # PrintColumn(s.inverse())
        print(s.inverse())