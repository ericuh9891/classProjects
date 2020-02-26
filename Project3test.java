/*
Eric Y. U Huang
CISC 3320 - MW3
Project 3

This program determines if a number is a perfect number or not. The program takes in 3 arguments, first argument is the number that's
to be tested, the second number is the number of threads to use to test the number, and the third argument which is optional takes in
a true or false value to turn on console messages that displays thread statuses. If no third argument is provided, the default value is false.
The program uses a class called PerfectNumMultiThread that contains methods for determining if a number is a perfect number and also data 
structures to store factors found for said number. The PerfectNumMultiThread uses another class called Tasks which extends the thread class
from java standard library. The Tasks class will be doing the computation for computing factors and determining whether or not a number is
a perfect number.

Program Design:
I've neglected using the BigInteger class because the system I used to test this program is limited in computational power
and memory. A test of the perfect number 2,305,843,008,139,952,128 ran for 5 hours without finishing. Thus increasing
the size of the test numbers is unnessary. The program takes in the args and uses it to create an object of the PerfectNumMultiThread class.
When the object of the PerfectNumMultiThread class is created, objects of the Tasks class are also created depending on the second arguement entered.
The Tasks objects will each be assigned a portion of the numbers to be tested. The program will than call the PerfectNumMultiThread object's isPerfectNum method
which starts all the tasks objects that were created. The results from the Tasks Objects are returned to the PerfectNumMultiThread object which is then
accessible by the program. The Tasks objects will compute the factors from the numbers assigned to them but share all the factors to all other Tasks objects via 
static fields for the Tasks objects. Adding factors to these static fields are controlled with static synchronized methods to prevent race conditions.
*/

package project3test;
//Collections import to use the sort method in the Collections class
import java.util.Collections;
//Used Vector instead of ArrayList incase I need to do any operations with the iterator
import java.util.Vector;
//Class that contains the methods to determine whether a number is a perfect number or not and
//does it by using threads
class PerfectNumMultiThread{

    private long testNum; //Stores the number I want to test as a long which allows for testing of numbers from -2^63 to 2^63
    private int numThreads; //Stores the number of threads I want to use to test the test number   
    private Vector<Long> factors; //Stores the factors of the test number after it's been computed
    private long factorSum; //Stores the sum of the factors after the factors have been computed
    private Vector<Tasks> tasks = new Vector<Tasks>(); //Stores the Tasks objects
    private Tasks accessThread = new Tasks();//Tasks object used solely for accessing the static fields of the Tasks class
    private boolean displayStatus = false;//A boolean flag that's used for testing purposes. Enables PerfectNumMultiThread class and Tasks class to display important information during program execution
    private boolean isPerfectNum;
    /*
    Both contructors takes in a number that is to be tested for perfect number and the number of threads to use. 
    A boolean flag for the third argument indicates whether to print current running status of Tasks onto console.
    Also calls the createTasks method to create the Tasks for determining whether the test number is a perfect number
    */
    public PerfectNumMultiThread(long testNum, int numThreads, boolean displayStatus){
        this.testNum = testNum;
        this.numThreads = numThreads;
        this.displayStatus = displayStatus;
        createTasks(testNum,numThreads);
    }
    //Method that divides numbers that needs to be tested into seperate Tasks objects
    private void createTasks(long testNum, int numThreads){
        long divisor = (long)numThreads;
        long portionSize = testNum/divisor;
        long remainders = testNum%divisor;
        long tempHigh;
        long tempLow = 1;
        for(int i = 1; i <= numThreads; i++){
            tempHigh = i * portionSize;
            if(i == numThreads){
                tempHigh = (((portionSize * (long)i) + remainders) - 1);
            }
            tasks.add(new Tasks(tempHigh,tempLow,testNum,displayStatus));
            if(displayStatus == true){
                System.out.println("Task created with high:" + tempHigh + " and low:" + tempLow);
            }
            tempLow = tempHigh + 1;
        }
    }
    /*
    Method starts all the Tasks objects and waits for the threads to resolve before pulling the factors
    from a Tasks object
    */
    public boolean isPerfectNum(){
        try{
            //starts all the tasks objects
            for(int i = 0; i < tasks.size(); i++){
                tasks.get(i).start();
            }
            //loop that causes the main program to wait for all threads to finish before continuing
            for(int i = 0; i < tasks.size(); i++){
                tasks.get(i).join();
            }
            //Uses the Tasks object that was created for accessing static fields in the Tasks class to pull the factors found
            factors = accessThread.getFactors();
            //Adds up all the factors
            for(int i = 0; i < factors.size(); i++){
                factorSum = factorSum + factors.get(i);
            }
            //sets the boolean value of isPerfectNum
            if(factorSum == testNum){
                isPerfectNum = true;
            }
            else isPerfectNum = false;
        }
        catch (InterruptedException e){
            System.out.println("Thread Interrupted! " + e.toString());
        }
        //returns boolean value of whether test number is a perfect number or not
        finally{
            return isPerfectNum;
        }
    }
    //Standard getters and setters
    public long getTestNum() {
        return testNum;
    }

    public void setTestNum(long testNum) {
        this.testNum = testNum;
    }

    public int getNumThreads() {
        return numThreads;
    }

    public void setNumThreads(int numThreads) {
        this.numThreads = numThreads;
    }

    public Vector<Long> getFactors() {
        return factors;
    }

    public long getFactorSum() {
        return factorSum;
    }
    
    public Vector<Tasks> getTasks() {
        return tasks;
    }

    public void setTasks(Vector<Tasks> tasks) {
        this.tasks = tasks;
    }

    public Tasks getAccessThread() {
        return accessThread;
    }
    
    public boolean getDisplayStatus() {
        return displayStatus;
    }
    //sets the instance of object PerfectNumMultiThread to print to console status messages and also it's Tasks objects
    public void setDisplayStatus(boolean statusMessages) {
        this.displayStatus = statusMessages;
        tasks.get(0).setDisplayStatus(displayStatus);
    }
}
//Tasks class that is used as threads to compute whether a number is a perfect number of not
class Tasks extends Thread{
    private long high;//The upper bound of the numbers to be checked to see if it's a factor of the test number
    private long low;//The lower bound of the numbers to be checked to see if it's a factor of the test number
    private static long testNum;
    /*
    Used to determine whether the thread will terminate all other threads including itself when the sum of the factors are greater than the test number.
    The variable is set to static so all threads and access it and it's kept as volatile to ensure the most up to date value is visible to all threads
    */
    private volatile static long factorSum;
    /*
    Vector array to store all the factors found by threads and is shared by all threads by setting it static
    While I think setting an Vector array to volatile only ensures changes to the reference to the object is up to date, changes to the contents
    of the Vector array are not affected by volatile attribute. I've made it volatile just incase it does (wouldn't hurt).
    */
    private volatile static Vector<Long> factors = new Vector<Long>();
    /*
    Boolean flag that is used by each thread to determine if it needs to terminate itself. ALthough killFlag is given the volatile attribute,
    memory consistency is not needed here but it does aid in terminating threads faster if it has immediate access to the updated flag. killFlag is set to 
    static so it is shared amongst all threads
    */
    private volatile static boolean killFlag = false;
    /*
    Boolean flag used to turn on console messages for the current statuses of threads. Used for testing purposes only
    */
    private static boolean displayStatus = false;
    
    public Tasks(long high, long low, long testNum, boolean displayStatus){
        this.high = high;
        this.low = low;
        this.testNum = testNum;
        this.displayStatus = displayStatus;
    }
    //Empty constructor mainly to create a Tasks object that's used to access static fields
    public Tasks(){
    }
    //Standard getters and setters
    public static Vector<Long> getFactors() {
        return factors;
    }
    
    public static boolean getDisplayStatus() {
        return displayStatus;
    }

    public static void setDisplayStatus(boolean displayStatus) {
        Tasks.displayStatus = displayStatus;
    }
    /*
    Method given synchronized and static attribute to ensure only one thread at a time can add factors to the factor Vector array
    */
    private static synchronized void addFactor(long factor){
        factors.add(factor);
    }
    /*
    Method given synchronized and static attribute to ensure only one thread at a time can add a factor into the sum of factors
    */
    private static synchronized void addFactorSum(long factor){
        factorSum = factorSum + factor;
    }
    /*
    Method given static attribute because the parameters it uses are also static fields
    */
    private static boolean greaterThanSum(){
        if(factorSum > testNum){
            return true;
        }
        else return false;
    }
/*
The run method checks for factors starting from high to low. If a factor is found, then the synchronized methods is used to add the factor to the VectorList
and blocks other threads if they also found a factor. The factorSum is also updated when a factor is found with a synchronized method.
While the thread is running, it'll check if the killFlag is true, if it is then the thread will terminate itself. If a factorSum is greater than 
the test number then it will set the killFlag to true. Since the killFlag is a static, all threads can see it and self terminate if it is set to true.
The displayStatus flag is used to print to console when the thread starts, stops, and when it terminates other threads.
*/    
@Override
    public void run(){
        //Prints to console based on displayStatus when the thread is started, for testing purposes
        if(displayStatus == true){
            System.out.println("Thread: " + this.getId() + " started");
        }
            //Loop that runs from the high or low for testing factors
            for(long i = high; i >= low; i--){
                //If the killFlag is set to true, then thread will break out of the loop without finishing looking for factors
                if(killFlag == true){
                    //Prints to console that thread was terminated by another thread if displayStatus is true. Used for testing purposes
                    if(displayStatus == true){
                        System.out.println("Thread: " + this.getId() + " was terminated by another thread");
                    }
                    break;
                }
                //Checks if a number is a factor, if it is then the two synchronized methods to add the factors to the VectorList and to the factorSum are used
                if(testNum % i == 0){
                    addFactor(i);
                    addFactorSum(i);
                    /*
                    Checks to see if the sum of the factor is greater than the test number, if it is then it sets the killFlag to true
                    which will tell the other threads to break out of their loop and finish without looking for the rest of the factors
                    */
                    if(greaterThanSum()){
                        /*
                        Prints to console based on displayStatus when the thread determines that the sum of the factors are greater than the test number, for testing purposes
                        */
                        if(displayStatus == true){
                            System.out.println("Thread: " + this.getId() + " determined sum of factors is greater than test number");
                        }
                        //Sets the killFlag to true to signal the other threads to also exit out of their loop and not finish looking for factors
                        killFlag = true;
                        //Prints to console based on displayStatus when the thread self terminates, for testing purposes
                        if(displayStatus == true){
                            System.out.println("Thread: " + this.getId() + " is terminated");
                        }
                        break;
                    }
                }
            }
        //Prints to console based on displayStatus when the thread ends normally after checking for factors, for testing purposes
        if(displayStatus == true){
            System.out.println("Thread: " + this.getId() + " ended");
        }
    }
}

public class Project3test {
    /*
    Main method takes in up to 3 arguments, first 2 are required. First argument is the number that's checked for if it's a perfect number. The second argument
    is the number of threads to be created for checking the number for perfect number status. The third argument takes in a string of "true" or "false" which turns on/off console messages for the status of the
    program while it's running. If no third argument is given, the default value is set to false which means the console messages for program status will be turned off.
    */
    public static void main(String[] args) {
        //Stores the first argument which is the number to be checked for perfect number status
        long args1 = Long.parseLong(args[0]);
        //Stores the second argument which is the number of threads to be created to check the number for perfect number status
        int args2 = Integer.parseInt(args[1]);
        //Stores the third argument if supplied, otherwise it's set to false as default
        boolean displayStatus = false;
        //Checks if a third argument is given and stores it if a true or false value is given
        if(args.length == 3){
            if(args[2].equalsIgnoreCase("true")){
                displayStatus = true;
            }
            if(args[2].equalsIgnoreCase("false")){
                displayStatus = false;
            }
        }
        //Creates an object of PerfectNumMultiThread that will create the threads when the constructor is called
        PerfectNumMultiThread test = new PerfectNumMultiThread(args1,args2,displayStatus);
        //The .isPerfectNum() starts the threads and waits for them to finish before adding the factors found
        if(test.isPerfectNum()){
            System.out.println(test.getTestNum() + " is a perfect number");
            //Sorts the factors
            Collections.sort(test.getFactors());
            System.out.println("Factors are:");
            //Loop prints out all the factors onto console
            for(int i = 0; i < test.getFactors().size(); i++){
                System.out.println(test.getFactors().get(i) + "");
            }
            System.exit(0);
        }
        else{ 
            System.out.println(test.getTestNum() + " is not a perfect number");
            if(displayStatus == true){
                Collections.sort(test.getFactors());
                System.out.println("Factors are:");
                for(int i = 0; i < test.getFactors().size(); i++){
                    System.out.println(test.getAccessThread().getFactors().get(i) + "");
                }
            }
            System.exit(1);
        }
    }
}