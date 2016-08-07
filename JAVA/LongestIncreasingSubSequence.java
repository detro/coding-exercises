import java.util.List;
import java.util.ArrayList;

/**
 * Find the longest, non-necessarily contiguous, increasing sub-sequence in an array of integers.
 * The array should contain both positive and negative numbers.
 *
 * NOTE: The solution to this problem is reached via Dynamic Programming.
 */
public class LongestIncreasingSubSequence {

  private List<Integer> result;

  public LongestIncreasingSubSequence(int[] input) {
    int[] L = new int[input.length];      //< Longest Increasing sequence ending at "j"
    int[] Lprev = new int[input.length];  //< Previous element to "j" in the sequence of "L[j]"

    L[0] = 1;       //< first sequence is made of 1 element
    Lprev[0] = -1;  //< first sequence has no previous
    int maxL = 0;   //< at this stage, "0" is where the Longest Increasing sequence is

    for (int j = 1; j < input.length; ++j) {
      // Initialize "L[j]" so we can calculate it's "max length"
      L[j] = 0;

      for (int i = 0; i < j; ++i) {
        // If it's increasing, and it sequence length grows by adding "i" to the sequence
        if (input[i] <= input[j] && L[j] < L[i] + 1) {
          L[j] = L[i] + 1;
          Lprev[j] = i;
        }
      }

      if (L[maxL] < L[j]) {
        maxL = j;
      }
    }

    result = new ArrayList<Integer>();
    int curr = maxL;
    while (curr != -1) {
      result.add(0, input[curr]);
      curr = Lprev[curr];
    }
  }

  public List<Integer> getResult() {
    return result;
  }

  public static void main(String[] args) {
//        int[] input = {6, -1, 8, -5, -1, 2, 7, -9, -1, -2, -2, 11};
//    int[] input = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int[] input = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};

    LongestIncreasingSubSequence calc = new LongestIncreasingSubSequence(input);
    System.out.print("Solution: [ ");
    for (int element : calc.getResult()) {
      System.out.print(element + " ");
    }
    System.out.println("]");
  }
}
