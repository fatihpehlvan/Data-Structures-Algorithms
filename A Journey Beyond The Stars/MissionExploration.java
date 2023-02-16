import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MissionExploration {

    static Map<String, Planet> idPlanetMap = new HashMap<>();
    /**
     * Given a Galaxy object, prints the solar systems within that galaxy.
     * Uses exploreSolarSystems() and printSolarSystems() methods of the Galaxy object.
     *
     * @param galaxy a Galaxy object
     */
    public void printSolarSystems(Galaxy galaxy) {
        // TODO: YOUR CODE HERE
        List<SolarSystem> solarSystems = galaxy.exploreSolarSystems();
        galaxy.printSolarSystems(solarSystems);
    }

    /**
     * TODO: Parse the input XML file and return a list of Planet objects.
     *
     * @param filename the input XML file
     * @return a list of Planet objects
     */
    public Galaxy readXML(String filename) {
        List<Planet> planetList = new ArrayList<>();
        try {
            BufferedReader br = new BufferedReader(new FileReader(filename));
            String st;
            Planet planet;
            String id = null;
            int techLevel = 0;
            List<String> neighbours = new ArrayList<>();
            while ((st = br.readLine()) != null){
                st = st.trim();
                if (st.startsWith("</Planet>")){
                    planet = new Planet(id, techLevel, neighbours);
                    neighbours = new ArrayList<>();
                    idPlanetMap.put(id, planet);
                    planetList.add(planet);
                } else if (st.startsWith("<ID>")) {
                    id = st.substring(4);
                    id = id.substring(0, id.length()-5);
                } else if (st.startsWith("<TechnologyLevel>")){
                    st = st.substring(17);
                    techLevel = Integer.parseInt(st.substring(0, st.length()-18));
                } else if (st.startsWith("<PlanetID>")){
                    st = st.substring(10);
                    st = st.substring(0,st.length()-11);
                    neighbours.add(st);
                }
            }


        } catch (Exception e){
            e.printStackTrace();
        }
        return new Galaxy(planetList);
    }
}
