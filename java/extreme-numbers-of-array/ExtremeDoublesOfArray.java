import java.util.Arrays;

/*
 одномерный массив из 10 вещественных элементов,
 ...
 максимальным и минимальным элементами;
*/
class ExtremeDoublesOfArray {
    public static void main(String[] args){
        double[] numbers;
        double max = 0, min = 0;
        int len = 10;
        boolean maxIsSet = false, minIsSet = false;
        numbers = generateRandomIntArray(len);
        Arrays.sort(numbers); // sort an array to ease visual validation of a result
        System.out.print("Generated array: ");
        for (int i = 0; i < len; i++) {
            System.out.print(numbers[i] + "; ");
            if (!minIsSet) {
                min = numbers[i];
                minIsSet = true;
            }
            if (!maxIsSet) {
                max = numbers[i];
                maxIsSet = true;
            }
            if (min > numbers[i]) {
                min = numbers[i];
            }
            if (max < numbers[i]) {
                max = numbers[i];
            }
        }

        System.out.println(" ");
        System.out.println("Min element: " + min);
        System.out.println("Max element: " + max);
    }
    static double[] generateRandomIntArray(int len) {
        double[] numbers;
        numbers = new double[len];
        for (int i = 0; i < len; i++) {
            numbers[i] = getRandomNumber(-10000000d, 100000000d);
        }

        return numbers;
    }
    static double getRandomNumber(double min, double max) {
        return (double) ((Math.random() * (max - min)) + min);
    }
}
