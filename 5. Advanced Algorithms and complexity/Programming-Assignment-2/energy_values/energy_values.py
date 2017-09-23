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

def gauss(matrix):

    if len(matrix) == 0:
        return []
    size = len(matrix[0]) - 1
    size_rows = len(matrix)
    used_columns = [False] * size
    used_rows = [False] * size_rows

    def makePivot(selectedRow, selectedColumn):
        used_rows[selectedRow] = True
        used_columns[selectedColumn] = True

    def leftMostNonZeroInNonPivotRow():
        if False not in used_rows:
            return False
        initialRow = used_rows.index(False)
        for row in range(initialRow, size_rows):
            for column in range(size):
                if matrix[row][column] != 0 and column < size:
                    used_rows[row] = True
                    return (row, column)
        return False

    def swapRowToTopOfNonPivotRow(selectedRow):
        if False not in used_rows:
            return
        topNonPivotRow = used_rows.index(False)
        if topNonPivotRow < selectedRow:
            matrix[topNonPivotRow], matrix[selectedRow] = matrix[selectedRow], matrix[topNonPivotRow]
        selectedRow = topNonPivotRow

    def rescaleToMakePivotOne(selectedRow, selectedColumn):
        pivot = matrix[selectedRow][selectedColumn]
        matrix[selectedRow] = [elem/pivot for elem in matrix[selectedRow]]

    def substractToMakeOtherRowsZero(selectedRow, selectedColumn):
        for row in range(size_rows):
            if row != selectedRow:
                times = matrix[row][selectedColumn]
                matrix[row] = [i - (times * j) for i, j in zip(matrix[row], matrix[selectedRow])]

    while False in used_rows and False in used_columns:
        selectedRow, selectedColumn = leftMostNonZeroInNonPivotRow()
        swapRowToTopOfNonPivotRow(selectedRow)
        makePivot(selectedRow, selectedColumn)
        rescaleToMakePivotOne(selectedRow, selectedColumn)
        substractToMakeOtherRowsZero(selectedRow, selectedColumn)
    res = [matrix[row][-1] for row in range(size_rows)]
    for i in range(len(res)):
        if res[i] == -0.0:
            res[i] = 0.0
    return to_str(res)



def test():
    def run(data, expected, f=gauss):
        result = f(data)
        if result != expected:
            raise Exception("Expected %s, Actual: %s" % (expected, result))
    run([[1.0, 1.0, 3.0], [2.0, 3.0, 7.0]], ["2.000000", "1.000000"])
    run([[1.0, 1.0]], ["1.000000"])
    run([], [])
    run([[5.0, -5.0, -1.0], [-1.0, -2.0, -1.0]], ["0.200000", "0.400000"])
    run([[1.0, 0.0, 0.0, 0.0, 1.0], [0.0, 1.0, 0.0, 0.0, 5.0],
        [0.0, 0.0, 1.0, 0.0, 4.0], [0.0, 0.0, 0.0, 1.0, 3.0]],
        ["1.000000", "5.000000", "4.000000", "3.000000"])
    run([
        [2.0, 4.0, -2.0, 0.0, -2.0],
        [-1.0, -2.0, 1.0, -2.0, -1.0],
        [2.0, 2.0, 0.0, 2.0, 0.0]],
        ["-1.000000", "1.000000", "0.000000"])
    print("Tests passed")


if __name__ == '__main__':
    if debug:
        test()
    else:
        s = gauss(from_input())
        print(" ".join(s))