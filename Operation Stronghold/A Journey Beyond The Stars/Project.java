import java.util.HashSet;
import java.util.List;
import java.util.Set;


public class Project {
    private final String name;
    private final List<Task> tasks;
    private int durationTime = 0;
    public Project(String name, List<Task> tasks) {
        this.name = name;
        this.tasks = tasks;
    }

    /**
     * Schedule all tasks within this project such that they will be completed as early as possible.
     *
     * @return An integer array consisting of the earliest start days for each task.
     */
    public int[] getEarliestSchedule() {
        // TODO: YOUR CODE HERE
        int n = tasks.size();
        int[] returnArray = new int[n];
        Set<Integer> set = new HashSet<>();
        Digraph digraph = new Digraph(n);
        for (Task task : tasks){
            int x = 0;
            boolean a = true;
            for (int depend : task.getDependencies()){
                x = depend;
                if (!set.contains(depend)) {
                    digraph.addEdge(task.getTaskID(), depend);
                    set.add(depend);
                    a = false;
                }
            }
            if (a) digraph.addEdge(task.getTaskID(), x);
        }
        DepthFirstOrder depthFirstOrder = new DepthFirstOrder(digraph);
        for (int i : depthFirstOrder.reversePost()){
            int max = 0;
            for (int k : tasks.get(i).getDependencies()){
                if (max < returnArray[k] + tasks.get(k).getDuration()) max = returnArray[k] + tasks.get(k).getDuration();
            }
            returnArray[i] = max;
            durationTime = Math.max(durationTime, returnArray[i] + tasks.get(i).getDuration());
        }
        return returnArray;
    }


    /**
     * @return the total duration of the project in days
     */
    public int getProjectDuration() {
        int projectDuration = 0;
        // TODO: YOUR CODE HERE
        int [] schedule = getEarliestSchedule();
        projectDuration = tasks.get(schedule.length - 1).getDuration() + schedule[schedule.length - 1];
        return projectDuration;
    }

    public static void printlnDash(int limit, char symbol) {
        for (int i = 0; i < limit; i++) System.out.print(symbol);
        System.out.println();
    }

    public void printSchedule(int[] schedule) {
        int limit = 65;
        char symbol = '-';
        printlnDash(limit, symbol);
        System.out.println(String.format("Project name: %s", name));
        printlnDash(limit, symbol);

        // Print header
        System.out.println(String.format("%-10s%-45s%-7s%-5s", "Task ID", "Description", "Start", "End"));
        printlnDash(limit, symbol);
        for (int i = 0; i < schedule.length; i++) {
            Task t = tasks.get(i);
            System.out.println(String.format("%-10d%-45s%-7d%-5d", i, t.getDescription(), schedule[i], schedule[i] + t.getDuration()));
        }
        printlnDash(limit, symbol);
        System.out.println(String.format("Project will be completed in %d days.", tasks.get(schedule.length - 1).getDuration() + schedule[schedule.length - 1]));
        printlnDash(limit, symbol);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Project project = (Project) o;

        int equal = 0;

        for (Task otherTask : ((Project) o).tasks) {
            if (tasks.stream().anyMatch(t -> t.equals(otherTask))) {
                equal++;
            }
        }

        return name.equals(project.name) && equal == tasks.size();
    }

}
