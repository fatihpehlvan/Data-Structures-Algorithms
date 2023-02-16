import java.io.Serializable;
import java.util.Objects;

public class Router implements Serializable {
    static final long serialVersionUID = 33L;
    private String ipAddress;
    private boolean isDown;
    private Network network;
    private RoutingTable routingTable;

    public Router(String ipAddress, Network network) {
        this.ipAddress = ipAddress;
        this.network = network;
        this.routingTable = new RoutingTable(this);
    }

    public boolean isDown() {
        return isDown;
    }

    public void setDown(boolean down) {
        isDown = down;
    }

    public String getIpAddress() {
        return ipAddress;
    }

    public void setIpAddress(String ipAddress) {
        this.ipAddress = ipAddress;
    }

    public RoutingTable getRoutingTable() {
        return routingTable;
    }


    public Network getNetwork() {
        return network;
    }

    public void setNetwork(Network network) {
        this.network = network;
    }

    @Override
    public String toString() {
        return "Router{" +
                "ipAddress='" + ipAddress + '\'' +
                ", isDown=" + isDown +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Router router = (Router) o;
        return isDown == router.isDown && Objects.equals(ipAddress, router.ipAddress);
    }

    public void setRoutingTable(RoutingTable routingTable) {
        this.routingTable = routingTable;
    }
}
