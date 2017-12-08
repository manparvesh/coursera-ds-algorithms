import java.io.*;
import java.util.Locale;
import java.util.StringTokenizer;

public class CleaningApartment {
    private final InputReader reader;
    private final OutputWriter writer;

    public CleaningApartment(InputReader reader, OutputWriter writer) {
        this.reader = reader;
        this.writer = writer;
    }

    public static void main(String[] args) {
        InputReader reader = new InputReader(System.in);
        OutputWriter writer = new OutputWriter(System.out);
        new CleaningApartment(reader, writer).run();
        writer.writer.flush();
    }

    class Edge {
        int from;
        int to;
    }

    class ConvertHampathToSat {
        int numVertices;
        Edge[] edges;
        int countClauses;

        ConvertHampathToSat(int n, int m) {
            numVertices = n;
            edges = new Edge[m];
            for (int i = 0; i < m; ++i) {
                edges[i] = new Edge();
            }
        }

        void printEquisatisfiableSatFormula() {
            StringBuilder clauses = new StringBuilder();

            appearInPath(clauses);
            allVertexInPath(clauses);
            onlyOnceInPath(clauses);
            onlyOneInEachPosition(clauses);
            connectedVertex(clauses);
            writer.printf(countClauses + " " + numVertices * numVertices + "\n");
            writer.printf(clauses.toString());
        }

        private void appearInPath(StringBuilder clauses) {
            for (int i = 1; i < numVertices * numVertices + 1; i += numVertices) {
                for (int j = 0; j < numVertices; j++) {
                    clauses.append(i + j)
                            .append(" ");
                }
                clauses.append("0\n");
                countClauses++;
            }
        }

        private void allVertexInPath(StringBuilder clauses) {
            for (int i = 1; i < numVertices + 1; i++) {
                for (int j = 0; j < numVertices * numVertices; j += numVertices) {
                    clauses.append(i + j)
                            .append(" ");
                }
                clauses.append("0\n");
                countClauses++;
            }
        }

        private void onlyOnceInPath(StringBuilder clauses) {
            for (int i = 1; i < numVertices * numVertices + 1; i += numVertices) {
                for (int j = 0; j < numVertices; j++) {
                    for (int k = j + 1; k < numVertices; k++) {
                        clauses.append(-(i + j))
                                .append(" ")
                                .append(-(i + k))
                                .append(" 0\n");
                        countClauses++;
                    }
                }

            }
        }

        private void onlyOneInEachPosition(StringBuilder clauses) {
            for (int i = 1; i < numVertices + 1; i++) {
                for (int j = 0; j < numVertices * numVertices; j += numVertices) {
                    for (int k = j + numVertices; k < numVertices * numVertices; k += numVertices) {
                        clauses.append(-(i + j))
                                .append(" ")
                                .append(-(i + k))
                                .append(" 0\n");
                        countClauses++;
                    }
                }

            }
        }

        private void connectedVertex(StringBuilder clauses) {
            boolean[][] adj = new boolean[numVertices][numVertices];
            for (Edge edge : edges) {
                adj[edge.from - 1][edge.to - 1] = true;
                adj[edge.to - 1][edge.from - 1] = true;
            }
            for (int i = 0; i < numVertices; i++) {
                for (int j = i + 1; j < numVertices; j++) {
                    if (!adj[i][j]) {
                        for (int k = 0; k < numVertices - 1; k++) {
                            clauses.append(-((i + 1) * numVertices - (numVertices - 1) + k))
                                    .append(" ")
                                    .append(-((j + 1) * numVertices - (numVertices - 1) + k + 1))
                                    .append(" 0\n")

                                    .append(-((j + 1) * numVertices - (numVertices - 1) + k))
                                    .append(" ")
                                    .append(-((i + 1) * numVertices - (numVertices - 1) + k + 1))
                                    .append(" 0\n");
                            countClauses += 2;
                        }
                    }
                }
            }
        }

    }

    public void run() {
        int n = reader.nextInt();
        int m = reader.nextInt();

        ConvertHampathToSat converter = new ConvertHampathToSat(n, m);
        for (int i = 0; i < m; ++i) {
            converter.edges[i].from = reader.nextInt();
            converter.edges[i].to = reader.nextInt();
        }

        converter.printEquisatisfiableSatFormula();
    }

    static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;

        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }

        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

        public double nextDouble() {
            return Double.parseDouble(next());
        }

        public long nextLong() {
            return Long.parseLong(next());
        }
    }

    static class OutputWriter {
        public PrintWriter writer;

        OutputWriter(OutputStream stream) {
            writer = new PrintWriter(stream);
        }

        public void printf(String format, Object... args) {
            writer.print(String.format(Locale.ENGLISH, format, args));
        }
    }
}