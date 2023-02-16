import java.util.List;

public class Main {
    public static void main(String[] args) {
        System.out.println("### MISSION GROUNDWORK START ###");
        MissionGroundwork missionGroundwork = new MissionGroundwork();
        List<Project> projectList = missionGroundwork.readXML(args[0]);
        missionGroundwork.printSchedule(projectList);
        System.out.println("### MISSION GROUNDWORK END ###");

        System.out.println("### MISSION EXPLORATION START ###");
        MissionExploration missionExploration = new MissionExploration();
        Galaxy galaxy = missionExploration.readXML(args[1]);
        missionExploration.printSolarSystems(galaxy);
        System.out.println("### MISSION EXPLORATION END ###");

        System.out.println("### MISSION NETWORKING START ###");
        MissionNetworking missionNetworking = new MissionNetworking();
        SubspaceCommunicationNetwork network = missionNetworking.createNetwork(galaxy.getSolarSystems());
        missionNetworking.printMinimumCostCommunicationNetwork(network);
        System.out.println("### MISSION NETWORKING END ###");
    }
}
