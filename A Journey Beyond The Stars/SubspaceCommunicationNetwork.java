import java.util.*;

;

public class SubspaceCommunicationNetwork {

    private List<SolarSystem> solarSystems;
    private List<HyperChannel> hyperChannelGraph;
    private Map<String, Planet> map = new HashMap<>();
    private Set<Planet> set = new HashSet<>();
    /**
     * Perform initializations regarding your implementation if necessary
     * @param solarSystems a list of SolarSystem objects
     */
    public SubspaceCommunicationNetwork(List<SolarSystem> solarSystems) {
        // TODO: YOUR CODE HERE

        this.solarSystems = solarSystems;
        hyperChannelGraph = new ArrayList<>();
        Planet[] memo = new Planet[solarSystems.size()];
        for (int i = 0; i < solarSystems.size()-1; i++){
            for (int k = i+1; k < solarSystems.size(); k++){
                Planet maxI = null;
                Planet maxK = null;
                if (memo[i] != null) maxI = memo[i];
                if (memo[k] != null) maxK = memo[k];
                if (maxI == null){
                    maxI = solarSystems.get(i).getPlanets().stream().max(Comparator.comparing(Planet::getTechnologyLevel)).get();
                }
                if (maxK == null){
                    maxK = solarSystems.get(k).getPlanets().stream().max(Comparator.comparing(Planet::getTechnologyLevel)).get();
                }
                double average = (maxI.getTechnologyLevel() + maxK.getTechnologyLevel()) / 2d;
                double cost = Constants.SUBSPACE_COMMUNICATION_CONSTANT / average;
                HyperChannel hyperChannel = new HyperChannel(maxI, maxK, cost);
                hyperChannelGraph.add(hyperChannel);
                map.put(maxI.getId(), maxI);
                map.put(maxK.getId(), maxK);
            }
        }

        hyperChannelGraph.sort(Comparator.comparing(HyperChannel::getWeight));
    }

    /**
     * Using the solar systems of the network, generates a list of HyperChannel objects that constitute the minimum cost communication network.
     * @return A list HyperChannel objects that constitute the minimum cost communication network.
     */
    public List<HyperChannel> getMinimumCostCommunicationNetwork() {
        List<HyperChannel> minimumCostCommunicationNetwork = new ArrayList<>();
        Map<String , ArrayList<Planet>> mapArray = hyperChannelGraph.get(0).getMap();
        PriorityQueue<HyperChannel> pq = new PriorityQueue<>();
        pq.add(hyperChannelGraph.get(0));
        set.add(hyperChannelGraph.get(0).getFrom());
        while (!pq.isEmpty()){
            HyperChannel hyperChannel = pq.poll();
            Planet v =  hyperChannel.getFrom(), w = hyperChannel.getTo();
            if (set.contains(v) && set.contains(w)) continue;
            minimumCostCommunicationNetwork.add(hyperChannel);
            if (!set.contains(v)){
                set.add(v);
                for (Planet planet : mapArray.get(v.getId())){
                    Planet planet1 = map.get(planet.getId());
                    if (!set.contains(planet1)){
                        HyperChannel hp = find(planet1);
                        pq.add(hp);
                    }
                }
            }
            if (!set.contains(w)){
                set.add(w);
                for (Planet planet : mapArray.get(w.getId())){
                    Planet planet1 = map.get(planet.getId());
                    if (!set.contains(planet1) && planet1 != null){
                        HyperChannel hp = find(planet1);
                        pq.add(hp);
                    }
                }
            }
        }

        // TODO: YOUR CODE HERE
        return minimumCostCommunicationNetwork;
    }
    public HyperChannel find (Planet planet){
        for (HyperChannel hyperChannel : hyperChannelGraph){
            if (hyperChannel.getTo().equals(planet)){
                return hyperChannel;
            } if (hyperChannel.getFrom().equals(planet)){
                return hyperChannel;
            }
        }
        return null;
    }



    public void printMinimumCostCommunicationNetwork(List<HyperChannel> network) {
        double sum = 0;
        for (HyperChannel channel : network) {
            Planet[] planets = {channel.getFrom(), channel.getTo()};
            Arrays.sort(planets);
            System.out.printf("Hyperchannel between %s - %s with cost %f", planets[0], planets[1], channel.getWeight());
            System.out.println();
            sum += channel.getWeight();
        }
        System.out.printf("The total cost of the subspace communication network is %f.", sum);
        System.out.println();
    }
}
