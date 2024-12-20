#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Animal struct definition
struct Animal {
    int age;
    std::string sex;
    std::string species;
    std::string color;
    int weight;
    int birthYear;
    std::string name;
    std::string id; // Unique identifier for each animal
};

// Hard-coded current year
const int CURRENT_YEAR = 2024;

// Define arrays for names
const char* hyenaNames[] = {
    "Shenzi", "Banzai", "Ed", "Zig", "Bud", "Lou", "Kamari", "Wema", "Nne", "Madoa", "Prince Nevarah"
};
const char* lionNames[] = {
    "Scar", "Mufasa", "Simba", "Kiara", "King", "Drooper", "Kimba", "Nala", "Leo", "Samson", "Elsa", "Cecil"
};
const char* bearNames[] = {
    "Yogi", "Smokey", "Paddington", "Lippy", "Bungle", "Baloo", "Rupert", "Winnie the Pooh", "Snuggles", "Bert"
};
const char* tigerNames[] = {
    "Tony", "Tigger", "Amber", "Cosimia", "Cuddles", "Dave", "Jiba", "Rajah", "Rayas", "Ryker"
};

// Define species abbreviation and counters
std::string getSpeciesAbbreviation(const std::string& species) {
    if (species == "hyena") return "Hy";
    if (species == "lion") return "Li";
    if (species == "bear") return "Be";
    if (species == "tiger") return "Ti";
    return "XX"; // Default if species not found
}

// Function to assign a name based on species and count
std::string assignName(const std::string& species, int count) {
    if (species == "hyena") {
        return hyenaNames[count % (sizeof(hyenaNames) / sizeof(hyenaNames[0]))];
    } else if (species == "lion") {
        return lionNames[count % (sizeof(lionNames) / sizeof(lionNames[0]))];
    } else if (species == "bear") {
        return bearNames[count % (sizeof(bearNames) / sizeof(bearNames[0]))];
    } else if (species == "tiger") {
        return tigerNames[count % (sizeof(tigerNames) / sizeof(tigerNames[0]))];
    }
    return "Unnamed"; // Default name if species not found
}

// Function to generate a unique identifier
std::string generateUniqueId(const std::string& species, int count) {
    std::string abbreviation = getSpeciesAbbreviation(species);
    return abbreviation + (count < 10 ? "0" : "") + std::to_string(count); // Format: Hy01, Li02, etc.
}

// Parse animal details and assign a name
Animal parseAnimalDetails(const std::string& line, int& hyenaCount, int& lionCount, int& bearCount, int& tigerCount) {
    Animal animal;
    std::istringstream iss(line);

    // Extracting age
    std::string ageStr;
    iss >> ageStr;
    animal.age = std::stoi(ageStr);

    // Extracting sex
    std::string sexStr;
    iss >> sexStr;
    iss >> sexStr; // "old"
    iss >> animal.sex;

    // Extracting species
    std::string speciesStr;
    iss >> speciesStr;
    animal.species = speciesStr.substr(0, speciesStr.size() - 1); // Remove comma

    // Calculate birth year
    animal.birthYear = CURRENT_YEAR - animal.age;

    // Skip to color
    std::string skip;
    std::getline(iss, skip, ','); // Skip until "color"

    // Extracting color
    std::getline(iss, skip, ',');
    std::istringstream colorStream(skip);
    std::string colorLabel;
    colorStream >> colorLabel;
    animal.color = colorLabel;

    // Extracting weight
    std::string weightStr;
    std::getline(iss, weightStr);
    std::istringstream weightStream(weightStr);
    weightStream >> animal.weight;
    weightStream.ignore(6); // Ignore "pounds"

    // Assign a name based on species and count
    if (animal.species == "hyena") {
        animal.name = assignName(animal.species, hyenaCount);
        animal.id = generateUniqueId(animal.species, ++hyenaCount);
    } else if (animal.species == "lion") {
        animal.name = assignName(animal.species, lionCount);
        animal.id = generateUniqueId(animal.species, ++lionCount);
    } else if (animal.species == "bear") {
        animal.name = assignName(animal.species, bearCount);
        animal.id = generateUniqueId(animal.species, ++bearCount);
    } else if (animal.species == "tiger") {
        animal.name = assignName(animal.species, tigerCount);
        animal.id = generateUniqueId(animal.species, ++tigerCount);
    } else {
        animal.name = "Unnamed";
        animal.id = "XX00"; // Default ID if species not found
    }

    return animal;
}

int main() {
    std::ifstream file("C:/Users/patho/zookeeper'sChallenge/dataFiles/arrivingAnimals.txt");
    std::vector<Animal> animals;

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

    // Output the extracted details
    for (const auto& animal : animals) {
        std::cout << "ID: " << animal.id
                  << ", Name: " << animal.name
                  << ", Age: " << animal.age
                  << ", Sex: " << animal.sex
                  << ", Species: " << animal.species
                  << ", Color: " << animal.color
                  << ", Weight: " << animal.weight << " pounds"
                  << ", Birth Year: " << animal.birthYear
                  << std::endl;
    }

    return 0;
}
