// Multi Linked List Implementation in C++
#include <iostream>
#include <string>
#include <limits> // Fix for numeric_limits
using namespace std;

// Node structure for Child (Tim Pelaksana)
struct ChildNode {
    string teamName;
    ChildNode* nextChild;
};

// Node structure for Relation (Proyek)
struct RelationNode {
    string projectName;
    ChildNode* team;
    RelationNode* nextRelation;
};

// Node structure for Parent (Kota)
struct ParentNode {
    string cityName;
    RelationNode* projects;
    ParentNode* nextParent;
};

// Main Multi Linked List Class
class MultiLinkedList {
private:
    ParentNode* head;

    // Function to add a city
    void addCity(const string& cityName) {
        ParentNode* newCity = new ParentNode{cityName, nullptr, head};
        head = newCity;
    }

    // Function to add a project to a city
    void addProject(const string& cityName, const string& projectName) {
        ParentNode* city = head;
        while (city != nullptr && city->cityName != cityName) {
            city = city->nextParent;
        }
        if (city != nullptr) {
            RelationNode* newProject = new RelationNode{projectName, nullptr, city->projects};
            city->projects = newProject;
        }
    }

    // Function to add a team to a project in a city
    void addTeam(const string& cityName, const string& projectName, const string& teamName) {
        ParentNode* city = head;
        while (city != nullptr && city->cityName != cityName) {
            city = city->nextParent;
        }
        if (city != nullptr) {
            RelationNode* project = city->projects;
            while (project != nullptr && project->projectName != projectName) {
                project = project->nextRelation;
            }
            if (project != nullptr) {
                ChildNode* newTeam = new ChildNode{teamName, project->team};
                project->team = newTeam;
            }
        }
    }

    // Function to delete a city
    void deleteCity(const string& cityName) {
        ParentNode* city = head;
        ParentNode* prevCity = nullptr;
        while (city != nullptr && city->cityName != cityName) {
            prevCity = city;
            city = city->nextParent;
        }
        if (city != nullptr) {
            if (prevCity != nullptr) {
                prevCity->nextParent = city->nextParent;
            } else {
                head = city->nextParent;
            }
            delete city;
            cout << "Kota " << cityName << " berhasil dihapus." << endl;
        }
    }

    // Function to delete a project from a city
    void deleteProject(const string& cityName, const string& projectName) {
        ParentNode* city = head;
        while (city != nullptr && city->cityName != cityName) {
            city = city->nextParent;
        }
        if (city != nullptr) {
            RelationNode* project = city->projects;
            RelationNode* prevProject = nullptr;
            while (project != nullptr && project->projectName != projectName) {
                prevProject = project;
                project = project->nextRelation;
            }
            if (project != nullptr) {
                if (prevProject != nullptr) {
                    prevProject->nextRelation = project->nextRelation;
                } else {
                    city->projects = project->nextRelation;
                }
                delete project;
                cout << "Proyek " << projectName << " berhasil dihapus dari kota " << cityName << "." << endl;
            }
        }
    }

    // Function to delete a team from a project in a city
    void deleteTeam(const string& cityName, const string& projectName, const string& teamName) {
        ParentNode* city = head;
        while (city != nullptr && city->cityName != cityName) {
            city = city->nextParent;
        }
        if (city != nullptr) {
            RelationNode* project = city->projects;
            while (project != nullptr && project->projectName != projectName) {
                project = project->nextRelation;
            }
            if (project != nullptr) {
                ChildNode* team = project->team;
                ChildNode* prevTeam = nullptr;
                while (team != nullptr && team->teamName != teamName) {
                    prevTeam = team;
                    team = team->nextChild;
                }
                if (team != nullptr) {
                    if (prevTeam != nullptr) {
                        prevTeam->nextChild = team->nextChild;
                    } else {
                        project->team = team->nextChild;
                    }
                    delete team;
                    cout << "Tim " << teamName << " berhasil dihapus dari proyek " << projectName << " di kota " << cityName << "." << endl;
                }
            }
        }
    }

    // Function to find a city
    ParentNode* findCity(const string& cityName) {
        ParentNode* city = head;
        while (city != nullptr && city->cityName != cityName) {
            city = city->nextParent;
        }
        return city;
    }

    // Function to find a project in a city
    RelationNode* findProject(const string& cityName, const string& projectName) {
        ParentNode* city = findCity(cityName);
        if (city != nullptr) {
            RelationNode* project = city->projects;
            while (project != nullptr && project->projectName != projectName) {
                project = project->nextRelation;
            }
            return project;
        }
        return nullptr;
    }

    // Function to find a team in a project in a city
    ChildNode* findTeam(const string& cityName, const string& projectName, const string& teamName) {
        RelationNode* project = findProject(cityName, projectName);
        if (project != nullptr) {
            ChildNode* team = project->team;
            while (team != nullptr && team->teamName != teamName) {
                team = team->nextChild;
            }
            return team;
        }
        return nullptr;
    }

public:
    MultiLinkedList() : head(nullptr) {
        addCity("Kota Serang");
        addProject("Kota Serang", "Proyek Infrastruktur Jalan");
        addTeam("Kota Serang", "Proyek Infrastruktur Jalan", "Tim Pembangunan Jalan");
        addProject("Kota Serang", "Proyek Pembangunan Sekolah");
        addTeam("Kota Serang", "Proyek Pembangunan Sekolah", "Tim Pendidikan");
        addProject("Kota Serang", "Proyek Revitalisasi Pasar Tradisional");
        addTeam("Kota Serang", "Proyek Revitalisasi Pasar Tradisional", "Tim Ekonomi Lokal");

        addCity("Kota Cilegon");
        addProject("Kota Cilegon", "Proyek Perluasan Pelabuhan");
        addTeam("Kota Cilegon", "Proyek Perluasan Pelabuhan", "Tim Pembangunan Jalan");

        addCity("Kota Tangerang");

        addCity("Kota Tangerang Selatan");
        addProject("Kota Tangerang Selatan", "Proyek Digitalisasi Administrasi");
        addTeam("Kota Tangerang Selatan", "Proyek Digitalisasi Administrasi", "Tim Teknologi Informasi");
        addProject("Kota Tangerang Selatan", "Proyek Pengembangan Ruang Hijau");
        addTeam("Kota Tangerang Selatan", "Proyek Pengembangan Ruang Hijau", "Tim Tata Kota");
    }

    // Function to Show All Elements
    void showAllElements() {
        ParentNode* city = head;
        while (city != nullptr) {
            cout << "City: " << city->cityName << endl;
            RelationNode* project = city->projects;
            while (project != nullptr) {
                cout << "  Project: " << project->projectName << endl;
                ChildNode* team = project->team;
                while (team != nullptr) {
                    cout << "    Team: " << team->teamName << endl;
                    team = team->nextChild;
                }
                project = project->nextRelation;
            }
            city = city->nextParent;
        }
    }

    // Function to Show Cities
    void showCities() {
        ParentNode* city = head;
        while (city != nullptr) {
            cout << "City: " << city->cityName << endl;
            city = city->nextParent;
        }
    }

    // Function to Show Projects
    void showProjects() {
        ParentNode* city = head;
        while (city != nullptr) {
            RelationNode* project = city->projects;
            while (project != nullptr) {
                cout << "Project: " << project->projectName << " in City: " << city->cityName << endl;
                project = project->nextRelation;
            }
            city = city->nextParent;
        }
    }

    // Function to Show Teams
    void showTeams() {
        ParentNode* city = head;
        while (city != nullptr) {
            RelationNode* project = city->projects;
            while (project != nullptr) {
                ChildNode* team = project->team;
                while (team != nullptr) {
                    cout << "Team: " << team->teamName << " in Project: " << project->projectName << " in City: " << city->cityName << endl;
                    team = team->nextChild;
                }
                project = project->nextRelation;
            }
            city = city->nextParent;
        }
    }

    // Function to Show All Data Only in List City
    void showAllDataInListCity() {
        ParentNode* city = head;
        while (city != nullptr) {
            cout << "City: " << city->cityName << endl;
            city = city->nextParent;
        }
    }

    // Function to Show All Data Only in List Projects
    void showAllDataInListProjects() {
        ParentNode* city = head;
        while (city != nullptr) {
            RelationNode* project = city->projects;
            while (project != nullptr) {
                cout << "Project: " << project->projectName << " in City: " << city->cityName << endl;
                project = project->nextRelation;
            }
            city = city->nextParent;
        }
    }

    // Function to Show All Data Only in List Teams
    void showAllDataInListTeams() {
        ParentNode* city = head;
        while (city != nullptr) {
            RelationNode* project = city->projects;
            while (project != nullptr) {
                ChildNode* team = project->team;
                while (team != nullptr) {
                    cout << "Team: " << team->teamName << endl;
                    team = team->nextChild;
                }
                project = project->nextRelation;
            }
            city = city->nextParent;
        }
    }

    // Function to Show Child Data from a Specific Parent
    void showChildDataFromParent(const string& cityName) {
        ParentNode* city = findCity(cityName);
        if (city != nullptr) {
            cout << "City: " << city->cityName << endl;
            RelationNode* project = city->projects;
            while (project != nullptr) {
                ChildNode* team = project->team;
                while (team != nullptr) {
                    cout << "    Team: " << team->teamName << endl;
                    team = team->nextChild;
                }
                project = project->nextRelation;
            }
        } else {
            cout << "Kota tidak ditemukan." << endl;
        }
    }

    // Function to Show Parent Data with Related Child Data
    void showParentWithChildData() {
        ParentNode* city = head;
        while (city != nullptr) {
            cout << "City: " << city->cityName << endl;
            ChildNode* team;
            RelationNode* project = city->projects;
            while (project != nullptr) {
                team = project->team;
                while (team != nullptr) {
                    cout << "    Team: " << team->teamName << endl;
                    team = team->nextChild;
                }
                project = project->nextRelation;
            }
            city = city->nextParent;
        }
    }

    // Function to Show Child Data with Related Parent Data
    void showChildWithParentData() {
        ParentNode* city = head;
        while (city != nullptr) {
            RelationNode* project = city->projects;
            while (project != nullptr) {
                ChildNode* team = project->team;
                while (team != nullptr) {
                    cout << "Team: " << team->teamName << " in Project: " << project->projectName << " in City: " << city->cityName << endl;
                    team = team->nextChild;
                }
                project = project->nextRelation;
            }
            city = city->nextParent;
        }
    }

    // Function to Show Parent Data Related to a Specific Child
    void showParentWithSpecificChild(const string& teamName) {
        ParentNode* city = head;
        bool found = false;
        while (city != nullptr) {
            RelationNode* project = city->projects;
            while (project != nullptr) {
                ChildNode* team = project->team;
                while (team != nullptr) {
                    if (team->teamName == teamName) {
                        cout << "City: " << city->cityName << " has Team: " << team->teamName << " in Project: " << project->projectName << endl;
                        found = true;
                    }
                    team = team->nextChild;
                }
                project = project->nextRelation;
            }
            city = city->nextParent;
        }
        if (!found) {
            cout << "Team " << teamName << " not found in any city." << endl;
        }
    }

    // Function to count projects for each city
    void countProjectsForEachCity() {
        ParentNode* city = head;
        while (city != nullptr) {
            int projectCount = 0;
            RelationNode* project = city->projects;
            while (project != nullptr) {
                projectCount++;
                project = project->nextRelation;
            }
            cout << "City: " << city->cityName << " has " << projectCount << " projects." << endl;
            city = city->nextParent;
        }
    }

    // Function to count projects handled by a specific team
    void countProjectsHandledByTeam(const string& teamName) {
        ParentNode* city = head;
        int projectCount = 0;
        while (city != nullptr) {
            RelationNode* project = city->projects;
            while (project != nullptr) {
                ChildNode* team = project->team;
                while (team != nullptr) {
                    if (team->teamName == teamName) {
                        projectCount++;
                        break;
                    }
                    team = team->nextChild;
                }
                project = project->nextRelation;
            }
            city = city->nextParent;
        }
        cout << "Team: " << teamName << " is handling " << projectCount << " projects." << endl;
    }

    // Function to count teams without projects
    void countTeamsWithoutProjects() {
        ParentNode* city = head;
        int teamCount = 0;
        while (city != nullptr) {
            RelationNode* project = city->projects;
            while (project != nullptr) {
                ChildNode* team = project->team;
                while (team != nullptr) {
                    if (project->projectName.empty()) {
                        teamCount++;
                    }
                    team = team->nextChild;
                }
                project = project->nextRelation;
            }
            city = city->nextParent;
        }
        cout << "There are " << teamCount << " teams without projects." << endl;
    }

    // Function to edit a project
    void editProject(const string& cityName, const string& oldProjectName, const string& newProjectName) {
        ParentNode* city = findCity(cityName);
        if (city != nullptr) {
            RelationNode* project = city->projects;
            while (project != nullptr && project->projectName != oldProjectName) {
                project = project->nextRelation;
            }
            if (project != nullptr) {
                project->projectName = newProjectName;
                cout << "Proyek " << oldProjectName << " berhasil diubah menjadi " << newProjectName << " di kota " << cityName << "." << endl;
            } else {
                cout << "Proyek " << oldProjectName << " tidak ditemukan di kota " << cityName << "." << endl;
            }
        } else {
            cout << "Kota " << cityName << " tidak ditemukan." << endl;
        }
    }

    // Function to edit a team
    void editTeam(const string& cityName, const string& projectName, const string& oldTeamName, const string& newTeamName) {
        ParentNode* city = findCity(cityName);
        if (city != nullptr) {
            RelationNode* project = findProject(cityName, projectName);
            if (project != nullptr) {
                ChildNode* team = project->team;
                while (team != nullptr && team->teamName != oldTeamName) {
                    team = team->nextChild;
                }
                if (team != nullptr) {
                    team->teamName = newTeamName;
                    cout << "Tim " << oldTeamName << " berhasil diubah menjadi " << newTeamName << " di proyek " << projectName << " di kota " << cityName << "." << endl;
                } else {
                    cout << "Tim " << oldTeamName << " tidak ditemukan di proyek " << projectName << " di kota " << cityName << "." << endl;
                }
            } else {
                cout << "Proyek " << projectName << " tidak ditemukan di kota " << cityName << "." << endl;
            }
        } else {
            cout << "Kota " << cityName << " tidak ditemukan." << endl;
        }
    }

    void displayMainMenu() {
        cout << "\nMENU :\n";
        cout << "1. Insert City (Kota)\n";
        cout << "2. Insert Project (Proyek)\n";
        cout << "3. Insert Team (Tim Pelaksana)\n";
        cout << "4. Delete City (Kota)\n";
        cout << "5. Delete Project (Proyek)\n";
        cout << "6. Delete Team (Tim Pelaksana)\n";
        cout << "7. Find Element City\n";
        cout << "8. Find Element Projects\n";
        cout << "9. Find Element Teams\n";
        cout << "10. Show All Element\n";
        cout << "11. Show all data only in List City\n";
        cout << "12. Show all data only in List Projects\n";
        cout << "13. Show all data only in List Teams\n";
        cout << "14. Show child dari parent tertentu\n";
        cout << "15. Show setiap data parent beserta data child yang berelasi dengannya\n";
        cout << "16. Show child data beserta data parent yang masing-masing child miliki\n";
        cout << "17. Show parent data related to a specific child\n";
        cout << "18. Count projects for each city\n";
        cout << "19. Count projects handled by a specific team\n";
        cout << "20. Count teams without projects\n";
        cout << "21. Edit Project\n";
        cout << "22. Edit Team\n";
        cout << "0. Exit\n";
        cout << "Pilihan menu: ";
    }

    void handleMainMenu() {
        int choice;
        do {
            displayMainMenu();
            cin >> choice;

            switch (choice) {
            case 1: {
                string cityName;
                cout << "Masukkan nama kota: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, cityName);
                addCity(cityName);
                cout << "Kota " << cityName << " berhasil ditambahkan." << endl;
                break;
            }
            case 2: {
                string cityName, projectName;
                cout << "Masukkan nama kota: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, cityName);
                cout << "Masukkan nama proyek: ";
                getline(cin, projectName);
                addProject(cityName, projectName);
                cout << "Proyek " << projectName << " berhasil ditambahkan ke kota " << cityName << "." << endl;
                break;
            }
            case 3: {
                string cityName, projectName, teamName;
                cout << "Masukkan nama kota: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, cityName);
                cout << "Masukkan nama proyek: ";
                getline(cin, projectName);
                cout << "Masukkan nama tim: ";
                getline(cin, teamName);
                addTeam(cityName, projectName, teamName);
                cout << "Tim " << teamName << " berhasil ditambahkan ke proyek " << projectName << " di kota " << cityName << "." << endl;
                break;
            }
            case 4: {
                string cityName;
                cout << "Masukkan nama kota yang ingin dihapus: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, cityName);
                deleteCity(cityName);
                break;
            }
            case 5: {
                string cityName, projectName;
                cout << "Masukkan nama kota: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, cityName);
                cout << "Masukkan nama proyek yang ingin dihapus: ";
                getline(cin, projectName);
                deleteProject(cityName, projectName);
                break;
            }
            case 6: {
                string cityName, projectName, teamName;
                cout << "Masukkan nama kota: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, cityName);
                cout << "Masukkan nama proyek: ";
                getline(cin, projectName);
                cout << "Masukkan nama tim yang ingin dihapus: ";
                getline(cin, teamName);
                deleteTeam(cityName, projectName, teamName);
                break;
            }
            case 7: {
                string cityName;
                cout << "Masukkan nama kota yang ingin dicari: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, cityName);
                ParentNode* city = findCity(cityName);
                if (city != nullptr) {
                    cout << "Kota ditemukan: " << city->cityName << endl;
                } else {
                    cout << "Kota tidak ditemukan." << endl;
                }
                break;
            }
            case 8: {
                string cityName, projectName;
                cout << "Masukkan nama kota: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, cityName);
                cout << "Masukkan nama proyek yang ingin dicari: ";
                getline(cin, projectName);
                RelationNode* project = findProject(cityName, projectName);
                if (project != nullptr) {
                    cout << "Proyek ditemukan: " << project->projectName << " di Kota: " << cityName << endl;
                } else {
                    cout << "Proyek tidak ditemukan." << endl;
                }
                break;
            }
            case 9: {
                string cityName, projectName, teamName;
                cout << "Masukkan nama kota: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, cityName);
                cout << "Masukkan nama proyek: ";
                getline(cin, projectName);
                cout << "Masukkan nama tim yang ingin dicari: ";
                getline(cin, teamName);
                ChildNode* team = findTeam(cityName, projectName, teamName);
                if (team != nullptr) {
                    cout << "Tim ditemukan: " << team->teamName << " di Proyek: " << projectName << " di Kota: " << cityName << endl;
                } else {
                    cout << "Tim tidak ditemukan." << endl;
                }
                break;
            }
            case 10:
                showAllElements();
                break;
            case 11:
                showAllDataInListCity();
                break;
            case 12:
                showAllDataInListProjects();
                break;
            case 13:
                showAllDataInListTeams();
                break;
            case 14: {
                string cityName;
                cout << "Masukkan nama kota: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, cityName);
                showChildDataFromParent(cityName);
                break;
            }
            case 15:
                showParentWithChildData();
                break;
            case 16:
                showChildWithParentData();
                break;
            case 17: {
                string teamName;
                cout << "Masukkan nama tim yang ingin dicari: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, teamName);
                showParentWithSpecificChild(teamName);
                break;
            }
            case 18:
                countProjectsForEachCity();
                break;
            case 19: {
                string teamName;
                cout << "Masukkan nama tim: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, teamName);
                countProjectsHandledByTeam(teamName);
                break;
            }
            case 20:
                countTeamsWithoutProjects();
                break;
            case 21: {
                string cityName, oldProjectName, newProjectName;
                cout << "Masukkan nama kota: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, cityName);
                cout << "Masukkan nama proyek yang ingin diubah: ";
                getline(cin, oldProjectName);
                cout << "Masukkan nama proyek baru: ";
                getline(cin, newProjectName);
                editProject(cityName, oldProjectName, newProjectName);
                break;
            }
            case 22: {
                string cityName, projectName, oldTeamName, newTeamName;
                cout << "Masukkan nama kota: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, cityName);
                cout << "Masukkan nama proyek: ";
                getline(cin, projectName);
                cout << "Masukkan nama tim yang ingin diubah: ";
                getline(cin, oldTeamName);
                cout << "Masukkan nama tim baru: ";
                getline(cin, newTeamName);
                editTeam(cityName, projectName, oldTeamName, newTeamName);
                break;
            }
            case 0:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                choice = -1; // Ensure it stays in the loop for invalid numeric inputs
            }
        } while (choice != 0);
    }
};

int main(){
    MultiLinkedList mll;
    mll.handleMainMenu ();
    return 0;
}
