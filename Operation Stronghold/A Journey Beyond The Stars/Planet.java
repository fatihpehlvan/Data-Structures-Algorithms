import java.util.HashSet;
import java.util.List;

public class Planet implements Comparable {
    private final String id;
    private final int technologyLevel;
    private final List<String> neighbors;

    public Planet(String id, int technologyLevel, List<String> neighbors) {
        this.id = id;
        this.technologyLevel = technologyLevel;
        this.neighbors = neighbors;
    }

    public String getId() {
        return id;
    }

    public int getTechnologyLevel() {
        return technologyLevel;
    }

    public List<String> getNeighbors() {
        return neighbors;
    }


    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Planet planet = (Planet) o;
        return technologyLevel == planet.technologyLevel &&
                id.equals(planet.id) &&
                new HashSet<>(neighbors).equals(new HashSet<>(((Planet) o).getNeighbors()));
    }

    @Override
    public String toString() {
        return id;
    }

    @Override
    public int compareTo(Object o) {
        Integer ownId = Integer.parseInt(this.getId().substring(1));
        Integer oId = Integer.parseInt(((Planet) o).getId().substring(1));
        return ownId.compareTo(oId);
    }
}

