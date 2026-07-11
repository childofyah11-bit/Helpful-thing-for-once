import java.util.ArrayList;
import java.util.Scanner;

public class WeatherDashboard {

    // Simple class to store city weather inputs together
    static class WeatherReading {
        String city;
        double temperature; // in Celsius
        double humidity;    // percentage

        WeatherReading(String city, double temperature, double humidity) {
            this.city = city;
            this.temperature = temperature;
            this.humidity = humidity;
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        ArrayList<WeatherReading> records = new ArrayList<>();
        
        System.out.println("=========================================");
        System.out.println("     Regional Weather Data Console       ");
        System.out.println("=========================================");

        while (true) {
            System.out.print("\nEnter city name (or type 'exit' to view report): ");
            String city = scanner.nextLine().trim();
            
            if (city.equalsIgnoreCase("exit")) {
                break;
            }

            // Quick validation check to make sure the user didn't just hit enter
            if (city.isEmpty()) {
                System.out.println("Oops! City name cannot be empty. Try again.");
                continue;
            }

            try {
                System.out.print("Enter temperature in Celsius (°C): ");
                double temp = Double.parseDouble(scanner.nextLine());

                System.out.print("Enter relative humidity % (0-100): ");
                double humidity = Double.parseDouble(scanner.nextLine());

                // Guard rails for humidity range
                if (humidity < 0 || humidity > 100) {
                    System.out.println("Invalid data. Humidity must be between 0 and 100%.");
                    continue;
                }

                // Add data to our storage list
                records.add(new WeatherReading(city, temp, humidity));
                System.out.println("Successfully logged data for " + city + ".");

            } catch (NumberFormatException e) {
                System.out.println("Error: Please enter valid decimal numbers for weather metrics.");
            }
        }

        // Print final analytical brief if we actually have metrics to work with
        if (records.isEmpty()) {
            System.out.println("\nNo data collected today. Goodbye!");
        } else {
            printSummaryReport(records);
        }
        
        scanner.close();
    }

    private static void printSummaryReport(ArrayList<WeatherReading> records) {
        System.out.println("\n=================================================");
        System.out.println("             WEATHER ANALYSIS SUMMARY            ");
        System.out.println("=================================================");
        System.out.printf("%-15s %-12s %-10s %-15s\n", "City", "Temp (°C)", "Humidity", "Health Advisory");
        System.out.println("-------------------------------------------------");

        double tempSum = 0;
        WeatherReading peakHeatRecord = records.get(0);

        for (WeatherReading r : records) {
            tempSum += r.temperature;
            
            // Check for the highest recorded temp
            if (r.temperature > peakHeatRecord.temperature) {
                peakHeatRecord = r;
            }

            // Real-world threshold metrics to determine heat hazard warnings
            String alertMessage = "Normal Conditions";
            if (r.temperature >= 35 && r.humidity >= 70) {
                alertMessage = "CRITICAL HEAT RISK! 🔥";
            } else if (r.temperature >= 30 && r.humidity >= 50) {
                alertMessage = "High Caution ⚠️";
            }

            System.out.printf("%-15s %-12.1f %-10.0f%% %-15s\n", 
                r.city, r.temperature, r.humidity, alertMessage);
        }

        double averageTemp = tempSum / records.size();

        System.out.println("-------------------------------------------------");
        System.out.printf("Average Temperature:  %.2f°C\n", averageTemp);
        System.out.printf("Highest Peak Target:  %s at %.1f°C\n", peakHeatRecord.city, peakHeatRecord.temperature);
        System.out.println("=================================================");
    }
}
