// Andrew Powell 11/3/2024
// zookeepersChallenge.cpp
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Decided to not use Using Namespace std; Because you said to treat it like a professional presentation

// Create a struct that holds different details of information and organize it into category
struct Animal {
    int age;
    std::string sex;
    std::string species;
    std::string color;
    int weight;
    int birthYear;
    std::string name;
    std::string id; 
};

// creating a constant variable that will be set to the current year
const int CURRENT_YEAR = 2024;

// Alternative way for me to create a pointer for the Animal Names (creates arrays to hold species names)
const char* hyenaNames[] = { "Shenzi", "Banzai", "Ed", "Zig", "Bud", "Lou", "Kamari", "Wema", "Nne", "Madoa", "Prince Nevarah" };
const char* lionNames[] = { "Scar", "Mufasa", "Simba", "Kiara", "King", "Drooper", "Kimba", "Nala", "Leo", "Samson", "Elsa", "Cecil" };
const char* bearNames[] = { "Yogi", "Smokey", "Paddington", "Lippy", "Bungle", "Baloo", "Rupert", "Winnie the Pooh", "Snuggles", "Bert" };
const char* tigerNames[] = { "Tony", "Tigger", "Amber", "Cosimia", "Cuddles", "Dave", "Jiba", "Rajah", "Rayas", "Ryker" };

// Function to assign a name based on if the animal is a certain species and then it counts to the next name if it is taken
std::string assignName(const std::string& species, int count) {
    if (species == "hyena") return hyenaNames[count % (sizeof(hyenaNames) / sizeof(hyenaNames[0]))];
    if (species == "lion") return lionNames[count % (sizeof(lionNames) / sizeof(lionNames[0]))];
    if (species == "bear") return bearNames[count % (sizeof(bearNames) / sizeof(bearNames[0]))];
    if (species == "tiger") return tigerNames[count % (sizeof(tigerNames) / sizeof(tigerNames[0]))];
}

// Function to parse animal details and assign a name
Animal parseAnimalDetails(const std::string& line, int& hyenaCount, int& lionCount, int& bearCount, int& tigerCount) {
    Animal animal; // Declares animal
    std::istringstream iss(line); /*According to what I read this creates an input string stream from the line
                                    that can pick out individual pieces of information from the sentence (istringstream) */

    // Extract age
    iss >> animal.age;

    // Extract sex
    std::string sexStr;
    iss >> sexStr >> sexStr; // By repeating I was able to Skip the word old 
    iss >> animal.sex;

    // Extracting species
    std::string speciesStr;
    iss >> speciesStr;
    animal.species = speciesStr.substr(0, speciesStr.size() - 1); // Chatgpt recommended this to remove commas I could not remove on my own

    // Simple math to calculate birth year
    animal.birthYear = CURRENT_YEAR - animal.age;

    // Find animal color
    std::string skip;
    std::getline(iss, skip, ','); // Chatgpt reccommended I Skip until "color" using getline

    // Extracting color
    std::getline(iss, skip, ',');
    std::istringstream colorStream(skip);
    colorStream >> animal.color;

    // Extracting weight
    std::string weightStr;
    std::getline(iss, weightStr);
    std::istringstream weightStream(weightStr);
    weightStream >> animal.weight;
    weightStream.ignore(6); // Ignored the word "pounds" (again a chatgpt recommendation)

    // Assign a name and ID based on species and count to make sure each hyena for example has a unique count
    if (animal.species == "hyena") {
        animal.name = assignName(animal.species, hyenaCount);
        animal.id = "Hy" + std::to_string(++hyenaCount);
    }
    else if (animal.species == "lion") {
        animal.name = assignName(animal.species, lionCount);
        animal.id = "Li" + std::to_string(++lionCount);
    }
    else if (animal.species == "bear") {
        animal.name = assignName(animal.species, bearCount);
        animal.id = "Be" + std::to_string(++bearCount);
    }
    else if (animal.species == "tiger") {
        animal.name = assignName(animal.species, tigerCount);
        animal.id = "Ti" + std::to_string(++tigerCount);
    }

    // Format the ID to be always two digits
    std::string idPrefix = animal.id.substr(0, 2); // Extract the prefix
    int countNumber = std::stoi(animal.id.substr(2)); // Get the count as an integer (stoi converts text into Int)
    std::string formattedCount = (countNumber < 10 ? "0" : "") + std::to_string(countNumber); // Pad with zero if necessary (added because output was 1 instead of 01)
    animal.id = idPrefix + formattedCount; // Combine prefix and formatted count

    return animal;
}

// Function to output animal details
void outputAnimals(const std::string& title, const std::vector<Animal>& animals, std::ostream& os) {
    os << title << ":\n"; //os means Ostream for File output according to my google search
    for (const auto& animal : animals) {
        os << "ID: " << animal.id << ", Name: " << animal.name << ", Age: " << animal.age
            << ", Sex: " << animal.sex << ", Color: " << animal.color
            << ", Weight: " << animal.weight << " pounds\n";
    }
}

int main() {
    std::ifstream file("C:/Users/patho/dataFiles/arrivingAnimals.txt"); // Read arrivingAnimals.txt
    std::vector<Animal> animals; // Use information to create vector to hold objects for Animal

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    int hyenaCount = 0, lionCount = 0, bearCount = 0, tigerCount = 0;

    while (std::getline(file, line)) {
        animals.push_back(parseAnimalDetails(line, hyenaCount, lionCount, bearCount, tigerCount));
    }

    file.close();

    // Define vectors for each species
    std::vector<Animal> hyenas, lions, bears, tigers;

    // Sort animals into their respective categories
    for (const auto& animal : animals) {
        if (animal.species == "hyena") {
            hyenas.push_back(animal);
        }
        else if (animal.species == "lion") {
            lions.push_back(animal);
        }
        else if (animal.species == "bear") {
            bears.push_back(animal);
        }
        else if (animal.species == "tiger") {
            tigers.push_back(animal);
        }
    }

    // Output the categorized lists to console
    outputAnimals("Hyenas", hyenas, std::cout);
    std::cout << "\n";
    outputAnimals("Lions", lions, std::cout);
    std::cout << "\n";
    outputAnimals("Bears", bears, std::cout);
    std::cout << "\n";
    outputAnimals("Tigers", tigers, std::cout);

    // Write to zooPopulation.txt
    std::ofstream outputFile("C:/Users/patho/dataFiles/zooPopulation.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file!" << std::endl;
        return 1;
    }

    outputAnimals("Hyenas", hyenas, outputFile);
    outputFile << "\n";
    outputAnimals("Lions", lions, outputFile);
    outputFile << "\n";
    outputAnimals("Bears", bears, outputFile);
    outputFile << "\n";
    outputAnimals("Tigers", tigers, outputFile);

    outputFile.close();
    return 0;
}
