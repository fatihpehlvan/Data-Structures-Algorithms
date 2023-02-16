import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * This class accomplishes Mission Nuke'm
 */
public class DefenseAgainstEnemyTroops {
    private ArrayList<Integer> numberOfEnemiesArrivingPerHour;

    public DefenseAgainstEnemyTroops(ArrayList<Integer> numberOfEnemiesArrivingPerHour){
        this.numberOfEnemiesArrivingPerHour = numberOfEnemiesArrivingPerHour;
    }

    public ArrayList<Integer> getNumberOfEnemiesArrivingPerHour() {
        return numberOfEnemiesArrivingPerHour;
    }

    private int getRechargedWeaponPower(int hoursCharging){
        return hoursCharging*hoursCharging;
    }

    /**
     *     Function to implement the given dynamic programming algorithm
     *     SOL(0) <- 0
     *     HOURS(0) <- [ ]
     *     For{j <- 1...N}
     *         SOL(j) <- max_{0<=i<j} [ (SOL(i) + min[ E(j), P(j − i) ] ]
     *         HOURS(j) <- [HOURS(i), j]
     *     EndFor
     *
     * @return OptimalEnemyDefenseSolution
     */
    public OptimalEnemyDefenseSolution getOptimalDefenseSolutionDP(){
        // TODO: YOUR CODE HERE
        int n = numberOfEnemiesArrivingPerHour.size();
        int[] sol = new int[n+1];
        int[][] hours = new int[n+1][];
        hours[0] = new int[]{};
        sol[0] = 0;

        for (int j = 1; j <= n; j++){
            int max = 0;
            int indexI = 0;
            for (int i = 0; i < j; i++){
                int result = (int) (sol[i] + Math.min(numberOfEnemiesArrivingPerHour.get(j-1), Math.pow(j-i,2)));
                if (max < result) {
                    max = result;
                    indexI = i;
                }
            }
            //if (sol[j] == 0 || max < sol[j]) {
                sol[j] = max;
                int[] copyArray = new int[hours[indexI].length + 1];
                System.arraycopy(hours[indexI], 0, copyArray, 0, hours[indexI].length);
                copyArray[hours[indexI].length] = j;
                hours[j] = copyArray;
            //}
        }
        int index = 0;
        int max = 0;
        for (int i = 0; i < sol.length;i++){
            if (sol[i] > max){
                max = sol[i];
                index = i;
            }
        }
        ArrayList<Integer> returnArray = new ArrayList<>();
        for (int i = 0; i < hours[index].length; i++)
            returnArray.add(hours[index][i]);
        return new OptimalEnemyDefenseSolution(max, returnArray);
    }
}
