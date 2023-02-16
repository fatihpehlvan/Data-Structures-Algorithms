import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;

/**
 * This class accomplishes Mission Exterminate
 */
public class OptimalFinalDefenseGP
{
    private ArrayList<Integer> bombWeights;

    public OptimalFinalDefenseGP(ArrayList<Integer> bombWeights) {
        this.bombWeights = bombWeights;
    }

    public ArrayList<Integer> getBombWeights() {
        return bombWeights;
    }

    /**
     *
     * @param maxNumberOfAvailableAUAVs the maximum number of available AUAVs to be loaded with bombs
     * @param maxAUAVCapacity the maximum capacity of an AUAV
     * @return the minimum number of AUAVs required using first fit approach over reversely sorted items.
     * Must return -1 if all bombs can't be loaded onto the available AUAVs
     */
    public int getMinNumberOfAUAVsToDeploy(int maxNumberOfAvailableAUAVs, int maxAUAVCapacity)
    {
        int[] index = new int[bombWeights.size()];
        // First sort all weights in decreasing order
        bombWeights.sort(Collections.reverseOrder());
        // Initialize result (Count of AUAVs)
        int result = 0;
        int n = bombWeights.size();
        int counter = 0;
        // Create an array to store remaining space in AUAVs, there can be at most maxNumberOfAvailableAUAVs AUAVs
        // Place items one by one
        for (int i = 0; i < n ; i++){
            if (index[i] == 1) continue;
            counter++;
            int max = maxAUAVCapacity;
            if (bombWeights.get(i) > max) return -1;
            else if (bombWeights.get(i) == max) {
                index[i] = 1;
                result++;
                if (result > maxNumberOfAvailableAUAVs) return -1;
                continue;
            } else {
                index[i] = 1;
                max -= bombWeights.get(i);
            }
            for (int j = i+1; j < n; j++){
                if (index[j] == 1) continue;
                int element = bombWeights.get(j);
                if (max - element > 0){
                    counter++;
                    max-= element;
                    index[j] = 1;
                } else if (max - element == 0){
                    counter++;
                    index[j] = 1;
                    break;
                }
            }
            result++;
            if (result > maxNumberOfAvailableAUAVs) return -1;
        }
        if (counter == bombWeights.size() && result <= maxNumberOfAvailableAUAVs) return result;
        return -1;
    }
    public void printFinalDefenseOutcome(int maxNumberOfAvailableAUAVs, int AUAV_CAPACITY){
        int minNumberOfAUAVsToDeploy = this.getMinNumberOfAUAVsToDeploy(maxNumberOfAvailableAUAVs, AUAV_CAPACITY);
        if(minNumberOfAUAVsToDeploy!=-1) {
            System.out.println("The minimum number of AUAVs to deploy for complete extermination of the enemy army: " + minNumberOfAUAVsToDeploy);
        }
        else{
            System.out.println("We cannot load all the bombs. We are doomed.");
        }
    }
}
