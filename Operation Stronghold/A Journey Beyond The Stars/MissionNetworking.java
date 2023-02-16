import java.util.List;

public class MissionNetworking {

    public SubspaceCommunicationNetwork createNetwork(List<SolarSystem> solarSystems) {
        return new SubspaceCommunicationNetwork(solarSystems);
    }

    /**
     * Given a SubspaceCommunicationNetwork, prints the HyperChannels that constitute the minimum cost communication network.
     * Uses printMinimumCostCommunicationNetwork() and getMinimumCostCommunicationNetwork() methods of the SubspaceCommunicationNetwork
     * @param network a SubspaceCommunicationNetwork
     */
    public void printMinimumCostCommunicationNetwork(SubspaceCommunicationNetwork network) {
        // TODO: YOUR CODE HERE
        network.printMinimumCostCommunicationNetwork(network.getMinimumCostCommunicationNetwork());
    }
}
