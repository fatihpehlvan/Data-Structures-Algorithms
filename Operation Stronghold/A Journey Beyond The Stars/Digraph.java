import java.util.ArrayList;
import java.util.List;

public class Digraph {
    private final int V;
    private final List<List<Integer>> adj;
    public Digraph(int V)
    {
        this.V = V;

        adj = new ArrayList<>();

        for (int v = 0; v < V; v++)
            adj.add(new ArrayList<>());
    }
    public void addEdge(int v, int w)
    {
        adj.get(v).add(w);
    }
    public Iterable<Integer> adj(int v)
    { return adj.get(v); }

    public int V() {
        return V;
    }
}
