/*
 одномерный массив из 10 вещественных элементов,
 вычислить произведение элементов массива,
 расположенных между максимальным и минимальным элементами;
*/
class DoublesOfArrayMultiplier {
    public static void main(String[] args){
        double[] numbers;
        int len = 10;
        boolean maxIsSet = false, minIsSet = false;
        int minPos = 0;
        int maxPos = 0;
        double min = 0, max = 0;
        numbers = generateRandomIntArray(len);
        for (int i = 0; i < len; i++) {
            if (!minIsSet) {
                minPos = i;
                min = numbers[i];
                minIsSet = true;
            }
            if (!maxIsSet) {
                maxPos = i;
                max = numbers[i];
                maxIsSet = true;
            }
            if (min > numbers[i]) {
                minPos = i;
                min = numbers[i];
            }
            if (max < numbers[i]) {
                maxPos = i;
                max = numbers[i];
            }
        }
        int startFrom, finishAt;
        startFrom = minPos + 1;
        finishAt = maxPos - 1;
        if (minPos > maxPos) {
            startFrom = maxPos + 1;
            finishAt = minPos - 1;
        }
        if (finishAt - startFrom <= 1) {
            System.out.println("No values in between");
            return;
        }
        if (startFrom + 2 == finishAt) {
            System.out.println("Single value in between: " + numbers[startFrom + 1]);
            return;
        }
        double result = numbers[startFrom];
        for (int k = startFrom + 1; k <= finishAt; k++) {
            System.out.println("Process: " + result + " * " + numbers[k]); // for visual comparison

            result = result * numbers[k];
        }

        System.out.println("Result: " + result + "\n");

        // for visual comparison
        System.out.print("Generated array: ");
        for (int i = 0; i < len; i++) {
            System.out.print(numbers[i] + "; ");
        }
        System.out.println(" ");
        System.out.println("Min element: " + min);
        System.out.println("Max element: " + max);
    }
    static double[] generateRandomIntArray(int len) {
        double[] numbers;
        numbers = new double[len];
        for (int i = 0; i < len; i++) {
            numbers[i] = getRandomNumber();
        }

        return numbers;
    }
    static double getRandomNumber() {
        return (double) Math.random();
    }
}
