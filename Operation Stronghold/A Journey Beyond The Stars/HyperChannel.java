import java.util.*;

public class HyperChannel implements Comparable<HyperChannel> {
    private Planet to;
    private Planet from;
    private Double cost;
    private static Map<String , ArrayList<Planet>> map = new HashMap<>();

    public Map<String, ArrayList<Planet>> getMap() {
        return map;
    }

    public HyperChannel(Planet to, Planet from, Double cost) {
        if (map.containsKey(to.getId())){
            map.get(to.getId()).add(from);
        } else {
            map.put(to.getId(), new ArrayList<Planet>(){{add(from);}});
        }
        if (map.containsKey(from)){
            map.get(from).add(to);
        } else {
            map.put(from.getId(), new ArrayList<Planet>(){{add(to);}});
        }
        this.to = to;
        this.from = from;
        this.cost = cost;
    }

    public Planet getTo() {
        return to;
    }

    public Planet getFrom() {
        return from;
    }

    public Double getWeight() {
        return cost;
    }


    @Override
    public int compareTo(HyperChannel o) {
        if (cost < o.getWeight())
            return 1;
        else if (cost > o.getWeight())
            return -1;
        return 0;

    }
}
