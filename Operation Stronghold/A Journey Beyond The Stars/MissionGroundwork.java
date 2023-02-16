import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class MissionGroundwork {

    /**
     * Given a list of Project objects, prints the schedule of each of them.
     * Uses getEarliestSchedule() and printSchedule() methods of the current project to print its schedule.
     * @param projectList a list of Project objects
     */
    public void printSchedule(List<Project> projectList) {
        // TODO: YOUR CODE HERE
        for (Project pr : projectList){
            int[] arr = pr.getEarliestSchedule();
            pr.printSchedule(arr);
        }
    }

    /**
     * TODO: Parse the input XML file and return a list of Project objects
     *
     * @param filename the input XML file
     * @return a list of Project objects
     */
    public List<Project> readXML(String filename) {
        List<Project> projectList = new ArrayList<>();
        // TODO: YOUR CODE HERE
        try {
            BufferedReader br = new BufferedReader(new FileReader(filename));
            String st;
            Project project;
            int taskID = 0;
            String name = null;
            int duration = 0;
            String description = null;
            Task task;
            List<Task> tasks = new ArrayList<>();
            List<Integer> dependencies = new ArrayList<>();
            while ((st = br.readLine()) != null){
                st = st.trim();
                if (st.startsWith("</Project>")){
                    project = new Project(name, tasks);
                    projectList.add(project);
                    tasks = new ArrayList<>();
                } else if (st.startsWith("<Name>")) {
                    name = st.substring(6);
                    name = name.substring(0, name.length()-7);
                } else if (st.startsWith("<TaskID>")){
                    String id = st.substring(8);
                    taskID = Integer.parseInt(id.substring(0, id.length()-9));
                } else if (st.startsWith("<Description>")){
                    description = st.substring(13);
                    description = description.substring(0, description.length()-14);
                } else if (st.startsWith("<Duration>")){
                    st = st.substring(10);
                    duration = Integer.parseInt(st.substring(0, st.length()-11));
                } else if (st.startsWith("<DependsOnTaskID>")){
                    st = st.substring(17);
                    st = st.substring(0, st.length()-18);
                    dependencies.add(Integer.valueOf(st));
                } else if (st.startsWith("</Task>")){
                    task = new Task(taskID, description,duration, dependencies);
                    dependencies = new ArrayList<>();
                    tasks.add(task);
                }
            }
        }catch (Exception e){
            e.printStackTrace();
        }
        return projectList;
    }
}
