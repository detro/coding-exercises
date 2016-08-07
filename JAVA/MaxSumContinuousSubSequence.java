import java.util.HashMap;
import java.util.Map;

/**
 * Maximum subarray problem is the task of finding the contiguous subarray
 * within a one-dimensional array of numbers which has the largest sum.
 *
 * For example, for the sequence of values
 *
 *   −2, 1, −3, 4, −1, 2, 1, −5, 4;
 *
 * the contiguous subarray with the largest sum is
 *
 *   4, −1, 2, 1
 *
 * with sum 6.
 *
 * NOTE: This is a Dynamic Programming solution for this problem.
 * For more info, consult literature or just start from
 * {@link https://en.wikipedia.org/wiki/Maximum_subarray_problem}.
 */
public class MaxSumContinuousSubSequence {

    private long maxSumSubSequenceValue;
    private int[] maxSumSubSequence;

    public MaxSumContinuousSubSequence(int[] input) {
        int[] sumSubSequenceValues = new int[input.length];
        Map<Integer, int[]> sumSubSequences = new HashMap<Integer, int[]>();

        int maxSubSequenceIdx = 0;
        sumSubSequenceValues[0] = input[0];
        sumSubSequences.put(0, new int[]{0, 0});

        for (int i = 1; i < input.length; ++i) {
            // Dynamic Programming core function
            if (sumSubSequenceValues[i-1] + input[i] > input[i]) {
                sumSubSequenceValues[i] = sumSubSequenceValues[i-1] + input[i];
                sumSubSequences.put(i, new int[]{ sumSubSequences.get(i-1)[0], i });
            } else {
                sumSubSequenceValues[i] = input[i];
                sumSubSequences.put(i, new int[]{i, i});
            }

            // Update max in situ (to avoid re-parsing later)
            if (sumSubSequenceValues[i] > sumSubSequenceValues[maxSubSequenceIdx]) {
                maxSubSequenceIdx = i;
            }
        }

        maxSumSubSequenceValue = sumSubSequenceValues[maxSubSequenceIdx];
        maxSumSubSequence = sumSubSequences.get(maxSubSequenceIdx);
    }

    public long getValue() {
        return maxSumSubSequenceValue;
    }

    public int[] getSequence() {
        return maxSumSubSequence;
    }

    public static void main(String[] args) {
//        int[] input = {6, -1, 8, -5, -1, 2, 7, -9, -1, -2, -2, 11};
        int[] input = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

        MaxSumContinuousSubSequence calc = new MaxSumContinuousSubSequence(input);
        System.out.println(String.format("Max Sum sub-sequence is between [%d, %d] and is %d",
                calc.getSequence()[0],
                calc.getSequence()[1],
                calc.getValue()));
    }

}
