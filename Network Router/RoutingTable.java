import java.io.Serializable;
import java.util.*;

public class RoutingTable implements Serializable {

    static final long serialVersionUID = 99L;
    private final Router router;
    private final Network network;
    private final List<RoutingTableEntry> entryList;
    private double cost;

    public RoutingTable(Router router) {
        this.router = router;
        this.network = router.getNetwork();
        this.entryList = new ArrayList<>();
    }

    /**
     * updateTable() should calculate routing information and then instantiate RoutingTableEntry objects, and finally add
     * them to RoutingTable object’s entryList.
     */
    public void updateTable() {
        // TODO: YOUR CODE HERE
        for (Router r : network.getRouters()){
            if (!r.equals(router)){
                Stack<Link> linkStack;
                if (router.isDown()) linkStack = new Stack<>();
                else linkStack = pathTo(r);
                RoutingTableEntry routingTable = new RoutingTableEntry(router.getIpAddress(), r.getIpAddress(), linkStack);
                boolean contains = true;
                for (RoutingTableEntry routingTableEntry : entryList){
                    if (routingTableEntry.getSourceIpAddr().equals(router.getIpAddress()) && r.getIpAddress().equals(routingTableEntry.getDestinationIpAddr())){
                        routingTableEntry.setFullPath(linkStack);
                        contains = false;
                    }
                }
                if (contains)
                    entryList.add(routingTable);
            }
        }
    }

    /**
     * pathTo(Router destination) should return a Stack<Link> object which contains a stack of Link objects,
     * which represents a valid path from the owner Router to the destination Router.
     *
     * @param destination Destination router
     * @return Stack of links on the path to the destination router
     */
    public Stack<Link> pathTo(Router destination) {
        Stack<Link> l = new Stack<>();
        // TODO: YOUR CODE
        Map<String, String> edgeTo = new HashMap<>();
        Map<String, Double> distTo = new HashMap<>();
        PriorityQueue<String> pq = new PriorityQueue<>();
        for (int i = 0; i < destination.getNetwork().getRouters().size(); i++)
            distTo.put(destination.getNetwork().getRouters().get(i).getIpAddress(), Double.POSITIVE_INFINITY);
        distTo.put(router.getIpAddress(), 0.0);

        String id = router.getIpAddress();
        pq.add(id);
        while (!pq.isEmpty()){
            id = pq.poll();
            for (Link r : network.getLinks()){
                if (Objects.equals(r.getIpAddress1(), id) || Objects.equals(r.getIpAddress2(), id)){
                    String v = id;
                    String w = r.getOtherIpAddress(id);
                    if (network.getRouterWithIp(w).isDown()) continue;
                    if (distTo.get(w) > distTo.get(v) + r.getCost()){
                        distTo.put(w, distTo.get(v) + r.getCost());
                        edgeTo.put(w, v);
                        if (!pq.contains(w)) pq.add(w);
                    }
                }
            }
        }
        id = destination.getIpAddress();
        cost = distTo.get(id);
        while (edgeTo.containsKey(id)) {
            for (Link link : network.getLinks()) {
                if (Objects.equals(link.getIpAddress1(), id) && Objects.equals(link.getIpAddress2(), edgeTo.get(id))) {
                    l.add(link);
                } else if (Objects.equals(link.getIpAddress2(), id) && Objects.equals(link.getIpAddress1(), edgeTo.get(id))) {
                    l.add(link);
                }
            }
            id = edgeTo.get(id);
        }

        return l;
    }


    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        RoutingTable that = (RoutingTable) o;
        return router.equals(that.router) && entryList.equals(that.entryList);
    }

    public List<RoutingTableEntry> getEntryList() {
        return entryList;
    }

    public Router getRouter() {
        return router;
    }

    public Network getNetwork() {
        return network;
    }

    public double getCost() {
        return cost;
    }

    public void setCost(double cost) {
        this.cost = cost;
    }

}
