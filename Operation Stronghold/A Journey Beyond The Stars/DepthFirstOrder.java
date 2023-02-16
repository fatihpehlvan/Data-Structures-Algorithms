import java.util.Stack;

public class DepthFirstOrder
{
    private boolean[] marked;
    private Stack<Integer> reversePost;
    private int time = 0;
    public DepthFirstOrder(Digraph G)
    {
        reversePost = new Stack<>();
        marked = new boolean[G.V()];
        for (int v = 0; v < G.V(); v++){
            if (!marked[v]) dfs(G, v);
        }

    }
    private void dfs(Digraph G, int v)
    {
        marked[v] = true;
        for (int w : G.adj(v)) {
            if (!marked[w]) dfs(G, w);
        }
        reversePost.push(v);
    }
    public Stack<Integer> reversePost()
    { return reversePost; }
}